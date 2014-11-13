#include "ArmUp.h"
#include "../Subsystems/ArmPIDSubsystem.h"
#include "../ShootingTargetDefs.h"

static const float MotorSpeedVoltage = -1.0;  // This will be scaled by the Arm Subsystem.

ArmUp::ArmUp() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::armPIDSubsystem);
	
}

// Called just before this Command runs the first time
void ArmUp::Initialize() {
	Robot::armPIDSubsystem->SetReadyToFireField(false);
}

// Called repeatedly when this Command is scheduled to run
void ArmUp::Execute() {
	Robot::armPIDSubsystem->ManualMoveArmControl(MotorSpeedVoltage);
	Robot::armPIDSubsystem->UpdateReadyToFireField(TargetShooterSetPoint);
}

// Make this return true when this Command no longer needs to run execute()
bool ArmUp::IsFinished() {
	return Robot::armPIDSubsystem->PollUpperArmLimit();
}

// Called once after isFinished returns true
void ArmUp::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmUp::Interrupted() {
}
