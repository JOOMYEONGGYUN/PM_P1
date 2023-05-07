class Page {
    public:
        Page(int x1, int y1, int w1, int h1, int id1, char c1);
        Page(int id1);
        int getx(){return x;}
        int gety(){return y;}
        int getw(){return width;}
        int geth(){return height;}
        int getid(){return id;}
        char getc(){return content;}
        void setx(int x1){x=x1;}
        void sety(int y1){y=y1;}
        void setw(int w1){width=w1;}
        void seth(int h1){height=h1;}
        void setc(char c1){content=c1;}
    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content; 
};

Page::Page(int x1, int y1, int w1, int h1, int id1, char c1){
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




