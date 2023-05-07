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

    private:
        int num_jobs, width, height; 
        ofstream& output; 
        char* board; 
        Page* page[];
};


Board::Board(int num_jobs, int width, int height, ofstream& output_stream): output(output_stream) {
    this->width = width;
    this->height = height;
    this->num_jobs = num_jobs;

    board = new char[width*height];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h*width + w] = ' ';
        }
    }

}

Board::~Board() {
    delete board;
    
}


void Board::print_board() {
    int h, w;
    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
    
    for (h = 0; h < height; h++) {
        output << "| ";
        for (w = 0; w < width; w++) {
            output << board[h*width + w] << " ";
        }
        output << "| " << endl;
    }

    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
    output << ">> (" << job_idx <<") ";
    switch(job_type) {
        
        case 'i':
            output << "Insert ";
            break;
        case 'd':
            output << "Delete ";
            break;
        case 'm':
            output << "Modify ";
            break;
    }

    output << id << endl;
}


void Board::insert_page(int x1, int y1, int w1, int h1, int id1, char c1) {
    Page page1(x1,y1,w1,h1,id1,c1);
    page[id1] = &page1;
    for(int i = 0; i < h1; i++){
        for(int j = 0; j < w1; j++){
            board[x1+j+width*i] = c1;
        }
    }
}

void Board::delete_page(int id) {
    
}

void Board::modify_content(int id, char content) {
   

}
void Board::modify_position(int id, int x, int y) {
   
    
}
