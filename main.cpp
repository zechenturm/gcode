#include <iostream>
#include <string>
#include <vector>

#include "gcodeParser.hpp"

const std::string sampleCode = "N1 G00 X43#N2 G10#N3 G12 Z10#N4 G20#";

GCodeParser gp;

int main()
{
  gp.parse(sampleCode);
  gp.printLines();
  
  return 0;
}