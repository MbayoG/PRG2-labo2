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
	uint16_t taxesVoilier[taillePort], taxesPeche[taillePort], taxesPlaisance[taillePort];

	for(size_t i = 0; i<taillePort; ++i){
		switch(bateau[i].type){
			case VOILIER:
				totalVoilier += bateau[i].taxeBase + bateau[i].taxeSpec;
				taxesVoilier[nbVoilier] = bateau[i].taxeBase + bateau[i].taxeSpec;
				++nbVoilier;
				break;
			case MOTEUR_PECHE:
				totalPeche += bateau[i].taxeBase + bateau[i].taxeSpec;
				taxesPeche[nbPeche] = bateau[i].taxeBase + bateau[i].taxeSpec;
				++nbPeche;
				break;
			case MOTEUR_PLAISANCE:
				totalPlaisance += bateau[i].taxeBase + bateau[i].taxeSpec;
				taxesPlaisance[nbPlaisance] = bateau[i].taxeBase + bateau[i].taxeSpec;
				++nbPlaisance;
				break;
			default:
				break;
		}
	}
	qsort(taxesVoilier, nbVoilier, sizeof(uint16_t), cmpfunc);
	double moyenneVoilier = (double)totalVoilier/nbVoilier;
	double moyennePeche = (double)totalPeche/nbPeche;
	double moyennePlaisance = (double)totalPlaisance/nbPlaisance;

	double ecartTypeVoilier = 0, ecartTypePeche = 0, ecartTypePlaisance = 0;
	for(int i = 0; i < nbVoilier; ++i){
		ecartTypeVoilier += pow((double)taxesVoilier[i]-moyenneVoilier,2);
	}
	for(int i = 0; i < nbPeche; ++i){
		ecartTypePeche += pow((double)taxesPeche[i]-moyennePeche,2);
	}
	for(int i = 0; i < nbPlaisance; ++i){
		ecartTypePlaisance += pow((double)taxesPlaisance[i]-moyennePlaisance,2);
	}
	ecartTypeVoilier/=moyenneVoilier; //TODO: verifier si moyenne !=0
	ecartTypePeche/=moyennePeche;
	ecartTypePlaisance/=moyennePlaisance;


	double medianeVoilier = nbVoilier%2 ? taxesVoilier[nbVoilier/2] : (double)(taxesVoilier[(nbVoilier+1)/2]+taxesVoilier[(nbVoilier-1)/2])/2;
	double medianePeche = nbPeche%2 ? taxesPeche[nbPeche/2] : (double)(taxesPeche[(nbPeche+1)/2]+taxesPeche[(nbPeche-1)/2])/2;
	double medianePlaisance = nbPlaisance%2 ? taxesPlaisance[nbPlaisance/2] : (double)(taxesPlaisance[(nbPlaisance+1)/2]+taxesPlaisance[(nbPlaisance-1)/2])/2;

	printf("Somme des taxes:\n %-20s: %d\n %-20s: %d\n %-20s: %d\n","Voiliers", totalVoilier, "Bateaux de peche", totalPeche, "Bateaux de plaisance", totalPlaisance);
	printf("Moyenne des taxes:\n %-20s: %.1f\n %-20s: %.1f\n %-20s: %.1f\n","Voiliers", moyenneVoilier, "Bateaux de peche", moyennePeche, "Bateaux de plaisance", moyennePlaisance);
	printf("Mediane des taxes:\n %-20s: %.1f\n %-20s: %.1f\n %-20s: %.1f\n","Voiliers", medianeVoilier, "Bateaux de peche", medianePeche, "Bateaux de plaisance", medianePlaisance);
	printf("Ecart type des taxes:\n %-20s: %.1f\n %-20s: %.1f\n %-20s: %.1f\n","Voilier", ecartTypeVoilier, "Bateaux de peche", ecartTypePeche, "Bateaux de plaisance", ecartTypePlaisance);
}

#endif //PRG2_LABO2_BATEAUX_H
