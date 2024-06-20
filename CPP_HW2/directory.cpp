#include "directory.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
namespace MyOS{
Directory :: Directory()  : File() { }

  void Directory ::  mkdir(){
 //also should loading the files in the directory
        if(is_find()) throw std::runtime_error("The directory is already exist");
        size_t dotpos = name.find_last_of('.');
        if(dotpos != std::string :: npos && dotpos < name.size()-1) throw std::runtime_error("Invalid extension");
        else {
        std::ofstream inputfile(MYDISK,std::ios::app);
        if(!inputfile.is_open())  throw std::runtime_error("The file could not be opened");
        inputfile << path<<  name <<"#"<<get_current_date()<<"^@\n"; // THERE ARE JUST SYMBOLS THAT I USE TO SPLIT THE FILE
        inputfile.close();
        std::ofstream inpfile(MYDISK,std::ios::app);
        inpfile << path  << name<<"/"<< ".#" <<get_current_date()<<"^@\n";
        inpfile << path <<name<<"/"<<  "..#"<<get_creation_date()<<"^@\n";
        inpfile.close();
       
        files.push_back(this);
       
        }
  }
 

void Directory :: rmdir(){

  if(!is_find()) throw std::runtime_error("The directory is not found"); // exceptions
  if(!is_directory()) throw std::runtime_error("The file is not directory.Use rm command for regularfile.");
  if(islinked_directory(name)==0) throw std::runtime_error("The linked is regular file.Use rm command for regularfile.");
  std::ifstream inputfile(MYDISK);
  if(!inputfile.is_open())  throw std::runtime_error("The file could not be opened");
  
  std::ofstream outputfile("temp.txt");
  std::string line;
  std::string temp = path + name;
  while(getline(inputfile,line)){
    if(line.substr(0,temp.size()) != temp){
      outputfile << line << std::endl;
    }
  }
  inputfile.close();
  outputfile.close();
  std::remove(MYDISK);
  std::rename("temp.txt",MYDISK);

}
void Directory :: ls() {  //# TO DO -> FIND THE REAL TIME OF THE FILE
  // print the files in the current directory
      MyOS :: RegularFile* rg= new MyOS :: RegularFile();
    std::ifstream inputfile(MYDISK);
    if(!inputfile.is_open())   throw std::runtime_error("The file could not be opened");
    std::vector<std::string>lines;
    std::string line;
    int flag;
    while(getline(inputfile,line)) lines.push_back(line);
    inputfile.close();

    for(const auto& line : lines){
        flag =0;
      if(line.substr(0,path.size()) == path){
            int len = path.size();
            for(std::string:: size_type i = path.size(); i < line.size(); i++) {
                if(line[i] == '/') { // directory ise  bu 
                    len = i;
                    flag = 1;
                    break;
                } 
            } // len is the index of the last '/' character
    if(!flag){
        size_t i = path.size();
        while(line[i] !='#') i++;
        name = line.substr(len,i-path.size());
       size_t j =i;
       while(line[j] != '^') j++; // content
       date = line.substr(i+1,j-i-1);
       if(line.size() == j+1 ) continue;
        size_t k = j;
        while(line[k] !='@') k++;
        rg-> clear_content(); // clear the content of the regular file
        for(size_t s =j+1 ; s<k; s++){
         rg->set_content(line[s]);
        }  files.push_back(this);

     help_list(rg);
        }
      }
   }  
    delete rg;
}

void Directory :: ls_recursive(std:: ifstream& inputfile){

         MyOS :: RegularFile* rg= new MyOS :: RegularFile();
        std::string line;
        if(getline(inputfile,line)) {
       if(line.substr(0,path.size()) == path){
        size_t i = path.size();
        while(line[i] !='#') i++;
        name = line.substr(path.size(),i-path.size());
        size_t j =i;
        while(line[j] != '^') j++; // content
        date = line.substr(i+1,j-i-1);
        if(line.size() == j+1 ) return;
        size_t k = j;
        while(line[k] !='@') k++;
        rg-> clear_content(); // clear the content of the regular file
        for(size_t s =j+1 ; s<k; s++)
        rg->set_content(line[s]);   
        files.push_back(rg);
        help_list(rg);
        }
        ls_recursive(inputfile);
      }
      else { 
           delete rg;
           return;
      }
}

 std::string Directory :: get_creation_date()const{

   std:: ifstream inputfile(MYDISK);
   std::string line;
 while(getline(inputfile,line)){
     if(line.substr(0,path.size() +1) ==path +"."){
            int i = path.size()+1;
            while(line[i] !='#') i++;
            int j =i;
            while(line[j] !='^') j++;
            
            inputfile.close();
            return line.substr(i+1,j-i-1);
     }
 }
    inputfile.close();
    return "";
}

void Directory :: help_list(RegularFile* rg )const {
      if(date[0] == 'l') std :: cout << "L " << name << "          "<< date.substr(1,date.size())<< "   " << rg->calculate_byte() << "  byte" <<std:: endl;
      else if(date[0] =='q')   std :: cout << "L " << name << "          "<< date.substr(1,date.size())<<std:: endl;
      else  if(!is_directory())       std::cout<<"F "<< name << "       " << date << "     " << rg->calculate_byte()<< " byte" << std:: endl;
      else  std :: cout << "D " << name << "          "<< date <<std:: endl; 
}

  void Directory:: cd(){
     if(name==" " || name =="/" || name == "./MYOS/"  || name == "/MYOS/") {
        path = "./MYOS/";
        std::cout <<path <<"\n";
        return;
    }

   else if(name == "." || name =="./") {
        std::cout <<path <<"\n";
         return;
         }

   else if(name== ".."){
      if(path =="./MYOS/") throw std::runtime_error("You are already in the root directory");
          int i = path.size()-2;
          while(path[i] != '/') i--;
          path = path.substr(0,i+1);
          std::cout <<path <<"\n";
          return;
     }
       std::string old_path = path;
   if(!is_directory()) throw std::runtime_error("The file is not directory");
   std::string backup_path = path;
   
   if(name.find('/') !=std::string::npos){ // iF INPUT LIKE cd /MYOS/mydir/mydir2 ...
    std::vector<std::string> pathtokens;
    std::istringstream iss(name);
    std::string part;
    while(std::getline(iss,part,'/')) pathtokens.push_back(part);

    for(const auto& nam : pathtokens){
        name = nam;
        if(is_find()) path = path + name + "/";
        else {
            path = backup_path;
            throw std::runtime_error("The directory is not found");
        }
    }
      return;
   }
     
   if(!islinked_directory(name)) throw std::runtime_error("The linked " +name + " is not directory");
   if(!is_find()) throw std::runtime_error("The directory is not found " + name);
   else   path +=name+ "/";   
}

Directory :: ~Directory() { 
    for(const auto& fileptr : files) delete fileptr;
    files.clear();
}


} // end of namespace MyOS