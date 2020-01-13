#include <iostream>
#include <stdlib.h>
#include "time.h"
//#include "../include/algorithm.h"
#include "algorithm.h"
using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

Board* set_board(Board* oldb, Board* newb, int* index, Player me){
    Board* t_board = new Board;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            int times = oldb->get_orbs_num(i, j);       
            for(int t = 0; t < times; t++){
                char color = oldb->get_cell_color(i, j);
                Player tmp(color);
                t_board->place_orb(i, j, &tmp);
            }
        }   
    }
    t_board->place_orb(index[0], index[1], &me);
    return t_board;
}

struct direction{
    int index[2];
    int num;
};

bool enemy_around(int* me_index, int* e_index, Board* board, Player me){
    if(e_index[0]==-1 && e_index[1]==-1)
        return false;
    int res = 0;
    direction up, down, left, right;
    up.num = 5;
    down.num = 5;
    left.num = 5;
    right.num = 5;
    if(e_index[1]+1 < COL){
        if(board->get_cell_color(e_index[0], e_index[1]+1) == me.get_color()){
            res = 1;
            right.index[0] = e_index[0];
            right.index[1] = e_index[1]+1;
            right.num = board->get_capacity(e_index[0], e_index[1]+1) - board->get_orbs_num(e_index[0], e_index[1]+1);
        }
    }
    if(e_index[0]+1 < ROW){
        if(board->get_cell_color(e_index[0]+1, e_index[1]) == me.get_color()){
            res = 1;
            down.index[0] = e_index[0]+1;
            down.index[1] = e_index[1];
            down.num = board->get_capacity(e_index[0]+1, e_index[1]) - board->get_orbs_num(e_index[0]+1, e_index[1]);
        }
    }
    if(e_index[1]-1 > 0){
        if(board->get_cell_color(e_index[0], e_index[1]-1) == me.get_color()){
            res = 1;
            left.index[0] = e_index[0];
            left.index[1] = e_index[1]-1;
            left.num = board->get_capacity(e_index[0], e_index[1]-1) - board->get_orbs_num(e_index[0], e_index[1]-1);
        }
    }
    if(e_index[0]-1 > 0){
        if(board->get_cell_color(e_index[0]-1, e_index[1]) == me.get_color()){
            res = 1;
            up.index[0] = e_index[0]-1;
            up.index[1] = e_index[1];
            up.num = board->get_capacity(e_index[0]-1, e_index[1]) - board->get_orbs_num(e_index[0]-1, e_index[1]);
        }
    }

    if(res){
        direction min = up.num < down.num ? up : down;
        min = min.num < left.num ? min : left;
        min = min.num < right.num ? min : right;

        me_index[0] = min.index[0];
        me_index[1] = min.index[1];
    }

    return res;
}

bool find_enemy_index(Board* oldb, Board* newb, int* index, int* enemy_index, Player player){
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if(newb->get_orbs_num(i, j) != oldb->get_orbs_num(i, j)){
                enemy_index[0] = i;
                enemy_index[1] = j;
                if(enemy_around(index, enemy_index, oldb, player)){
                    return 1;
                }
            }
        }
    }
    enemy_index[0] = -1;
    enemy_index[1] = -1;

    return 0;
}

bool board_is_full(Board* board){
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if(board->get_orbs_num(i, j) == 0){
                return 0;
            }
        }
    }
    return 1;
}

void select_from_lowest_capacity(int* index, Board* board, Player player){
    int min = 10;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if(board->get_cell_color(i, j) == player.get_color() || board->get_cell_color(i, j) == 'w'){
                if(board->get_orbs_num(i, j) == 0){
                    if(min > board->get_capacity(i, j)){
                        min = board->get_capacity(i, j);
                        index[0] = i; index[1] = j;
                    }
                }
            }
        }
    }
}

void select_from_lowest_state(int* index, Board* board, Player player){
    int min = 10;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if(board->get_cell_color(i, j) == player.get_color()){
                int less = board->get_capacity(i, j) - board->get_orbs_num(i, j);
                if(less < min){
                    min = less;
                    index[0] = i; index[1] = j;
                }
            }
        }
    }
}

struct dir{
    int count;
    int arr_index[2];
};

bool select_dangerous_pt(int* index, Board* board, Player player){
    dir max;
    max.count = 0;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            int dangerous_num = 0;
            if(board->get_cell_color(i, j) == player.get_color()){
                if(i+1 < ROW && board->get_cell_color(i+1, j) != player.get_color()){
                    int enemy_less = board->get_capacity(i+1, j) - board->get_orbs_num(i+1, j);
                    int my_less = board->get_capacity(i, j) - board->get_orbs_num(i, j);
                    if(my_less == 1 && enemy_less == 1){
                        dangerous_num += 1;
                    }
                }
                if(i-1 > 0 && board->get_cell_color(i-1, j) != player.get_color()){
                    int enemy_less = board->get_capacity(i-1, j) - board->get_orbs_num(i-1, j);
                    int my_less = board->get_capacity(i, j) - board->get_orbs_num(i, j);
                    if(my_less == 1 && enemy_less == 1){
                        dangerous_num += 1;
                    }
                }
                if(j+1 < COL && board->get_cell_color(i, j+1) != player.get_color()){
                    int enemy_less = board->get_capacity(i, j+1) - board->get_orbs_num(i, j+1);
                    int my_less = board->get_capacity(i, j) - board->get_orbs_num(i, j);
                    if(my_less == 1 && enemy_less == 1){
                        dangerous_num += 1;
                    }
                }
                if(j-1 > 0 && board->get_cell_color(i, j-1) != player.get_color()){
                    int enemy_less = board->get_capacity(i, j-1) - board->get_orbs_num(i, j-1);
                    int my_less = board->get_capacity(i, j) - board->get_orbs_num(i, j);
                    if(my_less == 1 && enemy_less == 1){
                        dangerous_num += 1;
                    }
                }
                if(dangerous_num > max.count){
                    max.arr_index[0] = i;
                    max.arr_index[1] = j;
                    max.count = dangerous_num;
                }
            }
        }
    }
    if(max.count > 0){
        index[0] = max.arr_index[0];
        index[1] = max.arr_index[1];
        return 1;
    }
    else{
        return 0;
    }
}

void algorithm_A(Board board, Player player, int index[]){
    //index[0]=0;
    //index[1]=0;
    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    static Board *newb = new Board;
    
    int enemy_index[2];
    
    if(find_enemy_index(&board, newb, index, enemy_index, player)){
        delete(newb);
        newb = set_board(&board, newb, index, player);
        return;
    }
    
    if(select_dangerous_pt(index, &board, player)){
        delete(newb);
        newb = set_board(&board, newb, index, player);
        return;
    }

    if(board_is_full(&board)){
        select_from_lowest_state(index, &board, player);
    }
    else{
        select_from_lowest_capacity(index, &board, player);
    }
    delete(newb);
    newb = set_board(&board, newb, index, player);
    
}