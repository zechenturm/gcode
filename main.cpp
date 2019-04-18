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
  gp.parse(sampleCode);
  gp.printLines();
  
  return 0;
}