class Page {
    public:
        Page(int x1, int y1, int w1, int h1, int id1, char c1);
        Page(int id1);
        int getx(int id1){return x;}
        int gety(int id1){return y;}
        int getw(int id1){return width;}
        int geth(int id1){return height;}
        int getid(int id1){return id;}
        char getc(int id1){return content;}
        void setx(int id1, int x1){x=x1;}
        void sety(int id1, int y1){y=y1;}
        void setw(int id1, int w1){width=w1;}
        void seth(int id1, int h1){height=h1;}
        void setc(int id1, char c1){content=c1;}
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
    x = getx(id1);
    y = gety(id1);
    width = getw(id1);
    height = geth(id1);
    content = getc(id1);
}