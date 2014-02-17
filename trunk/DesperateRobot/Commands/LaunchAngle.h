#ifndef LAUNCHANGLE_H
#define LAUNCHANGLE_H

#include "../Robot.h"

/**
 *
 *
 * @author DriverStation
 */
class LaunchAngle: public Command {
public:
	LaunchAngle();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	float angleVoltage;
};

#endif
