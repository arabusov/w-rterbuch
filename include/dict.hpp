#ifndef dict_hpp
#define dict_hpp 1

#include <vector>
#include <fstream>
#include "word.hpp"

class Dict
{
  private:
    std::vector<Word*> words;
    std::string file_string;
  public:
    Dict ();
    Dict (std::string filename);
    ~Dict ();
    bool CheckInDict (Word *fWord);
    int GetWordID (Word *fWord);
    void AddWord (Word *fWord);
    Word *GetWord (unsigned int pos);
    unsigned int GetDictSize (void);
};
#endif
