#include "Bateaux.h"

int main(void) {

    /*Bateau alinghi = {
            .nomBateau = "Alinghi",
            .bateauType = VOILIER,
            .genre = {.voilier = {.surfaceVoilure = 300}}
    };

    Bateau espadon = {
            .nomBateau = "Espadon",
            .bateauType = MOTEUR_PECHE,
            .genre = {.moteur = {.puissance = 1000,
                    .typeBateauMoteur = {.moteurPeche = {.tonnes_poissons = 20}}}}
    };

    Bateau farniente = {
            .nomBateau = "Farniente",
            .bateauType = MOTEUR_PLAISANCE,
            .genre = {
                    .moteur = {
                            .puissance = 100,
                            .typeBateauMoteur = {
                                    .moteurPlaisance = {
                                            .nomProprietaire = "James Lamer"
                                    }
                            }
                    }
            }
    };*/
	Bateau alinghi = voilier("Alinghi", 300);
	Bateau espadon = peche("Espadon", 1000, 20);
	Bateau farniente = plaisance("Farniente", 100, 100, "James Lamer");
	Bateau flyingDutch = plaisance("Flying Dutch", 20, 150, "Davy Jones");
    afficher(&alinghi);
    afficher(&espadon);
    afficher(&farniente);
	afficher(&flyingDutch);

    return EXIT_SUCCESS;
}