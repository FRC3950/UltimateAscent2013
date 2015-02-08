#ifndef MoveCommand_H
#define MoveCommand_H

#include "Commands/Command.h"
#include "WPILib.h"
#include "../Subsystems/DriveSubsystem.h"



class MoveCommand: public Command
{
public:
	MoveCommand(DriveHeading heading, float distenceInInches);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	const DriveHeading m_heading;
	const float m_distanceInInches;
	bool m_startedMoving;
	bool m_setup;
};

#endif
