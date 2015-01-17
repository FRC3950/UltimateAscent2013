#ifndef RobotConfig_Variant_h
#define RobotConfig_Variant_h

#include <stdexcept>
#include <string>
#include <iostream>
#include <assert.h>

#include "PlatformDefs.h"

// Thrown when the variant's type doesn't match what is expected by the user.
class VariantTypeMismatchException : public std::runtime_error
{
public:
    explicit VariantTypeMismatchException(const std::string& what_arg)
    : runtime_error(what_arg)
    {
        
    }
    
    explicit VariantTypeMismatchException(const char *what_arg)
    : runtime_error(what_arg)
    {
        
    }
    
    VariantTypeMismatchException(const VariantTypeMismatchException& o) NOEXCEPT
    : runtime_error(o)
    {
        
    }
    
    VariantTypeMismatchException& operator=(const VariantTypeMismatchException& rhs) NOEXCEPT
    {
        runtime_error::operator=(rhs);
        
        return *this;
    }
    
    virtual ~VariantTypeMismatchException() NOEXCEPT
    {
        
    }
};


class Variant {
public:
    enum ValueType
    {
        None,       // Variant isn't storing anything.
        Bool,       // Variant is storing a boolean.
        Int,        // Variant is storing an int.
        Double,     // Variant is storing a double.
        String      // Variant is storing a string.
    };
    
    explicit Variant();
    explicit Variant(int value);
    explicit Variant(double value);
    explicit Variant(bool value);
    explicit Variant(const std::string &value);
    
    Variant(const Variant& o);
    Variant& operator=(const Variant &rhs);
    
	ValueType getType() const
    {
        return valueType;
    }
    
    void setValue(bool value);
    void setValue(int value);
    void setValue(double value);
    void setValue(const std::string &value);
    
    bool getBool() const;
    int getInt() const;
    double getDouble() const;
    const std::string &getString() const;
    
    bool operator==(const Variant &o) const;
    
private:
    void copy(const Variant &other);
    
    ValueType valueType;
    union {
        bool boolValue;
        int intValue;
        double doubleValue;
    };
    
    // Can't put classes inside unions.
    std::string strValue;
};

#endif
