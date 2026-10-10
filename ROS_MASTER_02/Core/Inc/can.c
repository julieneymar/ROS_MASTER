/*
 * can.c
 *
 *  Created on: Apr 16, 2026
 *      Author: julie
 */


#include "can.h"


CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
CAN_FilterTypeDef sFilterConfig;


void Can_Init(void)
{
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    sFilterConfig.SlaveStartFilterBank = 27;
    sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;

    // Setting the CAN Filter
    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    // Start the CAN peripheral
    if (HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
    }

    // Activate CAN RX notification
    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
}


void Can_Test_Send(){
	uint8_t TxData[8];                         // 8 octets de données maximum (DLC=8)
	uint32_t TxMailbox = 0;                    // Stocke quelle boîte aux lettres est utilisée
	TxHeader.StdId = 0x000F;                   // Identifiant standard : 0x0F (15 en décimal)
	TxHeader.ExtId = 0x00;                     // Pas d'ID étendu
	TxHeader.RTR = CAN_RTR_DATA;               // Trame de données (pas de demande distante)
	TxHeader.IDE = CAN_ID_STD;                 // Utilise un ID standard (11 bits)
	TxHeader.DLC = 8;                          // 8 octets de données
	TxHeader.TransmitGlobalTime = DISABLE;     // Désactive l'estampille temporelle
	for (int i = 0; i < 8; i++)
		{
			TxData[i] = 1 << i;
		}
		printf("CAN Send:%02X %02X %02X %02X %02X %02X %02X %02X \n",
				TxData[0], TxData[1], TxData[2], TxData[3],
				TxData[4], TxData[5], TxData[6], TxData[7]);
	    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK)
	    {
	        Error_Handler();
	    }
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	if (hcan->Instance == CAN1)
		{
			uint8_t RxData[8];  // buffer pour les donnes reçu
			if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)  // _RX_FIFO0 : lit depuis le FIFO 0	&RxHeader : récupère l'en-tête (ID, DLC, etc.) xData : récupère les 8 octets de données
			{
				Error_Handler();
			}
			else
			{
				printf("CAN Receive:%02X %02X %02X %02X %02X %02X %02X %02X \n",
						RxData[0], RxData[1], RxData[2], RxData[3],
						RxData[4], RxData[5], RxData[6], RxData[7]);
			}
		}
}
