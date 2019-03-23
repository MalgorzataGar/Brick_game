#pragma once
#include "CObiekt.h"

class CPilka :
	public CObiekt
{
	const float predkosc;
	float kierunek_x;
	float kierunek_y;
	SDL_Texture *pileczka;
public:
	CPilka(SDL_Renderer *r);
	~CPilka();

	void aktualizuj(float delta);
	void render(float delta);
	inline void ustaw_x(float x1) { x = x1; };
	inline void ustaw_y(float y1) { y = y1; };
	void zmien_kierunek(float x1, float y1);
	inline const  float daj_kierunek_x() { return kierunek_x; };
	inline const float daj_kierunek_y() { return kierunek_y; };
	inline void ustaw_kx(int kx) { kierunek_x *= kx; };
	inline void ustaw_ky(int ky) { kierunek_y *= ky; };
};

