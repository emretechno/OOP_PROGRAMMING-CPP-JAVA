#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "file.hpp"
#include "regularfile.hpp"

namespace MyOS{
class Directory : public File{
   public :   
        Directory();
       ~Directory();
        void ls();
        void ls_recursive(std::ifstream& inputfile);
        void add_file(MyOS::File* file) { files.push_back(file); } 
        void mkdir();
        void rmdir();
        void cd();
        std::string  get_creation_date() const;

       class Iterator {
    public:
        Iterator(const std::vector<MyOS::File*>& files, size_t index = 0)
            : files(files), current_index(index) {}

        Iterator& operator++() {
            ++current_index;
            return *this;
        }

        MyOS::File* operator*() const {
            return files[current_index];
        }

        bool operator!=(const Iterator& other) const {
            return current_index != other.current_index;
        }

        bool operator==(const Iterator& other) const {
            return current_index == other.current_index;
        }

    private:
        const std::vector<MyOS::File*>& files;
        size_t current_index;
    };

    Iterator begin() const {
        return Iterator(files);
    }

    Iterator end() const {
        return Iterator(files, files.size());
    }
    private:
        void help_list(RegularFile* rg)const ; //user should not acces this function
         std::vector<MyOS::File*> files;
  };

}
#endif