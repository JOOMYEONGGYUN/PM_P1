#ifndef BOARD_H
#define BOARD_H
#include <fstream>
#include "page.h"

using std::endl;
using std::ofstream;

class Board {
    public:
        Board(int num_jobs, int width, int height, ofstream& output_stream);
        ~Board();

        void print_board();
        void print_job(int job_idx, char job_type, int id);

        //job functions
        void insert_page(int x1, int y1, int w1, int h1, int id1, char c1);
        void delete_page(int id);
        void modify_content(int id, char content);
        void modify_position(int id, int x, int y);
        Page* page;
        Page* page_save;
        int array1[32768], array2[32768];
        

    private:
        int num_jobs, width, height; 
        ofstream& output; 
        char* board; 
};
#endif