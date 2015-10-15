/* ###################################################################
**     Filename    : Events.c
**     Project     : K22F-NRF24-Test
**     Processor   : MK22FN512VLH12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-09-18, 09:08, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*! dspiCom1 IRQ handler */
void SPI0_IRQHandler(void)
{
#if DSPICOM1_DMA_MODE
  DSPI_DRV_EdmaIRQHandler(FSL_DSPICOM1);
#else
  DSPI_DRV_IRQHandler(FSL_DSPICOM1);
#endif
  /* Write your code here ... */
}

void Delay_ms(uint32_t mSecDelay)
{
	DelayCounter = 0;
	while(mSecDelay > DelayCounter)
	{

	}
}

void PIT0_IRQHandler(void)
{
  /* Clear interrupt flag.*/
	Counter++;
	DelayCounter++;
	if(1000 < Counter)
	{
		//GPIO_DRV_TogglePinOutput(LEDRGB_BLUE);
		Counter = 0;
	}
	else
	{

	}

  PIT_HAL_ClearIntFlag(g_pitBase[FSL_PITTIMER1], FSL_PITTIMER1_CHANNEL);
  /* Write your code here ... */
}

void FTM1_IRQHandler(void)
{
  FTM_DRV_IRQHandler(FSL_FLEXTIMER1);
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
