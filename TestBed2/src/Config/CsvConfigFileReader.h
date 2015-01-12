//
//  CsvConfigFileReader.h
//  RobotConfig
//
//  Created by Robert Saccone on 12/5/14.
//  Copyright (c) 2014 Robert Saccone. All rights reserved.
//

#ifndef __RobotConfig__CsvConfigFileReader__
#define __RobotConfig__CsvConfigFileReader__

#include <fstream>
#include <string>
#include <vector>

#include "ConfigFileReader.h"
#include "Variant.h"

class CsvConfigFileReader : public ConfigFileReader
{
public:
    CsvConfigFileReader(const std::string &filename);
    virtual ~CsvConfigFileReader();
    
    virtual bool getNextConfigItem(std::string &itemName, Variant &value);
    
private:
    enum TokenType
    {
        None,
        Comment,
        ColumnContents,
        Comma,
        EndOfLine,
        EndOfFile
    };
    
    TokenType getNextToken(std::string &token);
    
    std::ifstream inFile;               // Input file to read from.
    std::string filename;               // Holds the filename.
    std::vector<std::string> tokens;    // Used to store token that
                                        // are created when parsing a
                                        // line.
    

    
    int lastLineProcessed;              // Line number of the last line
                                            // in the file that was processed.
    int tokenCounter;                   // Counts the number of tokens on the current line.
    
    bool fileClosed;                // Indicates whether the file is open or closed.
};

#endif /* defined(__RobotConfig__CsvConfigFileReader__) */
