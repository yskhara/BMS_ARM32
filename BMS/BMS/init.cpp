#include "init.h"

void GPIO_Pin_Init(GPIO_TypeDef* GPIOx, 
	uint32_t GPIO_Pin, 
	GPIOMode_TypeDef GPIO_Mode,
	GPIOSpeed_TypeDef GPIO_Speed, 
	GPIOOType_TypeDef GPIO_OType, 
	GPIOPuPd_TypeDef GPIO_PuPd)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//GPIO_StructInit(&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed;
	GPIO_InitStruct.GPIO_OType = GPIO_OType;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd;

	GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void PeripheralInit::InitClock(void)
{
	/* TIMx clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);


}

void PeripheralInit::InitGPIO(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	

	//GPIO_InitTypeDef GPIO_InitStructure;
	//GPIO_StructInit(&GPIO_InitStructure);

	/* Configure GPIOA */
	GPIO_Pin_Init(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5, GPIO_Mode_AN, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	//GPIO_Pin_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	GPIO_Pin_Init(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_DOWN);

	/* Configure GPIOB */
	GPIO_Pin_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_OUT, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_DOWN);
	GPIO_Pin_Init(GPIOB, GPIO_Pin_8, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	
	/* Configure GPIOC */
	GPIO_Pin_Init(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_DOWN);
	GPIO_Pin_Init(GPIOC, GPIO_Pin_13, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	//GPIO_Pin_Init(GPIOC, GPIO_Pin_13, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_UP);

	/* TIM1_CH1 output port is on PC0(default)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);*/

	// maps alternate functions.
	//GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_1); // TIM2_CH1/TIM2_ETR is on af1
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_8); //COMP1OUT is on af8

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_6); //TIM1CH1 is on af6
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_6); //TIM1CH2 is on af6
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_6); //TIM1CH1N is on af6
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_6); //TIM1CH2N is on af6

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF_2); //TIM1CH1 is on af2
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_2); //TIM1CH2 is on af2
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_2); //TIM1CH3 is on af2
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_2); //TIM1CH4 is on af2

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource13, GPIO_AF_4);
}

void PeripheralInit::InitEXTI()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_StructInit(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line21;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);


	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);
}

void PeripheralInit::InitNVIC()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = COMP1_2_3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

// 
// TIM1 used for main MOSFET switching
// 
void PeripheralInit::InitTIM1()
{
	/* TIMx clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);

	int pwmfreq = 25000;

	// Time base configuration     72MHz / 36 / 2 / 1000 = 1kHz
	TIM_TimeBaseStructure.TIM_Period = PwmStepCount - 1; // count 0-999 => 1000
	TIM_TimeBaseStructure.TIM_Prescaler = 2; // presc: x36
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned3;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	// PWM1 Mode configuration: TIM1_CH1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}

void PeripheralInit::InitADC1()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;

	RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div12);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);

	/*
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	*/


	ADC_CommonStructInit(&ADC_CommonInitStructure);
	ADC_StructInit(&ADC_InitStructure);

	/* Calibration procedure */
	ADC_VoltageRegulatorCmd(ADC1, ENABLE);

	ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
	ADC_StartCalibration(ADC1);

	while (ADC_GetCalibrationStatus(ADC1) != RESET);
	//calibration_value = ADC_GetCalibrationValue(ADC1);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;

	ADC_CommonInit(ADC1, &ADC_CommonInitStructure);

	ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;
	ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;
	ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;
	ADC_InitStructure.ADC_NbrOfRegChannel = 1;

	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC2 regular channel14 configuration to sample time = 55.5 cycles */
	//ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);

	/* Enable ADC2  */
	//ADC_Cmd(ADC2, ENABLE);

	/* Enable ADC2 reset calibaration register */
	//ADC_ResetCalibration(ADC2);

	/* Check the end of ADC1 reset calibration register */
	//while (ADC_GetResetCalibrationStatus(ADC2));

	/* Start ADC2 calibaration */
	//ADC_StartCalibration(ADC2);
	/* Check the end of ADC2 calibration */
	//while (ADC_GetCalibrationStatus(ADC2));

	NVIC_EnableIRQ(IRQn::ADC1_2_IRQn);
}

void PeripheralInit::InitCOMP1(const Comp1InvInp cii, const CompOutPol pol, const CompMode mode)
{
	// Note: comparators require no clock input
	COMP_InitTypeDef COMP_InitStruct;
	//COMP_StructInit(&COMP_InitStruct);

	COMP_InitStruct.COMP_InvertingInput		= static_cast<uint32_t>(cii);
	COMP_InitStruct.COMP_OutputPol			= static_cast<uint32_t>(pol);
	COMP_InitStruct.COMP_Mode				= static_cast<uint32_t>(mode);
	COMP_InitStruct.COMP_NonInvertingInput	= COMP_NonInvertingInput_IO1;
	COMP_InitStruct.COMP_Output				= COMP_Output_None;
	COMP_InitStruct.COMP_BlankingSrce		= COMP_BlankingSrce_None;
	COMP_InitStruct.COMP_Hysteresis			= COMP_Hysteresis_No;

	COMP_Init(COMP_Selection_COMP1, &COMP_InitStruct);
}

void PeripheralInit::EnableCOMP1()
{
	COMP_Cmd(COMP_Selection_COMP1, ENABLE);
}

void PeripheralInit::InitUSART2()
{
	USART_InitTypeDef USART_InitStruct;
	USART_StructInit(&USART_InitStruct);

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_Pin_Init(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, GPIO_Mode_AF, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);	// USART2_TX
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);	// USART2_RX

	USART_DeInit(USART2);
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStruct);

	USART_Cmd(USART2, ENABLE);

	/*
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	USART_ClearITPendingBit(USART2, USART_IT_TXE);
	*/
	/* Enable USART2 Receive and Transmit interrupts 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);*/

	//blink();

	//NVIC_EnableIRQ(USART2_IRQn);
}

/*
void PeripheralInit::SetCOMP1InvInp(const Comp1InvInp cii)
{
	/*!< Write to COMPx_CSR register *
	*(__IO uint32_t *) (COMP_BASE + COMP1) |= static_cast<uint32_t>(cii);
}

void PeripheralInit::SetCOMP1OutPol(const CompOutPol pol)
{
	/*!< Write to COMPx_CSR register *
	*(__IO uint32_t *) (COMP_BASE + COMP1) |= static_cast<uint32_t>(pol);
}
*/
