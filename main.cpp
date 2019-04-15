#include <iostream>
#include <string>
#include <vector>

const std::string sampleCode = "N1 G00#N2 G10#N3 G12#N4 G20#";

struct line_t
{
  unsinged int number;
  std::str command;
  std::str parameters;
}

void splitLines(const std::string& code, std::vector<std::string>& buffer)
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

int main()
{
  std::vector<std::string> lines;
  splitLines(sampleCode, lines);
  for (auto line : lines)
  {
    std::cout << "line: " << line << std::endl;
  }
  return 0;
}