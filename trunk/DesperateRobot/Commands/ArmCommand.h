#ifndef ARMCOMMAND_H
#define ARMCOMMAND_H

#include "../Robot.h"

/**
 *
 *
 * @author DriverStation
 */
class ArmCommand: public Command {
public:
	ArmCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
