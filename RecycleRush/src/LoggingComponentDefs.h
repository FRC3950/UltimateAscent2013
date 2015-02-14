#if !defined(LOGGING_COMPONENT_DEFS_H)

#define LOGGING_COMPONENT_DEFS_H

#include "Logger.h"

const unsigned int RobotLogId				= 1U << 0; 	//0x00000001U;  
const unsigned int GantrySubsystemLogId 	= 1U << 1;  //0x00000002U;
const unsigned int DriveSubsystemLogId 		= 1U << 2;  //0x00000004U;
const unsigned int IntakeSubsystemLogId 	= 1U << 3;  //0x00000008U;
const unsigned int PneumaticsSubsystemLogId	= 1U << 4;  //0x00000010U;
const unsigned int ShooterSubsystemLogId	= 1U << 5;	//0x00000020U;
const unsigned int VisionTargetingId		= 1U << 6;	//0x00000040U;
const unsigned int ConfigurationId			= 1U << 7;  //0x00000080U;

const unsigned int DefaultLoggingMask = (RobotLogId | ConfigurationId | DriveSubsystemLogId | VisionTargetingId | GantrySubsystemLogId | IntakeSubsystemLogId);
const Logger::MessageType DefaultLoggingLevel = Logger::kTRACE;

#endif
