#pragma once

#include <vector>
#include <string>

class GCodeParser
{
  public: 
    void parse(const std::string& gcode);
    void printLines();

  private:

  struct line_t
  {
    unsigned int number;
    std::string command;
    std::string parameters;
  };
    unsigned int lineNumber;
    std::vector<line_t> lines;    

    void splitLines(const std::string& code);
    int parseLineNumber(const std::string& text);

    friend std::ostream& operator << (std::ostream& os, const line_t& line);
};