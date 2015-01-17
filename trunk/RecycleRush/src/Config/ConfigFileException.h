//
//  ConfigFileException.h
//  RobotConfig
//
//  Created by Robert Saccone on 12/5/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#ifndef __RobotConfig__ConfigFileException__
#define __RobotConfig__ConfigFileException__

#include "ConfigException.h"

#include "PlatformDefs.h"

class ConfigFileException : public ConfigException
{
public:
    explicit ConfigFileException(const std::string& what_arg);
    
    explicit ConfigFileException(const char *what_arg);
    
    ConfigFileException(const ConfigFileException& o) NOEXCEPT;
    
    ConfigFileException& operator=(const ConfigFileException& rhs) NOEXCEPT;
    
    virtual ~ConfigFileException() NOEXCEPT;
};


#endif /* defined(__RobotConfig__ConfigFileException__) */
