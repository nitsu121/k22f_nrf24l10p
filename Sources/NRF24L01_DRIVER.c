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
	  Delay_ms(1);
	  SendArray[0] = TempStatus & 0xF0;
	  //Read_Status();
	  //Write_Register(unsigned char RegisterNumber, unsigned char * SendArray, unsigned char * RecievedArray, unsigned char NumOfBytesToRead)
	  Write_Register(0x07, SendArray, ReadArray, 1);
}

void Init_NRF24L(void)
{
	unsigned char TempValue = 0;

	  CE_OFF;
	  Delay_ms(100);
	  //Write_Register(unsigned char RegisterNumber, unsigned char * SendArray, unsigned char * RecievedArray, unsigned char NumOfBytesToRead)
	  unsigned char SendArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	  unsigned char ReadArray[10];


	  SendArray[0] = 0x26; //TX not-power-up 2_byte_CRC EnableCRC
	  //
	  //unsigned char Write_Reg_Varified(unsigned char RegisterNumber, unsigned char * SendArray, unsigned char NumOfBytesToRead)
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
	  //Write_Reg_Varified(0x0A, SendArray, 5);

	  SendArray[0] = 0x11;
	  SendArray[1] = 0x22;
	  SendArray[2] = 0x33;
	  SendArray[3] = 0x44;
	  SendArray[4] = 0x55;
	  Write_Register(0x10, SendArray, ReadArray, 5);
	  //Write_Reg_Varified(0x10, SendArray, 5);

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

#if 0
	  Write_Reg_Varified(0, SendArray, 1);
	  //

	  SendArray[0] = 0x00;
	  Write_Reg_Varified(1, SendArray, 1);

	  SendArray[0] = 0x01; //disable autoacknak
	  Write_Reg_Varified(2, SendArray, 1);

	  SendArray[0] = 0x03;
	  Write_Reg_Varified(3, SendArray, 1);

	  SendArray[0] = 0x00;
	  Write_Reg_Varified(4, SendArray, 1);

	  SendArray[0] = 0x02;
	  Write_Reg_Varified(5, SendArray, 1);

	  SendArray[0] = 0x07;
	  Write_Reg_Varified(6, SendArray, 1);

	  SendArray[0] = 0xE7;
	  SendArray[1] = 0xE7;
	  SendArray[2] = 0xE7;
	  SendArray[3] = 0xE7;
	  SendArray[4] = 0xE7;
	  Write_Reg_Varified(0x10, SendArray, 5);
#endif

}


#if 0
void Init_NRF24L(void)
{
	unsigned char TempValue = 0;

	  CE_OFF;
	  Delay_ms(100);
	  //Write_Register(unsigned char RegisterNumber, unsigned char * SendArray, unsigned char * RecievedArray, unsigned char NumOfBytesToRead)
	  unsigned char SendArray[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	  unsigned char ReadArray[10];


	  SendArray[0] = 0x0C; //TX not-power-up 2_byte_CRC EnableCRC
	  //
	  //unsigned char Write_Reg_Varified(unsigned char RegisterNumber, unsigned char * SendArray, unsigned char NumOfBytesToRead)
	  Write_Reg_Varified(0, SendArray, 1);
	  //

	  SendArray[0] = 0x00;
	  Write_Reg_Varified(1, SendArray, 1);

	  SendArray[0] = 0x01; //disable autoacknak
	  Write_Reg_Varified(2, SendArray, 1);

	  SendArray[0] = 0x03;
	  Write_Reg_Varified(3, SendArray, 1);

	  SendArray[0] = 0x00;
	  Write_Reg_Varified(4, SendArray, 1);

	  SendArray[0] = 0x02;
	  Write_Reg_Varified(5, SendArray, 1);

	  SendArray[0] = 0x07;
	  Write_Reg_Varified(6, SendArray, 1);

	  SendArray[0] = 0xE7;
	  SendArray[1] = 0xE7;
	  SendArray[2] = 0xE7;
	  SendArray[3] = 0xE7;
	  SendArray[4] = 0xE7;
	  Write_Reg_Varified(0x10, SendArray, 5);


}
#endif


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

	//DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, &Send[0], Read, 5, 10000);
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
	//DSPI_DRV_MasterInit(FSL_DSPICOM1, &dspiCom1_MasterState, &dspiCom1_MasterConfig0);
	//DSPI_DRV_MasterTransferBlocking(FSL_DSPICOM1, NULL, &Send[0], Read, 5, 10000);
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

unsigned char Send_Last_Payload(unsigned char NumberOfTimesToSend)
{
	unsigned char ReturnFlag = 0;

	return (ReturnFlag);
}

unsigned char Read_Status()
{
	unsigned char ReturnFlag = 0;
	unsigned char ReadArray[2] = {0, 0};
	//unsigned char Read_Register(unsigned char RegisterNumber, unsigned char * RecieveArray, unsigned char NumOfBytesToRead)
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
