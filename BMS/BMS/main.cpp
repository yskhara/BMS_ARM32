#include "main.h"

uint32_t _clocks_in_us;

MotorState state;

__IO uint16_t ADC1ConvertedValue;

void delay_us(unsigned int delay)
{
	unsigned int t = delay * _clocks_in_us;
	for (unsigned int i = 0; i < t; i++)
	{
		__NOP();
	}
}

void blink()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	delay_us(10000);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

int main(void)
{
	//SystemInit();

	_clocks_in_us = SystemCoreClock / 1000000;

	PeripheralInit::InitGPIO();
	PeripheralInit::InitEXTI();
	PeripheralInit::InitNVIC();

	PeripheralInit::InitTIM1();
	//PeripheralInit::InitTIM2();
	//PeripheralInit::InitTIM4();


	PeripheralInit::InitUSART2();

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	blink();
	//printf("Initialization completed.\n");

	/*
	 *      ||    hi    | lo  |
	 * -----++----------+-----+
	 *    0 || PC0(CH1) | PC2 |
	 *    1 || PC1(CH2) | PC3 |
	 */


	//state = MotorState::Brake;


	// init position
	//GPIO_ResetBits(GPIOC, GPIO_Pin_2);// | GPIO_Pin_3);
	//GPIO_SetBits(GPIOC, GPIO_Pin_3);

	// positive value for forward, negative for reverse

	while (1)
	{
		blink();
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE == RESET)) {}
		USART_SendData(USART2, 'A');
		/*
		if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);
			uint16_t d = USART_ReceiveData(USART2);
			//Motor::ChangeRotationSpeed(d);
			while (USART_GetFlagStatus(USART2, USART_FLAG_TXE == RESET)) {}
			USART_SendData(USART2, d);
		}
		*/
	}

	for (int i = 0; i < 128; i++)
	{
		Motor::ChangeRotationSpeed(i);
		delay_us(10000);
	}


	delay_us(50000);
	blink();
	//Motor::ChangeRotationSpeed(-100);

	//delay_us(500000);

	//Motor::Brake();


	while(1){ }


	signed short actual = 0, desired = 0;

	while (1)
	{
		// Main loop


		switch (state)
		{
		case MotorState::Coast: 
			// break;
		case MotorState::Brake: 
			// confirm the motor stopped and set state to "Stop".
			// just wanna make sure the motor is stopped but dont wanna use adc to measure speed...ugh



			break;
		case MotorState::Stop: 
			if (desired > 0)
			{
				state = MotorState::Forward;
			}
			else if (desired < 0)
			{
				state = MotorState::Reverse;
			}
			break;
		case MotorState::Forward: 
			if (desired == 0)
			{
				actual = 0;
				state = Motor::ChangeRotationSpeed(0);
			}
			else if (desired < 0)
			{
				actual = 0;
				Motor::Brake();
				state = MotorState::Brake;
			}
			else if (desired > 0)
			{
				// forward where actual > 0
				if (desired > actual)
				{
					Motor::ChangeRotationSpeed(++actual);
				}
				else if (desired < actual)
				{
					Motor::ChangeRotationSpeed(--actual);
				}
			}
			break;
		case MotorState::Reverse: 
			if (desired == 0)
			{
				state = Motor::ChangeRotationSpeed(0);
			}
			else if (desired > 0)
			{
				Motor::Brake();
				state = MotorState::Brake;
			}
			else if (desired < 0)
			{
				// reverse where actual < 0
				if (desired > actual)
				{
					Motor::ChangeRotationSpeed(++actual);
				}
				else if (desired < actual)
				{
					Motor::ChangeRotationSpeed(--actual);
				}
			}
			break;
		default:
			break;
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		delay_us(10000);
	}

	return 0;
}
