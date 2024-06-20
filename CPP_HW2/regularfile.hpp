#ifndef MY_REGULARFILE_H
#define MY_REGULARFILE_H
#include "file.hpp"
#include <iterator>
#include <iostream>
 // every regular file has a content and byte
namespace MyOS {

class RegularFile : public  File {

    public :
        RegularFile();
        ~RegularFile() override;
        int calculate_byte()override;
        void cat() override;
        void set_content(const char& c) { content.push_back(c); }
        void clear_content() { content.clear(); }
        std::vector<char> get_content() const { return content; }
        int get_size() const { return content.size();}

    private:
        std::vector<char> content;
        size_t byte; // reguarfiles have bytes
        
};

}

#endif