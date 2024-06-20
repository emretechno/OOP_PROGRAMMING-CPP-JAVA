#include  "file.hpp"
#include "regularfile.hpp"
#define DISKMAXBYTE 10000000
namespace MyOS {
  File ::   File() { name = ""; date = ""; path = "./MYOS/";  }
 
  void File :: rm(){

     if(name == "MYOS" || name == MYDISK) throw std::runtime_error("OS CANNOT BE DELETED");
    size_t slashpos = name.find('/');
    if(slashpos !=std::string::npos) throw std::runtime_error("Just enter the directory or filename(Ex :rm deneme.txt)");
     if(!is_find())throw std::runtime_error("The file is not found");
     if(is_directory() && (islinked_directory(name) !=0))  throw std::runtime_error("The " + name + " is not regular file.Use rmdir for directory");
    std::ifstream inputfile(MYDISK);
    std:: ofstream outputfile("temp.txt");
    std::string line;
    std::string sign = path + name;

        
              while(getline(inputfile,line)){
                if(line.substr(0,sign.size()) != path+name){
                  outputfile << line << std::endl;
                }
              }


    inputfile.close();
    outputfile.close();
    std::remove(MYDISK);
    std::rename("temp.txt",MYDISK);
  }
  bool  File :: is_directory() const {

     size_t dotpos = name.find_last_of('.');
         if(dotpos != std::string :: npos && dotpos < name.size()-1) return false;
         else return true;

  }

std::string  File :: get_current_date() const{
    // Get the current time point
    auto currentTimePoint = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

    // Convert the time_t object to a string representation
    char currentTimeStr[100];
    strftime(currentTimeStr, sizeof(currentTimeStr), "%b %d %H:%M", localtime(&currentTime));
    
    return currentTimeStr;

}

bool File :: is_find()const{
    std::fstream inputfile(MYDISK);
  
    if(!inputfile.is_open())  throw std::runtime_error("The file could not be opened");
    std::string line;
   int flag;
    while(getline(inputfile,line)) 
    {   
      flag = 0;
      if(line.substr(0,path.size()) == path){
            int len = path.size();
            for(std::string:: size_type i = path.size(); i < line.size(); i++) {
                if(line[i] == '/') { // directory ise  bu 
                    len = i;
                    flag = 1;
                    break;
                } 
            } // len is the index of the first '/' character
          if(flag == 0) { // yani / isareti yok yani directory demek bu.
          if(line[len] =='.' || line.substr(len,2) == "..") continue;
          int i = path.size();
          while(line[i] !='#') i++;
          if(name == line.substr(len,i-len)) return true;
          }   
            }
        
}
    inputfile.close();
   return false;
}

void File :: copy_from_regularos( std::ifstream&  infile , const std::string& filename, int& vos_flag){

  size_t l = filename.find_last_of('/');
  std::ofstream outputfile(MYDISK,std::ios::app);
   name = filename.substr(l+1 , filename.size());
   size_t tmpb = 0;
   if(is_find()) throw std:: runtime_error("The file you want to copy from computer is already exist!");
  vos_flag = 0;
  char c;
  while(infile.get(c)){
    tmpb++; 
  }
  if(tmpb + get_disk_byte() > DISKMAXBYTE) { 
     outputfile.close();
     infile.close();
     throw std::runtime_error("The disk was gonna exceeded.Could not copied.");
   }
  
  else {
    outputfile << path << filename.substr(l+1,filename.size()) << "#"<<get_current_date()<<"^";
     infile.close();
      infile.open(filename);
      while(infile.get(c)){
        if(c !='\n' &&  c !='@') outputfile << c;
       else if(c =='\n' || c == '@') outputfile << "`";
      }

  }
   outputfile << "@" << std::endl;
   outputfile.close();
  infile.close();

}

void File :: cp( std::string& filename){
//#to do - > berkay.txt de faliba calismali  ,ayni directoryde copylenebilirmi o da var.
  int vos_flag =2;
 std::ifstream infile(filename);
      MyOS :: RegularFile* rf = new MyOS :: RegularFile();

 if(infile.is_open()){  copy_from_regularos(infile, filename , vos_flag); return; } // if found from OS 
 else{vos_flag =1;  std::cerr << "The file was not found in the local computer , checking from virtual MYOS..." << std::endl; }

if(vos_flag){ //MY VIRTUAL
      std::string temp_path = path;
  size_t dotpos = filename.find_last_of('.');
  if(filename[0]!='.' && filename[0] =='/') filename = "." + filename;
  size_t slashpos = filename.find_last_of('/');     
  if(dotpos !=std::string :: npos && dotpos <filename.size()-1) { 
     if(slashpos == std::string ::npos )  throw std::runtime_error("Please enter path before the file name.(/MYOS/.../filename)");
      name = filename.substr(slashpos+1,filename.size());
       path = filename.substr(0,slashpos+1);
         if(!is_find()) { path =temp_path;  throw std::runtime_error("The file is not found"); }
         path = temp_path;
     int ind = filename.size()-1;
         while(filename[ind] !='/') ind--;
      name = filename.substr(ind+1,filename.size());
      // IF THE FILE WILL BE COPIED
    std::ifstream inputfile(MYDISK);
     std::string line;
     while(getline(inputfile,line)){
      int i =0; // ##Y U S U F EMR E KILICE R 66226150288  
      while(line[i] !='#') i++;
      if(line.substr(0,i) == path+name)  throw  std::runtime_error("The file is already exist");
      int  brkpt = 0;
      for(int s = line.size()-1; s>= 0 ; s--){ //impossible to not '/' character
        if(line[s] =='/' ){
        brkpt = s;
        break;
        }
      }
      if(line.substr(brkpt + 1 , i - brkpt-1) == name ){ // onlye copy the texted filE
      int j=i;
      while(line[j] !='^') j++;
      for(size_t  s = j+1 ; s < line.size()-1 ; s++){
        rf->set_content(line[s]);    
      }
  
      }
       
     }
      inputfile.close();
       if(get_disk_byte() + rf->calculate_byte() >DISKMAXBYTE) { throw std::runtime_error("The disk was gonna exceeded.Could not copied."); }
      std::ofstream outputfile(MYDISK,std::ios::app);
      outputfile<<path+name<<"#"<<get_current_date()<<"^";
      for(const auto& ch : rf->get_content())  outputfile << ch;
      outputfile << "@" << std::endl;
     outputfile.close();
    
     delete rf;

  }else { //# TODO TAKE INPUT ONLY THE DIRECTORY NAME , NOT A WHOLE PATH 
    name = filename;
    if(filename.substr(0,2) == "./") name = filename;
    else if(filename[0] =='/') name = "." +filename;
    else name = path + filename;
    std::vector<std::string> filenames;
    if(name+"/" == path) throw std::runtime_error("You are already in this directory");
    std::string pure_name;
    for(int k = name.size()-1 ; k> 0 ; k--){
      if(name[k] =='/'){
        pure_name= name.substr(k+1,name.size());
        break;
      }
    }
  //  if(path +pure_name == name) throw std::runtime_error("The directory is already exist");
    std::ifstream inputfile(MYDISK);
    std::string line;
    while(getline(inputfile,line)){
     if(line.substr(0,name.size()) == name ) {
      int i = name.size();
      while(line[i] !='#') i++;
      int j = i;
      while(line[j] !='^') j++;
      int k = j;
      while(line[k] !='@') k++;
      int u =0;
    for(int s = line.size() ; s>= 0 ; s--){
      if(line[s] =='/'){
        u = s;
        break;
      }
    }
    std::string name_tmp = line.substr(u+1,i-u-1);
    date = get_current_date();
    std::string cont = line.substr(j+1,k-j-1);
    name = pure_name;
    if(is_find()) throw std::runtime_error("The directory is already exist");
     if(name_tmp =="." || name_tmp =="..") {continue;}
    else {  if( name_tmp !=pure_name){
       filenames.push_back(path+name_tmp+"#"+date+"^"+cont+"@"); 
    }
    }
  
     }
    }
    inputfile.close();
    std::ofstream outputfile(MYDISK,std::ios::app);
    for(const auto& ln : filenames){
      outputfile << ln << std::endl;
    }
    outputfile.close();
      if(filenames.size() == 0) throw std::runtime_error("The directory is not found!.Ensure that you have in right path or enther the whole path(./MYOS/.../filename)"); //KENDI YERI MI ACABA  ??
  } 

}

}
int File :: islinked_directory(const std::string& targ) const{
       std::ifstream inputfile(MYDISK);
        std::string line;
        std::string sign = path + targ;

       while(getline(inputfile,line)){
         if(line.substr(0,sign.size()) == sign){
           int i = path.size();
           while(line[i] !='#') i++;
          if(line[i+1]=='l' ) return 0;
          else if(line[i+1]=='q') return 1;
        }
        
       }
      
        inputfile.close();
        return 2;
}
size_t File :: get_disk_byte() const {
   std::ifstream inputfile(MYDISK);
    if(!inputfile.is_open()) throw std::runtime_error("The file could not be opened"); 
    char ch;
    size_t disk_size =0;
    while(inputfile.get(ch)) disk_size++;
    inputfile.close();
    return disk_size;
}
File :: ~File() { }

} //namespace MyOs
