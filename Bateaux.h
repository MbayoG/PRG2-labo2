#ifndef PRG2_LABO2_BATEAUX_H
#define PRG2_LABO2_BATEAUX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define FORMAT_TAXES "Taxes des %s\n Somme : %d\n Moyenne : %.2f\n Mediane : %.2f\n Ecart-type : %.2f\n"

typedef enum {
	VOILIER,
	MOTEUR_PECHE,
	MOTEUR_PLAISANCE
} TypeBateau;

typedef struct {
	uint16_t surfaceVoilure;

} Voilier;

typedef struct {
	uint8_t tonnes_poissons;
} MoteurPeche;

typedef struct {
	uint8_t longueur;
	const char* nomProprietaire;
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
	const char* nomBateau;
	Genre genre;
	TypeBateau type;
	uint16_t taxeBase;
	uint16_t taxeSpec;
} Bateau;

static const char* typeBateauChar[] = {"Voilier", "Bateau de peche", "Bateau de plaisance"};

double afficheTaxes(TypeBateau type, const double* somme, const double* mediane, const double* moyenne, const double* ecartType);

void afficherBateaux(const Bateau *b);

// TODO: créer des macro pour les valeurs des taxes, ou une struct et 2 unions

Bateau voilier(const char* nom, uint16_t surfaceVoilure);


Bateau peche(const char* nom, uint16_t puissance, uint8_t tonnes_poissons);

Bateau plaisance(const char* nom, uint16_t puissance, uint8_t longueur, const char* proprietaire);


int cmpfunc (const void* a, const void * b);

//TODO: compléter la fonction de calcule des sommes, moyenne, etc... des taxes
void calculTaxes(Bateau *bateau, const size_t taillePort);

#endif //PRG2_LABO2_BATEAUX_H
