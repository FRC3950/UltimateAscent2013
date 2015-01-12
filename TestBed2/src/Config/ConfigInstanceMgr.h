/*
 * ConfigInstanceMgr.h
 *
 *  Created on: Jan 8, 2015
 *      Author: DriverStation
 */


#ifndef SRC_CONFIG_CONFIGINSTANCEMGR_H_
#define SRC_CONFIG_CONFIGINSTANCEMGR_H_

#include"ConfigMgr.h"

class ConfigInstanceMgr {
public:
	static ConfigMgr *getInstance(const std::string &filename, bool failOnFileNotFound);

	static ConfigMgr *getInstance()
	{
		return instance;
	}


private:
	ConfigInstanceMgr();

	static ConfigMgr *instance;

};




#endif /* SRC_CONFIG_CONFIGINSTANCEMGR_H_ */
