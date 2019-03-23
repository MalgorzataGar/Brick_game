#include "CPilka.h"
#include <math.h>


CPilka::CPilka(SDL_Renderer *r)
	:CObiekt(r), predkosc(550)
{
	SDL_Surface *surface = IMG_Load("mops.png");
	pileczka = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	x = 400;
	y = 560;
	wysokosc = 24;
	szerokosc = 24;

	zmien_kierunek(1, 1);
}
CPilka::~CPilka()
{
	SDL_DestroyTexture(pileczka);
}
void CPilka::aktualizuj(float delta)
{
	x += kierunek_x*delta;
	y += kierunek_y*delta;

}
void CPilka::render(float delta)
{
	SDL_Rect prostokat;
	prostokat.x = (int)(x + 0.5f);
	prostokat.y = (int)(y + 0.5f);
	prostokat.w = szerokosc;
	prostokat.h = wysokosc;
	SDL_RenderCopy(renderer, pileczka, 0, &prostokat);
}
void CPilka::zmien_kierunek(float x1, float y1)
{
	float dlugosc_wektora = sqrt((x1*x1) + (y1*y1));
	kierunek_x = predkosc*(x1 / dlugosc_wektora);
	kierunek_y = predkosc*(y1 / dlugosc_wektora);
	//zdefiniowana predkosc okresla nam jak szybko bd zmieniac sie pozycja pilki
	//wartosci x1 i y1 musza byc porownane ze soba by okreslic w ktorym kierunku jaki %przyrost

}


