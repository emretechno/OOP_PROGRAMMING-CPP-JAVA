
#include "linkedFile.hpp"

namespace MyOS{

void LinkedFile :: cat() {
    if(fileptr== nullptr){
        std::cerr << "File not found" << std::endl;
        return;
    } 
    if(RegularFile* rg = dynamic_cast<RegularFile*> (fileptr )){
        rg->cat();
    } else  throw  std::runtime_error("The file is not regular file");
   
}

void LinkedFile :: link(){ 
      int type =0 ;
      std::string origin_name = name;

      size_t l = name.find_last_of('/');
      std::string pure_name = name.substr(l+1,name.size());
       if(pure_name.find('.') !=std::string::npos) type =1;
       if(name[0] !='.' && name[0] =='/') name = "." + name;
 
    if(name.find('/')==std::string::npos) throw std::runtime_error("You should enter the whole path.(Ex : /MYOS/.../filename)");
  
    std :: ifstream infile(MYDISK);
    if(!infile.is_open()) throw std::runtime_error("The mydisk.txt could not be opened");
      std::string line , sourcename , sourcecontent;

    int flg = 0;
    if(type == 1){  //file  
     while(getline(infile,line)){
        int s = 0;
        int slash = line.find_last_of('/');
        while(line[s] !='#') s++;
        if(line.substr(0,s) == name){
        sourcename = line.substr(slash+1,s-slash-1);
        int i = s+1;
        while(line[i] != '^') i++;
        sourcecontent = line.substr(i+1,line.size()-1);
        flg = 1;
       
        }
     }
      std::ofstream outfile(MYDISK,std::ios::app);
    if(!outfile.is_open()) throw std::runtime_error("The file could not be opened");
   if(flg) outfile << path << target << "#" <<"l"+get_current_date() << " linked -> " << sourcename << "^" << sourcecontent << std::endl;
    outfile.close();
    } // ##Y U S U F EMR E KILICE R 66226150288  MY SIGNATURE 
     else { // directory
        size_t dotpos = target.find_last_of('.');
        if(dotpos !=std::string :: npos && dotpos <origin_name.size()-1) throw std::runtime_error("Do not enter the extension of the file");
        if(origin_name[0] =='/' && origin_name[0] !='.') origin_name = "." + origin_name;
        std :: ofstream outfile(MYDISK,std::ios::app);
        while(getline(infile,line)){
            if(line.substr(0,origin_name.size()) ==origin_name){
            int s = 0;

            while(line[s] !='#') s++;
            sourcename = line.substr(origin_name.size(),s-origin_name.size());
            int i = s+1;
            while(line[i] != '^') i++;
            sourcecontent = line.substr(i+1,line.size()-1);
            if(sourcename=="") outfile << path << target << "#" <<"q"+get_current_date()<<"  linked" << sourcename <<"^@" << std::endl;
            else outfile << path << target+sourcename<< "#" <<"q"+get_current_date()<< "^" << sourcecontent<< std::endl;
            flg = 1;
            }
        }
        outfile.close();
     }

    infile.close();
    if(flg == 0) throw std::runtime_error("The file could not be found.Enter whole path before the file name(Ex :: /MYOS/.../filename)");

       }
}