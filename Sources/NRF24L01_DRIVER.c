/*
 * NRF24L01_DRIVER.c
 *
 *  Created on: Sep 18, 2015
 *      Author: Justin.Flor
 */


#include "dspiCom1.h"
#include "NRF24L01_DRIVER.h"


void Clear_NRF_Int_Flags(void)
{
	  unsigned char SendArray[2] = {0, 0};
	  unsigned char ReadArray[2];
	  unsigned char TempStatus = 0;
	  TempStatus = Read_Status();
	  //Delay_ms(1);
	  SendArray[0] = TempStatus & 0xF1;
	  Write_Register(0x07, SendArray, ReadArray, 1);
}

void Set_NRF24L_Rx_Mode()
{
	CE_OFF;
	Delay_ms(100);
	unsigned char SendArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	Flush_Tx();
	Flush_Rx();

	SendArray[0] = 0x0F;
	Write_Reg_Varified(0x00, SendArray, 1);

	CE_ON;
}

void Set_NRF24L_Tx_Mode()
{
	CE_OFF;
	Delay_ms(100);
	unsigned char SendArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	Flush_Tx();
	Flush_Rx();

	SendArray[0] = 0x0E;
	Write_Reg_Varified(0x00, SendArray, 1);
}


void Init_NRF24L(void)
{
	  CE_OFF;
	  Delay_ms(100);
	  unsigned char SendArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	  unsigned char ReadArray[10];


	  SendArray[0] = 0x26; //TX not-power-up 2_byte_CRC EnableCRC
	  Write_Reg_Varified(6, SendArray, 1);

	  SendArray[0] = 0x05;
	  Write_Reg_Varified(0x11, SendArray, 1);

	  SendArray[0] = 0x00;
	  Write_Reg_Varified(0x05, SendArray, 1);

	  SendArray[0] = 0x11;
	  SendArray[1] = 0x22;
	  SendArray[2] = 0x33;
	  SendArray[3] = 0x44;
	  SendArray[4] = 0x55;
	  Write_Register(0x0A, SendArray, ReadArray, 5);

	  SendArray[0] = 0x11;
	  SendArray[1] = 0x22;
	  SendArray[2] = 0x33;
	  SendArray[3] = 0x44;
	  SendArray[4] = 0x55;
	  Write_Register(0x10, SendArray, ReadArray, 5);

	  SendArray[0] = 0x01;
	  Write_Reg_Varified(0x02, SendArray, 1);

	  Clear_NRF_Int_Flags();

	  SendArray[0] = 0x01;
	  Write_Reg_Varified(0x01, SendArray, 1);

	  SendArray[0] = 0x2F;
	  Write_Reg_Varified(0x04, SendArray, 1);

	  Flush_Tx();
	  Flush_Rx();

	  SendArray[0] = 0x0E;
	  Write_Reg_Varified(0x00, SendArray, 1);
}

unsigned char Write_Reg_Varified(unsigned char RegisterNumber, unsigned char * SendArray, unsigned char NumOfBytesToRead)
{
	unsigned char ReturnFlag = 0;
	unsigned char TempValue = 0;
	unsigned char ReadArray[10];

	while(!(SendArray[0] == TempValue))
	{
	  Write_Register(RegisterNumber, SendArray, ReadArray, 1);
	  Delay_ms(10);
	  Read_Register(RegisterNumber, &TempValue, 1);
	  Delay_ms(10);
	}

	return(ReturnFlag);
}

unsigned char Read_Register(unsigned char RegisterNumber, unsigned char * RecieveArray, unsigned char NumOfBytesToRead)
{
	unsigned char ReturnFlag = 0;
	unsigned char TempSendArray[50];
	unsigned char TempReadArray[50];
	unsigned char Counter = 0;
	TempSendArray[0] = RegisterNumber | R_REGISTER;

	DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, TempSendArray, TempReadArray, NumOfBytesToRead + 1, 10000);
	ReturnFlag = TempReadArray[0];

	while(NumOfBytesToRead > Counter)
	{
		RecieveArray[Counter] = TempReadArray[Counter + 1];
		Counter++;
	}

	return (ReturnFlag);
}

unsigned char Write_Register(unsigned char RegisterNumber, unsigned char * SendArray, unsigned char * RecievedArray, unsigned char NumOfBytesToRead)
{
	unsigned char ReturnFlag = 0;
	unsigned char TempSendArray[50];
	unsigned char TempReadArray[50];
	unsigned char Counter = 0;
	TempSendArray[0] = RegisterNumber | W_REGISTER;

	while(NumOfBytesToRead > Counter)
	{
		TempSendArray[Counter + 1] = SendArray[Counter];
		Counter++;
	}

	DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, TempSendArray, TempReadArray, NumOfBytesToRead + 1, 10000);
	ReturnFlag = TempReadArray[0];

	Counter = 0;

	while(NumOfBytesToRead > Counter)
	{
		RecievedArray[Counter] = TempReadArray[Counter + 1];
		Counter++;
	}

	return (ReturnFlag);
}


unsigned char ReadPayload(unsigned char * ReadArray, unsigned char NumberOfBytesToRead)
{
	unsigned char ReturnFlag = 0;
	unsigned char TempSendArray[100];
	unsigned char TempReadArray[100];
	unsigned char Count = 0;
	TempSendArray[0] = R_RX_PAYLOAD;

	DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, TempSendArray, TempReadArray, NumberOfBytesToRead + 1, 10000);

	while(NumberOfBytesToRead > Count)
	{

		ReadArray[Count] = TempReadArray[Count + 1];
		Count++;
	}

	Flush_Rx();

	return (ReturnFlag);
}


unsigned char Send_Last_Payload(unsigned char NumberOfTimesToSend)
{
	unsigned char ReturnFlag = 0;
	return (ReturnFlag);
}

unsigned char Read_Status()
{
	unsigned char ReturnFlag = 0;
	unsigned char ReadArray[2] = {0, 0};
	Read_Register(0x07, ReadArray, 1);
	ReturnFlag = ReadArray[0];
	return (ReturnFlag);
}

unsigned char SendNewPayload(unsigned char * PayloadArrayToSend, unsigned char NumberOfBytesToSend)
{
	unsigned char ReturnFlag = 0;
	unsigned char TempSendArray[50];
	unsigned char TempReadArray[50];
	unsigned char SendArray[10];
	unsigned char ReadArray[10];
	unsigned char Counter = 0;

	SendArray[0] = 0x0E; //TX not-power-up 2_byte_CRC EnableCRC
	Write_Register(0, SendArray, ReadArray, 1); // power up rf mod.
	Flush_Tx();
	Flush_Rx();
	TempSendArray[0] = W_TX_PAYLOAD;

	while(NumberOfBytesToSend > Counter)
	{
		TempSendArray[Counter + 1] = PayloadArrayToSend[Counter];
		Counter++;
	}

	DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, TempSendArray, TempReadArray, NumberOfBytesToSend + 1, 10000);
	ReturnFlag = TempReadArray[0];

	CE_ON;
	Delay_ms(1);
	CE_OFF;

	return (ReturnFlag);
}

unsigned char Flush_Tx()
{
	unsigned char ReturnFlag = 0;
	unsigned char ReadArray[2] = {0, 0};
	unsigned char SendArray[2] = {FLUSH_TX, 0};
	DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, SendArray, ReadArray, 1, 10000);
	ReturnFlag = ReadArray[0];
	return (ReturnFlag);
}

unsigned char Flush_Rx()
{
	unsigned char ReturnFlag = 0;
	unsigned char ReadArray[2] = {0, 0};
	unsigned char SendArray[2] = {FLUSH_RX, 0};
	DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, SendArray, ReadArray, 1, 10000);
	ReturnFlag = ReadArray[0];
	return (ReturnFlag);
}
