#include "CMur.h"



CMur::CMur(SDL_Renderer *r)
	:CObiekt(r), dx(0), dy(16)
{
	SDL_Surface *powierzchnia = IMG_Load("cegla.png");
	cegla = SDL_CreateTextureFromSurface(renderer, powierzchnia);
	SDL_FreeSurface(powierzchnia);

	powierzchnia = IMG_Load("bok.png");
	bok = SDL_CreateTextureFromSurface(renderer, powierzchnia);
	SDL_FreeSurface(powierzchnia);

	srand(time(0));
	x = 16;
	y = 0;
	szerokosc = 768;
	wysokosc = 600;


}
CMur::~CMur()
{
	SDL_DestroyTexture(bok);
	SDL_DestroyTexture(cegla);
}
void CMur::utworz_mur()
{

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			CCegla cegla;
			cegla.ustaw_typ(rand() % 4);
			cegla.ustaw_stan(true);
			sciana[i][j] = cegla;

		}
	}

}
void CMur::aktualizuj(float delta)
{

}
void CMur::render(float delta)
{
	//reder cegielek
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			CCegla pomocnicza = sciana[i][j];
			//if (!pomocnicza.daj_stan())
			if (!pomocnicza.daj_stan())
			{
				continue;//sprawdzamy stan cegly, mozemy tworzyc rozne levele
			}
			SDL_Rect prostokat;//wskaznik na ktory z prostokatow z 4 chcemy wskazac
			prostokat.x = (pomocnicza.daj_typ() % 2)*pomocnicza.daj_szerokosc();
			prostokat.y = (pomocnicza.daj_typ() / 2)*pomocnicza.daj_wysokosc();
			prostokat.w = pomocnicza.daj_szerokosc();
			prostokat.h = pomocnicza.daj_wysokosc();

			SDL_Rect part;//cel ekranu gdzie trafi cegla
			part.x = dx + x + i*pomocnicza.daj_szerokosc();
			part.y = dy + y + j*pomocnicza.daj_wysokosc();
			part.w = pomocnicza.daj_szerokosc();
			part.h = pomocnicza.daj_wysokosc();

			SDL_RenderCopy(renderer, cegla, &prostokat, &part);



		}
	}
	//renderowanie bokow
	SDL_Rect sciana;
	sciana.x = 0;
	sciana.y = 0;
	sciana.w = 16;
	sciana.h = 600;
	SDL_RenderCopy(renderer, bok, 0, &sciana);
	sciana.x = 800 - 16;
	sciana.y = 0;
	sciana.w = 16;
	sciana.h = 600;
	SDL_RenderCopy(renderer, bok, 0, &sciana);


}
