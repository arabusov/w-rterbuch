#include <iostream>
#include <string>
#include <sstream>
//#include "dict.hpp"

int main (int argc, char ** argv)
{
  std::string helpstr =
  "\tWörterbuch ver. 0.01\n\
Usage: worterbuch ACTION [operands]\n\
Current actions:\n\
-t, --test: run test;\n\
-a, --add: add word to dictionary, arguments are FIRST_LANG SECOND_LANG DICT_FILE\n";
  std::stringstream ss;
  switch (argc)
  {
    case 1: 
      std::cout << helpstr << std::endl;
      break;
    case 2:
      ss << argv[1];
      if (!ss.str().compare("-t") || !ss.str().compare ("--test"))
        //run test here.
        std::cout << "-t" << std::endl;
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
        ;
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

