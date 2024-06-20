#include <iostream>
#include "Chess_Board.h"
using namespace std;

int main(){
      int flag = 1;
    do{
    cout <<" WELCOME TO MENU " << endl;
    cout<<" ---------------- " << endl;
    cout <<" 1->START A NEW GAME " << endl;
    cout <<" 2-> LOAG A GAME " <<endl;
    cout <<" 3->SHOW BEST SCORE " << endl;
    cout <<" 4->EXIT " << endl;
    char choice;
    cin >> choice;
     Chess_Board brd;
    switch(choice){
        case '1' : 
                 brd.start_game();
            break;
         case  '2' :
            cout <<"LOAD A GAME " << endl;
            brd.load_game();
            break;
        case '3' :
            cout <<" BEST SCORE IS : " << brd.get_best_score() << endl;
            break;
        case '4' :
            cout <<" EXITING " << endl<<endl;
            flag  =0;
            break;
        default :
            cout <<" INVALID CHOICE " << endl;
            break;
    }
    }   while(flag);

    return 0;
}
