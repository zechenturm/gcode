#include <iostream>
#include <string>
#include <vector>

#include "gcodeParser.hpp"

const std::string sampleCode = "N1 G00#N2 G10#N3 G12#N4 G20#";

struct line_t
{
  unsigned int number;
  std::string command;
  std::string parameters;
};

GCodeParser gp;

int main()
{
  std::vector<std::string> lines;
  gp.splitLines(sampleCode, lines);
  for (auto line : lines)
  {
    std::cout << "line: " << line << std::endl;
    std::cout << "line number " << gp.parseLineNumber(line.substr(0,2), 0) << std::endl;
  }
  return 0;
}