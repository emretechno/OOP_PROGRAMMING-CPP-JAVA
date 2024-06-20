#include "regularfile.hpp"
namespace MyOS{

RegularFile :: RegularFile() : File() , byte(0) { }

RegularFile :: ~RegularFile() { }



int  RegularFile :: calculate_byte()  {
    byte =0;
      for(std::vector<char>:: const_iterator it = content.begin() ; it !=content.end() ; it++)    byte++;  //READ ONLY
            return byte; //
}
void RegularFile :: cat() {
    if(islinked_directory(name) ==1) throw std::runtime_error("The input is linked directory.Cat works for only files.");//sadece son kismi okuyor find zaten
    if(!is_find()) throw std::runtime_error("cat : The file is not found.Ensure that you are in the correct directory!(Ex :cat a.cpp )");//sadece son kismi okuyor find zaten
    if(is_directory() && (islinked_directory(name) != 0)) throw std::runtime_error("cat : The input is directory.Cat works for only files.");//sadece son kismi okuyor find zaten
    std::ifstream inputfile(MYDISK);
    std::string line; // ### Y U S U F EMR E KILICE R 66226150288  
    std::string temp = path + name;
    while(getline(inputfile,line)){
        if(line.substr(0,temp.size()) == temp) {
         
          int i = temp.size();
           while(line[i] !='^') i++;
          for(size_t s = i +1 ; s < line.size()-1 ; s++){
              content.push_back(line[s]);
              if(line[s] != '`') std::cout << line[s];
              else std::cout<<"\n";
          }
          
        }
    }
    inputfile.close();
    std::cout << std::endl;
    
}

}// my namespace;