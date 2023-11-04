
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameIsOver;
const int width = 30;
const int height = 20;
int nTail;
int tailX[100], tailY[100];
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, UP, RIGHT, DOWN};
eDirection dir;

void setupGame()
{
    gameIsOver = false;
    nTail = 0;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitX = rand() % (width - 1);
    fruitY = rand() % (height - 1);
    score = 0;
}

void draw()
{
    system("cls");

    for (int i{}; i < width; ++i)
        cout << '#';
 
    cout << endl;

    for (int i{}; i < height; ++i)
    {
        for (int j{}; j < width; ++j)
        {
            if (j == 0 || j == width - 1)
                cout << '#';
            else if (i == y && j == x)
                cout << '0';
            else if (i == fruitY && j == fruitX)
                cout << 'F';
            else {
                bool print = false;
                for (int k{}; k < nTail; ++k)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        print = true;
                        cout << 'o';
                    }
                        
                }
                if (!print) 
                    cout << " ";
            }
                
        }
        cout << endl;
    }


    for (int i{}; i < width; ++i)
         cout << '#';
    cout << endl;
}

void handleInput()
{
    if (_kbhit())
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            gameIsOver = true;
            cout << "finish";
            break;
        default: 
            break;
        }
}

void logic()
{

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; ++i)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;
        
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case UP:
        y--;
        break;
    case RIGHT:
        x++;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    for (int i{}; i < nTail; ++i)
    {
        if (x == tailX[i] && y == tailY[i])
            gameIsOver = true;
    }

    if (x == 0 || x == width - 1 || y == -1 || y == height) {

    }
    if (x == 0)
        x = width - 2;

    if (x == width - 1)
        x = 1;

    if (y == -1)
        y = height - 1;

    if (y == height)
        y = 0;
        

    if ( y == fruitY && x == fruitX) {
        score++;
        nTail++;

        fruitX = rand() % (width - 1);
        if (fruitX == 0)
            fruitX = 1;

        fruitY = rand() % (height - 1);
        if (fruitY == 0)
            fruitY = 1;

        for (int i{}; i < nTail; ++i)
        {
            while (fruitX == x || fruitX == tailX[i] || fruitY == y || fruitY == tailY[i] || fruitX == 0 || fruitY == 0)
            {
                fruitX = rand() % (width - 1);
                fruitY = rand() % (height - 1);
            }
        }
    }
        
}

int main()
{
    setupGame();

    while (!gameIsOver)
    {
        draw();
        handleInput();
        logic();
        Sleep(100);
    }
    cout << "Your score is: " << score << '\n';
           
    return 0;


}
