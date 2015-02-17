#ifndef STALL_COMMAND_H
#define STALL_COMMAND_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class StallCommand: public Command {
public:
	StallCommand(double stallTimeInSecs = 0.0);
	// Can be called after construction but before
	// first execution.
	void SetStallTime(double stallTimeInSecs);
	
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	double stallTimeInSecs_;
	double startStallTime_;
};

#endif
