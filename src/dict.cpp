#include <sstream>
#include <fstream>
#include <iostream>
#include "dict.hpp"

Dict::Dict ()
{
  file_string = "tmp.dic";
  //init Dict from default file if it exists
  Dict ("tmp.dic");
}

Dict::Dict (std::string file_str)
{
  std::ifstream file;
  file_string = file_str;
  file.open (file_str.c_str()); 
  if (file.is_open())
  {
    std::string line;
    while ( getline (file, line))
    {
      Word *fWord = new Word (line);
      words.push_back (fWord);
    }
    file.close();
  }
}

Dict::~Dict ()
{
}

bool Dict::CheckInDict (Word *fWord)
{
  for (unsigned int i=0;i<words.size();i++)
    if (*(words[i]) == *fWord)
      return true;
  return false;
}

unsigned int Dict::GetDictSize (void)
{
  return words.size();
}

Word *Dict::GetWord (unsigned int pos)
{
  return words[i];
}

void Dict::AddWord (Word *fWord)
{
  for (int i=0; i< words.size(); i++)
    if (*words[i] == *fWord)
    {
      std::cout << "Already exists! " << i << std::endl;
      return;
    }
  std::ofstream file;
  file.open (file_string.c_str(), std::ios::app);
  words.push_back (fWord);
  file << fWord->GetFirstLang () << " " << fWord->GetSecondLang () << " 0 0" << std::endl;
  file.close();
}
