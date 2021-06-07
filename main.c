/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Meli Léo, Guilan Mbayo
 Date creation  : 27.05.2021

 Description    : Création d'un port et des bateaux s'y trouvant. Appelle des fonctions d'affichage des bateaux et des
 						statistiques des taxes par type de bateau.

 Remarque(s)    : Selon les remarques faites dans le feedback du labo 1, il est nécessaire d'utiliser PRIu64, comme vu
 						en cours, afin d'afficher les size_t, or cela nous déclenche un warning que nous avons par conséquent
 						décidé d'ignorer.

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include "Bateaux.h"

int main(void) {

	Bateau port[] = {
		voilier("Alinghi", 300),
		peche("Brochet", 1000, 20),
		plaisance("Black Pearl", 100, 100, "Jack Sparrow"),
		voilier("Queen Anne's Revenge", 400),
		voilier("Vaudoise", 50),
		voilier("Slave1", 50),
		plaisance("Yellow submarine", 1000, 220, "John Lennon"),
		plaisance("HMS Victory", 200, 200, "Horatio Nelson"),
		plaisance("Flying Dutch", 20, 150, "Davy Jones")
	};

	size_t taillePort = sizeof(port) / sizeof(Bateau);

	for (size_t i = 0; i < taillePort; ++i) {
		printf("BATEAU %"PRIu64":\n", i + 1);
		afficherBateaux(&port[i]);
	}

	calculerStatistiques(port, taillePort);

	return EXIT_SUCCESS;
}
