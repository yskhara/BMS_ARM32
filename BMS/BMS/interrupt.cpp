#include "interrupt.h"

extern __IO uint32_t TimingDelay;
extern __IO uint16_t ADC1ConvertedValue;

extern "C"
{
	/******************************************************************************/
	/*            Cortex-M4 Processor Exceptions Handlers                         */
	/******************************************************************************/

	/**
		* @brief  This function handles NMI exception.
		* @param  None
		* @retval None
		*/
	void NMI_Handler(void)
	{
	}

	/**
	  * @brief  This function handles Hard Fault exception.
	  * @param  None
	  * @retval None
	  */
	void HardFault_Handler(void)
	{
		/* Go to infinite loop when Hard Fault exception occurs */
		while (1)
		{
		}
	}

	/**
	  * @brief  This function handles SVCall exception.
	  * @param  None
	  * @retval None
	  */
	void SVC_Handler(void)
	{
	}

	/**
	  * @brief  This function handles PendSVC exception.
	  * @param  None
	  * @retval None
	  */
	void PendSV_Handler(void)
	{
	}

	/**
	  * @brief  This function handles SysTick Handler.
	  * @param  None
	  * @retval None
	  */
	void SysTick_Handler(void)
	{
	}

	void EXTI15_10_IRQHandler(void)
	{
		if (EXTI_GetFlagStatus(EXTI_Line13) == SET)
		{
			/* Clear interrupt flag */
			EXTI_ClearFlag(EXTI_Line13);
		}
	}

	void ADC1_2_IRQHandler(void)
	{
		if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == SET)
		{
			ADC1ConvertedValue = ADC_GetConversionValue(ADC1);
		}
	}

	/* Handle COMP1 interrupt */
	void COMP1_2_3_IRQHandler(void)
	{
		if (EXTI_GetFlagStatus(EXTI_Line21) == SET)
		{
			//COMP1Interrupt();
			/* Clear interrupt flag */
			EXTI_ClearFlag(EXTI_Line21);
		}
	}

	/* Handle TIM4 interrupt */
	void TIM4_IRQHandler(void)
	{
		if (TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) == SET)
		{
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);
		}
	}
	
	void USART2_IRQHandler(void)
	{
		if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET)
		{
			int16_t d = USART_ReceiveData(USART2);
			//Motor::ChangeRotationSpeed(d);
			USART_SendData(USART2, d);
		}
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
