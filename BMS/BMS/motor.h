#pragma once
#include "main.h"

namespace Motor
{
	static const int PwmOffset = 50;
	static const int PwmMax = 491;
	static const int PwmRange = PwmMax - PwmOffset;

	MotorState ChangeRotationSpeed(int8_t speed);
	MotorState Brake(void);
}
