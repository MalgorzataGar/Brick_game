#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "CGra.h"
#include <time.h>
#include <stdio.h>


using namespace std;

CGra::CGra()
	:opoznienie(500)
{
	okno = 0;
	renderer = 0;
	gracz = 0;
	imie = "";

}
CGra::~CGra()
{
	delete mur;
	delete odbijacz;
	delete kulka;
	SDL_DestroyTexture(tekstura);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(okno);
	SDL_DestroyTexture(tlo);
	SDL_DestroyTexture(gra);
	SDL_DestroyTexture(wyjscie);
	SDL_DestroyTexture(nazwa_gracza);
	SDL_Quit();
}
bool CGra::inicjalizacja()
{
	SDL_Init(SDL_INIT_VIDEO);
	//tworzymy okienko
	okno = SDL_CreateWindow("Niszczymy wszystkie cegly", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!okno)
	{
		cout << "blad tworzenia okna " << SDL_GetError() << endl;
		return false;

	}
	renderer = SDL_CreateRenderer(okno, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		cout << "Probel  przy twozreniu rendera" << SDL_GetError() << endl;
		return false;

	}
	SDL_Surface *powierzchnia = IMG_Load("test.png");
	tekstura = SDL_CreateTextureFromSurface(renderer, powierzchnia);


	czas_odniesienia = SDL_GetTicks();
	

	//MENU
	powierzchnia = IMG_Load("tlo.png");
	tlo = SDL_CreateTextureFromSurface(renderer, powierzchnia);
	powierzchnia = IMG_Load("start2.png");
	gra = SDL_CreateTextureFromSurface(renderer, powierzchnia);
	powierzchnia = IMG_Load("wyjscie2.png");
	wyjscie = SDL_CreateTextureFromSurface(renderer, powierzchnia);
	powierzchnia = IMG_Load("nazwagracza2.png");
	nazwa_gracza = SDL_CreateTextureFromSurface(renderer, powierzchnia);



	SDL_FreeSurface(powierzchnia);
	mur = new CMur(renderer);
	odbijacz = new COdbijaczka(renderer);
	kulka = new CPilka(renderer);


	return true;

}
bool CGra::menu()
{
	int Mx = 0;
	int My = 0;
	
	SDL_Event e;
	SDL_Event wpis;
	string imie_gracza;
	

	SDL_Rect tlo_prostokat;
	tlo_prostokat.x = 0;
	tlo_prostokat.y = 0;
	tlo_prostokat.w = 800;
	tlo_prostokat.h = 600;
	SDL_RenderCopy(renderer, tlo, 0, &tlo_prostokat);

	SDL_Rect nowa_gra_prostokat;
	nowa_gra_prostokat.x = 325;
	nowa_gra_prostokat.y = 100;
	nowa_gra_prostokat.w = 200;
	nowa_gra_prostokat.h = 75;

	SDL_RenderCopy(renderer, gra, 0, &nowa_gra_prostokat);

	SDL_Rect wyjscie_prostokat;
	wyjscie_prostokat.x = 325;
	wyjscie_prostokat.y = 250;
	wyjscie_prostokat.w = 200;
	wyjscie_prostokat.h = 75;

	SDL_RenderCopy(renderer, wyjscie, 0, &wyjscie_prostokat);

	SDL_Rect imie_prostokat;
	imie_prostokat.x = 325;
	imie_prostokat.y = 400;
	imie_prostokat.w = 200;
	imie_prostokat.h = 75;
	SDL_RenderCopy(renderer, nazwa_gracza, 0, &imie_prostokat);
	SDL_RenderPresent(renderer);

	

	while (1)
	{
		SDL_GetMouseState(&Mx, &My);
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) return false;
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					SDL_GetMouseState(&Mx, &My);
					if (Mx >= nowa_gra_prostokat.x && Mx <= nowa_gra_prostokat.x + nowa_gra_prostokat.w && My >= nowa_gra_prostokat.y
						&& My <= nowa_gra_prostokat.y + nowa_gra_prostokat.h)
					{
						
						return true;
					}
					else if (Mx >= wyjscie_prostokat.x && Mx <= wyjscie_prostokat.x + wyjscie_prostokat.w && My >= wyjscie_prostokat.y
						&& My <= wyjscie_prostokat.y + wyjscie_prostokat.h)
					{
						return false;
					}
					else if (Mx >= imie_prostokat.x && Mx <= imie_prostokat.x + imie_prostokat.w && My >= imie_prostokat.y
						&& My <= imie_prostokat.y + imie_prostokat.h)
					{
						SDL_ShowSimpleMessageBox(0, "no to problem...", "Funkcja dostepna po wykupieniu dodatku'koniec sesji'!", okno);
						/*if (SDL_PollEvent(&wpis))
						{
							SDL_StartTextInput();
							if (wpis.type == SDL_TEXTINPUT)
							{
								imie += wpis.text.text;

							}
							SDL_StopTextInput();
							continue;
						}*/
					}
					else continue;

				}
			}
		}
	}
	
}
void CGra::run()
{
	
	if (menu())
	{
		nowa_gra();
		clock_t start, stop;
		double czas;
		start = clock();
		while (1)
		{
			SDL_Event e;
			if (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT) break;
			}
			unsigned int obecny_czas = SDL_GetTicks();
			float delta = (obecny_czas - czas_odniesienia) / 1000.0f;//przyrost czasu
			/*if (obecny_czas - fpstick >= opoznienie)//czy wystarczajaco czasu minelo
			{
				fps = framecount*(1000.0f / (obecny_czas - fpstick));
				fpstick = obecny_czas;
				framecount = 0;

			}
			else
			{
				framecount++;
			}*/
			czas_odniesienia = obecny_czas;
			aktualizuj(delta);
			render(delta);
			if (liczenie() == 140)
			{
				stop = clock();
				czas = (double)(stop - start) / CLOCKS_PER_SEC;
				punkty = 144 - (ile_razy_spadlo * 5) - (czas*0.01);
				zapis_do_pliku(punkty);
				/*char p2[4];
				sprintf(p2, "%d", punkty);
				char p1[10] = { "Uzyskano " };
				char p3[9] = { " punktow" };
				char *wiadomosc="";
				strcat(wiadomosc, p1);
				strcat(wiadomosc, p2);
				strcat(wiadomosc, p3);*/
				SDL_ShowSimpleMessageBox(0, "BRAWO","Kliknij ok by grac od nowa", okno);
				nowa_gra();
			}

		}
	}

}
void CGra::nowa_gra()
{
	SDL_Delay(500);
	
	mur->utworz_mur();
	resetuj_odbijaczke();
	ustaw_kulke();
	
	punkty = 0;

}
void CGra::resetuj_odbijaczke()
{
	stan_odbijaczki = true;
	ustaw_kulke();
	ile_razy_spadlo++;

}
void CGra::ustaw_kulke()
{
	kulka->ustaw_x(odbijacz->daj_x() + (odbijacz->daj_szerokosc() / 2) - (kulka->daj_szerokosc() / 2));
	kulka->ustaw_y(odbijacz->daj_y() - kulka->daj_wysokosc());
}
void CGra::aktualizuj(float delta)
{

	int myszka_x, myszka_y;
	Uint8 stan_myszki = SDL_GetMouseState(&myszka_x, &myszka_y);
	ustaw_x_odbijaczki(myszka_x - (odbijacz->daj_szerokosc() / 2.0f));

	if (stan_myszki&SDL_BUTTON(1))
	{
		if (stan_odbijaczki)
		{
			stan_odbijaczki = false;
			kulka->zmien_kierunek(1, -1);

		}
	}
	if (stan_odbijaczki)
	{
		ustaw_kulke();
	}
	//sprawdzamy wszystkie kolizje
	kolizja_mur();
	kolizja_odbijaczka();
	kolizja_cegla();

	
	mur->aktualizuj(delta);
	odbijacz->aktualizuj(delta);

	if (!stan_odbijaczki)
	{
		kulka->aktualizuj(delta);
	}
}
void CGra::ustaw_x_odbijaczki(float x)
{
	float nowy_x;
	if (x < mur->daj_x())
	{
		//min wartoscc odbijaczki
		nowy_x = mur->daj_x();
	}
	else if (x + odbijacz->daj_szerokosc() > mur->daj_x() + mur->daj_szerokosc())
	{
		//max wartosc
		nowy_x = mur->daj_x() + mur->daj_szerokosc() - odbijacz->daj_szerokosc();

	}
	else
	{
		nowy_x = x;
	}
	odbijacz->ustaw_x(nowy_x);
}
void CGra::kolizja_mur()
{
	//gora
	if (kulka->daj_y() < mur->daj_y())
	{
		//kulka sie odbija
		kulka->ustaw_y(mur->daj_y());
		kulka->ustaw_ky(-1);
	}
	else if (kulka->daj_y() + kulka->daj_wysokosc() > mur->daj_y() + mur->daj_wysokosc())
	{
		//jestesmy na dnie, kulka stracona
		resetuj_odbijaczke();
	}
	//boki
	if (kulka->daj_x() <= mur->daj_x())
	{
		//lewo
		kulka->ustaw_x(mur->daj_x());
		kulka->ustaw_kx(-1);
	}
	else if (kulka->daj_x() + kulka->daj_szerokosc() >= mur->daj_x() + mur->daj_szerokosc())
	{
		//prawo
		kulka->ustaw_x(mur->daj_x() + mur->daj_szerokosc() - kulka->daj_szerokosc());
		kulka->ustaw_kx(-1);

	}
}
float CGra::odbicie(float x_uderzenia)
{
	//odbicie w zakresie od 0 do dl odbijaczki
	if (x_uderzenia < 0)
	{
		x_uderzenia = 0;
	}
	else if (x_uderzenia > odbijacz->daj_szerokosc())
	{
		x_uderzenia = odbijacz->daj_szerokosc();

	}
	//to co po lewej stronie odbijacza idzie na lewo reszta na prawo
	x_uderzenia -= odbijacz->daj_szerokosc() / 2.0f;
	//skalowanie by bylo w przedziale -2.0f do 2.0f
	return 2.0f*(x_uderzenia / (odbijacz->daj_szerokosc() / 2.0f));

}
void CGra::kolizja_odbijaczka()
{
	float srodek_x_kulki = kulka->daj_x() + (kulka->daj_szerokosc() / 2.0f);

	if (kulka->kolizja(odbijacz))
	{
		kulka->ustaw_y(odbijacz->daj_y() - kulka->daj_wysokosc());
		kulka->zmien_kierunek(odbicie(srodek_x_kulki - odbijacz->daj_x()), -1);
	}
}
void CGra::pilka_od_cegly(int odbite_miejsce)
{
	//0-lewo;1-gora;2-prawo;3-dol


	int zmiana_x = 1;
	int zmiana_y = 1;

	if (kulka->daj_kierunek_x() > 0) {
		if (kulka->daj_kierunek_y() > 0) {
			// x i y rosna
			if (odbite_miejsce == 0 || odbite_miejsce == 3) {
				zmiana_x = -1;//odbite z lewej lub z dolu
			}
			else
			{
				zmiana_y = -1;
			}
		}
		else if (kulka->daj_kierunek_y() < 0) {
			// y ujemne
			// +1 -1
			if (odbite_miejsce == 0 || odbite_miejsce == 1) {
				zmiana_x = -1;
			}
			else {
				zmiana_y = -1;
			}
		}
	}
	else if (kulka->daj_kierunek_x() < 0) {
		// x ujemne
		if (kulka->daj_kierunek_y() > 0) {
			// y dodatnie
			// -1 +1
			if (odbite_miejsce == 2 || odbite_miejsce == 3) {
				zmiana_x = -1;
			}
			else {
				zmiana_y = -1;
			}
		}
		else if (kulka->daj_kierunek_y() < 0) {
			// x i y ujemne
			// -1 -1
			if (odbite_miejsce == 1 || odbite_miejsce == 2) {
				zmiana_x = -1;
			}
			else {
				zmiana_y = -1;
			}
		}
	}
	//nowy kierunek ustalany przez zmiany
	kulka->zmien_kierunek(zmiana_x*kulka->daj_kierunek_x(), zmiana_y*kulka->daj_kierunek_y());


}
void CGra::render(float delta)
{
	SDL_RenderClear(renderer);
	mur->render(delta);
	odbijacz->render(delta);
	kulka->render(delta);

	SDL_RenderPresent(renderer);//aktualizujemy obraz
}
int CGra::liczenie()
{
	int pozostale_cegly = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{

			CCegla pomocnicza = mur->sciana[i][j];

			if (pomocnicza.daj_stan())
			{
				pozostale_cegly++;
			}

		}
	}
	return pozostale_cegly;
}
void CGra::kolizja_cegla() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			CCegla pomocnicza = mur->sciana[i][j];

			// czy cegla wgl jest
			if (pomocnicza.daj_stan()) {
				float cegla_szer = pomocnicza.daj_szerokosc();
				float cegla_wys = pomocnicza.daj_wysokosc();
				// wspolrzedne cegly
				float cegla_x = mur->daj_dx() + mur->daj_x() + i*pomocnicza.daj_szerokosc();
				float cegla_y = mur->daj_dy() + mur->daj_y() + j*pomocnicza.daj_wysokosc();


				float w = 0.5f * (kulka->daj_szerokosc() + cegla_szer);
				float h = 0.5f * (kulka->daj_wysokosc() + cegla_wys);
				float dx = (kulka->daj_x() + 0.5f*kulka->daj_szerokosc()) - (cegla_x + 0.5f*cegla_szer);
				float dy = (kulka->daj_y() + 0.5f*kulka->daj_wysokosc()) - (cegla_y + 0.5f*cegla_wys);

				if (fabs(dx) <= w && fabs(dy) <= h) {

					mur->sciana[i][j].ustaw_stan(false);

					float wy = w * dy;
					float hx = h * dx;

					if (wy > hx) {
						if (wy > -hx) {
							// dol
							pilka_od_cegly(3);
						}
						else {
							// lewo
							pilka_od_cegly(0);

						}
					}
					else {
						if (wy > -hx) {
							// prawo
							pilka_od_cegly(2);
						}
						else {
							// gora

							pilka_od_cegly(1);

						}
					}
					return;
				}
			}
		}
	}
}
void CGra::zapis_do_pliku(int pkt)const
{
	int ilosc_graczy = 0;
	ifstream gracz;
	gracz.open("TabelaWynikow.txt");
	try
	{
		if (gracz.good())
		{

			string linia;
			while (getline(gracz, linia))
				++ilosc_graczy;

		}
		else throw 1;

	}
	catch (...)
	{
		cerr << "Wystapil blad!" << endl;
	}

	gracz.close();
	ofstream wyniki;

	wyniki.open("TabelaWynikow.txt", ios::app);
	try
	{
		if (wyniki.good())
		{
			wyniki << (ilosc_graczy + 1) << ".Punkty: " << punkty << endl;
		}
		else throw 1;

	}
	catch (...)
	{
		cerr << "Wystapil blad!" << endl;
	}

	wyniki.close();
}
void CGra::zapis_do_pliku(int pkt, bool menu)const
{

	if (menu == true)
	{


		ofstream wyniki;

		wyniki.open("TabelaWynikow.txt", ios::app);


		if (wyniki.good())
		{
			wyniki << imie << ".Punkty: " << punkty << endl;
		}
		wyniki.close();
	}
}