#pragma once

#include <vector>
#include <string>

class GCodeParser
{
  public: 
    void parse(const std::string& gcode);
    void printLines();

  private:
    unsigned int lineNumber;
    std::vector<std::string> lines;    

    void splitLines(const std::string& code, std::vector<std::string>& buffer);
    int parseLineNumber(const std::string& text);
};