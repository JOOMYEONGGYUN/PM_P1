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

static int count = 0;

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
    page[id1] = page1;
    for(int i = 0; i < h1; i++){
        for(int j = 0; j < w1; j++){
            board[x1 + j + width * i] = c1;
        }
    }
    array1[count] = id1; 
    array2[id1] = count;
    count++;
    print_board();
}

void Board::delete_page(int id) {
    for(int i = count; i >= array2[id]; i--){
        page_save[array1[i]] = page[array1[i]];//다른 페이지에 복사
        Page page_temp(array1[i]);
        page[array1[i]] = page_temp;//초기화
    }

    array2[id] = 0;
    count--; // delete 대상 page의 array2 초기화 및 count-1

    for(int i = array2[id]; i <= count; i++){
        array1[i] = page_save[array1[i+1]].getid();
        array2[array1[i]]--;
    }// array1 다시 채우기 및 array2 1씩 줄이기 

    for(int i = array2[id]; i <= count; i++){
        page[array1[i]] = page_save[array1[i]];
    }// page 다시 채우기

    for(int a = array2[id]; a <= count; a++){
        for(int i = 0; i < page[array1[a]].geth(); i++){
            for(int j = 0; j < page[array1[a]].getw(); j++){
                board[page[array1[a]].getx() + j + width * i] = page[array1[a]].getc();
            }
        }
    }// board 다시 채우기
    print_board();
}

void Board::modify_content(int id, char content) {
   page[id].setc(content);
   for(int a = array2[id]; a <= count; a++){
        for(int i = 0; i < page[array1[a]].geth(); i++){
            for(int j = 0; j < page[array1[a]].getw(); j++){
                board[page[array1[a]].getx() + j + width * i] = page[array1[a]].getc();
            }
        }
    }
    print_board();
}

void Board::modify_position(int id, int x, int y) {
   page[id].setx(x);
   page[id].sety(y);
   for(int a = array2[id]; a <= count; a++){
        for(int i = 0; i < page[array1[a]].geth(); i++){
            for(int j = 0; j < page[array1[a]].getw(); j++){
                board[page[array1[a]].getx() + j + width * i] = page[array1[a]].getc();
            }
        }
    }
    print_board();
}

