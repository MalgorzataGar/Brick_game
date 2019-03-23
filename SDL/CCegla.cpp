#include "CCegla.h"



CCegla::CCegla()
	:wysokosc(24), szerokosc(64)
{


}
CCegla::~CCegla()
{

}
CCegla &CCegla::operator=(CCegla &c)
{
	if (&c != this)
	{
		stan = c.daj_stan();
		typ = c.daj_typ();

	}
	return (*this);
}