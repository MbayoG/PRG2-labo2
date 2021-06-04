#ifndef PRG2_LABO2_BATEAUX_H
#define PRG2_LABO2_BATEAUX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define FORMAT_TAXES "des taxes:\n %-20s: %.1f\n %-20s: %.1f\n %-20s: %.1f\n\n"

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

static const char* typeBateauChar[] = {"Voilier", "Bateau de peche", "Bateau de plaisance"};

double calculTaxes(const double* taxes);

// TODO utiliser une largeur de champ variable plutot que %-15s (un macro format par exemple)
void afficher(const Bateau *b);

// TODO: créer des macro pour les valeurs des taxes

Bateau voilier(const char *nom, uint16_t surfaceVoilure);


Bateau peche(const char *nom, uint16_t puissance, uint8_t tonnes_poissons);

Bateau plaisance(const char *nom, uint16_t puissance, uint8_t longueur, const char *proprietaire);


int cmpfunc (const void * a, const void * b);

//TODO: compléter la fonction de calcule des sommes, moyenne, etc... des taxes
void afficherTaxes(Bateau bateau[], const size_t taillePort);

#endif //PRG2_LABO2_BATEAUX_H
