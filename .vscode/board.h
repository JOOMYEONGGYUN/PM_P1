#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "page.h"

using std::endl;
using std::ofstream;
using std::vector;
using std::map;
using std::find;
using std::remove;

class Board {
    public:
        Board(int num_jobs, int width, int height, ofstream& output_stream);
        ~Board();
        void print_board();
        void print_job(int job_idx, char job_type, int id);
        //job functions
        void insert_page(int x, int y, int w, int h, int id, char content);
        void delete_page(int id);
        void modify_content(int id, char content);
        void modify_position(int id, int x, int y);
        void set_board(int x, int y, int w, int h, char cont); // board set
        void board_insert(int x, int y, int w, int h, int id); //insert id to boardlst
        void board_delete(int x, int y, int w, int h, int id); //delete id from boardlst
        void delete_seq(int id, int idcop); //page를 순차적으로 삭제
        int findminidx(int id); //해당 page 위의 page 중에 가장 index가 작은 것 return
        void insert_seq(int id, int idcop); // page를 순차적으로 insert
        int findmaxidx(int id); // 해당 page 위의 page 중 가장 index 큰 것 return

    private:
        int num_jobs, width, height;
        ofstream& output; 
        char* board;
        map <int, Page> pagemap; //page의 id와 page를 저장
        vector<int>* boardlst; //겹치는 content의 index를 boardlst에 넣음
};


Board::Board(int num_jobs, int width, int height, ofstream& output_stream): output(output_stream) {
    this->width = width;
    this->height = height;
    this->num_jobs = num_jobs;

    board = new char[width*height];
    boardlst = new vector<int>[width * height];
    Page def = Page(' ');
    pagemap.insert({-1, def});

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h*width + w] = ' ';
            boardlst[h*width + w].push_back(-1);
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

void Board::insert_page(int x, int y, int w, int h, int id, char c){
    Page newpage = Page(x, y, w, h, id, c);
    pagemap.insert({id, newpage});
    board_insert(x, y, w, h, id);
    set_board(x, y, w, h, c);
    print_board();
}

void Board::delete_page(int id){
    int save = id;
    delete_seq(id, save);
    insert_seq(id, save);
    board_delete(pagemap[id].getx(), pagemap[id].gety(), pagemap[id].getw(), pagemap[id].geth(), id);
    pagemap.erase(id); 
}

void Board::modify_content(int id, char content){
   int save = id;
   delete_seq(id, save); // 페이지 순차적 삭제
   int x = pagemap[id].getx();
   int y = pagemap[id].gety();
   int w1 = pagemap[id].getw();
   int h1 = pagemap[id].geth();
   Page modpage = Page(x, y, w1, h1, id, content);
   pagemap[id] = modpage; // modify content
   for (int h = y; h < y + h1; h++){
        for (int w = x; w < x + w1; w++){
            board[h * width + w] = content;
        }
    }
    print_board();
    insert_seq(id, save); //페이지 순차적 삽입
}

void Board::modify_position(int id, int x, int y) {
   int idcop = id;
   delete_seq(id, idcop); // 페이지 순차적 삭제
   int oldx = pagemap[id].getx();
   int oldy = pagemap[id].gety();
   int w1 = pagemap[id].getw();
   int h1 = pagemap[id].geth();
   char cont = pagemap[id].getc();
   for (int h = y; h < y + h1; h++){
        for (int w = x; w < x + w1; w++){
            int k = h * width + w;
            for (auto itr = boardlst[k].begin(); itr != boardlst[k].end(); itr++){
                if (pagemap[boardlst[k][itr - boardlst[k].begin()]].getc() == board[k]){
                    boardlst[k].insert(itr + 1, id); // boardlst의 새로운 position에 id 삽입
                    break;
                }
            }
            board[k] = cont; // board에 새로운 position 입력
        }
    }
    print_board();
    insert_seq(id, idcop);
    for (int h = oldy; h < oldy + h1; h++){
        for (int w = oldx; w < oldx + w1; w++){
            int k = h * width + w;
            boardlst[k].erase(remove(boardlst[k].begin(), boardlst[k].end(), id)); // delete old positions
        }
    }
    Page modpage = Page(x, y, w1, h1, id, cont);
    pagemap[id] = modpage; // modify content
}

void Board::set_board(int x, int y, int w1, int h1, char cont){
    for (int h = y; h < y + h1; h++) {
        for (int w = x; w < x + w1; w++) {
            board[h*width + w] = cont;
        }
    }
}

void Board::board_insert(int x, int y, int w1, int h1, int id){
    for (int h = y; h < y + h1; h++){
        for (int w = x; w < x + w1; w++){
            boardlst[h * width + w].push_back(id);
        }
    }
}

void Board::board_delete(int x, int y, int w1, int h1, int id){
    for (int h = y; h < y + h1; h++){
        for (int w = x; w < x + w1; w++){
            int k = h * width + w;
            boardlst[k].erase(find(boardlst[k].begin(), boardlst[k].end(), id));
        }
    }
}

void Board::delete_seq(int id, int idcop){
    if (findminidx(id) == 32768){
        for (int h = pagemap[id].gety(); h < pagemap[id].gety() + pagemap[id].geth(); h++) {
            for (int w = pagemap[id].getx(); w < pagemap[id].getx() + pagemap[id].getw(); w++) {
                int j = h * width + w;
                board[j] = pagemap[boardlst[j][find(boardlst[j].begin(), boardlst[j].end(), id) - boardlst[j].begin() - 1]].getc();
            }
        }
        print_board();
    } 
    else{
        delete_seq(findminidx(id), idcop);
        delete_seq(id, idcop);
    }
}

int Board::findminidx(int id){
    int idmin = 32768;
    for (int h = pagemap[id].gety(); h < pagemap[id].gety() + pagemap[id].geth(); h++){
        for (int w = pagemap[id].getx(); w < pagemap[id].getx() + pagemap[id].getw(); w++){
            int k = h * width + w;
            if (board[k] != pagemap[id].getc()){
                int j = boardlst[k][find(boardlst[k].begin(), boardlst[k].end(), id) - boardlst[k].begin() + 1];
                if (j < idmin){
                    idmin = j;
                }
            }
        }
    }
    return idmin;
}

void Board::insert_seq(int id, int idcop){
    if (findmaxidx(id) != -1){ 
        if (id != idcop){ 
            set_board(pagemap[id].getx(), pagemap[id].gety(), pagemap[id].getw(), pagemap[id].geth(), pagemap[id].getc());
            print_board();
            }
        insert_seq(findmaxidx(id), idcop);
        insert_seq(id, idcop);
    }
    else{
        if (id != idcop){
            for (int h = pagemap[id].gety(); h < pagemap[id].gety() + pagemap[id].geth(); h++){
                for (int w = pagemap[id].getx(); w < pagemap[id].getx() + pagemap[id].getw(); w++){
                    if (board[h * width + w] == pagemap[id].getc()){
                        return;
                    }
                }
            }
        set_board(pagemap[id].getx(), pagemap[id].gety(), pagemap[id].getw(), pagemap[id].geth(), pagemap[id].getc());
        print_board();
    }
}
}

int Board::findmaxidx(int id){
    int idmax = -1;
    vector<int> idcand;
    for (int h = pagemap[id].gety(); h < pagemap[id].gety() + pagemap[id].geth(); h++){
        for (int w = pagemap[id].getx(); w < pagemap[id].getx() + pagemap[id].getw(); w++){
            int k = h * width + w;
            int j = -1;
            for (int itr = boardlst[k].size() - 1; itr >=0; itr--){
                if (boardlst[k][itr] == id){
                    j = itr; 
                    break;
                }
            }
            if (j != boardlst[k].size() - 1){ 
                if (idcand.size() != 0){
                    if (find(idcand.begin(), idcand.end(), boardlst[k][j + 1]) == idcand.end()){
                        idcand.push_back(boardlst[k][j + 1]); 
                    }
                } 
                else{
                    idcand.push_back(boardlst[k][j + 1]);
                }
                for (auto elem : idcand){
                    if (board[k] == pagemap[elem].getc()){
                        idcand.erase(remove(idcand.begin(), idcand.end(), elem)); 
                    }
                }
            }
        }
    }
    for (auto elem : idcand){
        if (elem > idmax){
            idmax = elem;
        }
    }
    return idmax; 
}