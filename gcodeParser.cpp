#include "gcodeParser.hpp"

#include <iostream>
#include <algorithm>

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
    // command starts here, ie after line number: if line number is explicitly given, find first space, otherwise start at 0
    const int cmd_start = code[str_start] == 'N' ? code.find_first_of(' ', str_start)+1 : str_start;
    const int param_start = std::min(code.find_first_of(' ', cmd_start), code.find_first_of(delim, cmd_start)) ;
    line.command = code.substr(cmd_start, param_start-cmd_start);
    line.number = parseLineNumber(code.substr(str_start,cmd_start-str_start-1));
    std::cout << param_start << std::endl;
    line.parameters = (param_start > 0 && param_start < str_end) ? code.substr(param_start+1, str_end-param_start-1) : "";
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
  os << line.number << ": " << line.command << "<" << line.parameters << ">";
  return os;
}