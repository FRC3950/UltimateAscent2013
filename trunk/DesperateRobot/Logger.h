#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>

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
   
   void Log(MessageType type, const char* message, ...);
   
   void SetLoggingLevel(MessageType newLevel) { m_loggingLevel = newLevel; }
   bool IsLogging(MessageType type) { return type >= m_loggingLevel; }

protected:
   Logger(bool logToConsole, bool logToFile);
   void LogToFile(const char *msgType, const char *message, va_list args);
   void LogToConsole(const char *msgType, const char *message, va_list args);
private:
   static Logger *m_instance;
   FILE *m_logFile;
   MessageType m_loggingLevel;
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
