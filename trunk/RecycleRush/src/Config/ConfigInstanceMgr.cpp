/*
 * ConfigInstanceMgr.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: DriverStation
 */
#include"ConfigInstanceMgr.h"

#include <sstream>
#include "ConfigFileException.h"
#include"CsvConfigFileReader.h"
#include "../Logger.h"
#include "../LoggingComponentDefs.h"

ConfigMgr *ConfigInstanceMgr::instance = 0;

ConfigMgr* ConfigInstanceMgr::getInstance(const std::string &filename, bool failOnFileNotFound){

	if (instance != 0)
	{
	   return instance;
	}

	try
	{
		CsvConfigFileReader configReader(filename);
		instance = new ConfigMgr(configReader);
	}
	catch (ConfigFileException &ex)
	{
		Logger *logger = Logger::GetInstance(true, true);

		if (failOnFileNotFound)
		{
	        // Failed to open the file.
	        // Throw an exception.
	        std::ostringstream strBldr;
	        strBldr << "Caught exception: ";
	        strBldr << ex.what();
	        strBldr << ", FATAL ERROR - Robot terminating.";

	        logger->Log(RobotLogId, Logger::kERROR, strBldr.str().c_str());

	        throw;
		}

        std::ostringstream strBldr;
        strBldr << "Caught exception: ";
        strBldr << ex.what();
        strBldr << ", WARNING - Robot running with HARDCODED default values.";

        logger->Log(RobotLogId, Logger::kWARNING, strBldr.str().c_str());

        instance = new ConfigMgr();
	}


	return instance;
}




