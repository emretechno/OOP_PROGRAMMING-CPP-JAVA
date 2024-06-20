
#ifndef PIECES_H
#define PIECES_H
#include <iostream>
#include <vector>
#include "Pointvalues.h"
using namespace std;

class Pieces{
    public :
        Pieces();
        friend ostream& operator<<(ostream& os , const Pieces&p);
        char  get_piece() const { return piecetype;}
        int   get_coordx() const {return coord_x ; }
        int   get_coordy() const { return coord_y ; };
        int   get_updated_x() const { return updated_x;}
        int   get_updated_y() const { return updated_y;}
        void  set_coordx( int value )  { coord_x = value; }
        void  set_coordy( int value )  { coord_y= value ; };
        void  set_updated_x(int value )  { updated_x = value;}
        void  set_updated_y( int value)  {  updated_y = value;}
        void  set_piece(char type);
        void  set_point(double value);
        double   get_point() const { return point;}
              // copy constructor
        char& operator[](int index);
        const char&  operator[](int index) const;
         ~Pieces();

     private :
            char piecetype;
            int coord_x , coord_y;
            int updated_x,updated_y;
            double point;
            vector<char>symbol;
            Pointvalues value;
            
};
#endif