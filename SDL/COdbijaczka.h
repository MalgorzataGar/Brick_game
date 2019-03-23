#pragma once
#include "CObiekt.h"
class COdbijaczka :
	public CObiekt
{
	SDL_Texture *odbijaczka;
public:
	COdbijaczka(SDL_Renderer *r);
	~COdbijaczka();
	void aktualizuj(float delta);
	void render(float delta);
	inline void ustaw_x(float x1) { x = x1; };
};

