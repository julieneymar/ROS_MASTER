/*
 * uart_Servo.c
 *
 *  Created on: Oct 8, 2026
 *      Author: julie
 */


#include "uart_Servo.h"


uint16_t sync_servo[] = {MEDIAN_VALUE, MEDIAN_VALUE, MEDIAN_VALUE, MEDIAN_VALUE, MID_VAL_ID5, MID_VAL_ID6};

uint8_t New_Frame = 0;   // flag pour indiquer si trame dispo ou pas
uint8_t Rx_Data[RX_MAX_BUF] = {0};   // stock le trame reçu
uint8_t Rx_index = 0;     // indique l'index du stock du trame
uint8_t Rx_Flag = 0;



// Control Servo, id=[1-254], value=[MIN_PULSE, MAX_PULSE], time=[0, 2000] ; servo position durée
void UartServo_Ctrl(uint8_t id, uint16_t value, uint16_t time)
{
    uint8_t head1 = 0xff;
    uint8_t head2 = 0xff;
    uint8_t s_id = id & 0xff;
    uint8_t len = 0x07;
    uint8_t cmd = 0x03;
    uint8_t addr = 0x2a;

    if (value > MAX_PULSE)
        value = MEDIAN_VALUE;
    else if (value < MIN_PULSE)
        value = MEDIAN_VALUE;

    uint8_t pos_H = (value >> 8) & 0xff;
    uint8_t pos_L = value & 0xff;

    uint8_t time_H = (time >> 8) & 0xff;
    uint8_t time_L = time & 0xff;

    uint8_t checknum = (~(s_id + len + cmd + addr +
                          pos_H + pos_L + time_H + time_L)) & 0xff;
    uint8_t data[] = {head1, head2, s_id, len, cmd, addr,
                      pos_H, pos_L, time_H, time_L, checknum};

    USART3_Send_ArrayU8(data, sizeof(data));
}

// Set the cache value for synchronous write
void UartServo_Set_Snyc_Buffer(uint16_t s1, uint16_t s2, uint16_t s3, uint16_t s4, uint16_t s5, uint16_t s6)
{
    sync_servo[0] = s1;
    sync_servo[1] = s2;
    sync_servo[2] = s3;
    sync_servo[3] = s4;
    sync_servo[4] = s5;
    sync_servo[5] = s6;

    for (int i = 0; i < 6; i++)
    {
        if (sync_servo[i] > MAX_PULSE)
        {
            sync_servo[i] = MEDIAN_VALUE;
        }
        else if (sync_servo[i] < MIN_PULSE)
        {
            sync_servo[i] = MEDIAN_VALUE;
        }
    }
}

// Write different parameters to multiple steering engines at the same time
void UartServo_Sync_Write(uint16_t sync_time)
{
    uint8_t head1 = 0xff;
    uint8_t head2 = 0xff;
    uint8_t s_id = 0xfe;
    uint8_t len = 0x22; /*len= sizeof(data)-4*/
    uint8_t cmd = 0x83;
    uint8_t addr = 0x2a;
    uint8_t data_len = 0x04;

    uint8_t ctrl_id[MAX_SERVO_NUM] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

    uint8_t pos_n_H[MAX_SERVO_NUM] = {0};
    uint8_t pos_n_L[MAX_SERVO_NUM] = {0};

    uint8_t pos_sum = 0;
    uint8_t time_H = (sync_time >> 8) & 0xff;
    uint8_t time_L = sync_time & 0xff;

    for (uint8_t i = 0; i < MAX_SERVO_NUM; i++)
    {
        pos_n_H[i] = (sync_servo[i] >> 8) & 0xff;
        pos_n_L[i] = sync_servo[i] & 0xff;
        pos_sum = (pos_sum + ctrl_id[i] + pos_n_H[i] + pos_n_L[i] + time_H + time_L) & 0xff;
    }

    uint8_t checknum = (~(s_id + len + cmd + addr + data_len + pos_sum)) & 0xff;

    uint8_t data[] = {head1, head2, s_id, len, cmd, addr, data_len,
                      ctrl_id[0], pos_n_H[0], pos_n_L[0], time_H, time_L,
                      ctrl_id[1], pos_n_H[1], pos_n_L[1], time_H, time_L,
                      ctrl_id[2], pos_n_H[2], pos_n_L[2], time_H, time_L,
                      ctrl_id[3], pos_n_H[3], pos_n_L[3], time_H, time_L,
                      ctrl_id[4], pos_n_H[4], pos_n_L[4], time_H, time_L,
                      ctrl_id[5], pos_n_H[5], pos_n_L[5], time_H, time_L,
                      checknum};
    USART3_Send_ArrayU8(data, sizeof(data));
}

// Active le couple avec 1 ou desactive avec 0
void UartServo_Set_Torque(uint8_t enable)
{
    uint8_t on_off = 0x00;
    if (enable)
    {
        on_off = 0x01;
    }
    uint8_t head1 = 0xff;
    uint8_t head2 = 0xff;
    uint8_t s_id = 0xfe; // broadcast
    uint8_t len = 0x04;
    uint8_t cmd = 0x03;
    uint8_t addr = 0x28;

    uint8_t checknum = (~(s_id + len + cmd + addr + on_off)) & 0xff;
    uint8_t data[] = {head1, head2, s_id, len, cmd,
                      addr, on_off, checknum};
    USART3_Send_ArrayU8(data, sizeof(data));
}

// Write target ID(1~250)
void UartServo_Set_ID(uint8_t id)
{
    if ((id >= 1) && (id <= 250))
    {
        uint8_t head1 = 0xff;
        uint8_t head2 = 0xff;
        uint8_t s_id = 0xfe;
        uint8_t len = 0x04;
        uint8_t cmd = 0x03;
        uint8_t addr = 0x05;
        uint8_t set_id = id;

        uint8_t checknum = (~(s_id + len + cmd + addr + set_id)) & 0xff;
        uint8_t data[] = {head1, head2, s_id, len, cmd,
                          addr, set_id, checknum};
        USART3_Send_ArrayU8(data, sizeof(data));
    }
}



//demande la position actuelle du servo
void UartServo_Get_Angle(uint8_t id)
{
    uint8_t head1 = 0xff;
    uint8_t head2 = 0xff;
    uint8_t s_id = id & 0xff;
    uint8_t len = 0x04;
    uint8_t cmd = 0x02;
    uint8_t param_H = 0x38;
    uint8_t param_L = 0x02;

    uint8_t checknum = (~(s_id + len + cmd + param_H + param_L)) & 0xff;
    uint8_t data[] = {head1, head2, s_id, len, cmd, param_H, param_L, checknum};
    USART3_Send_ArrayU8(data, sizeof(data));
}

// Fonction de reception du trame du servo, un seul octet à la fois
void UartServo_Revice(uint8_t Rx_Temp)
{
    switch (Rx_Flag)
    {
    case 0:   							// attend ff
        if (Rx_Temp == 0xff)
        {
            Rx_Data[0] = 0xff;
            Rx_Flag = 1;
        }
        break;

    case 1:
        if (Rx_Temp == 0xf5)
        {
            Rx_Data[1] = 0xf5;
            Rx_Flag = 2;
            Rx_index = 2;
        }
        else
        {
            Rx_Flag = 0;
            Rx_Data[0] = 0x0;
        }
        break;

    case 2:
        Rx_Data[Rx_index] = Rx_Temp;
        Rx_index++;
        if (Rx_index >= RX_MAX_BUF)
        {
            Rx_Flag = 0;
            New_Frame = 1;
        }
        break;
    default:
        break;
    }
}

// La vérification du checksum : Parses serial port data, returns 1 on success, 0 otherwise
uint8_t UartServo_Rx_Parse(void)
{
    uint8_t result = 0;
    if (New_Frame)
    {
        result = 1;
        New_Frame = 0;
        uint8_t checknum = (~(Rx_Data[2] + Rx_Data[3] + Rx_Data[4] + Rx_Data[5] + Rx_Data[6])) & 0xff;
        if (checknum == Rx_Data[7])
        {
            uint8_t s_id = Rx_Data[2];
            uint16_t read_value = Rx_Data[5] << 8 | Rx_Data[6];

            // Print the servo position data
            printf("read arm value:%d, %d\n", s_id, read_value);
        }
    }
    return result;
}


uint8_t servo_id = 0x01;

void Servo_Test (void){
	if (Key1_State(KEY_MODE_ONE_TIME))
		{
			BUZZER_ON;
			HAL_Delay(10);
			BUZZER_OFF;
			static int press = 0;
			press++;
			printf("press:%d\n", press);

			UartServo_Get_Angle(servo_id);
			HAL_Delay(12);
			if (press%2)
			{
				UartServo_Ctrl(servo_id, 1000, 500);
			}
			else
			{
				UartServo_Ctrl(servo_id, 3000, 500);
			}
		}
	UartServo_Rx_Parse();
	HAL_Delay(10);

}
