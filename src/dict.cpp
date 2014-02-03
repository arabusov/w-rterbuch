#include <sstream>
#include <fstream>
#include <iostream>
#include "dict.hpp"

Dict::Dict ()
{
  file.open ("tmp.dic",std::ios::in);
  if (!file.is_open())
  {
    file.open ("tmp.dic", std::ios::out);
    file.close();
    file.open ("tmp.dic", std::ios::in);
  }
  //init Dict from default file if it exists
  Dict (file);
}

Dict::Dict (std::string file_str)
{
  file.open (file_str.c_str(), std::ios::in); 
  if (file.is_open())
  {
    std::string line;
    while ( getline (file, line))
    {
      Word *fWord = new Word (line);
      words.push_back (fWord);
    }
  }
}

Dict::~Dict ()
{
  if (file.is_open())
    file.close();
}

bool Dict::CheckInDict (Word *fWord)
{
  for (unsigned int i=0;i<words.size();i++)
    if (*(words[i]) == *fWord)
      return true;
  return false;
}

void Dict::AddWord (Word *fWord)
{
  words.push_back (fWord);
}
