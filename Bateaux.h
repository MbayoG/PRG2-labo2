#ifndef PRG2_LABO2_BATEAUX_H
#define PRG2_LABO2_BATEAUX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define TAXE_BASE_VOILIER 50. // Taxe de base pour les voiliers.
#define TAXE_BASE_MOTEUR 100. // Taxe de base pour les bateaux à moteur.

#define TAXE_LIMITE_VOILIER 200.     // Limitation de la taxe spécifique pour les voiliers.
#define TAXE_LIMITE_PECHE 20.        // Limitation de la taxe spécifique pour les bateaux de pêche.
#define TAXE_LIMITE_PLAISANCE 100.  // Limitation de la taxe spécifique pour les bateaux de plaisance.

#define TAXE_SPECIFIQUE_VOILIER 25.    // Taxe spécifique pour les voiliers.
#define TAXE_SPECIFIQUE_PECHE 100.     // Taxe spécifique pour les bateaux de pêche.
#define TAXE_SPECIFIQUE_PLAISANCE 50.  // Taxe spécifique pour les bateaux de plaisance.

#define TAXE_PLAISANCE_MULTIPLIEUR 15. // Multiplieur pour la taxe spécifique des bateaux de plaisance.

#define FORMAT_TAXES "Taxes des %s\n Somme : %.2f\n Moyenne : %.2f\n Mediane : %.2f\n Ecart-type : %.2f\n"
#define FORMAT_BATEAU "%-15s:"

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
} Peche;

typedef struct {
	uint8_t longueur;
	const char* nomProprietaire;
} Plaisance;

typedef union {
	Peche typePeche;
	Plaisance typePlaisance;
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
} Bateau;

int compare (const void * a, const void * b);
static const char* typeBateauChar[] = {"Voilier", "Bateau de peche", "Bateau de plaisance"};

double afficheTaxes(TypeBateau type, double somme, double moyenne, double mediane, double ecartType);

void afficherBateaux(const Bateau *b);

// TODO: créer des macro pour les valeurs des taxes, ou une struct et 2 unions

Bateau voilier(const char* nom, uint16_t surfaceVoilure);

Bateau peche(const char* nom, uint16_t puissance, uint8_t tonnes_poissons);

Bateau plaisance(const char* nom, uint16_t puissance, uint8_t longueur, const char* proprietaire);

/**
 * Calcul la taxe d'un voilier.
 * @param b -> Bateau de type Voilier.
 * @return La taxe du voilier.
 */
double calculerVoilierTaxe(const Bateau* b);

/**
 * Calcul la taxe d'un bateau de pêche.
 * @param b -> Bateau de pêche.
 * @return La taxe du bateau de pêche.
 */
double calculerPecheTaxe(const Bateau* b);

/**
 * Calcul la taxe d'un bateau de plaisance.
 * @param b -> Bateau de plaisance.
 * @return  La taxe du bateau de plaisance.
 */
double calculerPlaisanceTaxe(const Bateau* b);

double calculerMediane(const double taxes[], const unsigned types[], size_t taille, TypeBateau type, size_t nbBateau);

double calculerEcartType(const double taxes[], const unsigned types[], size_t taille, double moyenne, TypeBateau type);

void calculTaxes(Bateau *bateau, size_t taillePort);

#endif //PRG2_LABO2_BATEAUX_H
