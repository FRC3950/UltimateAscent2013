#ifndef DISABLED_ARM_PID_MODE_H
#define DISABLED_ARM_PID_MODE_H

#include "../Robot.h"

/**
 *
 *
 * @author DriverStation
 */
class DisableArmPIDMode: public Command {
public:
	DisableArmPIDMode();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
