//
//  ConfigFileReader.h
//  RobotConfig
//
//  Created by Robert Saccone on 12/5/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#ifndef RobotConfig_ConfigFileReader_h
#define RobotConfig_ConfigFileReader_h

#include "Variant.h"

// Interface used to abstract how to read from a config file.
class ConfigFileReader
{
public:
    virtual bool getNextConfigItem(std::string &itemName, Variant &value) = 0;
};

#endif
