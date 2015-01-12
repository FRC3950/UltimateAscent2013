#include "variant.h"

#include <map>
#include <sstream>

namespace  {

struct VariantToKeywordMapIniter
{
	static const std::map<Variant::ValueType, std::string> init()
	{
		std::map<Variant::ValueType, std::string> typeToKwMap;
		typeToKwMap.insert(std::pair<Variant::ValueType, std::string>(Variant::Bool, "Bool"));
		typeToKwMap.insert(std::pair<Variant::ValueType, std::string>(Variant::Int, "Int"));
		typeToKwMap.insert(std::pair<Variant::ValueType, std::string>(Variant::Double, "Double"));
		typeToKwMap.insert(std::pair<Variant::ValueType, std::string>(Variant::String, "String"));
        
        return typeToKwMap;
	}
};

const std::map<Variant::ValueType,std::string> valueTypeToStringMap = VariantToKeywordMapIniter::init();

void throwIfTypeMismatch(Variant::ValueType expectedType, Variant::ValueType actualType)
{
    if (actualType != expectedType)
    {
    	std::map<Variant::ValueType, std::string>::const_iterator actualTypeIterator = valueTypeToStringMap.find(actualType);
    	std::map<Variant::ValueType, std::string>::const_iterator expectedTypeIterator = valueTypeToStringMap.find(expectedType);
        
        std::ostringstream strBldr;
        
        strBldr << "Variant expected to contain: " << expectedTypeIterator->second << ", acutally contained: " << actualTypeIterator->second;
        
        throw VariantTypeMismatchException(strBldr.str());
    }
}
    
}

Variant::Variant()
    : valueType(Variant::None)
{
}

Variant::Variant(const Variant& o)
{
    copy(o);
}

Variant& Variant::operator=(const Variant &rhs)
{
    copy(rhs);
    
    return *this;
}

void Variant::copy(const Variant &other)
{
    switch (other.valueType)
    {
        case Bool:
            setValue(other.getBool());
            break;
            
        case Int:
            setValue(other.getInt());
            break;
            
        case Double:
            setValue(other.getDouble());
            break;
            
        case String:
            setValue(other.getString());
            break;
            
        default:
            // This should never happen.
            assert(0);
            break;
    }
}

Variant::Variant(int value)
{
    setValue(value);
}

Variant::Variant(double value)
{
    setValue(value);
}

Variant::Variant(bool value)
{
    setValue(value);
}

Variant::Variant(const std::string &value)
{
    setValue(value);
}

bool Variant::operator==(const Variant &o) const
{
    // Comparing to ourselve?
    if (this == &o)
    {
        return true;
    }
    
    if (valueType != o.valueType)
    {
        return false;
    }
    
    switch (valueType)
    {
        case Bool:
            return (boolValue == o.boolValue);
            
        case Int:
            return (intValue == o.intValue);
            
        case Double:
            return (doubleValue == o.doubleValue);
            
        case String:
            return (strValue == o.strValue);
            
        default:
            // This should never happen.
            assert(0);
            break;
    }
    
    return false;
}

void Variant::setValue(bool value)
{
    boolValue = value;
    valueType = Bool;
}

void Variant::setValue(int value)
{
    intValue = value;
    valueType = Int;
}

void Variant::setValue(double value)
{
    doubleValue = value;
    valueType = Double;
}

void Variant::setValue(const std::string &value)
{
    strValue = value;
    valueType = String;
}

bool Variant::getBool() const
{
    throwIfTypeMismatch(Variant::Bool, valueType);
    
    return boolValue;
}

int Variant::getInt() const
{
    throwIfTypeMismatch(Variant::Int, valueType);
    
    return intValue;
}

double Variant::getDouble() const
{
    throwIfTypeMismatch(Variant::Double, valueType);
    
    return doubleValue;
}

const std::string & Variant::getString() const
{
    throwIfTypeMismatch(Variant::String, valueType);
    
    return strValue;
}
