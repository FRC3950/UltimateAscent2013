#ifndef AutoRotateCommand_H
#define AutoRotateCommand_H

#include "../CommandBase.h"
#include "../Subsystems/DriveSubsystem.h"
#include "WPILib.h"


class AutoRotateCommand: public CommandBase
{
public:
	AutoRotateCommand(float angle, RotateDirection direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float angle;
	RotateDirection direction;
};

#endif
