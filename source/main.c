//My atttempt to have a moving square
//This project needs to be compiled with SDL 2, with the headers in the right place too
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "function.h"

#define INC 2 //increment for the square's movement

//Global variables
enum gameState {
    SPLASHSCREEN,
    PLAYGAME,
    GAMEOVER,
    EXIT
};

SDL_Window* window;
SDL_Surface* windowSurface;
SDL_Surface* image[FILES];
char* filename[FILES] = {"../ressources/background.bmp", "../ressources/blacksquare.bmp", "../ressources/whitesquare.bmp" };

int i; //my favorite counter variable

//File variables
Uint8 * keyboardKeys;
SDL_Rect square = {(WIDTH/2-20), (HEIGHT/2-20), 20, 20};
SDL_Rect target = {100, 100, 20, 20};
char gameMode = SPLASHSCREEN;
SDL_Event event;
int score;


/*
    Functions prototype
*/
void mainLoop(void);
void menu(void);
void gameOver(int score);

int main(int argc, char* args[])
{
    startSDL();

    for (i=0; i<FILES; i++)
    {
        image[i] = loadBMP(filename[i]);
    }
    bool exit = false;
    while (!exit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (gameMode)
            {
            case SPLASHSCREEN:
                menu();
                break;
            case PLAYGAME:
                mainLoop();
                break;
            case GAMEOVER:
                gameOver(score);
                break;
            case EXIT:
                exit = true; //I wanted to push an SDL_QUIT event ;_;
                break;
            default:
                printf("Wut?! What the hell man?");
            }
            if (event.type == SDL_QUIT)
            {
                exit = true;
            }
        }
    }

    quitSDL();
    return 0;
}

void mainLoop(void)
{
    // initial render
    SDL_BlitSurface(image[0], NULL, windowSurface, NULL);
    SDL_BlitSurface(image[1], NULL, windowSurface, &square);
    SDL_UpdateWindowSurface(window);

    if (event.type == SDL_KEYDOWN) //This is a mess, and will be solved soon
    {
        SDL_PollEvent(&event);
        while (event.type != SDL_KEYUP)
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            else
            {
                SDL_PollEvent(&event);
                SDL_PumpEvents();
                keyboardKeys = SDL_GetKeyboardState(NULL);

                if ((keyboardKeys[SDL_SCANCODE_UP] && !keyboardKeys[SDL_SCANCODE_DOWN])
                    || (keyboardKeys[SDL_SCANCODE_W] && !keyboardKeys[SDL_SCANCODE_S]))
                {
                    square.y -= INC ;
                    if (square.y < 0)
                    {
                        square.y = 470 + square.y;
                    }
                }
                if ((keyboardKeys[SDL_SCANCODE_DOWN] && !keyboardKeys[SDL_SCANCODE_UP])
                    || (keyboardKeys[SDL_SCANCODE_S] && !keyboardKeys[SDL_SCANCODE_W]))
                {
                    square.y = square.y + INC;
                    if (square.y>=470)
                    {
                        square.y = 0;
                    }

                }
                if ((keyboardKeys[SDL_SCANCODE_RIGHT] && !keyboardKeys[SDL_SCANCODE_LEFT])
                    || (keyboardKeys[SDL_SCANCODE_D] && !keyboardKeys[SDL_SCANCODE_A]))
                {
                    square.x = square.x + INC;
                    if (square.x>=630)
                    {
                        square.x = 0;
                    }
                }
                if ((keyboardKeys[SDL_SCANCODE_LEFT] && !keyboardKeys[SDL_SCANCODE_RIGHT])
                    || (keyboardKeys[SDL_SCANCODE_A] && !keyboardKeys[SDL_SCANCODE_D]))
                {
                    square.x -= INC;
                    if (square.x < 0)
                    {
                        square.x = 630 + square.x;
                    }
                }
/* Leftovers from trying to detect a collision, needs to be improved
                if ((square.x > target.x) && (square.x < (target.x+20))
                    && (square.y>target.y) && (square.y<(target.y+20))){
                    score +=1;
                    gameMode = GAMEOVER;
                    break;
                }
*/
/* Old code just waiting to be deleted when I'm sure I don't need it anymore
                else if ((keyboardKeys[SDL_SCANCODE_LEFT] && !keyboardKeys[SDL_SCANCODE_RIGHT])
                    || (keyboardKeys[SDL_SCANCODE_A] && !keyboardKeys[SDL_SCANCODE_D]))
                {
                    square.x -= INC;
                    if (square.x < 0)
                        square.x = 630 + square.x;
                }
                else if ((keyboardKeys[SDL_SCANCODE_RIGHT] && !keyboardKeys[SDL_SCANCODE_LEFT])
                         || (keyboardKeys[SDL_SCANCODE_D] && !keyboardKeys[SDL_SCANCODE_A]))
                {
                    square.x = (square.x + INC) % 630;
                }


                else
                {
                    printf("Screw that! Something else...\n");
                }
    */            //render
                SDL_BlitSurface(image[0], NULL, windowSurface, NULL);
                SDL_BlitSurface(image[1], NULL, windowSurface, &square);
                SDL_UpdateWindowSurface(window);

                printf("Pos: x= %d, y= %d\n", square.x, square.y);
            }
        }
    }
}

void menu(void)
{
    printf("Sup'. I'm the boss (menu).\n");
    gameMode = PLAYGAME;
}

void gameOver(int score)
{
    printf("You lose! your score is %d! Yay!\n", score);
    gameMode = EXIT;
}

//foo
