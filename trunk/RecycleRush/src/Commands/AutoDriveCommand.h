#ifndef AutoDriveCommand_H
#define AutoDriveCommand_H

#pragma once

#include "../CommandBase.h"
#include "../Subsystems/DriveSubsystem.h"
#include "WPILib.h"


class AutoDriveCommand: public CommandBase
{
public:
	AutoDriveCommand(DriveHeading heading, float distanceInInches, float speedScaleFactor = 1.0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	DriveHeading driveHeading;
	float distanceToDriveInInches;
	float motorSpeedScaleFactor;
	bool autoDriveIsSetup;
};

#endif
