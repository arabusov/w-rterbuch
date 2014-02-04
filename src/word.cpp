#include <string>
#include <sstream>
#include <iostream>
#include "word.hpp"

Word::Word (std::string first, std::string second, int n_t, int n_p_t)
{
  first_lang = first; second_lang = second; num_tests = n_t; num_passed_tests = n_p_t;
}

inline bool Word::space (char ch)
{
  return (ch==' ')||(ch=='\t');
}

Word::Word (std::string line)
{
  unsigned int i=0;
  std::string first_word, second_word;
  while ((i<line.length())&&(!this->space(line[i]))) i++;
  first_lang = line.substr (0,i);
  while ((i<line.length())&&(this->space(line[i]))) i++;
  int start_pos = i;
  while ((i<line.length())&&(!this->space(line[i]))) i++;
  second_lang = line.substr (start_pos,i-start_pos);
  while ((i<line.length())&&(this->space(line[i]))) i++;
  std::stringstream ss;
  start_pos = i;
  while ((i<line.length())&&(!this->space(line[i]))) i++;  
  ss << line.substr (start_pos, i-start_pos);
  ss >> num_tests;
  ss << line.substr (i,line.length()-i);
  ss >> num_passed_tests;
}

Word:: Word ()
{
  Word ("","",0,0);
}

Word::~Word () {;}


bool Word::operator== (const Word & fWord) const
{
  return (!this->first_lang.compare(fWord.first_lang))&&
  (!this->second_lang.compare(fWord.second_lang));
}
  
bool Word::operator!= (const Word & fWord) const
{
  return !(*this == fWord);
}
