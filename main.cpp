#include <iostream>
#include <string>
#include <vector>

const std::string sampleCode = "N1 G00#N2 G10#N3 G12#N4 G20#";

struct line_t
{
  unsigned int number;
  std::string command;
  std::string parameters;
};

int parseLineNumber(const std::string& text, int lastLineNum)
{
  switch (text.length())
  {
    case 0:
      // there is no explicit line number given
      return ++lastLineNum;
      // erroneus line number
      case 1:
      return ++lastLineNum; //TODO return some sort of error?
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
    std::cout << "line number " << parseLineNumber(line.substr(0,2), 0) << std::endl;
  }
  return 0;
}