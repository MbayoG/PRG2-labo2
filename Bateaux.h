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
// TODO afficher les taxes
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

// TODO: créer des typedef pour les taxes

Bateau voilier(const char* nom, uint16_t surfaceVoilure){
	return (Bateau) {.nomBateau = nom, .genre = { .voilier = {.surfaceVoilure = surfaceVoilure}}, .bateauType = VOILIER, .taxeBase = 50, .taxeSpec = surfaceVoilure<200 ? 0 : 25};
}

Bateau peche(const char* nom, uint16_t puissance, uint8_t tonnes_poissons){
	return (Bateau) {.nomBateau = nom, .genre = { .moteur ={ .puissance = puissance, .typeBateauMoteur = { .moteurPeche = { .tonnes_poissons = tonnes_poissons}}}}, .taxeBase = 100, .taxeSpec = tonnes_poissons<20 ? 0 : 100};
}

Bateau plaisance(const char* nom, uint16_t puissance,uint8_t longueur, const char* proprietaire){
	return (Bateau) {.nomBateau = nom, .genre = { .moteur ={.puissance = puissance, .typeBateauMoteur ={ .moteurPlaisance ={ .longueur = longueur, .nomProprietaire = proprietaire}}}}, .taxeBase = 100, .taxeSpec = puissance<100 ? 50 : longueur*15};
}
#endif //PRG2_LABO2_BATEAUX_H
