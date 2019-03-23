#pragma once
#include "CObiekt.h"
#include "CCegla.h"
#include <stdlib.h>
#include <time.h>
class CMur :
	public CObiekt
{
	
	SDL_Texture *bok;
	SDL_Texture *cegla;
	const float dx;
	const float dy;
public:
	CCegla sciana[12][12];//szer wys
	CMur(SDL_Renderer *r);
	~CMur();
	void aktualizuj(float delta);
	inline const float daj_dx() { return dx; };
	inline const float daj_dy() { return dy; };
	void render(float delta);
	void utworz_mur();
	
};

