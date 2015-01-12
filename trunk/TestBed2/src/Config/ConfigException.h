//
//  ConfigException.h
//  RobotConfig
//
//  Created by Robert Saccone on 12/5/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#ifndef __RobotConfig__ConfigException__
#define __RobotConfig__ConfigException__

#include <stdexcept>

#include "PlatformDefs.h"

class ConfigException : public std::runtime_error
{
public:
    explicit ConfigException(const std::string& what_arg);
    
    explicit ConfigException(const char *what_arg);
    
    ConfigException(const ConfigException& o) NOEXCEPT;
    
    ConfigException& operator=(const ConfigException& rhs) NOEXCEPT;
    
    virtual ~ConfigException() NOEXCEPT;
};

#endif /* defined(__RobotConfig__ConfigException__) */
