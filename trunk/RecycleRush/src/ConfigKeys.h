#pragma once

#include <string>

// Contains the predefined configuration keys:
namespace ConfigKeys
{
	// Gantry Subsystem Keys.
	extern const std::string Gantry_OutputCheckContainerAlignmentInSecsConfigKey;

	// Drive Subsystem Keys.
	extern const std::string Drive_CreateGyroKey;
	extern const std::string Drive_UseGyroKey;
	extern const std::string Drive_WheelDiameterInInchesKey;
	extern const std::string Drive_CountsPerShaftRotationKey;
	extern const std::string Drive_EnableSafety;
	extern const std::string Drive_SafetyTimeOut;

	extern const std::string Drive_TwistToleranceMin;
	extern const std::string Drive_TwistToleranceMax;
	extern const std::string Drive_TwistScaleFactor;

	extern const std::string Drive_YToleranceMin;
	extern const std::string Drive_YToleranceMax;

	extern const std::string Drive_XToleranceMin;
	extern const std::string Drive_XToleranceMax;
}
