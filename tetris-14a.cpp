#include "wincursor.h"
#define nSize	4		// How many squares are there in a tetromino
#define nType   7               // How many tetromino types
#define nLeftBorder	9
#define nRightBorder	23
#define nBottomBorder   21
#define nTopBorder      1

enum Movement { UP, ROTATE = 0, DOWN, LEFT, RIGHT };

Screen myScreen;

#include "tetris.h"

void init_game();
void game_over();

int main()
{
    int i, x0;
    int c;
    init_game();
    int next_i = 5;

    while (true)
    {
        x0 = (rand() % (nRightBorder - nLeftBorder -1 -3 -2) )+ 2;
        i = next_i;
        next_i = rand() % nType;
        CTetromino b(next_i, nRightBorder + 6, 4);
        CTetromino a(i, i+2);
        b.Draw();
        if (a.detect_confliction())     // a newly constructed tetromino
            break;                      // conflicts, then game over
        do {
            myScreen.redraw();
            c=myScreen.key();
            switch (c)
            {
                case 'q':
                    game_over();
                    return 0;
                    break;
                case KEY_LEFT:
                case 'h':
                    a.Move(LEFT);
                    break;
                case KEY_RIGHT:
                case 'l':
                    a.Move(RIGHT);
                    break;
                case KEY_UP:
                case 'k':
                    a.Move(ROTATE);
                    break;
                case ' ':
                case KEY_DOWN:
                case 'j':
                    while( a.Move(DOWN) )
                    {
                        myScreen.redraw();
                        Sleep(60);
                    }
                    break;
            }
        } while (a.Move(DOWN));
        b.Erase();
    }

    myScreen.redraw();
    game_over();
    return 0;
}

void init_game()
{
    int y0, x0;
    myScreen.setTimeOut(300);
    String star("**");

    for (y0=nTopBorder + 1; y0< nBottomBorder; y0++)
    {
        star.show(y0, nLeftBorder * 2);
        star.show(y0, nRightBorder * 2);
    }

    for (x0=(nLeftBorder + 1) * 2; x0<nRightBorder * 2; x0+=2)
    {
        star.show(nBottomBorder, x0);
    }
    myScreen.redraw();
}

void game_over()
{
    String msg("Game Over!", nTopBorder + 1, nRightBorder*2 + 2);
    msg.show();
    myScreen.redraw();
    myScreen.pause(2);
}
