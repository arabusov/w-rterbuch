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
  std::stringstream ss;
  ss << line;
  ss >> first_lang >> second_lang >> num_tests >> num_passed_tests;
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
