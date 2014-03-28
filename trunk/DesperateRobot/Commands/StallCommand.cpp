#include "StallCommand.h"

StallCommand::StallCommand(double stallTimeInSecs) 
	: stallTimeInSecs_(stallTimeInSecs)
{
	if (stallTimeInSecs_ < 0.0)
	{
		stallTimeInSecs_ = 0.0;
	}
}

void StallCommand::SetStallTime(double stallTimeInSecs)
{
	if (stallTimeInSecs >= 0)
	{
		stallTimeInSecs_ = stallTimeInSecs;
		SetTimeout(stallTimeInSecs);
	}
}

// Called just before this Command runs the first time
void StallCommand::Initialize() {
	if (stallTimeInSecs_ > 0.0)
	{
		SetTimeout(stallTimeInSecs_);
	}
}

// Called repeatedly when this Command is scheduled to run
void StallCommand::Execute() {
	// Nothing to do.
}

// Make this return true when this Command no longer needs to run execute()
bool StallCommand::IsFinished() {
	
	// Stall time specified?
	if (stallTimeInSecs_ > 0.0)
	{
		return IsTimedOut();
	}
	
	return true;
}

// Called once after isFinished returns true
void StallCommand::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StallCommand::Interrupted() {
}
