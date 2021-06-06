#include "Bateaux.h"

int main(void) {

	Bateau port[] = {
		voilier("Alinghi", 300),
		peche("Espadon", 1000, 20),
		plaisance("Farniente", 100, 100, "James Lamer"),
		voilier("Queen Anne's Revenge", 400),
		voilier("Vaudoise", 50),
		voilier("Slave1", 50),
		plaisance("Flying Dutch", 20, 150, "Davy Jones")
	};

	size_t taillePort = sizeof(port)/sizeof(Bateau);

	for(size_t i = 0; i < taillePort; ++i){
		printf("BATEAU %d:\n", (int)i+1);
		afficherBateaux(&port[i]);
	}

   calculerStatistiques(port, taillePort);


	return EXIT_SUCCESS;
}