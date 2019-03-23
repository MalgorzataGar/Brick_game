#include "COdbijaczka.h"



COdbijaczka::COdbijaczka(SDL_Renderer *r)
	:CObiekt(r)
{
	SDL_Surface *powierzchnia = IMG_Load("odbijaczka.png");
	odbijaczka = SDL_CreateTextureFromSurface(renderer, powierzchnia);
	SDL_FreeSurface(powierzchnia);

	szerokosc = 128;
	wysokosc = 32;
	y = 560;
}
COdbijaczka::~COdbijaczka()
{
	SDL_DestroyTexture(odbijaczka);
}
void COdbijaczka::aktualizuj(float delta)
{

}
void COdbijaczka::render(float delta)
{
	SDL_Rect prostokat;
	prostokat.x = (int)(x + 0.5f);
	prostokat.y = (int)(y + 0.5f);
	prostokat.w = szerokosc;
	prostokat.h = wysokosc;
	SDL_RenderCopy(renderer, odbijaczka, 0, &prostokat);

}