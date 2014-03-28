#include "LaunchAngle.h"
#include "../Subsystems/ArmPIDSubsystem.h"
#include "../Logger.h"
#include "../LoggingComponentDefs.h"
#include "../SmartDashboardFields.h"
#include "../ShootingTargetDefs.h"
#include "../UtilFun.h"


static const float AutonomousLowerEpsilon = 0.06;
static const float AutonomousUpperEpsilon = 0.06;

LaunchAngle::LaunchAngle(bool autonomousMode /* = false */)
	: angleVoltage(0.0),
	  autonomous(autonomousMode)
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::armPIDSubsystem);
}

// Called just before this Command runs the first time
void LaunchAngle::Initialize() {
	Robot::armPIDSubsystem->SetReadyToFireField(false);
}

// Called repeatedly when this Command is scheduled to run
void LaunchAngle::Execute() {
	angleVoltage = Robot::armPIDSubsystem->SetAbsolutePIDTarget(TargetShooterSetPoint);
	Logger::GetInstance()->Log(ArmPIDSubsystemLogId, Logger::kWARNING, "LaunchAngle : Seeking a POT Reading of %f", angleVoltage);
}


// Make this return true when this Command no longer needs to run execute()
bool LaunchAngle::IsFinished() {
	float potVoltage = Robot::armPIDSubsystem->GetPotentiometerReading();
	
	Logger::GetInstance()->Log(ArmPIDSubsystemLogId, Logger::kWARNING, "LaunchAngle : POT Reading %f", potVoltage);

	SmartDashboard::PutNumber("Arm Pot", potVoltage);
	SmartDashboard::PutNumber("Arm Seeking Pot Voltage", angleVoltage);

	bool finished = false;
	
	if (!autonomous)
	{
		Robot::armPIDSubsystem->UpdateReadyToFireField(angleVoltage, potVoltage);
	}
	else
	{
		finished = Robot::armPIDSubsystem->UpdateReadyToFireField(angleVoltage,
				                                                  potVoltage,
				                                                  AutonomousLowerEpsilon,
				                                                  AutonomousUpperEpsilon);
		
		Logger::GetInstance()->Log(ArmPIDSubsystemLogId, Logger::kINFO, "LaunchAngle : POT Reading %f has %s target voltage", 
				                   potVoltage, finished ? "MET" : "NOT MET");

	}
	return finished;
}

// Called once after isFinished returns true
void LaunchAngle::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LaunchAngle::Interrupted() {
}
