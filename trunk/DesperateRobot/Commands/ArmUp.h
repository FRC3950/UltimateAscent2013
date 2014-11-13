#ifndef ARMUP_H
#define ARMUP_H

#include "../Robot.h"

/**
 *
 *
 * @author DriverStation
 */
class ArmUp: public Command {
public:
	ArmUp();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
