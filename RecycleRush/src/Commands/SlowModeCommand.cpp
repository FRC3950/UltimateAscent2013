#include "SlowModeCommand.h"
#include "../Robot.h"

SlowModeCommand::SlowModeCommand()
	: m_slowModeEnabled(false)
{
}

// Called just before this Command runs the first time
void SlowModeCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void SlowModeCommand::Execute()
{
	m_slowModeEnabled = !m_slowModeEnabled;
}

// Make this return true when this Command no longer needs to run execute()
bool SlowModeCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SlowModeCommand::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SlowModeCommand::Interrupted()
{
}
