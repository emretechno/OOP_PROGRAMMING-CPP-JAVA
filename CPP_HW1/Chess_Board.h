
#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <iostream>
#include <vector>
#include "Pieces.h"
#include <fstream>
using namespace std;
class Chess_Board{
    public :
            Chess_Board();
            Chess_Board(const Chess_Board& other);

            void initialize(); //initialize the board
            void start_game(); //start the game
            void load_game();
            void update_board(); //update the board after the movement
            void restore_board(); //undo the last movement
            void print_board()const;
            void take_command();
            void update_coordinates();
            void check_and_apply();
            void give_movement_error(char s) const;
            void illegal_movement_error(char st)const;  
            void copy_coordinates(int& oldx , int& oldy , int& old_upx , int& old_upy);
            void find_location(int&row , int&col , char king) const ; 
            void set_isgameover(int value) { user = value;}   
            void print_board_to_file(ofstream& file)const;
            void set_old_coordinates( const int& oldx , const int& oldy,const int& oldupx , const int& oldupy); 
            void restore_point(const int& oldx , const int& oldy,const int& oldupx , const int& oldupy ,char temp , int old_point , int updated_point);
            void set_simulate_coordinates(int i , int j , int k , int l , int& oldpoint , int& updatedpoint , char& temp);
            /* NOT : I DIDNOT MAKE "CONTROL FUNCTIONS"  CONSTANT BECAUSE I MODIFY THE ERROR TYPES TO GIVE PROPER ERROR MESSAGE FOR ANY ILLEGAL MOVEMENT.*/

            bool control_pawn() ; // also sets the error type
            bool control_rook(); // also sets the error type thus could not be const
            bool control_knigth() ;
            bool control_bishop();
            bool control_rookway() ;
            bool control_bishopway();
            bool control_king();
            bool control_queen();
            bool is_king_underattack();
            bool is_checkmate();
            bool empty(const int& ,const int&) const;
            bool white(const int& x , const int& y);
            bool black(const int& x , const int& y);
            bool is_in_danger(const int& x , const int& y, const string& type);
            bool valid_input(int value);
            
            const double calculate_score(const string& s);
            int get_best_score()const ;
            int len_command()const ;
            int get_user() const { return user;}
            int  get_positive(int value);
            
            string suggest_movement(); // write "sgst" to get suggestion
            string turn_message() const { return (user == 1) ? "[White's" : "[Black's " ; }
            string err_turn_message() const { return (user ==1 ) ? "Black's " : "White's "; }

            ~Chess_Board();

   private:
            vector<vector<Pieces >> board;
            const int  SIZE;
            Pieces piece;
            char *command;
            int user;
            int error_type;
            void save_game();
            bool from_valid_place();
            bool to_valid_place();
            bool is_game_over();
            bool check_piece_movement();
};

   void find_best_coordinates_for_suggestion(int& oldx ,int i ,int& oldy ,int j , int& old_upx ,int k ,int& old_upy,int l) ;  

#endif