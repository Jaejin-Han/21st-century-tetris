//  Tetromino class definitions

#include "tetromino.hpp"
#include "board.hpp"

const int Tetromino::coords_table[7][4][2] = { 

    { { 0, -1 }, { 0, 0 }, { -1, 0 }, { -1, 1 } },      //type 0            Z-Block
                                                        //       |_|_|_
                                                        //         |_|_| 

    { { 1, -1 }, { 0, -1 }, { 0, 0 }, { 0, 1 } },       //type 1   |_|      J-Block
                                                        //         |_|
                                                        //       |_|_|

    { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } },         //type 3 |_|_|      O-Block
                                                        //       |_|_|

    { { -1, 0 }, { 0, 0 }, { 1, 0 }, { 0, 1 } },        //type 4 |_|_|_|    T-Block
                                                        //         |_|

    { { 0, -1 }, { 0, 0 }, { 1, 0 }, { 1, 1 } },        //type 5            S-Block
                                                        //         |_|_|
                                                        //       |_|_|

    { { 0, -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 } },        //type 6 |_|        I-Block
                                                        //       |_|
                                                        //       |_|
                                                        //       |_|

    { { -1, -1 }, { 0, -1 }, { 0, 0 }, { 0, 1 } }       //type 7 |_|        L-Block
                                                        //       |_|_
                                                        //       |_|_|

};

Tetromino::Tetromino(int new_type) {
    type = new_type;
    free_fall = false;
    speed_up = false;
    status = INACTIVE;
    movement = NONE;
    coords = new int[4][2];

    for (int i = 0; i < 4 ; i++) {
        coords[i][0] = coords_table[type][i][0];
        coords[i][1] = coords_table[type][i][1];
    }
}

void Tetromino::rotate_left() {
    for (int i = 0; i < SIZE; i++) {
        int temp = coords[i][0];
        coords[i][0] = -coords[i][1];
        coords[i][1] = temp;
    }
}

void Tetromino::rotate_right() {
    for (int i = 0; i < SIZE; i++) {
        int temp = coords[i][0];
        coords[i][0] = coords[i][1];
        coords[i][1] = -temp;
    }
}

void Tetromino::get_shadow(Board *board, int shadow_y[]) {

    // Preserve tetromino state 
    int temp_y = y;
    Status temp_status = status;

    while (!has_landed()) {
        for (int i = 0; i < SIZE; i++)
            // Lands on tetromino or bottom of the board 
            if (board->color[get_block_y(i)][get_block_x(i)] != -1 || y >= board->ROWS) {
                lands();
                y--;
                break;
            }
        if (!has_landed())
            y++;
    }

    // Save the position
    for (int i = 0; i < SIZE; i++)
        shadow_y[i] = get_block_y(i); 

    // Return tetromino to initial state
    y = temp_y;
    status = temp_status;
}

