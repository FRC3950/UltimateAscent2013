#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdarg.h>
#include <stdio.h>

#include <WPILib.h>

//************************************************
// In order to enable file writing see Logger.cpp
// ************************************************

class Logger
{
public:
   typedef enum 
   {
	  kINFO = 0,
      kWARNING = 1, 
      kERROR = 2 
   } MessageType;
   
   static Logger* GetInstance(bool logToConsole = false, bool logToFile = false);

   virtual ~Logger();
   
   void SetLoggingLevel(MessageType newLevel) { m_loggingLevel = newLevel; }
   MessageType GetLoggingLevel() const { return m_loggingLevel; }
   
   void SetLoggingMask(unsigned int newMask) { m_loggingMask = newMask; }
   unsigned int GetLoggingMask() const { return m_loggingMask; }
   
   bool IsLogging(unsigned int componentSet, MessageType type) 
   { 
	   return ((componentSet & m_loggingMask) && (type >= m_loggingLevel)); 
   }

   void Log(unsigned int componentSet, MessageType type, const char* message, ...)
   {
	   if (IsLogging(componentSet, type))
	   {
		  va_list args;
		  va_start(args, message);

		  LogInternal(type, message, args);
		  
		  va_end(args);
	   }
   }
   
protected:
   Logger(bool logToConsole, bool logToFile);
   void LogInternal(MessageType type, const char* message, va_list args);
   void LogToFile(const char *timeStr, const char *msgType, const char *message, va_list args);
   void LogToConsole(const char *timeStr, const char *msgType, const char *message, va_list args);
   char *getTimeStamp();

private:
   static Logger *m_instance;

   ReentrantSemaphore m_lock;
   char *m_timeStringBuffer;
   FILE *m_logFile;
   MessageType m_loggingLevel;
   unsigned int m_loggingMask;
   bool m_logToConsole;
};

inline Logger* Logger::GetInstance(bool logToConsole /*= false*/, bool logToFile /*= false*/)
{
   if (m_instance == NULL)
   {
      m_instance = new Logger(logToConsole, logToFile);
   }
   
   return m_instance;
}

#endif
