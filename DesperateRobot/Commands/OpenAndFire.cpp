#include "OpenAndFire.h"

OpenAndFire::OpenAndFire() {
	AddSequential(new OpenClaw());
	AddSequential(new Fire());
}
	
