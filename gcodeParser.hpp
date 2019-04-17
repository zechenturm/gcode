#pragma once

#include <vector>
#include <string>

class GCodeParser
{
  public: 
    void splitLines(const std::string& code, std::vector<std::string>& buffer);
    int parseLineNumber(const std::string& text);

  private:
    unsigned int lineNumber;

};