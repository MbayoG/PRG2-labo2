#ifndef PRG2_LABO2_BATEAUX_H
#define PRG2_LABO2_BATEAUX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


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
	typeBateau type;
	uint16_t taxeBase;
	uint16_t taxeSpec;
} Bateau;

const char *typeBateauChar[] = {"Voilier", "Bateau de peche", "Bateau de plaisance"};


// TODO utiliser une largeur de champ variable plutot que %-15s (un macro format par exemple)
void afficher(const Bateau *b) {
	printf("%-15s: %s\n", "Nom", b->nomBateau);
	printf("%-15s: %s\n", "Genre", typeBateauChar[b->type]);
	switch (b->type) {
		case VOILIER:
			printf("%-15s: %d\n", "Voilure [m2]", b->genre.voilier.surfaceVoilure);
			break;
		case MOTEUR_PECHE:
			printf("%-15s: %d\n", "Moteurs [CV]", b->genre.moteur.puissance);
			printf("%-15s: %d\n", "Peche [t]", b->genre.moteur.typeBateauMoteur.moteurPeche.tonnes_poissons);
			break;
		case MOTEUR_PLAISANCE:
			printf("%-15s: %d\n", "Moteurs [CV]", b->genre.moteur.puissance);
			printf("%-15s: %d\n", "Longueur [m]", b->genre.moteur.typeBateauMoteur.moteurPlaisance.longueur);
			printf("%-15s: %s\n", "Proprietaire", b->genre.moteur.typeBateauMoteur.moteurPlaisance.nomProprietaire);
			break;
	}
	printf("%-15s: %d\n", "Taxes", b->taxeSpec + b->taxeBase);
	printf("\n");

}

// TODO: créer des macro pour les valeurs des taxes

Bateau voilier(const char *nom, uint16_t surfaceVoilure) {
	return (Bateau) {.nomBateau = nom, .genre = {.voilier = {.surfaceVoilure = surfaceVoilure}},
		.type = VOILIER, .taxeBase = 50, .taxeSpec =   surfaceVoilure < 200 ? 0 : 25};
}

Bateau peche(const char *nom, uint16_t puissance, uint8_t tonnes_poissons) {
	return (Bateau) {.nomBateau = nom, .genre = {.moteur ={.puissance = puissance, .typeBateauMoteur = {.moteurPeche = {.tonnes_poissons = tonnes_poissons}}}},
		.type = MOTEUR_PECHE, .taxeBase = 100, .taxeSpec =   tonnes_poissons < 20 ? 0 : 100};
}

Bateau plaisance(const char *nom, uint16_t puissance, uint8_t longueur, const char *proprietaire) {
	return (Bateau) {.nomBateau = nom, .genre = {.moteur ={.puissance = puissance, .typeBateauMoteur ={.moteurPlaisance ={.longueur = longueur, .nomProprietaire = proprietaire}}}},
		.type = MOTEUR_PLAISANCE, .taxeBase = 100, .taxeSpec =   puissance < 100 ? 50 : (uint16_t) longueur * 15};
}


int cmpfunc (const void * a, const void * b) {
	return ( *(uint16_t *)a - *(uint16_t *)b );
}

//TODO: compléter la fonction de calcule des sommes, moyenne, etc... des taxes
void afficherTaxes(Bateau bateau[], const size_t taillePort){
	// parcourir le tableau et stocker les taxes par type de bateau
	// effectuer les différentes opérations
	// afficher les résultats
	uint16_t totalVoilier = 0, totalPeche = 0, totalPlaisance = 0,
				nbVoilier = 0, nbPeche = 0, nbPlaisance = 0;
	uint16_t taxesVoilier[taillePort];

	for(size_t i = 0; i<taillePort; ++i){
		switch(bateau[i].type){
			case VOILIER:
				totalVoilier += bateau[i].taxeBase + bateau[i].taxeSpec;
				taxesVoilier[nbVoilier] = bateau[i].taxeBase + bateau[i].taxeSpec;
				++nbVoilier;
				break;
			case MOTEUR_PECHE:
				totalPeche += bateau[i].taxeBase + bateau[i].taxeSpec;
				++nbPeche;
				break;
			case MOTEUR_PLAISANCE:
				totalPlaisance += bateau[i].taxeBase + bateau[i].taxeSpec;
				++nbPlaisance;
				break;
			default:
				break;
		}
	}
	qsort(taxesVoilier, nbVoilier, sizeof(uint16_t), cmpfunc);
	double ecartTypeVoilier = 0;
	for(int i = 0; i < nbVoilier; ++i){
		ecartTypeVoilier += pow((double)taxesVoilier[i]-((double)totalVoilier/nbVoilier),2);
	}

	ecartTypeVoilier/=(totalVoilier/nbVoilier);

	printf("Somme des taxes:\n %-14s: %d\n","Voiliers", totalVoilier);
	printf("Moyenne des taxes:\n %-14s: %d\n","Voiliers", totalVoilier/nbVoilier);
	printf("Mediane des taxes:\n %-14s: %d\n","Voiliers", nbVoilier%2 ? taxesVoilier[nbVoilier/2] : (taxesVoilier[(nbVoilier+1)/2]+taxesVoilier[(nbVoilier-1)/2])/2);
	printf("Moyenne des taxes:\n %-14s: %d\n","Voiliers", totalVoilier/nbVoilier);
	printf("Ecart type des taxes:\n %-14s: %.1f\n","Voilier", ecartTypeVoilier);
}

#endif //PRG2_LABO2_BATEAUX_H
