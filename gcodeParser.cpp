#include "gcodeParser.hpp"

#include <iostream>

int GCodeParser::parseLineNumber(const std::string& text)
{
  switch (text.length())
  {
    case 0:
      // there is no explicit line number given
      return ++lineNumber;
      // erroneus line number
      case 1:
      return ++lineNumber; //TODO return some sort of error?
    default: 
      const int length = text.length() - 1; // first letter is 'N' so don't count that
      int lineNumber = 0;
      int multiplier = 1;
      for (int i = 0; i < length; i++)
      {
        lineNumber += (text[length-i]-'0')*multiplier;
        multiplier *= 10;
      }
      return lineNumber;
  }
}

void GCodeParser::splitLines(const std::string& code)
{
  constexpr char delim = '#';
  int str_end = 0, str_start = 0;
  while (str_end != -1)
  {
    str_end = code.find(delim, str_start);
    std::cout << str_start << ":" << str_end << std::endl;
    line_t line;
    line.command = code.substr(str_start, str_end-str_start);
    std::cout << code.substr(str_start, str_end-str_start) << std::endl;
    line.number = parseLineNumber(line.command.substr(0, line.command.find_first_of(' ')));
    line.parameters = ""; //TODO split line correctly
    lines.push_back(line);
    str_start = str_end+1;
  }
  if (lines.back().command == "")
  {
    lines.pop_back();
  }
}

void GCodeParser::parse(const std::string& gcode)
{
  splitLines(gcode);

}

void GCodeParser::printLines()
{
  for (auto line : lines)
  {
    std::cout << "line: " << line << std::endl;
  }
}

std::ostream& operator << (std::ostream& os, const GCodeParser::line_t& line)
{
  os << line.number << ": " << line.command << " " << line.parameters;
  return os;
}