#include "Pieces.h" 
#include "Chess_Board.h"
#include <iostream>
#include <vector>
#include <fstream> //for file operations
#include <cstring> //I WANTED TO USER CHAR ARRAY INSTEAD OF STRING.THUS I NEED cstring library
#include <iomanip> //for setprecision
using namespace std;

// NOT!!!!! WRITE ->> "sgst"  <<-- TO GET SUGGESTION 
Chess_Board :: Chess_Board() : SIZE(8) , user(1) , error_type(0){ // my consructor
    command = new char[5];
    board.resize(SIZE);
    for(int i =  0 ; i < SIZE ; i++){
        board[i].resize(SIZE);
    }
    initialize();
}

Chess_Board :: Chess_Board(const Chess_Board& other) : SIZE(8){ // my copy constructor ,it is essential for big three and also i used it
    user = other.user;
    error_type = other.error_type;
    command = new char[5];
    strcpy(command,other.command);
    board.resize(SIZE);
    for(int i = 0 ; i< SIZE ; i++){
        board[i].resize(SIZE);
    }
    for(int i = 0 ; i< SIZE ; i++){
        for(int j = 0 ; j< SIZE ; j++){
            board[i][j].set_piece(other.board[i][j].get_piece());
            board[i][j].set_point(other.board[i][j].get_point());
        }
    }
}
void Chess_Board :: initialize() {
             //note that I have an vector symbol , they have same indexes as the board so that I can print the board with only 1 for loop.
       for(int i = 0 ; i  < SIZE; i++){
        board[0][i].set_piece(piece[i]);
        board[SIZE-1][i].set_piece(piece[i]-32);
        board[1][i].set_piece('p');
        board[SIZE-2][i].set_piece('P');
       }
       for(int i = 0 ;  i < SIZE ; i++){
            board[1][i].set_point(static_cast<int>(Pointvalues::pawn));
            board[SIZE-2][i].set_point(static_cast<int>(Pointvalues ::pawn));
        }
       
        //setting the points which I used enums to do that.
        board[0][0].set_point(static_cast<double>(Pointvalues::rook));
        board[0][1].set_point(static_cast<double>(Pointvalues::knight));
        board[0][2].set_point(static_cast<double>(Pointvalues::bishop));
        board[0][3].set_point(static_cast<double>(Pointvalues ::queen));
        board[0][4].set_point(static_cast<double>(Pointvalues::king));
        board[0][5].set_point(static_cast<double>(Pointvalues::bishop));
        board[0][6].set_point(static_cast<double>(Pointvalues::knight));
        board[0][7].set_point(static_cast<double>(Pointvalues::rook));
        board[SIZE-1][0].set_point(static_cast<double>(Pointvalues::rook));
        board[SIZE-1][1].set_point(static_cast<double>(Pointvalues::knight));
        board[SIZE-1][2].set_point(static_cast<double>(Pointvalues::bishop));
        board[SIZE-1][3].set_point(static_cast<double>(Pointvalues::queen));
        board[SIZE-1][4].set_point(static_cast<double>(Pointvalues::king));
        board[SIZE-1][5].set_point(static_cast<double>(Pointvalues::bishop));
        board[SIZE-1][6].set_point(static_cast<double>(Pointvalues::knight));
        board[SIZE-1][7].set_point(static_cast<double>(Pointvalues::rook));
    
}

bool Chess_Board :: valid_input(int value){ // to check if the input is valid or not
    if(value >=0 && value <=7 ) return true; // 9 durumunu bi dusun
    return false;
}

void Chess_Board :: save_game(){ // to save the game
    cerr << "You quited the game! Do you want to save it ?(y/n) : ";
    char choice;
    cin >> choice;
    if(choice == 'y'){
        ofstream file;
        string filename;
        cout << "Enter the file name you want to save :";
        cin >> filename;
        file.open(filename);
        file<<user<<endl;
        print_board_to_file(file);
        file.close();
    }
    else if(choice == 'n') exit(0);
    else {
        cerr << "Invalid input ! " <<endl;
        save_game();
    }
}

void Chess_Board :: load_game(){ // to load the game
    ifstream inputfile;
    string filename;
    cout << "Enter the file name you saved :";
    cin >> filename;
    inputfile.open(filename);
    if(!inputfile.is_open()){
        cerr << "File cannot be found ! " <<endl;
        exit(1);
    }
    int last_user;
    inputfile >> last_user;
    user = last_user;
    char c;
    cout << "Last board : " <<endl<<endl;
    int i  = 0 , j = 0;
    while(inputfile.get(c)){
     if(c !=' ' && c != '\n'){
        board[i][j].set_piece(c);
        j++;
        if(j == SIZE) { j = 0 ; i++;}
     }
    }
    
    inputfile.close();
    print_board();
    take_command();
    update_board();
}
void Chess_Board :: start_game(){ // to start the game
   
    cout << "Welcome to the Chess Game!" << endl<<endl;
    print_board();
    take_command();
    update_board(); 
}

void Chess_Board :: take_command(){ // to take the command from user and then I also check if it is applyiable.
     
    while(!is_game_over()){
    if(user ==1 ){ 
      int flag = 0;
      cout << turn_message() <<" Turn]"<<endl;
    cout << "Current Score : " <<fixed << setprecision(1) << calculate_score("white") <<endl;
    
      cout << "Enter your move:"; // NOT!!!!! WRITE ->> "sgst"  <<-- TO GET SUGGESTION 
      cin >> command;
     if(strcmp(command,"sgst") ==0) {flag = 1 ;strcpy(command,suggest_movement().c_str()); }
       if(flag) cout<< "Suggested Move: "<< command <<endl;

     if(command[0] == 'q') {  save_game(); break; }
     while(len_command() != 4){ // less than 4 means invalid command
         cout << "Enter a valid command like :(a1b2) ";
         cin >> command;
     }
    
      check_and_apply();
      user = 2; //turn the user to make it interactive
    }
      if(user ==2 ){ //same things.
      int flag =0;
          cout << turn_message() << "Turn] :"<<endl;
        cout << "Current score is : " << fixed << setprecision(1) << calculate_score("black") <<endl;
         cout << "Enter your move:";
          cin >> command;
         if(strcmp(command,"sgst") ==0) {flag = 1 ;strcpy(command,suggest_movement().c_str()); }
       if(flag) cout<< "Suggested Move: "<< command <<endl;
               if(command[0] == 'q'){ save_game(); break; } 
            while(len_command() != 4){
         cout << "Enter a valid command like : (a1b2) ";
         cin >> command;
     }

          check_and_apply();
          user = 1;
      }
    }    
}

void Chess_Board :: update_coordinates(){  // i update string to integer to make it easier to use.
              piece.set_coordx(get_positive(SIZE - (command[1]- '0' )));
              piece.set_coordy(command[0]- 'a');
              piece.set_updated_x(get_positive(SIZE-(command[3] - '0')));
              piece.set_updated_y(command[2] - 'a');
              while(!valid_input(piece.get_coordx())   || !valid_input(piece.get_coordy()) ||
              !valid_input(piece.get_updated_x()) || !valid_input(piece.get_updated_y()) ){
               
              cout << "ENTER A VALID INPUT(between a-g and 1-8 : )";
              cin >> command;
              piece.set_coordx(get_positive(SIZE - ( command[1]-'0')));
              piece.set_coordy(command[0]-'a');
              piece.set_updated_x(get_positive(SIZE -(command[3] - '0')));
              piece.set_updated_y(command[2] - 'a');
        }
}
bool  Chess_Board :: from_valid_place(){ // if user tries to move the other player's piece , it is invalid.This function also checks if user tries to move empty space.
          
     if( user ==2 && (board[piece.get_coordx()][piece.get_coordy()].get_piece()  < 'a' ||  board[piece.get_coordx()][piece.get_coordy()].get_piece() >'z'  )
         || (user ==1  && (board[piece.get_coordx()][piece.get_coordy()].get_piece()  < 'A' ||  board[piece.get_coordx()][piece.get_coordy()].get_piece() >'Z'))) {
         if (board[piece.get_coordx()][piece.get_coordy()].get_piece()=='.') { 
            error_type = 0;
           cout <<"You cannnot move to space !" <<endl;
            return false; }
        else {error_type = 0 ; cerr<< "You cannot play with " << err_turn_message() << "pieces ! "<<endl; return false; } 
         
    }
        return true;
}
bool Chess_Board :: to_valid_place() { //if user tries to move his own piece to his own piece , it is invalid.
    if ((user == 1 && (board[piece.get_updated_x()][piece.get_updated_y()].get_piece() > 'A' && board[piece.get_updated_x()][piece.get_updated_y()].get_piece() < 'Z')) || (user == 2 && (board[piece.get_updated_x()][piece.get_updated_y()].get_piece() > 'a' && board[piece.get_updated_x()][piece.get_updated_y()].get_piece() < 'z')))
    {    error_type = 5;
        return false;
    }

return true;
}

bool Chess_Board :: empty(const int& x ,const int& y ) const{  //checks if it is empty.
    if (board[x][y].get_piece() != '.')
        return false;
    else
        return true;

}

 void Chess_Board :: find_location(int&row , int &col , char king) const { // it finds the location of king.
    for(int i = 0 ; i<SIZE; i++){
        for(int j = 0 ; j<SIZE ;j++){
            if(board[i][j].get_piece() == king){
                row = i;
                col =j;
                break;
            }
        }
    }
 }  

 int Chess_Board :: get_positive(int value){
 if(value < 0) value *=-1;if(command[1] =='9' || command[3] == '9')value = 9; return value;}
void Chess_Board :: set_old_coordinates( const int& old_x , const int& old_y,const int& old_upx , const int& old_upy){ // to set the old coordinates
    piece.set_coordx(old_x);
    piece.set_coordy(old_y);
    piece.set_updated_x(old_upx);
    piece.set_updated_y(old_upy);
}


void Chess_Board :: print_board() const{ // to print the board

    for(int i = 0 ; i< SIZE ; i++){
     cout << 8-i << " " << "| " ;
        for(int j = 0 ; j <SIZE ; j++){
            cout << board[i][j].get_piece()<< "  ";
        }
        cout <<endl;
    }

    cout <<"   ";

    for(int k = 0 ; k< SIZE ; k++){
        cout<<"---";
    }

    cout <<endl <<"    ";
    for(int l = 0; l< SIZE ; l++) cout << static_cast<char>(l+'a') << "  ";
    
    cout << endl;
    cout <<endl;
}


void Chess_Board :: print_board_to_file(ofstream& fl)const { // to print the board to file
    for(int i = 0 ; i< SIZE ; i++){
   
        for(int j = 0 ; j <SIZE ; j++){
            fl << board[i][j].get_piece()<< "  ";
        }
        fl <<endl;
    }
    
    fl << endl;
    fl <<endl;
}
void Chess_Board ::give_movement_error(char s ) const{
        //these are error types.I write valid error message for each error type.
        if(error_type == 1)          cerr << "There is a piece on way "<<endl;
        else if (error_type == 2)    cerr << " You cannot forward more than 1 space !" << endl; // just for pawn error.
        else if (error_type == 3)    cerr << " You cannot forward more than 2 space !" << endl; // just for pawn error.
        else if (error_type == 4)    cerr<< "It is not a legal movement.You cannot jump!!" << endl; // just for pawn error.  
        else if (error_type == 5)    cerr <<"You cannot move your own piece !"  <<endl; //tovalid place error
        else if(error_type!= 0) { cerr << "It is an illegal movement for ";
        if(s =='p' || s =='P') cout << "Pawn"<<endl;
        else if(s =='r' || s =='R') cout << "Rook"<<endl;
        else if(s =='n' || s =='N') cout << "Knight"<<endl;
        else if(s =='b' || s =='B') cout << "Bishop"<<endl;
        else if(s =='q' || s =='Q') cout << "Queen"<<endl;
        else if(s =='k' || s =='K') cout << "King"<<endl;
     }
      
}
bool Chess_Board :: white(const int& x1,const int& y1){ // to check if piece is white
  if(board[x1][y1].get_piece() > 'A' && board[x1][y1].get_piece() < 'Z' ) return true;

    return false;
}
bool Chess_Board :: black(const int& x, const int& y){ // to check if pieces is black
     if(board[x][y].get_piece() > 'a' && board[x][y].get_piece() < 'z' ) return true;

    return false;
}
int Chess_Board::len_command()const { // to find the length of command
    int i = 0;
    while(command[i] != '\0') i++;
    return i;
}
int Chess_Board :: get_best_score()const { // to get the best score
    ifstream inputfile;
    inputfile.open("scores.txt");
    if(!inputfile.is_open()){
        cerr << "File cannot be found ! " <<endl;
        exit(1);
    }
    int value;
    inputfile >> value;
    int max  =value ;
    while(inputfile >> value){
        if(value > max) max = value;
    }
    inputfile.close();
    return max;

}
void Chess_Board :: restore_board(){  // if i want to undo the movement, I use restore board.
if(piece.get_coordx() == piece.get_updated_x() && piece.get_coordy() == piece.get_updated_y()) return;
                             board[piece.get_coordx()][piece.get_coordy()].set_piece(piece.get_piece());
                             board[piece.get_updated_x()][piece.get_updated_y()].set_piece('.');
                             board[piece.get_coordx()][piece.get_coordy()].set_point(piece.get_point());
                             board[piece.get_updated_x()][piece.get_updated_y()].set_point(0);
}

 void Chess_Board :: copy_coordinates(int& oldx , int& oldy , int& old_upx , int& old_upy){ // to copy the coordinates
        oldx = piece.get_coordx();
        oldy = piece.get_coordy();
        old_upx = piece.get_updated_x();
        old_upy = piece.get_updated_y();
 }

void Chess_Board :: update_board(){ // to update the board with new movement and also new points.
    if(piece.get_coordx() == piece.get_updated_x() && piece.get_coordy() == piece.get_updated_y()) return;

    board[piece.get_updated_x()][piece.get_updated_y()].set_piece(board[piece.get_coordx()][piece.get_coordy()].get_piece());
    board[piece.get_coordx()][piece.get_coordy()].set_piece('.');
    board[piece.get_updated_x()][piece.get_updated_y()].set_point(board[piece.get_coordx()][piece.get_coordy()].get_point());
    board[piece.get_coordx()][piece.get_coordy()].set_point(0);
}

bool Chess_Board :: is_game_over(){
    return false;  
}

bool Chess_Board :: control_pawn(){ // to control the pawn movement
    if(user == 1 ) {
          if (piece.get_coordx()!= 6 &&  piece.get_coordx() - piece.get_updated_x()> 1) // if it is not the first movement , it cannot go more than 1 space
            {
                error_type =2;
              
                return false;
            }
             if (piece.get_coordx() == 6 && piece.get_coordx() - piece.get_updated_x() > 2) // if it is the first movement , it cannot go more than 2 space
            {
                error_type = 3;
                return false;
            }
               
             if  (piece.get_updated_x() >= piece.get_coordx() || piece.get_coordy() != piece.get_updated_y()){

                 if(empty(piece.get_updated_x(),piece.get_updated_y())){  // if it is empty , it cannot go forward
                  error_type =6;
                return false;
                 }
             if( (piece.get_updated_y() !=piece.get_coordy()) &&( board[piece.get_updated_x()][piece.get_updated_y()].get_piece()=='.' ||  (board[piece.get_updated_x()][piece.get_updated_y()].get_piece() >'A' &&  board[piece.get_updated_x()][piece.get_updated_y()].get_piece()<'Z'))) return false; // if it is not empty , it cannot go forward
              // if piece.gety != piece.getupdatedy 
            }
            if(piece.get_updated_y() == piece.get_coordy() && !empty(piece.get_updated_x(),piece.get_updated_y())) return false;
    }
    if(user == 2 ){
           if (piece.get_coordx() != 1 &&  piece.get_updated_x() - piece.get_coordx() > 1) // same logics.
            {
                error_type = 2;
                
                return false;
            }
            if (piece.get_coordx() == 1 && piece.get_updated_x() - piece.get_coordx() > 2)
            {
                 error_type = 3;
                
                return false;
            }
             if ((piece.get_updated_x() <=piece.get_coordx() ||  piece.get_coordy() != piece.get_updated_y()  ))
             {
             if(empty(piece.get_updated_x(),piece.get_updated_y())){
                error_type = 6;  
                return false;
             }
             if( (piece.get_updated_y() !=piece.get_coordy()) && ( board[piece.get_updated_x()][piece.get_updated_y()].get_piece()=='.' ||  (board[piece.get_updated_x()][piece.get_updated_y()].get_piece() >'a' &&  board[piece.get_updated_x()][piece.get_updated_y()].get_piece()<'z'))) return false;
             
           }
              if(piece.get_updated_y() == piece.get_coordy() &&( piece.get_coordx() == piece.get_updated_x() )) return false;
      }


         if( !empty(piece.get_updated_x(),piece.get_updated_y()) /*gidecegi yer doluysa ve  */  && to_valid_place() /* */  && piece.get_coordy() == piece.get_updated_y() ){  //emptyi bir dusun
                    //bosluga yukari hamle yapmiyosa ve kendi adamina da degilse 
                    error_type = 4;
                    return false;
             } 
             if(piece.get_coordy() != piece.get_updated_y() && empty(piece.get_updated_x(),piece.get_updated_y())) return false;
             if(piece.get_coordy() != piece.get_updated_y() && piece.get_coordx() == piece.get_updated_x() && !empty(piece.get_updated_x(),piece.get_updated_y())) return false;


               if(piece.get_updated_x() == 0 || piece.get_updated_x() == 7 ){
                cout << "User " << user <<" Has a pawn to promote !" <<endl;
                cout << "WHAT DO YOU WANT" <<endl;
                cout << "1)Queen" <<endl;
                cout << "2)Rook" <<endl;
                cout << "3)Bishop" <<endl;
                cout << "4)Knight" <<endl;
                char choice;
                fflush(stdin);
                cin >> choice;

                switch(choice){
                    case '1': 
                    if(piece.get_updated_x() ==0) {  board[piece.get_coordx()][piece.get_coordy()].set_piece('Q'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::queen));}
                       else {  board[piece.get_coordx()][piece.get_coordy()].set_piece('q'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::queen));}
                        break;
                    case '2':

                      if(piece.get_updated_x() ==0){ board[piece.get_coordx()][piece.get_coordy()].set_piece('R'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::rook));}
                       else{ board[piece.get_coordx()][piece.get_coordy()].set_piece('r'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::rook));}
                        break;
                    case '3':

                       if(piece.get_updated_x() == 0) {   board[piece.get_coordx()][piece.get_coordy()].set_piece('B'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::bishop));}
                       else {  board[piece.get_coordx()][piece.get_coordy()].set_piece('b'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::bishop));}
                        break;
                    case '4':
                    
                 if(piece.get_updated_x() == 0 ) { board[piece.get_coordx()][piece.get_coordy()].set_piece('N'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::knight));}
                       else {  board[piece.get_coordx()][piece.get_coordy()].set_piece('n'); board[piece.get_coordx()][piece.get_coordy()].set_point(static_cast<double>(Pointvalues::knight));}
                      break;
                        default :
                       cerr << "Invalid choice !" <<endl;
                      break;
                }

               } 

                    return true;
}

bool Chess_Board :: control_rookway() { // I SHOULD CHECK BOTH FOR GOING X AXIS AND Y AXIS
         int flag = 0;
         if(!to_valid_place()) return false;
    if(piece.get_coordx() != piece.get_updated_x()){
        if(piece.get_coordx() < piece.get_updated_x()) flag = 1;  // eger gidecegi yerin x i daha buyukse yer degistiriyoruz ki for dongusunde buyukten kucuge gitsin

 if(flag ){
    for(int i = piece.get_coordx()+1  ; i <piece.get_updated_x() ; i++){
     if(  !empty(i,piece.get_coordy()) ){
            error_type = 1; // if the way is not empty , it is invalid , there is a piece on way.
            return false;
                    }
                 }
             }
               else  for(int i = piece.get_updated_x()+1  ; i <piece.get_coordx() ; i++){ //eger 
                    if( !empty(i,piece.get_coordy()) ){
                        error_type = 1; // if the way is not empty , it is invalid , there is a piece on way.
                        return false;
                    }
                }
             }
    else { 
        if(piece.get_coordy() < piece.get_updated_y())  flag = 1;

               if(flag ){
                 for(int i = piece.get_coordy()+1  ; i<piece.get_updated_y() ; i++){
                    if(!empty(piece.get_coordx(),i)){
                        error_type = 1; // if the way is not empty , it is invalid , there is a piece on way.
                    return false;
                    }
                 }
               }
               else  for(int i = piece.get_updated_y()+1 ; i <piece.get_coordy() ; i++){ // just checkking the way
                    if(!empty(piece.get_coordx(),i)){ // if the way is not empty , it is invalid , there is a piece on way.
                        error_type = 1;
                        return false;
                    }
                }
           }   
    return true;
}

bool Chess_Board :: control_rook() {

          if(!to_valid_place() )  return false;

       if(piece.get_coordx() != piece.get_updated_x() && piece.get_coordy() != piece.get_updated_y()) {  // if he tries go across
                    return false;
                }
                else { //if the movement is legal , but is it valid  ?
                     if(!control_rookway()) return false; // kendi adami ustune kontrolu artik bosluga ve rakiba atlayabilir
              }
           return true;
}
bool Chess_Board :: control_knigth(){
             
         if(!to_valid_place()) return false;
      if (((abs(piece.get_coordx() - piece.get_updated_x())) == 2 && (abs(piece.get_coordy() - piece.get_updated_y()) == 1)) ||
       ((abs(piece.get_coordx() - piece.get_updated_x())) == 1 && (abs(piece.get_coordy() - piece.get_updated_y()) == 2)))

                     return true;
          else {
                error_type = 1;
             return false;
     }
}

bool Chess_Board :: control_bishopway(){
             if(!to_valid_place() ) return false;
    int  stepx , stepy; // to determine the direction 
           if(piece.get_updated_x() < piece.get_coordx())  stepx = -1; // first determine if we gonna increase or decrease the x and y
           else stepx = 1;
           if(piece.get_updated_y() < piece.get_coordy())  stepy = -1;
           else stepy = 1;

            for(int i = 1; i< abs(piece.get_updated_x() - piece.get_coordx()) ; i++){ //then check every space if it is empty
               if( !empty( piece.get_coordx()+ i * stepx  , piece.get_coordy()+ i * stepy)){ // if it full , then cannot jump.
                    error_type = 1;
                   return false;
               }
            }

         return true;
}

bool Chess_Board :: control_bishop(){
            if(!to_valid_place() ) return false;
        if(abs(piece.get_coordx() - piece.get_updated_x()) != abs(piece.get_coordy() - piece.get_updated_y())){ // if it is not diagonal , it is invalid movement
                error_type = 1;
              return false;
            }
          else {
                 if(!control_bishopway()) return false;
        }
   return true;
}

bool Chess_Board :: control_queen() {

 if( !control_rook() && !control_bishop() ) return false; //if illegal for queen  , return false

       return true;
}

bool Chess_Board ::  control_king() {// to control the knng mvement
    if(piece.get_updated_x() < 0 || piece.get_updated_x() > 7 || piece.get_updated_y() < 0 || piece.get_updated_y() > 7) return false;
     if(abs(piece.get_coordx() - piece.get_updated_x()) >1  || abs(piece.get_coordy() - piece.get_updated_y()) >1 ){
             return false;
            }

  return true;
}

bool  Chess_Board :: check_piece_movement(){
    int flag =0;
      char c = board[piece.get_coordx()][piece.get_coordy()].get_piece();
       switch(c){
          case 'P' :
                user =1;
                if(!control_pawn())   flag =1; 
                break; 
                
         case 'p' :
                user =2;
                if(!control_pawn())  flag =1; 
                break; 

        case 'R':
                 user = 1;
                if(!control_rook())  flag =1;  
                 break;
        case 'r':
                user =2;
                if(!control_rook()) flag =1;
                break;
                
        case 'N':
                user = 1;
                if(!control_knigth()) flag =1;
                break;

        case 'n':
                user = 2 ;
                if(!control_knigth()) flag =1;
                break;

        case 'B' :
                user = 1;
                if( !control_bishop()) flag =1;
                break;

        case 'b' :
                 user =2;
                 if(!control_bishop())  flag =1;
                 break;
        case 'K' :
                 user = 1; 
                if(!control_king()) flag =1;
                 break;

       case 'k':
                user =2;
                if(!control_king()) flag =1;
                break;
      case 'Q':
                 user =1;
                if(!control_queen())  flag =1;
                 break;
      case 'q':
                user = 2; 
                if(!control_queen()) flag =1;
                break;

      default :
                break;
                
       }
        if(flag) return false;

return true;
    }


void Chess_Board :: check_and_apply(){
          update_coordinates();
 while(  (!from_valid_place()) || (!to_valid_place())  || (!check_piece_movement() ) ){ // bi tanesinin bile  false demek , icin true olmasi yani whileye girmesi
        give_movement_error(board[piece.get_coordx()][piece.get_coordy()].get_piece());
         cout << "Enter again ! : ";

         cin >> command;
          update_coordinates();     
      }     

        while(is_king_underattack()){

              if(is_checkmate()) {
                ofstream file; // to write the score to file
                file.open("scores.txt",ios::app);
                if(!file.is_open()){
                    cerr << "File cannot be found ! " <<endl;
                    exit(1);
                }
                if(user == 1) file << calculate_score("black") <<endl;
                else file << calculate_score("white") <<endl;
                file.close();

                 exit(0);
              }
              cout << "Your king is under attack!You must rescue it! : ";
              cin >> command;
              update_coordinates(); 
            
             
        }
         print_board();
         
        }
bool Chess_Board :: is_king_underattack(){

    int k_x , k_y , old_x , old_y , old_upx , old_upy; // cordination of king
    piece.set_piece(board[piece.get_coordx()][piece.get_coordy()].get_piece()); // my temp coordinates and type piece to undo the movemtn if it necesary   4
    copy_coordinates(old_x,old_y,old_upx,old_upy); // to copy the coordinates that I will use it later
    if( check_piece_movement()) { update_board();} //  if movmement is valid  , lets update the board for now.
     

    int temp = user;
         if(user ==1){ 
             find_location(k_x,k_y,'K'); // to find the location of king
             for(int k =0  ; k < SIZE ; k++){
                for(int l =0 ; l < SIZE ; l++){
                    if(black(k,l)){
                        piece.set_updated_x(k_x);
                        piece.set_updated_y(k_y);
                        piece.set_coordx(k);
                        piece.set_coordy(l);
                        if(check_piece_movement()) { //if is there any vqalid movement for black piece to attack the king , then it is under attack.
                               set_old_coordinates(old_x,old_y,old_upx,old_upy);
                                restore_board();
                                user = temp;
                            return true;
                        }
                    }

                }
             }
         }
         user = temp;
         if(user == 2 ){ //same logic for user 2  , black
            find_location(k_x,k_y,'k'); // to find the location of king 
                for(int k =0  ; k < SIZE ; k++){
                    for(int l =0 ; l < SIZE ; l++){
                        if(white(k,l)){
                            piece.set_coordx(k);
                            piece.set_coordy(l);
                            piece.set_updated_x(k_x);
                            piece.set_updated_y(k_y);
                             if(check_piece_movement()){ //if is there any vqalid movement for white piece to attack the king , then it is under attack.,Restore the board and return true.
                             set_old_coordinates(old_x,old_y,old_upx,old_upy);
                               restore_board();
                               user = temp;
                                return true;
                            }
                        }
    
                    }
                }
         }                                           
            set_old_coordinates(old_x,old_y,old_upx,old_upy);  //if there is no valid movement , restore the board and return false.             
            board[piece.get_updated_x()][piece.get_updated_y()].set_piece(piece.get_piece());
            board[piece.get_coordx()][piece.get_coordy()].set_piece('.');
         return false;
}

bool Chess_Board ::  is_checkmate(){
    int k_x , k_y;
    if(user == 1) find_location(k_x,k_y,'K');
    else find_location(k_x,k_y,'k');
   for(int i = 0 ; i< SIZE ;i++){ // assume that every white is the attacker and check if there is any valid movement to prevent the checkmate.
    for(int j = 0 ; j <SIZE ; j++){
        if(user == 1 && white(i,j)){
            for(int k = 0 ; k < SIZE ; k++){
                for(int l = 0 ; l < SIZE ;l++){
                    piece.set_coordx(i);
                    piece.set_coordy(j);
                    piece.set_updated_x(k);
                    piece.set_updated_y(l);
                    if(i != k && j != l){
                
                   piece.set_piece(board[i][j].get_piece());
                   char temp = board[k][l].get_piece();

                   if(check_piece_movement()){
                    if(!is_king_underattack()) { // if there is any valid movement , then it is not checkmate.
                          cout << "youcan prevent the checkmate " << static_cast<char>(j+'a') << SIZE - i << " -> " << static_cast<char>(l+'a') << SIZE - k <<endl;
                            board[i][j].set_piece(piece.get_piece());
                            board[k][l].set_piece(temp); // restore the board
                          return false;
                    }
                   }

                    }

                }
            }

        }

        if(user == 2 && black(i,j)){
            for(int k = 0 ; k< SIZE; k++){
                for(int l = 0 ; l < SIZE ; l++){
                    piece.set_coordx(i);
                    piece.set_coordy(j);
                    piece.set_updated_x(k);
                    piece.set_updated_y(l);
                    if(i != k && j != l){
                    if(check_piece_movement()){
                        piece.set_piece(board[i][j].get_piece());
                        char temp = board[k][l].get_piece();
                        if(!is_king_underattack()){ // if there is any valid movement , then it is not checkmate.
                            cout << "you can prevent the checkmate: " << static_cast<char>(j+'a') << SIZE - i << " -> " << static_cast<char>(l+'a') << SIZE - k <<endl;
                            board[i][j].set_piece(piece.get_piece());
                            board[k][l].set_piece(temp); // restore the board
    
                            return false;
                           
                        }
                    
                    }
                }
                }
            }
        }
       

    }
   }

     cout << " USER : " << user << " HAS CHECKMATED ! " <<endl;
    return true;
}
string Chess_Board :: suggest_movement(){
   int score = -1000;
   char up_piece;
   int old_point , updated_point;
   char* result = new char[5];
   int best_x , best_y , best_upx , best_upy;
    int old_user = user;
    strcpy(command,"----");
        for(int i = 0 ; i< SIZE ; i++){
            for(int j = 0 ; j< SIZE ;j++){

      if(user == 1){
                if(white(i,j)){
                    for(int k = 0; k <SIZE ; k++){
                        for(int l = 0 ; l< SIZE ; l++){
                            set_simulate_coordinates(i,j,k,l,old_point,updated_point,up_piece);

                            if(i != k && j != l){
                            if(k == 0 && board[i][j].get_piece() == 'P' && check_piece_movement()){ result[0]= static_cast<char>(j+'a');
                                result[1]= SIZE - i + '0';
                                result[2]= static_cast<char>(l+'a');
                                result[3]= SIZE - k + '0';
                                result[4] = '\0'; 
                                return result;} 
                            else if(check_piece_movement() && to_valid_place() && from_valid_place()){
                                    update_board();
                            if(calculate_score("white") - calculate_score("black") >= score){
                             score = calculate_score("white") - calculate_score("black");
                             find_best_coordinates_for_suggestion(best_x,i,best_y,j,best_upx,k,best_upy,l);

                            }
                          
                            }
                        }
                          restore_point(i,j,k,l,up_piece,old_point,updated_point);
                    }
                }
                }
                }
        if(user ==2 ){ 
            if(black(i,j)){
                for(int k = 0 ; k < SIZE ; k++){
                    for(int l = 0 ; l < SIZE ; l++){
                        
                  set_simulate_coordinates(i,j,k,l,old_point,updated_point,up_piece);
                        if(i != k && j != l){
                            
                        if(k ==0 && board[i][j].get_piece() == 'p' && check_piece_movement()) { result[0]= static_cast<char>(j+'a');
                                result[1]= SIZE - i + '0';
                                result[2]= static_cast<char>(l+'a');
                                result[3]= SIZE - k + '0';
                                result[4] = '\0';
                                return result;}  
                             
                         else if(check_piece_movement() && to_valid_place() && from_valid_place()){
                            update_board();
                            if((calculate_score("black") -calculate_score("white")) >= score){
                                score = calculate_score("black") - calculate_score("white");
                                find_best_coordinates_for_suggestion(best_x,i,best_y,j,best_upx,k,best_upy,l);
    
                            }
                          
                        }
                     
                        }

                        restore_point(i,j,k,l,up_piece,old_point,updated_point);
                    }
                          
                    }
                }
            }
        }
      
        } 
        user = old_user;
        result[0]= static_cast<char>(best_y+'a');
        result[1]= SIZE - best_x + '0';
        result[2]= static_cast<char>(best_upy+'a');
        result[3]= SIZE - best_upx + '0';
        return result;
     }  
       void find_best_coordinates_for_suggestion(int& oldx , int i ,  int& oldy , int j ,  int& old_upx , int k ,  int& old_upy , int l){
        oldx = i;
        oldy = j;
        old_upx = k;
        old_upy = l;
       }   

void Chess_Board :: set_simulate_coordinates(int i , int j , int k , int l , int& oldpoint , int& updatedpoint , char& temp){
    piece.set_coordx(i);
    piece.set_coordy(j);
    piece.set_updated_x(k);
    piece.set_updated_y(l);
    piece.set_piece(board[i][j].get_piece());
    oldpoint = board[i][j].get_point();
    updatedpoint = board[k][l].get_point();
    temp = board[k][l].get_piece();
}
void Chess_Board ::  restore_point(const int& oldx , const int& oldy,const int& oldupx , const int& oldupy ,char temp , int old_point , int updated_point){
    board[oldx][oldy].set_point(old_point);
    board[oldupx][oldupy].set_point(updated_point);
    board[oldx][oldy].set_piece(piece.get_piece());
    board[oldupx][oldupy].set_piece(temp);
    calculate_score("black");
    calculate_score("white");

}


 



const double Chess_Board :: calculate_score(const string& type){
    double tot = 0;
    if(type == "white"){
        for(int i = 0 ; i< SIZE ; i++){
            for(int j =0 ; j<SIZE ; j++){
                if(white(i,j) && board[i][j].get_piece() != 'K'){ // if it is white , then check if black can attack it.
                    if(is_in_danger(i,j,"white"))  tot += board[i][j].get_point()/2.0;  // if it is in danger , then add half of the point.
                   else  tot += board[i][j].get_point(); // if it is not in danger , then add the point.
                }   
            }
        }
    }
    else if(type == "black"){
        for(int i = 0 ; i< SIZE ; i++){
            for(int j =0 ; j<SIZE ; j++){
                if(black(i,j) && board[i][j].get_piece() != 'k'){ // if it is black , then check if white can attack it.
                    if(is_in_danger(i,j,"black"))  tot += board[i][j].get_point()/2.0;  // if it is in danger , then add half of the point.
                   else  tot += board[i][j].get_point();
                }
            }
        }
    }
    
    return tot;
}
bool Chess_Board :: is_in_danger(const int& x , const int&y , const string& type){
        int temp_user= user;
    for(int i =  0 ; i< SIZE ; i++){
        for(int j = 0 ; j < SIZE ; j++){
            if(type == "black"){ // if it is black , then check if white can attack it.
                if(white(i,j)){
                    piece.set_coordx(i);
                    piece.set_coordy(j);
                    piece.set_updated_x(x);
                    piece.set_updated_y(y);
                    if(check_piece_movement()) { user = temp_user ; return true;}
                }
            }
            if(type == "white"){
                if(black(i,j)){ // if it is white , then check if black can attack it.
                    piece.set_coordx(i);
                    piece.set_coordy(j);
                    piece.set_updated_x(x);
                    piece.set_updated_y(y);
                    if(check_piece_movement()) {user = temp_user; return true; }
                }
            }

        }
    }
    user = temp_user; // restore the user
    return false;
} 


Chess_Board :: ~ Chess_Board(){ // destructor
    delete []command;
    command = nullptr;
}
