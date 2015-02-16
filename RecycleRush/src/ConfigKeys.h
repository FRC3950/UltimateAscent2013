#pragma once

#include <string>

// Contains the predefined configuration keys:
namespace ConfigKeys
{
	// Autonomous Config Keys
	extern const std::string Auto1RS_MoveLeftDistance_Key;

	extern const std::string Auto1TS_MoveForwardDistance_Key;
	extern const std::string Auto1TS_MoveLeftDistance_Key;

	extern const std::string Auto3SS_MoveRightDistanceKey1;
	extern const std::string Auto3SS_MoveRightDistanceKey2;
	extern const std::string Auto3SS_MoveForwardDistanceKey1;
	extern const std::string Auto3SS_MoveForwardDistanceKey2;
	extern const std::string Auto3SS_MoveLeftDistanceKey1;

	extern const std::string Auto1CS2_MoveLeftDistanceKey;
	extern const std::string Auto1CS2_MoveBackDistanceKey;
	extern const std::string Auto1CS2_MoveRightDistanceKey1;
	extern const std::string Auto1CS2_MoveForwardDistanceKey;
	extern const std::string Auto1CS2_MoveRightDistanceKey2;

	// Gantry Subsystem Keys.
	extern const std::string Gantry_OutputCheckContainerAlignmentInSecsConfigKey;
	extern const std::string Gantry_DownLiftDelayInSecsConfigKey;

	// Drive Subsystem Keys.
	extern const std::string Drive_CreateGyroKey;
	extern const std::string Drive_UseGyroKey;
	extern const std::string Drive_WheelDiameterInInchesKey;
	extern const std::string Drive_CountsPerShaftRotationKey;
	extern const std::string Drive_AutoRotateMaxSpeedKey;
	extern const std::string Drive_AutoRotateSlowDownThresholdKey;
	extern const std::string Drive_AngleDecimalPlacesPrecisionKey;
	extern const std::string Drive_AutoRotateTargetAngleEpsilonKey;
	extern const std::string Drive_AutoDriveUseOneMotorForDistanceDriveKey;
	extern const std::string Drive_AutoDriveFowardBackHeadingSpeedScaleFactorKey;
	extern const std::string Drive_AutoDriveLeftRightHeadingSpeedScaleFactorKey;
	extern const std::string Drive_AutoDriveSlowDownThresholdInInchesKey;
	extern const std::string Drive_AutoDriveTargetDistanceEpsilonInInchesKey;
	extern const std::string Drive_EnableSafety;
	extern const std::string Drive_SafetyTimeOut;
	extern const std::string Drive_TwistToleranceMin;
	extern const std::string Drive_TwistToleranceMax;
	extern const std::string Drive_TwistScaleFactor;

	extern const std::string Drive_YToleranceMin;
	extern const std::string Drive_YToleranceMax;

	extern const std::string Drive_XToleranceMin;
	extern const std::string Drive_XToleranceMax;

	extern const std::string Drive_SlowDownScaleFactor;
	extern const std::string Drive_XScaleFactor;
	extern const std::string Drive_YScaleFactor;

	extern const std::string Drive_AutoDriveFrontLeftSpeedKey;
	extern const std::string Drive_AutoDriveFrontRightSpeedKey;
	extern const std::string Drive_AutoDriveBackLeftSpeedKey;
	extern const std::string Drive_AutoDriveBackRightSpeedKey;
}

