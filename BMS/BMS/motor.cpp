#include "motor.h"

namespace Motor
{
	MotorState ChangeRotationSpeed(int8_t speed)
	{
		if (speed == 0)
		{
			// Coast
			TIM_SetCompare1(TIM1, 0);
			TIM_SetCompare2(TIM1, 0);

			return MotorState::Coast;
		}

		if (speed == -128)
		{
			return Motor::Brake();

			//printf("OutOfRangeException");
			//return ChangeRotationSpeed(0);
		}

		// I think you don't even want to try to change this: 
		int pwm = (std::abs((float)speed) * (PwmRange / 127.0)) + PwmOffset;

		if (speed > 0)
		{
			// forward
			TIM_SetCompare1(TIM1, pwm);
			TIM_SetCompare2(TIM1, 0);
			return MotorState::Forward;
		}
		else
		{
			// reverse
			TIM_SetCompare1(TIM1, 0);
			TIM_SetCompare2(TIM1, pwm);
			return MotorState::Reverse;
		}
	}

	MotorState Brake(void)
	{
		TIM_SetCompare1(TIM1, 0);
		TIM_SetCompare2(TIM1, 0);

		return MotorState::Brake;
	}
}