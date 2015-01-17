//
//  StringUtils.h
//  RobotConfig
//
//  Created by Robert Saccone on 12/7/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#ifndef RobotConfig_StringUtils_h
#define RobotConfig_StringUtils_h

#include <ctype.h>
#include <functional>
#include <string>

// trim from start
inline std::string &ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
inline std::string &rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
inline std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}

#endif
