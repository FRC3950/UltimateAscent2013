#include "LaunchAngle.h"
#include "../Subsystems/ArmPIDSubsystem.h"
#include "../Logger.h"

LaunchAngle::LaunchAngle()
	: angleVoltage(0.0)
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::armPIDSubsystem);
	
}

// Called just before this Command runs the first time
void LaunchAngle::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void LaunchAngle::Execute() {
	angleVoltage = Robot::armPIDSubsystem->SetRelativePIDTarget(LAUNCHING_ANGLE);
	Logger::GetInstance()->Log(Logger::kWARNING, "LaunchAngle : Seeking a POT Reading of %f", angleVoltage);
}

// Make this return true when this Command no longer needs to run execute()
bool LaunchAngle::IsFinished() {
	float potVoltage = Robot::armPIDSubsystem->GetPotentiometerReading();
	
	Logger::GetInstance()->Log(Logger::kWARNING, "LaunchAngle : POT Reading %f", potVoltage);

	SmartDashboard::PutNumber("Arm Pot", potVoltage);
	SmartDashboard::PutNumber("Arm Seeking Pot Voltage", angleVoltage);
	
	if (Robot::armPIDSubsystem->HasReachedTargetVoltage(angleVoltage))
	{
		Logger::GetInstance()->Log(Logger::kWARNING, "LaunchAngle : Reached Target Voltage of %f", 
				                   angleVoltage);
		
		// Rob - Trying out not disabling the PID to see if the angle holds. return true;
	}
				                   
	return false;
}

// Called once after isFinished returns true
void LaunchAngle::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LaunchAngle::Interrupted() {
}
