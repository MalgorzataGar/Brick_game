#include "CObiekt.h"



CObiekt::CObiekt(SDL_Renderer *r)
{
	renderer = r;
	x = 0;
	y = 0;
	wysokosc = 1;
	szerokosc = 1;
}
CObiekt::~CObiekt()
{
}
void CObiekt::aktualizuj(float delta)
{
}
void CObiekt::render(float delta)
{
}
bool CObiekt::kolizja(CObiekt *obiekt)
{
	if ((x + szerokosc > obiekt->daj_x()) && (x < obiekt->daj_x() + obiekt->daj_szerokosc()) &&
		(y + wysokosc > obiekt->daj_y()) && (y < obiekt->daj_y() + obiekt->daj_wysokosc()))
	{
		return true;
	}
	else return false;
}
