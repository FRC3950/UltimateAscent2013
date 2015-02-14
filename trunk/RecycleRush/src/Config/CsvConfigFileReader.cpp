//
//  CsvConfigFileReader.cpp
//  RobotConfig
//
//  Created by Robert Saccone on 12/5/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#include "CsvConfigFileReader.h"

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <locale>
#include <map>
#include <sstream>
#include <vector>


#include "ConfigFileException.h"
#include "StringUtils.h"

#include "../Logger.h"
#include "../LoggingComponentDefs.h"


namespace
{
    const std::string BoolTypeKeyword = "bool";
    const std::string IntTypeKeyword = "int";
    const std::string DoubleTypeKeyword = "double";
    const std::string StringKeyword = "string";
    
    struct KeywordToVariantTypeMapIniter
    {
    	static const std::map<std::string, Variant::ValueType> init()
		{
    		std::map<std::string, Variant::ValueType> kwToTypeMap;
            kwToTypeMap.insert(std::pair<std::string, Variant::ValueType>(BoolTypeKeyword, Variant::Bool));
            kwToTypeMap.insert(std::pair<std::string, Variant::ValueType>(IntTypeKeyword, Variant::Int));
            kwToTypeMap.insert(std::pair<std::string, Variant::ValueType>(DoubleTypeKeyword, Variant::Double));
            kwToTypeMap.insert(std::pair<std::string, Variant::ValueType>(StringKeyword, Variant::String));
            
            return kwToTypeMap;
		}
    };

    const std::map<std::string, Variant::ValueType> keywordToValueTypeMap = KeywordToVariantTypeMapIniter::init();
    
    struct FalseValuesIniter
    {
    	static const std::vector<std::string> init()
		{
    		std::vector<std::string> falseValues;
    		falseValues.push_back("0");
    		falseValues.push_back("false");
    		falseValues.push_back("f");
    		
    		return falseValues;
		}
    };
    
    std::vector<std::string> falseBoolStrValues = FalseValuesIniter::init();
    
    void raiseErrorException(const char *msg,
                             const std::string &filename,
                             int lineNumber)
    {
        std::ostringstream strBldr;
        
        strBldr << msg << " on line " << lineNumber << "." << std::endl;
        strBldr << "Please correct the file - " << filename << std::endl;
        throw ConfigFileException(strBldr.str());
    }
    
    int convertStringToInt(const std::string &str,
                           const std::string &filename,
                           int sourceLineNumber)
    {
    	std::stringstream strStream(str);
    	
    	int result;
    	
    	strStream >> result;

    	if (strStream.fail())
    	{
			std::ostringstream strBldr;
			
			strBldr << "Couldn't convert " << str;
			strBldr << " to an integer on line " << sourceLineNumber << "." << std::endl;
			strBldr << "Please correct the file - " << filename << std::endl;

			throw ConfigFileException(strBldr.str());
		}
		
		return (result);
    }
    
    double convertStringToDouble(const std::string &str,
                                 const std::string &filename,
                                 int sourceLineNumber)
    {
    	std::stringstream strStream(str);
    	    	
    	double result;
    	    	
		strStream >> result;

		if (strStream.fail())
		{
			std::ostringstream strBldr;
			
			strBldr << "Couldn't convert " << str;
			strBldr << " to a double on line " << sourceLineNumber << "." << std::endl;
			strBldr << "Please correct the file - " << filename << std::endl;

			throw ConfigFileException(strBldr.str());
		}

		return result;
    }
    
    void setVariantFromData(Variant &variant,
                            const std::string &type,
                            const std::string &value,
                            const std::string &filename,
                            int lineNumber)
    {
        std::string normalizedTypeStr = type;
        
        // Normalize the type string by converting it to lowercase.
        std::transform(normalizedTypeStr.begin(), normalizedTypeStr.end(), normalizedTypeStr.begin(), ::tolower);

        std::map<std::string, Variant::ValueType>::const_iterator pos = keywordToValueTypeMap.find(normalizedTypeStr);
        
        if (pos != keywordToValueTypeMap.end())
        {
            Variant::ValueType valueType = pos->second;
            
            switch (valueType)
            {
            case Variant::Bool:
                {
                    bool boolValue = true;
                 
                    std::string normalizedValue = value;
                    
                    // Normalize the value string by converting it to lowercase.
                    std::transform(normalizedValue.begin(), normalizedValue.end(), normalizedValue.begin(), ::tolower);
                    
                    for (std::vector<std::string>::const_iterator it = falseBoolStrValues.begin();
                    	 it != falseBoolStrValues.end();
                    	 ++it)
                    {
                        if (*it == normalizedValue)
                        {
                            boolValue = false;
                            break;
                        }
                    }
                    
                    variant.setValue(boolValue);
                }
                return;
                
            case Variant::Int:
                    variant.setValue(convertStringToInt(value, filename, lineNumber));
                    return;
                
            case Variant::Double:
                    variant.setValue(convertStringToDouble(value, filename, lineNumber));
                    return;
                
            case Variant::String:
                variant.setValue(value);
                return;
                    
            default:  // This should never happen.
                assert(false);
                break;
            }
        }
        
        // Reaching here means an illegal value type was specified
        std::ostringstream strBldr;

        strBldr << "Unrecognized value type \'" << type << "\' ";
        strBldr << "specified on line number " << lineNumber << "." << std::endl;
        strBldr << " Please correct the file - " << filename << std::endl;
        throw ConfigFileException(strBldr.str());
    }
}

CsvConfigFileReader::CsvConfigFileReader(const std::string &filename)
    : filename(filename),
      tokens(3),
      lastLineProcessed(0),
      tokenCounter(0),      
      fileClosed(true)
{
    inFile.open(filename.c_str());
    if (inFile.fail())
    {
        // Failed to open the file.
        // Throw an exception.
        std::ostringstream strBldr;
        strBldr << "Couldn't open file: " << filename;
        throw ConfigFileException(strBldr.str());
    }
    
    fileClosed = false;
}

CsvConfigFileReader::~CsvConfigFileReader()
{
	
}

bool CsvConfigFileReader::getNextConfigItem(std::string &itemName, Variant &value)
{
    enum ParsingState
    {
        NeedNameField,
        NeedTypeFieldSep,
        NeedTypeField,
        NeedValueFieldSep,
        NeedValueField,
        NeedEOL,
        Done
    };
    
    ++lastLineProcessed;
    
    ParsingState state = NeedNameField;

    std::string token;
    
    tokens.clear();
    
    TokenType tokenType;
    
    while (state != Done)
    {
        tokenType = getNextToken(token);
        
        switch (state)
        {
        case NeedNameField:
            // Hit the end of file?
            if (tokenType == EndOfFile)
            {
                return false;
            }
                
            // Skip comment lines and blank lines.
            if ((tokenType == Comment) || (tokenType == EndOfLine))
            {
                ++lastLineProcessed;
                continue;
            }
            
            if (tokenType == ColumnContents)
            {
                tokens.push_back(token);
                state = NeedTypeFieldSep;
            }
            else
            {
                // Any other token is an error.
                raiseErrorException("Missing item name", filename, lastLineProcessed);
            }
            break;
                
        case NeedTypeFieldSep:
        case NeedValueFieldSep:
            if (tokenType == Comma)
            {
                state = (state == NeedTypeFieldSep) ? NeedTypeField : NeedValueField;
            }
            else
            {
                // Error should have received a comma.
                if (state == NeedTypeFieldSep)
                {
                    raiseErrorException("Missing comma separator after type field", filename, lastLineProcessed);
                }
                else
                {
                    raiseErrorException("Missing comma separator after value field", filename, lastLineProcessed);
                }
            }
            break;
                
        case NeedTypeField:
            if (tokenType == ColumnContents)
            {
                tokens.push_back(token);
                state = NeedValueFieldSep;
            }
            else
            {
                // Any other token is an error.
                raiseErrorException("Expected item type data column", filename, lastLineProcessed);
            }
            break;
                
        case NeedValueField:
            if ((tokenType == ColumnContents) && !token.empty())
            {
                tokens.push_back(token);
                state = NeedEOL;
            }
            else
            {
                raiseErrorException("Expected item value column", filename, lastLineProcessed);
            }
            break;
                
        case NeedEOL:
            if (tokenType == EndOfLine)
            {
                state = Done;
            }
            else
            {
                raiseErrorException("Expected eol after reading value field. Extraneous information.", filename, lastLineProcessed);
            }
            break;
                
        default:  // This should never happen.
            throw ConfigFileException("Unexpected Error.\n");
        }
    }
    
    if (state == Done)
    {

    	Logger::GetInstance()->Log(ConfigurationId, Logger::kTRACE, "CSVConfigFileReader: Parsed Line into \"%s\", \"%s\", \"%s\"",
    			                   tokens[0].c_str(), tokens[1].c_str(), tokens[2].c_str());

        setVariantFromData(value,
                           tokens[1],           // Type is in index one of the tokens array.
                           tokens[2],           // Value is in index two of the tokens array;
                           filename,
                           lastLineProcessed);
        
        itemName = tokens[0];
    }
    
    return true;
}

CsvConfigFileReader::TokenType CsvConfigFileReader::getNextToken(std::string &token)
{
    token.clear();
    
    bool insideDoubleQuote = false;
    
    TokenType tokenType = None;
    
    if (fileClosed)
    {
        return tokenType;
    }
    
    int nextChar;
    
    while ((nextChar = inFile.peek()) != EOF)
    {
    	char c = static_cast<char>(nextChar);
        if (tokenType == Comment)
        {
            inFile.get();
            token += c;
            
            if (c == '\n')
            {
                // End of comment line.
                return Comment;
            }
        }
        else if (insideDoubleQuote)
        {
            inFile.get();
            token += c;
            
            // Keep appending characters to the token until
            // either another double quote is found or until
            // eol is hit.
            if (c == '\"')
            {
                trim(token);
                
                // Found the matching end quote.
                return tokenType;
            }
            else if (c == '\n')
            {
                // Shouldn't hit a newline until after the matching double quote has been found.
                // error!
                std::ostringstream strBldr;
                
                strBldr << "Missing matching end \" ";
                strBldr << " on line " << lastLineProcessed << ".";
                strBldr << " Please correct." << std::endl;
                
                throw ConfigFileException(strBldr.str());
            }
        }
        else if ((c == '#') && (tokenType == None) && (tokenCounter == 0))
        {
            // Line is a comment line.
            tokenType = Comment;
            ++tokenCounter;
            inFile.get();
            token += c;
        }
        else if (c == '\"')
        {
            assert(!insideDoubleQuote);
            
            if (tokenType == None)
            {
                inFile.get();
                token +=c;
                tokenType = ColumnContents;
                ++tokenCounter;
                insideDoubleQuote = true;
            }
            else
            {
                // A double quote (") should always be
                // the first character in a column after
                // comma (excluding leading white space).
                // error!
                std::ostringstream strBldr;
                
                strBldr << "A \" must begin at the start of a column not in the middle.";
                strBldr << " Please correct line" << lastLineProcessed << " of the file." << std::endl;
                
                throw ConfigFileException(strBldr.str());
            }
        }
        else if (c == ',')
        {
            assert(!insideDoubleQuote);
            
            if (tokenType == None)
            {
                inFile.get();
                token += c;
                ++tokenCounter;
                return Comma;
            }
            
            // Have a token, return it.
            // Comma will be returned when the next
            // call for a token happens.
            trim(token);
            return tokenType;
        }
        else if (c == '\n')
        {
            assert(!insideDoubleQuote);
            
            if (tokenType == None)
            {
                inFile.get();
                token = '\n';
                tokenCounter = 0;
                return EndOfLine;
            }
            
            // Return the token as it stands.

            trim(token);
            return tokenType;
        }
        else
        {
            assert(!insideDoubleQuote);
            
            // Consume the character.
            inFile.get();
            
			bool isSpace = isspace(c) ? true : false;
            
            if (tokenType == ColumnContents)
            {
                token += c;
            }
            else if (tokenType == None)
            {
                if (!isSpace)
                {
                    tokenType = ColumnContents;
                    token += c;
                    ++tokenCounter;
                }
            }
        }
    }
    
    if (inFile.eof())
    {
        if (tokenType != None)
        {
            // The file is badly formed.
            std::ostringstream strBldr;
            strBldr << "Hit end of file prematurely. Error at line " << lastLineProcessed << ". Please check that the file is correctly formatted.";
            throw ConfigFileException(strBldr.str());
        }
        
        inFile.close();
        fileClosed = true;
        
        return EndOfFile;
    }

    // The file is badly formed.
    std::ostringstream strBldr;
    strBldr << "Error reading file at line " << lastLineProcessed << ". Please check that the file is correctly formatted.";
    throw ConfigFileException(strBldr.str());
}
