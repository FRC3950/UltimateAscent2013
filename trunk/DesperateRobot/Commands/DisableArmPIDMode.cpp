#include "DisableArmPIDMode.h"
#include "../Subsystems/ArmPIDSubsystem.h"
#include "../Logger.h"
#include "../LoggingComponentDefs.h"

DisableArmPIDMode::DisableArmPIDMode()
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::armPIDSubsystem);
	
}

// Called just before this Command runs the first time
void DisableArmPIDMode::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void DisableArmPIDMode::Execute() {
	Robot::armPIDSubsystem->SetPIDSubsystem(false);
	Logger::GetInstance()->Log(ArmPIDSubsystemLogId, Logger::kWARNING, "DisableArmPIDMode : PID Mode Disabled.");
}

// Make this return true when this Command no longer needs to run execute()
bool DisableArmPIDMode::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void DisableArmPIDMode::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DisableArmPIDMode::Interrupted() {
}
