#if !defined(__CONFIG_MGR__)

#define __CONFIG_MGR__

#include <map>
#include <string>

#include "ConfigFileReader.h"
#include "Variant.h"

class ConfigMgr
{
public:
    typedef Variant::ValueType ValueType;
    
    explicit ConfigMgr();

    ConfigMgr(ConfigFileReader &configFileReader);
    
    ValueType getType(const std::string &itemName) const;
    
    bool exists(const std::string &itemName) const;

    // All these method look up a value and if not found will simply return the passed defaultValue
    bool getBoolVal(const std::string &itemName, bool defaultValue) const;
    
    int getIntVal(const std::string &itemName, int defaultValue) const;
    
    double getDoubleVal(const std::string &itemName, double defaultValue) const;
    
    const std::string &getStringVal(const std::string &itemName, const std::string &defaultValue);
    
private:
    
    std::map<std::string, Variant> configMap;
};

#endif

