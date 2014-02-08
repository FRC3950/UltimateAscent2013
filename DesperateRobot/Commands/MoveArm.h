#ifndef MOVEARM_H
#define MOVEARM_H

#include "../Robot.h"

/**
 *
 *
 * @author DriverStation
 */
class MoveArm: public Command {
public:
	MoveArm();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
