#include "file.hpp"
#include "directory.hpp"
#include <sstream>
#include "regularfile.hpp"
#include "MyShell.hpp"
#include "linkedFile.hpp"
int main(){

     std::vector<MyOS :: File*> fl;
     fl.push_back(new MyOS:: Directory());
     fl.push_back(new MyOS :: RegularFile());
     fl.push_back(new MyOS :: LinkedFile());
     MyShell :: Shell shell;
    std::string command;
    std::cout <<"Welcome to my shell.Note that the root directory is /MYOS/ in this shell.\n";
    std::cout <<"Please write help to see the commands.\n\n";
  do {
    try{
         std::cout << "MyShell: "<< fl[0]->get_path() <<" ~% > ";
         std::getline(std::cin,command);
        shell.run(fl,command);

         
      } catch(const std::exception& e ){
        std::cerr << "Exception: " << e.what() << std::endl; 
    }

  }while(command != "q" && command != "e" && command!="Q");  

    return 0;
}