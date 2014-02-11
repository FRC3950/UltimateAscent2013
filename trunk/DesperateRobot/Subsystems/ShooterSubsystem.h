// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef SHOOTER_SUBSYSTEM_H
#define SHOOTER_SUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ShooterSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	DigitalInput* upperLimitSwitch;
	DigitalInput* lowerLimitSwitch;
	SpeedController* shooterMotor;
	DoubleSolenoid* triggerSolenoid;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	ShooterSubsystem();
	void InitDefaultCommand();
	void ReleaseTrigger();
	void SetShooterMotorVoltage(float voltage);
	bool CheckUpperLimitSwitch();
	bool CheckLowerLimitSwitch();
	bool IsArmed() { return armed;}
	
private:
	bool armed;

};

#endif
