#include "Bateaux.h"

int main(void) {
	//TODO: faire le tableau avec calloc
	Bateau port[4] = {};

	Bateau alinghi = voilier("Alinghi", 300);
	Bateau espadon = peche("Espadon", 1000, 20);
	Bateau farniente = plaisance("Farniente", 100, 100, "James Lamer");
	Bateau flyingDutch = plaisance("Flying Dutch", 20, 150, "Davy Jones");

	port[0] = alinghi;
	port[1] = espadon;
	port[2] = farniente;
	port[3] = flyingDutch;

	for(size_t i = 0; i < 4; ++i){
		afficher(&port[i]);
	}




	return EXIT_SUCCESS;
}