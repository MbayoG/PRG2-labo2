#ifndef PRG2_LABO2_BATEAUX_H
#define PRG2_LABO2_BATEAUX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


typedef enum {
	VOILIER,
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
	typeBateau bateauType;
	const uint8_t taxeBase;
	const uint8_t taxeSpec;
} Bateau;

const char *type_bateau[] = {"Voilier", "Bateau de peche", "Bateau de plaisance"};




// TODO utiliser une largeur de champ variable plutot que %-15s (un typdef format par exemple)
void afficher(const Bateau *b) {
	printf("%-15s: %s\n", "Nom", b->nomBateau);
	printf("%-15s: %s\n", "Genre", type_bateau[b->bateauType]);
	switch (b->bateauType) {
		case VOILIER:
			printf("%-15s: %d\n", "Voilure [m2]", b->genre.voilier.surfaceVoilure);
			break;
		case MOTEUR_PECHE:
			printf("%-15s: %d\n", "Moteurs [CV]", b->genre.moteur.puissance);
			printf("%-15s: %d\n", "Peche [t]", b->genre.moteur.typeBateauMoteur.moteurPeche.tonnes_poissons);
			break;
		case MOTEUR_PLAISANCE:
			printf("%-15s: %d\n", "Moteurs [CV]", b->genre.moteur.puissance);
			printf("%-15s: %s\n", "Proprietaire", b->genre.moteur.typeBateauMoteur.moteurPlaisance.nomProprietaire);
			break;
	}
	printf("\n");

}

// TODO: créer des constructeurs pour les bateaux

#endif //PRG2_LABO2_BATEAUX_H
