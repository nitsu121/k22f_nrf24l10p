/* ###################################################################
**     Filename    : main.c
**     Project     : K22F-NRF24-Test
**     Processor   : MK22FN512VLH12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-18, 09:08, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */
//

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "gpio1.h"
#include "dspiCom1.h"
#include "pitTimer1.h"
#include "uartCom1.h"
#include "dmaController1.h"
#include "NRF24L01_DRIVER.h"

#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  unsigned char SendArray[5] = {'J', 'U', 'S', 'T', 'I'};
  unsigned char ReadArray[100];

  Delay_ms(1000);
  GPIO_DRV_ClearPinOutput(LEDRGB_BLUE);
  Delay_ms(1000);
  GPIO_DRV_SetPinOutput(LEDRGB_BLUE);

  Init_NRF24L();
  UART_DRV_SendDataBlocking(FSL_UARTCOM1,SendArray, 5, 1000);
  // UART_DRV_Init(FSL_UARTCOM1,&uartCom1_State,&uartCom1_InitConfig0);
  GPIO_DRV_ClearPinOutput(LEDRGB_BLUE);
  Delay_ms(1000);
  GPIO_DRV_SetPinOutput(LEDRGB_BLUE);


  //GPIO_DRV_ClearPinOutput(LEDRGB_RED);
  Delay_ms(1000);
  //GPIO_DRV_SetPinOutput(LEDRGB_RED);
  //LEDRGB_RED

  unsigned char SendNotGet = 0;


  if(1 == SendNotGet)
  {
	  Set_NRF24L_Tx_Mode();
  }
  else
  {
	  Set_NRF24L_Rx_Mode();
  }


  while(1)
  {
	  Delay_ms(1000);
	  //GPIO_DRV_SetPinOutput(LEDRGB_BLUE);

	  //GPIO_DRV_ReadPinInput(uint32_t pinName);
	  //PUSH_BUTTON1

	  if(1 == SendNotGet)  // send
	  {
		  Clear_NRF_Int_Flags();
		  SendNewPayload(SendArray, 5);
		  Clear_NRF_Int_Flags();
		  GPIO_DRV_ClearPinOutput(LEDRGB_BLUE);
	  }
	  else  // read.
	  {
		  if(0x0E == Read_Status())
		  {
			  GPIO_DRV_SetPinOutput(LEDRGB_BLUE);
		  }
		  else
		  {
			  GPIO_DRV_ClearPinOutput(LEDRGB_BLUE);
			  ReadPayload(ReadArray, 5);
			  UART_DRV_SendDataBlocking(FSL_UARTCOM1,ReadArray, 5, 1000);
			  Clear_NRF_Int_Flags();
		  }
	  }

	  if(0 == GPIO_DRV_ReadPinInput(PUSH_BUTTON1))
	  {
		  GPIO_DRV_ClearPinOutput(LEDRGB_BLUE);
		  Delay_ms(300);
		  GPIO_DRV_SetPinOutput(LEDRGB_BLUE);
		  SendNotGet = 1;
		  Set_NRF24L_Tx_Mode();
		  while(0 == GPIO_DRV_ReadPinInput(PUSH_BUTTON1))
		  {

		  }
	  }
	  else
	  {

	  }

	  if(0 == GPIO_DRV_ReadPinInput(PUSH_BUTTON2))
	  {

		  GPIO_DRV_ClearPinOutput(LEDRGB_BLUE);
		  Delay_ms(300);
		  GPIO_DRV_SetPinOutput(LEDRGB_BLUE);
		  Delay_ms(300);
		  GPIO_DRV_ClearPinOutput(LEDRGB_BLUE);
		  Delay_ms(300);
		  GPIO_DRV_SetPinOutput(LEDRGB_BLUE);
		  SendNotGet = 0;
		  Set_NRF24L_Rx_Mode();
		  while(0 == GPIO_DRV_ReadPinInput(PUSH_BUTTON2))
		  {

		  }
	  }
	  else
	  {

	  }

  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
