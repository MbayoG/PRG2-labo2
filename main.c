#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CR printf("\n");
typedef enum {
    VOILIER = 0,
    MOTEUR_PECHE,
    MOTEUR_PLAISANCE
} typeBateau;

typedef struct {
    uint16_t surfaceVoilure;
} Voilier;

typedef struct {
    uint8_t tonnes_poissons;
} MoteurPeche;

typedef struct {
	uint8_t longueur;
    const char *nomProprietaire;
} MoteurPlaisance;

typedef union {
    MoteurPeche moteurPeche;
    MoteurPlaisance moteurPlaisance;

} TypeBateauMoteur;

typedef struct {
    uint16_t puissance;
    TypeBateauMoteur typeBateauMoteur;
} Moteur;

typedef union {
    Voilier voilier;
    Moteur moteur;
} Genre;

typedef struct {
    char *nomBateau;
    Genre genre;
    typeBateau tagType;
} Bateau;

const char *type_bateau[] = {"Voilier", "Bateau de peche", "Bateau de "
                                                           "plaisance"};

// TODO utiliser une largeur de champ variable plutot que %-15s
void afficher(const Bateau *b) {
    printf("%-15s: %s\n", "Nom", b->nomBateau);
    printf("%-15s: %s\n", "Genre", type_bateau[b->tagType]);
    switch (b->tagType) {
        case VOILIER:
            printf("%-15s: %d\n", "Voilure [m2]", b->genre.voilier
                    .surfaceVoilure);
            break;
        case MOTEUR_PECHE:
            printf("%-15s: %d\n", "Moteurs [CV]", b->genre.moteur.puissance);
            printf("%-15s: %d\n", "Peche [t]", b->genre.moteur.typeBateauMoteur
                    .moteurPeche.tonnes_poissons);
            break;
        case MOTEUR_PLAISANCE:
            printf("%-15s: %d\n", "Moteurs [CV]", b->genre.moteur.puissance);
            printf("%-15s: %s\n", "Proprietaire", b->genre.moteur
                    .typeBateauMoteur.moteurPlaisance.nomProprietaire);
            break;
    }
    printf("\n");

}

int main(void) {

    Bateau alinghi = {
            .nomBateau = "Alinghi",
            .tagType = VOILIER,
            .genre = {.voilier = {.surfaceVoilure = 300}}
    };

    Bateau espadon = {
            .nomBateau = "Espadon",
            .tagType = MOTEUR_PECHE,
            .genre = {.moteur = {.puissance = 1000,
                    .typeBateauMoteur = {.moteurPeche = {.tonnes_poissons = 20}}}}
    };

    Bateau farniente = {
            .nomBateau = "Farniente",
            .tagType = MOTEUR_PLAISANCE,
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
    };

    afficher(&alinghi);
    afficher(&espadon);
    afficher(&farniente);

    return EXIT_SUCCESS;
}