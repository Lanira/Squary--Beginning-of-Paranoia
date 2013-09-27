/*
    Header for function.c, contains some function definitions and variables
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#define WIDTH 640
#define HEIGHT 480
#define IMAGES 3
#define WHITES 10

extern SDL_Window* window;
extern SDL_Surface* windowSurface;
extern SDL_Surface* image[];
extern char* filename[];
extern int i;

/*Enumerations*/

//For the state machine responsive of game flow
enum gameState {
    SPLASHSCREEN,
    PLAYGAME, //might create a switch within its loop for levels or stages
    GAMEOVER,
    EXIT
};


enum whitesState {
    OFF, //un-intialized
    ON, //initialized
    DEAD, //was killed
};

/*Structures*/
struct Opponent {
    SDL_Rect square;
    int status;
};

//Returns a pointer to an array of surfaces, requires an array of surfaces filenames and length of that array
SDL_Surface* loadBMP(char* filename);

//My lazy way to start SDL, a window and associates a surface to it. You need to use "window" and "windowSurface" however.
void startSDL();
void quitSDL();

//basic function to move a square or a rectangle
void moveRect(SDL_Rect rectangle, int incrementY, int incrementX);

//Fills an array of opponents with random positions
void initWhites(struct Opponent opponent[], int number);

void moveOpponents(struct Opponent opponent[], int number);
