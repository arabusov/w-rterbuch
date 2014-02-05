#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include "dict.hpp"
#include "word.hpp"
#define __DEBUG__ 1
#define __LINUX__ 1

inline int run_test (char * str)
{
  Dict *dict = new Dict (str);
  unsigned int dict_size = dict->GetDictSize ();
  if (!dict_size)
  {
    std::cerr << "Empty dictionary in " << str <<" file! Aborted." << std::endl;
    return -4;
  }
  /*
   * Now we should create consequence of random words for the test 
   * it should be wise. Simple words should be skipped oftener than hard words.
   * Simple alhorithm: probability of the word's skiping is proportional to ratio num_passed_tests
   * and num_tests. So, now we shall release usual Monte-Carlo simulation method. Good luck!
   */
  #if __LINUX__
  unsigned int randomize;
  std::ifstream rand_file;
  rand_file.open ("/dev/random");
  rand_file.read(reinterpret_cast<char*>(&randomize), sizeof(randomize)); 
  rand_file.close();
  std::default_random_engine generator(randomize);
  #else
  std::default_random_engine generator();
  #endif
  std::uniform_real_distribution<double> real_distribution(0.0,1.0); //flat distribution
  std::uniform_int_distribution<unsigned int> int_distribution (0,dict_size-1);
  double real_rand;
  unsigned int int_rand;
  double probability;
  do
  {
    real_rand = real_distribution (generator);
    int_rand = int_distribution (generator);
    if (dict->GetWord(int_rand)->GetNumTests ()!= 0)
      probability = (double)dict->GetWord(int_rand)->GetNumPassedTests()/
                            (double)(dict->GetWord(int_rand)->GetNumTests()+1);//even in case 100:100 there
                                                                              //should be nonzero
                                                                              //probability.
    else
      probability = 0;
  } while (real_rand < probability);
  unsigned int choose_lang = int_distribution (generator) % 2; //Bug can be possible when DictSize == 1,
                                                               //but nowbody will use so short
                                                               //dicts.
  std::string test_str;
  Word *test_word;
  if (choose_lang)
  {
    std::string base_str = dict->GetWord(int_rand)->GetFirstLang ();
    std::cout << base_str << ": ";
    std::cin >> test_str;
    test_word = new Word (base_str, test_str, 0,0);
  }
  else
  {
    std::string base_str = dict->GetWord(int_rand)->GetSecondLang ();
    std::cout << base_str << ": ";
    std::cin >> test_str;
    test_word = new Word (test_str, base_str, 0,0);
  }
  int wordID = dict->GetWordID (test_word);
  if (0 <= wordID )
  {
    std::cout << "Passed." << std::endl;
    dict->GetWord (wordID)->Passed ();
  }
  else
  {
    std::cout << "Failed." << std::endl;
    dict->GetWord (int_rand)->Failed ();
  }
  delete dict;
  return 0;
} 
  

int main (int argc, char ** argv)
{
  std::string helpstr =
  "\tWörterbuch ver. 0.01-rc1\n\
Usage: worterbuch ACTION [operands] dictionary_file\n\
Current actions:\n\
-t, --test: run test, argument is dictionary_file;\n\
-a, --add: add word to dictionary, arguments are FIRST_LANG SECOND_LANG dictionary_file\n";
  std::stringstream ss;
  switch (argc)
  {
    case 1: 
      std::cout << helpstr << std::endl;
      break;
    case 3:
      ss << argv[1];
      if (!ss.str().compare("-t") || !ss.str().compare ("--test"))
        //run test here.
        return run_test (argv[2]);
      else
        if (!ss.str().compare("--add") || !ss.str().compare ("-a"))
        {
          std::cerr << "Too few operands!" << std::endl << "Aborted." << std::endl;
          return -1;
        }
        else
          if (!ss.str().compare("--help") || !ss.str().compare ("-h"))
            std::cout << helpstr;
          else
          {
            std::cerr << "Unrecognized action!" << std::endl << "Aborted." << std::endl;
            return -3;
          }
      break;
    case 5:
      ss << argv[1];
      if (!ss.str().compare("-t") || !ss.str().compare ("--test"))
      {
        std::cerr << "Too many operands!" << std::endl << "Aborted." << std::endl;
        return -2;
      }
      if (!ss.str().compare ("-a") || !ss.str().compare ("--add"))
      //run adding here
      {
        Word *word = new Word (argv[2],argv[3],0,0);
        Dict *dict = new Dict (argv[4]);
        dict->AddWord (word);
        delete dict;
      }
      else
      {
        std::cerr << "Unrecognized action!" << std::endl << "Aborted." << std::endl;
        return -3;
      }
      break;
    default:
      std::cerr << "Illegal expression. Try -h or --help" << std::endl << "Aborted." << std::endl;
    }
  return 0;
}

