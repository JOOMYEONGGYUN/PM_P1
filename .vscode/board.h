#include <fstream>
#include "page.h"
#include <vector>
#include <algorithm>

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
        
        void remove_pages(int id); 
        void return_pages();
        void insert_only(Page inserted); 
        

    private:
        int num_jobs, width, height, insert_count=0; 
        ofstream& output; 
        char* board; 
        Page* pagetrack; 
        std::vector<int> turn_back;
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
    while(pagetrack[insert_count].getid() != -1 ){ 
        insert_count++;
    }
    pagetrack[insert_count-1] = Page(x1, y1, width, height, id1, c1);
    pagetrack[insert_count-1].setboard(board); 

    for (int current_x=x1; current_x<x1+width; current_x++)
    {
        for (int current_y=y1; current_y<y1+height; current_y++)
        {   

            if (board[current_y*this->width + current_x] != ' ') // content를 update하기 전에 이미 값이 있었다면
            {
                for(int p=0; p<insert_count; p++)
                {
                    if(pagetrack[p].is_above(pagetrack[insert_count])) // 지금까지 insert된 page를 모두 찾아와 insert 하려는 page와 겹치는지 확인
                    {
                        pagetrack[p].abovepage(pagetrack[insert_count].getid());   // 겹친다면 아래에 있는 page의 above 벡터에 insert된 page id를 push_back()
                        sort(pagetrack[p].getabove().begin(), pagetrack[p].getabove().end());
                    }
                    
                }
            }
            board[current_y * this->width + current_x] = (char)content; // 모두 기록한 뒤 insert 진행
            
        }
    }
    print_board();
}

void Board::delete_page(int id) {
    remove_pages(id);
    return_pages();
}

void Board::modify_content(int id, char content) {
    remove_pages(id);
    int i = 0;
    while( pagetrack[i].getid() != id){
        i++;
    }
    pagetrack[i].setcontent((int)content);
    insert_only(pagetrack[i]);
    print_board();
    return_pages()
}

void Board::modify_position(int id, int x, int y) {
}

bool Board::isOn(Page page1, Page page2){
    int x1 = page1.getx();
    int y1 = page1.gety();
    int h1 = page1.geth();
    int w1 = page1.getw();

}

