#include "page.h"

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