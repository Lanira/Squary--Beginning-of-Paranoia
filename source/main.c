//My atttempt to have a moving square
//This project needs to be compiled with SDL 2, with the headers in the right place too
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "function.h"

#define INC 2 //increment for the square's movement

//Global variables
SDL_Window* window;
SDL_Surface* windowSurface;
SDL_Surface* backgroundSurface;
SDL_Surface* image[IMAGES];
char* filename[IMAGES] = {"../ressources/background.bmp", "../ressources/blacksquare.bmp", "../ressources/whitesquare.bmp" };

int i; //my favorite counter variable

//File variables
Uint8 * keyboardKeys;
SDL_Rect square = {(WIDTH/2-20), (HEIGHT/2-20), 20, 20};
char gameMode = SPLASHSCREEN;
SDL_Event event;
int score;
int time;

struct Opponent whites[WHITES]= {};


/*
    Functions prototype
*/
void mainLoop(void);
void menu(void);
void gameOver(int score);

int main(int argc, char* args[])
{
    startSDL();

    for (i=0; i<IMAGES; i++)
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
                printf("It looks like you made a typo while setting the gamemode. That was bound to happen\n");
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
    printf("Before initWhites()\n");
    //Give values to the white squares
    initWhites(whites, WHITES);
    printf("After initWhites() and before inital rendering\n");

    // initial render
    SDL_BlitSurface(image[0], NULL, windowSurface, NULL);
	for (i=0; i<10; i++)
	{
	    printf("Before bliting squares.\n");
		SDL_BlitSurface(image[2], NULL, windowSurface, &(whites[i].square));
	}
    SDL_BlitSurface(image[1], NULL, windowSurface, &square);
    SDL_UpdateWindowSurface(window);

    printf("After rendering and before game loop\n");

    while (1)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
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
                printf("Pos: x= %d, y= %d\n", square.x, square.y);
            }
        }
        //update whites

        printf("Before time\n");
        time = (int)(SDL_GetTicks()%500);
        if (time>250 && time<250)
        {
            moveOpponents(&whites, WHITES);
            printf("Smth\n");
        }


        //renderer
        SDL_BlitSurface(image[0], NULL, windowSurface, NULL);
        for (i=0; i<10; i++)
        {
            if (whites[i].status == ON)
            {
            SDL_BlitSurface(image[2], NULL, windowSurface, &whites[i].square);
            }
        }
        SDL_BlitSurface(image[1], NULL, windowSurface, &square);
        SDL_UpdateWindowSurface(window);

    }
}

void menu(void)
{
    printf("Greetings. I'm the menu.\n"); //Will eventually get replaced by a splashscreen
    gameMode = PLAYGAME;
}

void gameOver(int score)
{
    printf("You lose! Your score is %d! Yay!\n", score);
    gameMode = EXIT;
}

//foo
