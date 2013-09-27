/*    Functions to make SDL less painful*/#include <stdio.h>#include <stdlib.h>#include <time.h>#include <SDL.h>#include "function.h"void startSDL(){    if (SDL_Init(SDL_INIT_EVERYTHING)<0)    {        printf("Oh no! SDL could not start! Error; %s\n", SDL_GetError());        exit(1);    }    //Create the window    if((window = SDL_CreateWindow( "Squary: Beginning of Paranoia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN )) == NULL )    {        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );        exit(1);    }    //Black magic with screen and window    windowSurface = SDL_GetWindowSurface(window);}void quitSDL(){    //Deallocate surfaces    /* I feel like I don't really need to do this and it will just attract errors    for (i=0; i<IMAGES;i++)    {        SDL_FreeSurface(image[i]);        image[i] = NULL;    }    */	//Destroy window	SDL_DestroyWindow(window);	window = NULL;	SDL_FreeSurface(windowSurface);	windowSurface = NULL;	//Quit SDL subsystems	SDL_Quit();}//One day I'll upgrade to using textures and PNGs, when I fully understand the implicationsSDL_Surface* loadBMP(char* filename){    SDL_Surface* finalSurface = NULL;    SDL_Surface* temporarySurface = NULL;    //Load BMP and check for error	if((temporarySurface = SDL_LoadBMP(filename)) == NULL )	{		printf( "Tch! The .bmp %s could not be loaded! Error; %s\n", filename, SDL_GetError());        exit(1);    }    if ((finalSurface = SDL_ConvertSurface(temporarySurface, windowSurface->format, NULL))==NULL)    {        printf("Nope! Converting %s didn't work! Error; %s", filename, SDL_GetError());        exit(1);    }    SDL_FreeSurface(temporarySurface);    return finalSurface;}//I might use this if it actually gets messy enoughvoid moveRectangle(SDL_Rect rectangle, int incrementY, int incrementX){    rectangle.x = rectangle.x + incrementX;    rectangle.y = rectangle.y + incrementY;
    printf("Move!\n");}

void moveOpponents(struct Opponent opponent[], int number)
{
    printf("In moveOppenent\n");
    for (i=0; i<number; i++)
    {
        if (opponent[i].status == ON)
        {
            opponent[i].square.x += 20;
            opponent[i].square.y += 20;
            if (opponent[i].square.x>=630)
            {
                opponent[i].square.x = 0;
            }
            if (opponent[i].square.x < 0)
            {
                opponent[i].square.x = 630 + opponent[i].square.x;
            }
            if (opponent[i].square.y< 0)
            {
                opponent[i].square.y = 470 + opponent[i].square.y;
            }
            if (opponent[i].square.y>=470)
            {
                opponent[i].square.y = 0;
            }
        }
    }
}
void initWhites(struct Opponent opponent[], int number){
    printf("Start of initWhites()");    //srand((unsigned int)time(0));	for (i=0; i<number; i++)	{
		opponent[i].square.w = 20;
		opponent[i].square.h = 20;
		opponent[i].square.x = rand()%620;
		opponent[i].square.y = rand()%460;
		opponent[i].status = ON;	}}