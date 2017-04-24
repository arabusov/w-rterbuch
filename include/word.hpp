#ifndef word_hpp
#define word_hpp 1
#include <string>

class Word
{
  private:
    std::string first_lang, second_lang;
    int num_tests, num_passed_tests;
    bool space (char ch);
  public:
    Word ();
    Word (std::string first, std::string second, int n_t, int n_p_t);
    Word (std::string line);
    ~Word ();
    bool operator== (const Word & fWord) const;
    bool operator!= (const Word & fWord) const;
    inline void Passed () {num_tests++; num_passed_tests++;};
    inline void Failed () {num_tests++;};
    inline std::string GetFirstLang (void) const { return first_lang; }
    inline std::string GetSecondLang (void) const { return second_lang; }
    inline unsigned int GetNumTests (void) const { return num_tests; }
    inline unsigned int GetNumPassedTests (void) const { return num_passed_tests; }
};
#endif
