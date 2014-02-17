#ifndef FIND_ARM_POT_ORIGIN_H
#define FIND_ARM_POT_ORIGIN_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class FindArmPotOrigin: public Command {
public:
	FindArmPotOrigin();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
