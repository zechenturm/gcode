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

void GCodeParser::splitLines(const std::string& code, std::vector<std::string>& buffer)
{
  constexpr char delim = '#';
  int str_end = 0, str_start = 0;
  while (str_end != -1)
  {
    str_end = code.find(delim, str_start);
    std::cout << str_start << ":" << str_end << std::endl;
    buffer.push_back(code.substr(str_start, str_end-str_start));
    str_start = str_end+1;
  }
  if (buffer.back() == "")
  {
    buffer.pop_back();
  }
}

void GCodeParser::parse(const std::string& gcode)
{
  splitLines(gcode, lines);

}

void GCodeParser::printLines()
{
  for (auto line : lines)
  {
    std::cout << "line: " << line << std::endl;
    std::cout << "line number " << parseLineNumber(line.substr(0,2)) << std::endl;
  }
}