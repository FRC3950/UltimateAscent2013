/**
 * Extended from Team 3132's logger implementation
 * Logger.h
 * 
 * This class is a simple logging interface. The log filename is specified in the constructor
 * and uses a timestamp to identify the files.
 * 
 * This class uses C functions and not C++ IO, for no real reason, other than it was easier for
 * me to write quickly.
 */        
#include "Logger.h"
#include <limits.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

// Add this in to enable file writing.  It's a private function
// of the OS (according to WPI and Chief Delphi).
/** Private NI function needed to write to the VxWorks target */
// int Priv_SetWriteFileAllowed(uint32_t enable); 

Logger* Logger::m_instance = NULL;

static const char *LogDir = "/home/lvuser/Logs";

Logger::Logger(bool logToConsole, bool logToFile)
	: m_loggingLevel(kERROR),
	  m_loggingMask(UINT_MAX),
	  m_logToConsole(logToConsole)
{
   if (logToFile)
   {
	   // Must be called before file access to the CRIO is allowed.
	   // Add this in to enable file writing.  It's a private function
	   // of the OS (according to WPI and Chief Delphi).
	   // Priv_SetWriteFileAllowed(1);

#if 0

	   static char currDir[1024];

	   if (getcwd(currDir, sizeof(currDir)))
	   {
		   printf("Current directory = %s\n", currDir);
	   }
	   else
	   {
		   printf("Current directory COULDN'T be RETRIEVED.\n");
	   }
#endif

	   struct stat st = { 0 };

	   if (stat(LogDir, &st) == -1)
	   {
		   mkdir(LogDir, 0700);
	   }

	   // Determine the filename
	   time_t currentTime = time(NULL);
	   struct tm *theTime = localtime(&currentTime);
	   
	   // Create a filename
	   // Format of the filename is "Log-dd-mm-yyyy-hh.mm.ss.txt"
	   char *filename = (char *)calloc(512, sizeof(char));
	   
	   // Print the filename into the string
	   sprintf(filename, "%s/Log-%02d-%02d-%4d-%02d.%02d.%02d.txt",
			   LogDir,
			   theTime->tm_mday,
			   (theTime->tm_mon + 1),
			   (theTime->tm_year + 1900),
			   theTime->tm_hour, theTime->tm_min, theTime->tm_sec);
	   
	   // Open the file to write to
	   m_logFile = fopen(filename, "w");
	   
	   // Print a header into the file
	   if (m_logFile != NULL)
	   {
		  fprintf(m_logFile, "New log started at %s", asctime(theTime));
		  fprintf(m_logFile, "-------------------------------------------------------------\n");
	   }
	   else
	   {
		   int error = errno;
		   printf("*** Couldn't create log file %s reason %d ****\n",
				   filename, error);
	   }

	   free(filename);
   }
   else
   {
	   m_logFile = NULL;
   }
}

Logger::~Logger()
{
   // Close file
   if (m_logFile != NULL)
   {
      fflush(m_logFile);
      fclose(m_logFile);
   }
   
   // Set reference to null
   m_logFile = NULL;
}

static const char *ERROR_MSG = "ERROR\t";
static const char *WARN_MSG = "WARN\t";
static const char *INFO_MSG = "INFO\t";

#if defined(LOGGER_NOT_NEEDED)

void Logger::Log(MessageType type, const char* message, ...)
{
   if (IsLogging(type))
   {
	   const char *msgType;
	   
      // First print the message type
      switch (type)
      {
      case kERROR:
         msgType = ERROR_MSG;
         break;
      case kWARNING:
         msgType = WARN_MSG;
         break;
      case kINFO:
         msgType = INFO_MSG;
         break;
      default:
         msgType = INFO_MSG;
         break;
      }
      
      va_list args;
      va_start(args, message);
      
      if (m_logFile != NULL )
      {
    	  LogToFile(msgType, message, args);
      }
      
      if (m_logToConsole)
      {
    	  LogToConsole(msgType, message, args);
      }
      
      va_end(args);
   }
}
#endif

void Logger::LogInternal(MessageType type, const char* message, va_list args)
{
	const char *msgType;
	   
	// First print the message type
	switch (type)
	{
	case kERROR:
	  msgType = ERROR_MSG;
	  break;
	case kWARNING:
	  msgType = WARN_MSG;
	  break;
	case kINFO:
	  msgType = INFO_MSG;
	  break;
	default:
	  msgType = INFO_MSG;
	  break;
	}
	
	Synchronized guard(m_lock);

	if (m_logFile != NULL )
	{
		LogToFile(msgType, message, args);
	}
	
	if (m_logToConsole)
	{
		LogToConsole(msgType, message, args);
	}
}

void Logger::LogToFile(const char *msgTypeStr, const char* message, va_list args)
{
    fprintf(m_logFile, msgTypeStr);

    // Write to the file
    vfprintf(m_logFile, message, args);
    fprintf(m_logFile, "\n");
    
    fflush(m_logFile);
}

void Logger::LogToConsole(const char *msgTypeStr, const char *message, va_list args)
{
    printf(msgTypeStr);

    // Write to the file
    vprintf(message, args);
    printf("\n");
}


