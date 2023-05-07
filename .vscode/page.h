class Page {
    public:
        Page(int x1, int y1, int w1, int h1, int id1, int content);
        Page(int id1);
        Page();
        int getx(){return x;}
        int gety(){return y;}
        int getw(){return width;}
        int geth(){return height;}
        int getid(){return id;}
        int getc(){return content;}
        char* getboard(){return board;}
        void setx(int x1){this->x = x1;}
        void sety(int y1){this->y = y1;}
        void setw(int w1){this->width=w1;}
        void seth(int h1){this->height=h1;}
        void setc(int c1){this->content=c1;}
        void setboard(char* board){this->board = board;}
        std::vector<int> getabove(){return above;}
        void abovepage(int above_page);
        bool is_above(Page newpg);

    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id = -1; // unique id for each page
        char content; 
        std::vector<int> above; 
        char* board;
};

Page::Page(int x1, int y1, int w1, int h1, int id1, int c1){
    x = x1;
    y = y1;
    width = w1;
    height = h1;
    id = id1;
    content = c1;
}

Page::Page(int id1){
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    id = id1;
    content = ' ';
}

Page::Page(){}

void Page::abovepage(int above_page){
    this->above.push_back(above_page);
}

bool Page::is_above(Page newpg){
    if( x <= newpg.getx() && newpg.getx() < x+width){
        if(y<=newpg.gety() && newpg.gety()<y+height){
            return 1;
        }
    }
    if( x <= newpg.getx()+newpg.getw() && newpg.getx()+newpg.getw() < x+width){
        if(y<=newpg.gety() && newpg.gety()<y+height){
            return 1;
        }
    }
    if( x <= newpg.getx() && newpg.getx() < x+width){
        if(y<=newpg.gety()+newpg.geth() && newpg.gety()+newpg.geth()<y+height){
            return 1;
        }
    }
    if( x <= newpg.getx()+newpg.getw() && newpg.getx()+newpg.getw() < x+width){
        if(y<=newpg.gety()+newpg.geth() && newpg.gety()+newpg.geth()<y+height){
            return 1;
        }
    }
        return 0;
}

