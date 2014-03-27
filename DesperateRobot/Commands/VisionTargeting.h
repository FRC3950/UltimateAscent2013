#ifndef VISION_TARGETING_H
#define VISION_TARGETING_H

#include <Commands/Subsystem.h>
#include "../Robot.h"

/**
 *
 *
 * @author rsaccone
 */

// Forward declarations
class StallCommand;
class NetworkTable; 

class VisionTargeting : public Command 
{
public:
	VisionTargeting(StallCommand *stallCommand);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	NetworkTable *networkTable_;
	StallCommand *stallCommand_;
	bool targetActive_;
};

#endif
