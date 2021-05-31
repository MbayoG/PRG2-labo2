#include "Bateaux.h"

int main(void) {
	
	Bateau port[] = {
		voilier("Alinghi", 300),
		peche("Espadon", 1000, 20),
		plaisance("Farniente", 100, 100, "James Lamer"),
		plaisance("Flying Dutch", 20, 150, "Davy Jones")
	};

	size_t taillePort = sizeof(port)/sizeof(Bateau);

	for(size_t i = 0; i < taillePort; ++i){
		afficher(&port[i]);
	}

	afficherTaxes(port, taillePort);


	return EXIT_SUCCESS;
}