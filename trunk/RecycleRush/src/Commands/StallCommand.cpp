#include "StallCommand.h"

StallCommand::StallCommand(double stallTimeInSecs) 
	: stallTimeInSecs_(stallTimeInSecs),
	  startStallTime_(0.0)
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
	}
}

// Called just before this Command runs the first time
void StallCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void StallCommand::Execute() {
	if (stallTimeInSecs_ > 0.0)
	{
		if (startStallTime_ <= 0.0)
		{
			startStallTime_ = Timer::GetFPGATimestamp();
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool StallCommand::IsFinished() {
	if (stallTimeInSecs_ > 0.0)
	{
		double currTime = Timer::GetFPGATimestamp();

		if ((currTime - startStallTime_) >= stallTimeInSecs_)
		{
			startStallTime_ = 0.0;
			return true;
		}

		return false;
	}
	
	return true;
}

// Called once after isFinished returns true
void StallCommand::End() {
	startStallTime_ = 0.0;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StallCommand::Interrupted() {
}
