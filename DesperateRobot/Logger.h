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
      kERROR = 0, 
      kWARNING = 1, 
      kINFO = 2
   } MessageType;
   
   static Logger* GetInstance(bool logToConsole = false, bool logToFile = false);

   virtual ~Logger();
   
   void Log(MessageType type, const char* message, ...);
   
   void SetIsLogging(bool isLogging) { m_isLogging = isLogging; }
   bool IsLogging() { return m_isLogging; }

protected:
   Logger(bool logToConsole, bool logToFile);
   void LogToFile(const char *msgType, const char *message, va_list args);
   void LogToConsole(const char *msgType, const char *message, va_list args);
private:
   static Logger *m_instance;
   FILE *m_logFile;
   bool m_logToConsole;
   bool m_isLogging;
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
