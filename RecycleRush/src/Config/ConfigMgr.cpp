#include "ConfigMgr.h"

#include <sstream>
#include <vector>

#include "Logger.h"
#include "LoggingComponentDefs.h"


namespace
{
    Variant Empty;   // The one and only empty variant.
    
    // Helper to see if an item exists in the passed map
    // and if not, returns the Empty variant.
    const Variant &findVariant(const std::string &itemName,
                               const std::map<std::string, Variant>& map)
    {
        std::map<std::string, Variant>::const_iterator pos = map.find(itemName);
        
        return (pos != map.end()) ? pos->second : Empty;
    }
    
    bool getValueOrDefault(const Variant &variant, bool defaultValue)
    {
        if (variant.getType() != Variant::None)
        {
            return variant.getBool();
        }
        
        return defaultValue;
    }

    int getValueOrDefault(const Variant &variant, int defaultValue)
    {
        if (variant.getType() != Variant::None)
        {
            return variant.getInt();
        }
        
        return defaultValue;
    }
    
    double getValueOrDefault(const Variant &variant, double defaultValue)
    {
        if (variant.getType() != Variant::None)
        {
            return variant.getDouble();
        }
        
        return defaultValue;
    }

    const std::string &getValueOrDefault(const Variant &variant, const std::string &defaultValue)
    {
        if (variant.getType() != Variant::None)
        {
            return variant.getString();
        }
        
        return defaultValue;
    }
    
    const char *getValueOrDefault(const Variant &variant, const char *defaultValue)
    {
        if (variant.getType() != Variant::None)
        {
            return variant.getString().c_str();
        }
        
        return defaultValue;
    }
    
    template <typename T> T getValue(const std::string &itemName,
                                     const std::map<std::string, Variant>& map,
                                     T defaultValue)
    {
        const Variant &value = findVariant(itemName, map);
        
        return getValueOrDefault(value, defaultValue);
    }
    
    const std::string &getValue(const std::string &itemName,
                                const std::map<std::string, Variant>& map,
                                const std::string &defaultValue)
    {
        const Variant &value = findVariant(itemName, map);
        
        return getValueOrDefault(value, defaultValue);
    }
}

ConfigMgr::ConfigMgr()
{

}

ConfigMgr::ConfigMgr(ConfigFileReader &configFileReader)
{
    std::string itemName;
    Variant value(0);
    
    Logger *logger = Logger::GetInstance();

    while (configFileReader.getNextConfigItem(itemName, value))
    {
        configMap.insert(std::pair<std::string, Variant>(itemName, value));

        if (logger->IsLogging(RobotLogId, Logger::kTRACE))
        {
        	switch (value.getType())
        	{
        	case Variant::None:       // Variant isn't storing anything.
        		logger->Log(ConfigurationId, Logger::kTRACE, "ConfigMgr: Adding variant named \"%s\" with value None.\n",
        				    itemName.c_str());
        		break;

        	case Variant::Bool:       // Variant is storing a boolean.
        		logger->Log(ConfigurationId, Logger::kTRACE, "ConfigMgr: Adding variant named \"%s\" with type Bool, Value=%s.\n",
        				    itemName.c_str(), value.getBool() ? "TRUE" : "FALSE");
        		break;

        	case Variant::Int:        // Variant is storing an int.
        		logger->Log(ConfigurationId, Logger::kTRACE, "ConfigMgr: Adding variant named \"%s\" with type Int, Value=%d.\n",
        				    itemName.c_str(), value.getInt());
        		break;

        	case Variant::Double:     // Variant is storing a double.
        		logger->Log(ConfigurationId, Logger::kTRACE, "ConfigMgr: Adding variant named \"%s\" with type Double, Value=%g.\n",
        				    itemName.c_str(), value.getDouble());
        		break;

        	case Variant::String:     // Variant is storing a string.
        		logger->Log(ConfigurationId, Logger::kTRACE, "ConfigMgr: Adding variant named \"%s\" with type String, Value=\"%s\".\n",
        				    itemName.c_str(), value.getString().c_str());
        		break;

        	default:
        		logger->Log(ConfigurationId, Logger::kTRACE, "ConfigMgr: Adding variant named \"%s\" with unknown type.\n",
        				    itemName.c_str());
        		break;
        	}
        }
    }
}

int ConfigMgr::getIntVal(const std::string &itemName, int defaultValue) const
{
    return getValue(itemName, configMap, defaultValue);
}

double ConfigMgr::getDoubleVal(const std::string &itemName, double defaultValue) const
{
    return getValue(itemName, configMap, defaultValue);
}

bool ConfigMgr::getBoolVal(const std::string &itemName, bool defaultValue) const
{
    return getValue(itemName, configMap, defaultValue);
}

const std::string &ConfigMgr::getStringVal(const std::string &itemName, const std::string &defaultValue)
{
    return getValue(itemName, configMap, defaultValue);
}


ConfigMgr::ValueType ConfigMgr::getType(const std::string &itemName) const
{
    return findVariant(itemName, configMap).getType();
}

bool ConfigMgr::exists(const std::string &itemName) const
{
    return (configMap.find(itemName) != configMap.end());
}




