// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef GANTRYSUBSYSTEM_H
#define GANTRYSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class GantrySubsystem: public Subsystem {
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Solenoid* liftSolenoid;
	Solenoid* leftGripSolenoid;
	Solenoid* rightGripSolenoid;
	Solenoid* restraintSolenoid;
	DigitalInput* crateAlignedSwich;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	GantrySubsystem();

	void InitDefaultCommand();

	bool CheckContainerAlignedLimitSwitch();

	void FireLiftSolenoid(bool fire);
	bool ToggleLiftSolenoid();
	bool IsLiftRaised() const;

	void SetRestraintSolenoid(bool fire);
	bool ToggleRestraintSolenoid();
	bool IsRestraintApplied() const;

	void CloseGrip();
	void OpenGrip();
	bool ToggleGrip();

	bool IsGripClosed() const { return gripClosed; }

private:
	bool ToggleSolenoid(Solenoid* solenoid);

	bool gripClosed;
};

#endif