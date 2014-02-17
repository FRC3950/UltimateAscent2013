#ifndef AUTO_MOVE_FORWARD_H
#define AUTO_MOVE_FORWARD_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class AutoMoveForward: public Command {
public:
	AutoMoveForward();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
