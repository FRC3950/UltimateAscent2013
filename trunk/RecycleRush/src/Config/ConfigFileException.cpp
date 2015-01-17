//
//  ConfigFileException.cpp
//  RobotConfig
//
//  Created by Robert Saccone on 12/5/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#include "ConfigFileException.h"

#include "PlatformDefs.h"

ConfigFileException::ConfigFileException(const std::string& what_arg)
    : ConfigException(what_arg)
{
    
}

ConfigFileException::ConfigFileException(const char *what_arg)
    : ConfigException(what_arg)
{
    
}
    
ConfigFileException::ConfigFileException(const ConfigFileException& o) NOEXCEPT
    : ConfigException(o)
{
    
}
    
ConfigFileException& ConfigFileException::operator=(const ConfigFileException& rhs) NOEXCEPT
{
    ConfigException::operator=(rhs);
    
    return *this;
}

ConfigFileException::~ConfigFileException() NOEXCEPT
{
    
}
