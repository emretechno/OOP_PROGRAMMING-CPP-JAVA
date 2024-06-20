#include "Pieces.h"
#include <iostream>


char& Pieces :: operator[](int index){
    if(index <0 || index>7 ) exit(1);
    return symbol[index];
}
const char& Pieces :: operator[](int index) const {
     if(index <0 || index>7 ) exit(1);

    return symbol[index];
}

void Pieces :: set_piece(char type) { piecetype = type; }
void Pieces :: set_point(double  value) {  point = value;}
    
Pieces :: Pieces() : piecetype('.') ,symbol({'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}) ,coord_x(0) , coord_y() , updated_x(0), updated_y(0){}

ostream&  operator<<(ostream& os , const Pieces&p){
     os << p.piecetype;
    return os;
}

Pieces :: ~Pieces() {}


