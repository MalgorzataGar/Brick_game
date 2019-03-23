#pragma once
#include <SDL.h>
#include <SDL_image.h>
class CObiekt
{
protected:
    float x;
	float y;
	float wysokosc;
    float szerokosc;
	SDL_Renderer *renderer;
public:
	CObiekt(SDL_Renderer *r);
	virtual ~CObiekt();

	inline const float daj_wysokosc() { return wysokosc; };
	inline const float daj_szerokosc() { return szerokosc; };
	inline const float daj_x() { return x; };
	inline const float daj_y() { return y; };

	virtual void aktualizuj(float delta);
	virtual void render(float delta);
	bool kolizja(CObiekt *obiekt);


};

