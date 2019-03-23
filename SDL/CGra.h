#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "CMur.h"
#include "COdbijaczka.h"
#include "CPilka.h"



class CGra
{
	CMur *mur;
	COdbijaczka *odbijacz;
	CPilka *kulka;
	bool stan_odbijaczki;
	const int opoznienie;
	SDL_Window *okno;
	SDL_Renderer *renderer;
	SDL_Texture *tekstura;
	unsigned int czas_odniesienia;
    int punkty;
	int ile_razy_spadlo;
	int gracz;
	//	menu
	SDL_Texture *tlo, *gra, *wyjscie, *nazwa_gracza;
	std::string imie;
	//unsigned int fpstick, fps, framecount;

public:
	CGra();
	~CGra();
	bool inicjalizacja();
	bool menu();
	void run();
	
	void aktualizuj(const float delta);
	void render(const float delta);
	void nowa_gra();
	void resetuj_odbijaczke();
	void ustaw_kulke();

	void ustaw_x_odbijaczki(const float x);
	void kolizja_mur();
	float odbicie(const float x_uderzenia);
	void kolizja_odbijaczka();
	
	void kolizja_cegla();
	void pilka_od_cegly(const int odbite_miejsce);
	int liczenie();
	void zapis_do_pliku(const int pkt)const;
	void zapis_do_pliku(const int pkt, const bool menu)const;



};

