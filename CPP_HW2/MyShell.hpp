#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <string>
#include <iostream>
#include "file.hpp"
#include "directory.hpp"
#include <sstream>
#include "regularfile.hpp"
#include "linkedFile.hpp"
namespace MyShell{

class Shell {
    public :
      Shell() : filename("") {}
      void run(const std::vector<MyOS::File*>&fl , std::string& command);
      void set_command(const std::string& command, int index);
      ~Shell();
      void help() const ;
  private :
        std:: string filename;
};
}
#endif