#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
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
  std::ofstream file;
  file.open (file_string.c_str());
  for (auto &it: words)
  {
    file << it->GetFirstLang () << "\t" << it->GetSecondLang () << "\t"
      << it->GetNumTests () << "\t" << it->GetNumPassedTests () 
      << std::endl;
    delete it;
  }
  words.clear();
  file.close();
}

bool Dict::CheckInDict (Word *fWord)
{
  return (std::find (words.begin(), words.end(), fWord) != words.end());
}

int Dict::GetWordID (Word *fWord)
{
  for (unsigned int i=0;i<words.size();i++)
    if (*(words[i]) == *fWord)
      return i;
  return -1;
}

unsigned int Dict::GetDictSize ()
{
  return words.size();
}

Word *Dict::GetWord (unsigned int pos)
{
  return words[pos];
}

void Dict::AddWord (Word *fWord)
{
  if (CheckInDict (fWord))
  {
    std::cout << "Already exists! "<< fWord->GetFirstLang() << " " << fWord->GetSecondLang() << std::endl;
  }
  else
  {
    words.push_back (fWord);
  }
}

