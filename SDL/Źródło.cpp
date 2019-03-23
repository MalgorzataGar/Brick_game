#include <iostream>
#include "CGra.h"


using namespace std;

int main(int argc, char * argv[])
{

	CGra* gra = new CGra();
	if (gra->inicjalizacja()) {
		gra->run();
	}
	delete gra;
	return 0;
}