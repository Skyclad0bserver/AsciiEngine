#pragma once
#include <windows.h>
#include <vector>
#include <string>


int GetConsoleCols() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return columns;
}
int GetConsoleRows() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return rows;
}

void vec2dINIT(int cheight, int cwidth, std::vector<std::vector<int>>& vector) {
    std::vector<int> row(cwidth, 0);
    std::vector<std::vector<int>> point(cheight, row);
    vector = point;
}
void vec2dTextINIT(int cheight, int cwidth, std::vector<std::vector<std::string>>& vector) {
    std::vector<std::string> row(cwidth, "");
    std::vector<std::vector<std::string>> point(cheight, row);
    vector = point;
}

class Screen {
public:
    //Screen wrapping, yea or nay.
    bool wrap = false;
    //Pixel array
    std::vector<std::vector<int>> point;
    //Text array
    std::vector<std::vector<std::string>> text;
    void init() {
        //Init "Pixel" array. Vector of vectors, needs to be initialized i think.
        vec2dINIT(cwidth, cheight, point);
        //Init Text array. Seperate array for storing text than storing pixels, as pixels use integers instead of chars to chose what they are.
        //Uses a different init function as well, though its practically the same thing just for a vector of vector of strings.
        vec2dTextINIT(cwidth, cheight, text);
    }
    

    int height() {
        return cheight;
    }
    int width() {
        return cwidth;
    }

private:
    //Should pretty much always be Console Cols/Rows, and it is by default.
    const int cheight = GetConsoleCols();
    const int cwidth = GetConsoleRows();

};

void placePoint(Screen& screen, int a, int b, int character) {
    // I have no clue why these are reversed, but everything works when they are
    int x = b;
    int y = a;
    if (x >= 0 && x < screen.width() && y >= 0 && y < screen.height()) {
        screen.point[x][y] = character;
    }
}
void placeText(Screen& screen, int a, int b, std::string str) {
    // I have no clue why these are reversed, but everything works when they are
    int x = b;
    int y = a;
    if (x >= 0 && x < screen.width() && y >= 0 && y < screen.height()) {
        screen.text[x][y] = str;
    }
}

std::string renderScreen(Screen screen) {
    int x;
    int y;
    int count = 0;
    std::string str;

    for (x = 0; x < screen.width(); x++) {
        for (y = 0; y < screen.height(); y++) {

            //Run through text array
            if (screen.text[x][y] != "") {
                for (int i = 0; i < screen.text[x][y].length(); i++) {
                    str += screen.text[x][y][i];
                    screen.point[x][y + i] = 22;
                }
            }


            //Run through pixel array
            switch (screen.point[x][y]) {

            case 0:
                str += " ";
                break;
            case 1:
                str += "#";
                break;
            case 2:
                str += "-";
                break;
            case 3:
                str += "<";
                break;
            case 4:
                str += ">";
                break;
            case 5:
                str += ".";
                break;
            case 6:
                str += "?";
                break;
            case 7:
                str += "+";
                break;
            case 8:
                str += ":";
                break;
            case 9:
                str += "|";
                break;
            //Text case. If there is text in the text array, and nothing in the pixel array, do nothing. Text will always be on top.
            case 22:
                str + "";
                break;
               
            }
            
            count++;
        }
        if (count == screen.width()) {
            str += "\n";
        }
    }
    return str;
}

int sgn(double v) {
    return (v < 0) ? -1 : ((v > 0) ? 1 : 0);
}

//Shamelessly stolen from stackoverflow
void drawLine(Screen& screen, int x1, int y1, int x2, int y2, int character)
{
    int dx = x2 - x1;      /* the horizontal distance of the line */
    int dy = y2 - y1;      /* the vertical distance of the line */
    int dxabs = abs(dx);
    int dyabs = abs(dy);
    int sdx = sgn(dx);
    int sdy = sgn(dy);
    int x = dyabs >> 1;
    int y = dxabs >> 1;
    int px = x1;
    int py = y1;

    if (dxabs >= dyabs) /* the line is more horizontal than vertical */
    {
        for (int i = 0; i < dxabs; i++)
        {
            y += dyabs;
            if (y >= dxabs)
            {
                y -= dxabs;
                py += sdy;
            }
            px += sdx;
            placePoint(screen, px, py, character);
        }
    }
    else /* the line is more vertical than horizontal */
    {
        for (int i = 0; i < dyabs; i++)
        {
            x += dxabs;
            if (x >= dyabs)
            {
                x -= dyabs;
                px += sdx;
            }
            py += sdy;
            placePoint(screen, px, py, character);
        }
    }
}

void rect(Screen& screen, int x1, int y1, int x2, int y2, int character, int fill = 0) {
    placePoint(screen, x1, y1, character);
    drawLine(screen, x1, y1, x1, y2, character);
    drawLine(screen, x1, y1, x2, y1, character);
    drawLine(screen, x2, y1, x2, y2, character);
    drawLine(screen, x2, y2, x1, y2, character);
    if (fill != 0) {
        for (int i = 0; i < abs(y2 - y1); i++) {
            drawLine(screen, x1, y1 + i, x2, y1 + i, character);
        }
    }
}
//Seperate square function since characters are not square making it slightly annoying to make squares with the rect() function.
void square(Screen& screen, int x1, int y1, int l, int character, int fill = 0) {
    placePoint(screen, x1, y1, character);
    drawLine(screen, x1, y1, x1, y1+l, character);
    drawLine(screen, x1, y1, x1+l*2, y1, character);
    drawLine(screen, x1+l*2, y1, x1+l*2, y1+l, character);
    drawLine(screen, x1+l*2, y1+l, x1, y1+l, character);
    if (fill != 0) {
        for (int i = 0; i < abs((y1+l) - y1); i++) {
            drawLine(screen, x1, y1 + i, x1+l*2, y1 + i, character);
        }
    }
}

