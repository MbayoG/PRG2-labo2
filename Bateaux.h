#ifndef PRG2_LABO2_BATEAUX_H
#define PRG2_LABO2_BATEAUX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#define TAXE_BASE_VOILIER 50. // Taxe de base pour les voiliers.
#define TAXE_BASE_MOTEUR 100. // Taxe de base pour les bateaux à moteur.

#define TAXE_LIMITE_VOILIER 200.     // Limitation de la taxe spécifique pour les voiliers.
#define TAXE_LIMITE_PECHE 20.        // Limitation de la taxe spécifique pour les bateaux de pêche.
#define TAXE_LIMITE_PLAISANCE 100.  // Limitation de la taxe spécifique pour les bateaux de plaisance.

#define TAXE_SPECIFIQUE_VOILIER 25.    // Taxe spécifique pour les voiliers.
#define TAXE_SPECIFIQUE_PECHE 100.     // Taxe spécifique pour les bateaux de pêche.
#define TAXE_SPECIFIQUE_PLAISANCE 50.  // Taxe spécifique pour les bateaux de plaisance.

#define TAXE_PLAISANCE_MULTIPLIEUR 15. // Multiplieur pour la taxe spécifique des bateaux de plaisance.

#define FORMAT_TAXES "Taxes des %s\n  Somme : %.2f\n  Moyenne : %.2f\n  Mediane : %.2f\n  Ecart-type : %.2f\n\n" // Format pour l'affichage des statisqiques des taxes.
#define FORMAT_BATEAU "%-15s:" // Format pour l'affichage des bateaux.

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

static const char* typeBateauChar[] = {"Voilier", "Bateau de peche", "Bateau de plaisance"};

/**
 * Fonction de comparaison de variables de type double pour qsort.
 * @param a -> Valeur à comparer
 * @param b -> Valeur à comparer
 * @return -1 si inférieure; 0 si égale; 1 si supérieure.
 */
int comparerDouble (const void * a, const void * b);

/**
 * Affiche les statistiques des taxes
 * @param type      -> Type du bateau.
 * @param somme     -> Somme des taxes selon le type de bateau.
 * @param moyenne   -> Moyenne des taxes selon le type de bateau.
 * @param mediane   -> Médiane des taxes selon le type de bateau.
 * @param ecartType -> Ecart-Type des taxes selon le type de bateau.
 */
void afficherStatistiques(TypeBateau type, double somme, double moyenne, double mediane, double ecartType);

/**
 * Affiche un bateau.
 * @param b -> Bateau à afficher.
 */
void afficherBateaux(const Bateau *b);

/**
 * Créé un voilier.
 * @param nom               -> Nom du voilier.
 * @param surfaceVoilure    -> Surface de voilure.
 * @return Le bateau créé.
 */
Bateau voilier(const char* nom, uint16_t surfaceVoilure);

/**
 * Créé un bateau de pêche.
 * @param nom               -> Nom du bateau.
 * @param puissance         -> Puissance en CV des moteurs.
 * @param tonnes_poissons   -> Tonnes de poisson dont le bateau est autorisé à pécher.
 * @return Le bateau créé.
 */
Bateau peche(const char* nom, uint16_t puissance, uint8_t tonnes_poissons);

/**
 * Créé un bateau de plaisance.
 * @param nom           -> Nom du bateau.
 * @param puissance     -> Puissance des moteurs.
 * @param longueur      -> Longueur du bateau.
 * @param proprietaire  -> Nom du propriétaire du bateau.
 * @return Le bateau créé.
 */
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
 * @return La taxe du bateau de plaisance.
 */
double calculerPlaisanceTaxe(const Bateau* b);

/**
 * Calcule la médiane pour un type de bateau.
 * @param taxes     -> Liste des taxes de n'importe quel type de bateau.
 * @param types     -> Liste des types de chaque bateau présent dans le port. /!\ Elle doit correspondre à l'ordre de la liste des taxes.
 * @param taille    -> Nombre de bateau total.
 * @param type      -> Type des bateaux pour lesquels nous voulons calculer la médiane.
 * @param nbBateau  -> Nombre de bateaux de ce type.
 * @return La médiane pour le type de bateaux sélectionné.
 */
double calculerMediane(const double taxes[], const unsigned types[], size_t taille, TypeBateau type, size_t nbBateau);

/**
 * Calcule l'écart-type pour un type de bateau.
 * @param taxes     -> Liste des taxes de n'importe quel type de bateau.
 * @param types     -> Liste des types de chaque bateau présent dans le port. /!\ Elle doit correspondre à l'ordre de la liste des taxes.
 * @param taille    -> Nombre de bateaux total.
 * @param moyenne   -> Moyenne des taxes des bateaux du type sélectionné.
 * @param type      -> Type des bateaux pour lesquels nous voulons calculer la l'écart-type.
 * @return L'écart-type pour le type de bateaux séléctionné.
 */
double calculerEcartType(const double taxes[], const unsigned types[], size_t taille, double moyenne, TypeBateau type);

/**
 * Calcule la somme, la moyenne, la médiane et l'écart-type des taxes annuelles dues.
 * @param port          -> Port contenant des bateaux.
 * @param taillePort    -> Nombre de bateau total présent dans le port.
 */
void calculerStatistiques(Bateau *port, size_t taillePort);

#endif //PRG2_LABO2_BATEAUX_H
