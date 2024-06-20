
#include "MyShell.hpp"

namespace MyShell{

 //DYNAMIC CASTING IS THE KEY OF THE PROJECT

 void Shell :: run(const std::vector<MyOS::File*>&fl , std::string& command){
      
       if( command == "ls -r" || command == "ls -R"){  // if recursion 
            //space exceptions should be thought
             std::ifstream inputfile(MYDISK);
            if(!inputfile.is_open()) {
                throw std::runtime_error("The file could not be opened");
            }
            if(MyOS::Directory* dtr = dynamic_cast<MyOS :: Directory*> ( fl[0])){ //DOWNCASTING
             dtr->ls_recursive(inputfile);
             inputfile.close();
            }
        }
        else if(command.substr(0,2) ==  "ls") {
            if(MyOS:: Directory* dtr = dynamic_cast<MyOS:: Directory*> ( fl[0])){ //DOWNCASTING  
            dtr->ls();
            } 
            }
             

           else if(command.substr(0,5) == "rmdir"){
            if(command[5] != ' ') {
                throw std::runtime_error("The command is not valid");
                return;
            }
            set_command(command,6);
            if(MyOS :: Directory* dtr = dynamic_cast<MyOS:: Directory*> ( fl[0])) //DOWNCASTING
            {
            dtr->set_name(filename);
            dtr->rmdir();
            } else throw std::runtime_error("The file is not directory.Invalid extension."); //DOWNCASTING UNSECCESFUL  
            
         }

        else if(command.substr(0,2) == "rm"){
            
            if(command[2] != ' ') {
                std::cout << "The command is not valid" << std::endl;
                return;
            }
             set_command(command,3);
             if(MyOS :: Directory* dtr = dynamic_cast<MyOS :: Directory*>(fl[0])){ //DOWNCASTING
                dtr->set_name(filename);
                dtr->rm();
             } else { throw std::runtime_error("Unsuccessful downcasting"); }
        }
        else if(command.substr(0,5) =="mkdir"){
            if(command[5] != ' ') {
                throw std::runtime_error("The command is not valid");
                return;
            }
           set_command(command,6);
          if(MyOS:: Directory* dtr = dynamic_cast<MyOS :: Directory*> ( fl[0])){ //DOWNCASTING
           dtr->set_name(filename);
           dtr->mkdir();
           } else throw std::runtime_error("The file is not directory.Invalid extension."); //DOWNCASTING UNSECCESFUL
        }

        else if(command.substr(0,2) == "cd"){
   if(MyOS :: Directory* dtr = dynamic_cast<MyOS:: Directory*>(fl[0])){

        if(command =="cd" || command=="cd "){ dtr->set_name(" "); dtr->cd(); return; }
        else {  
         set_command(command,3);
         dtr->set_name(filename);
         dtr->cd();    
          } 

        } else throw std::runtime_error("The file is not directory.Invalid extension."); //DOWNCASTING UNSECCESFUL
      }
         else if(command.substr(0,3) == "cat") {
            if(command[3] != ' ') {
                throw std::runtime_error("The command is not valid");
                return;
            }
         
            MyOS :: RegularFile* rgfile = new MyOS :: RegularFile();  
            set_command(command,4);
            rgfile->set_name(filename); //FILENAME IS LINK
            rgfile->set_path(fl[0]->get_path()); //Directory* has path   
            MyOS :: LinkedFile* link = new MyOS :: LinkedFile(rgfile,fl[2]->get_name()); /*Linkedfile* has the name */
            link->cat();
           
           if(link != nullptr) delete link;
         }

         else if(command.substr(0,2) =="cp"){
            if(command[2] != ' ') {
                throw std::runtime_error("The command is not valid");
                return;
            }
             set_command(command,3);
            fl[0]->cp(filename);
 
         }
         else if(command.substr(0,4) =="link"){
            if(command[4] != ' ') {
                throw std::runtime_error("The command is not valid");
                return;
            }
             set_command(command,5);
             std::string linkname;
             int i  = 0;
                while(filename[i] != ' ') i++;
                std::string source= filename.substr(0,i);
        linkname = filename.substr(i+1,filename.size()-1);
        if(MyOS :: LinkedFile* lptr =dynamic_cast<MyOS :: LinkedFile*> (fl[2])){ //DOWNCASTING
           lptr->set_name(source);
           lptr->set_path(fl[0]->get_path());
           lptr->set_target(linkname);
           lptr->link();
        }
          
         }
          else if(command == "clear") fl[0]->clear_command();

          else if(command == "pwd") fl[0]->pwd();
          else if(command =="help") help();
         
    }

    void Shell:: set_command(const std::string& command, int index){
         int comsize = command.size();
             std::string temp = command.substr(index,comsize-1);
             int i = 0;
             while(temp[i] == ' ') i++;
             temp = temp.substr(i,comsize-1);
                filename = temp;
    }
    void Shell :: help() const {
      std::cout << "\nls : List the files in the current directory.\n";
      std::cout << "ls -r : List the files in the current directory recursively.\n";
      std::cout << "cd : Change the current directory to the given directory. You can cd more than one path such as :(cd mydir/mydir2 )\n";
      std::cout << "cp : Copy the given file or directory to the current directory.(Ex :cp /MYOS/mydir or , cp /MYOS/emre.txt )\n";
      std::cout << "mkdir : Create a new directory in the current directory.\n";
      std::cout << "rmdir : Remove the given directory from the current directory.No path input here.\n";
      std::cout << "rm : Remove the given file from the current directory.No path input here.\n";
      std::cout << "pwd : Print the current directory.\n";
      std::cout << "link : Create a link to the given file or directory  in the current directory.(Ex :link /MYOS/mydir mylink )\n";
      std::cout << "cat: Prints the content of the given file.(Ex :cat a.cpp )\n";
      std::cout << "clear: Clears the screen.\n";
      std::cout << "q : Quits the shell.\n";
    }

     
 
Shell :: ~Shell() { }

}


