#ifndef dict_hpp
#define dict_hpp 1

#include <vector>
#include <fstream>
#include "word.hpp"

class Dict
{
  private:
    std::vector<Word*> words;
    std::fstream file;
  public:
    Dict ();
    Dict (std::string filename);
    ~Dict ();
    bool CheckInDict (Word *fWord);
    void AddWord (Word *fWord);
};
#endif
