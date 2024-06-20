#ifndef MY_FILE_H
#define MY_FILE_H
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <iterator>
#define MYDISK "mydisk.txt"

   /*##README! IT WAS BECAUSE SAID ON PDF  THAT  MOST FUNCTIONS MUST BE IN FILE CLASS ,
   THAT IS WHY USED VIRTUAL FUCNTIONS TO IMPLEMENT THEM IN DERIVED CLASSES WHERE I USE THEM */
namespace MyOS {   //it is as abstract class for file system

 class File{ // my implelmentations of cat , mkdir ,rmdir , ls and other file related commands
      public :
            File();
            virtual ~File() = 0; //pure virtual function that makes my class abstract
            virtual void cat() { throw std::runtime_error("the command was not implemented"); }
            virtual int calculate_byte()  { throw  std::runtime_error("calculate_byte command is not implemented for this file type");}
            void rm();
            void cp( std::string& filename);
            void copy_from_regularos(std::ifstream& ,const std::string& filename , int& vos_flag);
            bool is_find()const;
            bool is_directory() const;
            size_t get_disk_byte() const;
            //MY INLINE FUNCTIONS.
            void pwd() const { std::cout << get_path() << std::endl; }
            void clear_command() { system("clear"); }
            std::string get_name() const { return name; }
            std::string get_date() const { return date; }
            std::string get_path() const { return path; }
            int islinked_directory(const std::string& trg) const;
            void set_name(std::string name) { this->name = name; }
            void set_date(std::string date) { this->date = date; }
            void set_path(std::string path) { this->path = path; }
     protected:
            std :: string get_current_date() const; // user should access to this function to get current date
            std::string name;
            std::string date;
            std:: string path; // every regularfile/directory has a path name and date.
            
 };

}

#endif