//
//  ConfigException.cpp
//  RobotConfig
//
//  Created by Robert Saccone on 12/5/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#include "ConfigException.h"

#include "PlatformDefs.h"

ConfigException::ConfigException(const std::string& what_arg)
: runtime_error(what_arg)
{
    
}

ConfigException::ConfigException(const char *what_arg)
: runtime_error(what_arg)
{
    
}

ConfigException::ConfigException(const ConfigException& o) NOEXCEPT
: runtime_error(o)
{
    
}

ConfigException& ConfigException::operator=(const ConfigException& rhs) NOEXCEPT
{
    runtime_error::operator=(rhs);
    
    return *this;
}

ConfigException::~ConfigException() NOEXCEPT
{
    
}
