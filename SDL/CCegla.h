#pragma once
#include <SDL.h>
#include <SDL_image.h>
class CCegla

{
	const float wysokosc;
	const float szerokosc;
	int typ;
	bool stan;

public:

	CCegla();
	~CCegla();
	CCegla &operator=(CCegla &c);
	inline float daj_wysokosc()const { return wysokosc; };
	inline float daj_szerokosc()const { return szerokosc; };
	inline bool daj_stan()const { return stan; };
	inline int daj_typ()const { return typ; };
	inline void ustaw_stan(bool s) { stan = s; };
	inline void ustaw_typ(int t) { typ = t; };

};

