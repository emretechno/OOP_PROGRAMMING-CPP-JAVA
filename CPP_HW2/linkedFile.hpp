#ifndef LINKED_FILE_H
#define LINKED_FILE_H
#include "file.hpp"
#include "directory.hpp"
namespace MyOS{
class LinkedFile : public File{
 public:
      LinkedFile() :fileptr(nullptr) , target("") {}
      LinkedFile(File* rg ,const std::string& linked) : fileptr(rg) , target(linked) {}
      void set_file(File* rg) { fileptr = rg; }
      void set_target(const std::string& linked) { target = linked; }
      void cat() override ;
      void link();
      ~LinkedFile() override { if(fileptr !=nullptr)  delete fileptr; }

  private : 
      File* fileptr;
      std::string target; // the name of the file that is linked
};

}//namespace MyOs
#endif