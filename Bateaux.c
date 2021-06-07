/*
 -----------------------------------------------------------------------------------
 Nom du fichier : Bateaux.c
 Auteur(s)      : Meli Léo, Guilan Mbayo
 Date creation  : 27.05.2021

 Description    : Fichier contenant les implémentations de fonctions d'un bateau.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include "Bateaux.h"

void afficherBateaux(const Bateau *b) {
	const char *typeBateauChar[] = {"Voilier", "Bateau de peche", "Bateau de plaisance"};
	printf(FORMAT_BATEAU"%s\n", "Nom", b->nomBateau);
	printf(FORMAT_BATEAU"%s\n", "Genre", typeBateauChar[b->type]);
	switch (b->type) {
		case VOILIER:
			printf(FORMAT_BATEAU"%"PRIu16"\n", "Voilure [m2]", b->genre.voilier.surfaceVoilure);
			printf(FORMAT_BATEAU"%.2f\n", "Taxe", calculerVoilierTaxe(b));
			break;
		case MOTEUR_PECHE:
			printf(FORMAT_BATEAU"%"PRIu16"\n", "Moteurs [CV]", b->genre.moteur.puissance);
			printf(FORMAT_BATEAU"%"PRIu8"\n", "Peche [t]", b->genre.moteur.typeBateauMoteur.typePeche.tonnes_poissons);
			printf(FORMAT_BATEAU"%.2f\n", "Taxe", calculerPecheTaxe(b));
			break;
		case MOTEUR_PLAISANCE:
			printf(FORMAT_BATEAU"%"PRIu16"\n", "Moteurs [CV]", b->genre.moteur.puissance);
			printf(FORMAT_BATEAU"%"PRIu8"\n", "Longueur [m]", b->genre.moteur.typeBateauMoteur.typePlaisance.longueur);
			printf(FORMAT_BATEAU"%s\n", "Proprietaire", b->genre.moteur.typeBateauMoteur.typePlaisance.nomProprietaire);
			printf(FORMAT_BATEAU"%.2f\n", "Taxe", calculerPlaisanceTaxe(b));
			break;
	}
	printf("\n");
}

int comparerDouble(const void *a, const void *b) {
	// Comme la comparaison de double par l'opérande == est impossible.
	// Nous comparons les valeurs par leurs différences.
	int ret = 0;
	double const *pa = a;
	double const *pb = b;
	double diff = *pa - *pb;
	if (diff > 0) {
		ret = 1;
	} else if (diff < 0) {
		ret = -1;
	} else {
		ret = 0;
	}
	return ret;
}

Bateau voilier(const char *nom, uint16_t surfaceVoilure) {
	return (Bateau) {.nomBateau = nom, .genre = {.voilier = {.surfaceVoilure = surfaceVoilure}},
		.type = VOILIER};
}

Bateau peche(const char *nom, uint16_t puissance, uint8_t tonnes_poissons) {
	return (Bateau) {.nomBateau = nom, .genre = {.moteur ={.puissance = puissance, .typeBateauMoteur = {.typePeche = {.tonnes_poissons = tonnes_poissons}}}},
		.type = MOTEUR_PECHE};
}

Bateau plaisance(const char *nom, uint16_t puissance, uint8_t longueur, const char *proprietaire) {
	return (Bateau) {.nomBateau = nom, .genre = {.moteur ={.puissance = puissance, .typeBateauMoteur ={.typePlaisance ={.longueur = longueur, .nomProprietaire = proprietaire}}}},
		.type = MOTEUR_PLAISANCE};
}

double calculerVoilierTaxe(const Bateau *b) {
	double taxe = TAXE_BASE_VOILIER;
	if (b->genre.voilier.surfaceVoilure >= TAXE_LIMITE_VOILIER)
		taxe += TAXE_SPECIFIQUE_VOILIER;
	return taxe;
}

double calculerPecheTaxe(const Bateau *b) {
	double taxe = TAXE_BASE_MOTEUR;
	if (b->genre.moteur.typeBateauMoteur.typePeche.tonnes_poissons >= TAXE_LIMITE_PECHE)
		taxe += TAXE_SPECIFIQUE_PECHE;
	return taxe;
}

double calculerPlaisanceTaxe(const Bateau *b) {
	double taxe = TAXE_BASE_MOTEUR;
	if (b->genre.moteur.puissance < TAXE_LIMITE_PLAISANCE)
		taxe += TAXE_SPECIFIQUE_PLAISANCE;
	else
		taxe += b->genre.moteur.typeBateauMoteur.typePlaisance.longueur * TAXE_PLAISANCE_MULTIPLIEUR;
	return taxe;
}

double calculerMediane(const double taxes[], const unsigned types[], size_t taille, TypeBateau type, size_t nbBateau) {
	double taxesSel[nbBateau];

	// Récupère toutes les taxes du type de bateau concerné.
	size_t cpt = 0;
	for (size_t i = 0; i < taille; ++i) {
		if (types[i] == type) {
			taxesSel[cpt] = taxes[i];
			++cpt;
		}
	}

	// Calcule de la médiane.
	qsort(taxesSel, nbBateau, sizeof(double), comparerDouble);
	double mediane = 0.;
	if (nbBateau % 2) {
		mediane = taxesSel[nbBateau / 2];
	} else {
		mediane = (taxesSel[(nbBateau + 1) / 2] + taxesSel[(nbBateau - 1) / 2]) / 2;
	}
	return mediane;
}

double calculerEcartType(const double taxes[], const unsigned types[], size_t taille, double moyenne, TypeBateau type) {
	double ecartType = 0.;
	double cpt = 0;
	for (size_t i = 0; i < taille; ++i) {
		// Récupère les taxes du type de bateau concerné.
		if (types[i] == type) {
			double diff = taxes[i] - moyenne;
			ecartType += pow(diff, 2);
			++cpt;
		}
	}
	return sqrt(ecartType / cpt);
}

void calculerStatistiques(Bateau *port, size_t taillePort) {

	// Étant données que nous ne connaissons pas encore le nombre de bateaux par type
	// et que nous ne voulons pas parcourir le port plus qu'il ne faut, ni initialiser des tableaux de trop grande tailles,
	// nous récupérons la liste des taxes accompagnée de la liste des types. Ainsi nous pourrons rassembler les taxes par type de bateau.
	// Il est de la plus haute importance que les deux listes soit dans le même ordre.
	TypeBateau typeBateau[taillePort];
	double taxes[taillePort];

	double sommeTaxesVoilier = 0, sommeTaxesPeche = 0, sommeTaxesPlaisance = 0, taxe = 0.;
	unsigned nbVoilier = 0, nbPeche = 0, nbPlaisance = 0;

	for (size_t i = 0; i < taillePort; ++i) {

		typeBateau[i] = port[i].type;

		switch (port[i].type) {
			case VOILIER:
				taxe = calculerVoilierTaxe(port + i);
				sommeTaxesVoilier += taxe;
				taxes[i] = taxe;
				++nbVoilier;
				break;
			case MOTEUR_PECHE:
				taxe = calculerPecheTaxe(port + i);
				sommeTaxesPeche += taxe;
				taxes[i] = taxe;
				++nbPeche;
				break;
			case MOTEUR_PLAISANCE:
				taxe = calculerPlaisanceTaxe(port + i);
				sommeTaxesPlaisance += taxe;
				taxes[i] = taxe;
				++nbPlaisance;
				break;
			default:
				break;
		}
	}

	// Calcule des moyennes de chaque type de bateau.
	double moyenneVoilier = sommeTaxesVoilier / nbVoilier;
	double moyennePeche = sommeTaxesPeche / nbPeche;
	double moyennePlaisance = sommeTaxesPlaisance / nbPlaisance;

	// Calcule des médianes de chaque type de bateau.
	double medianeVoilier = calculerMediane(taxes, typeBateau, taillePort, VOILIER, nbVoilier);
	double medianePeche = calculerMediane(taxes, typeBateau, taillePort, MOTEUR_PECHE, nbPeche);
	double medianePlaisance = calculerMediane(taxes, typeBateau, taillePort, MOTEUR_PLAISANCE, nbPlaisance);

	// Calcule de l'écart-type de chaque type de bateau.
	double ecartTypeVoilier = calculerEcartType(taxes, typeBateau, taillePort, moyenneVoilier, VOILIER);
	double ecartTypePeche = calculerEcartType(taxes, typeBateau, taillePort, moyennePeche, MOTEUR_PECHE);
	double ecartTypePlaisance = calculerEcartType(taxes, typeBateau, taillePort, moyennePlaisance, MOTEUR_PLAISANCE);

	//Affichage du séparateur entre les bateaux et les taxes
	printf("-----------------------------------------------\n");

	// Affichage des statistiques par type.
	afficherStatistiques(VOILIER, sommeTaxesVoilier, moyenneVoilier, medianeVoilier, ecartTypeVoilier);
	afficherStatistiques(MOTEUR_PECHE, sommeTaxesPeche, moyennePeche, medianePeche, ecartTypePeche);
	afficherStatistiques(MOTEUR_PLAISANCE, sommeTaxesPlaisance, moyennePlaisance, medianePlaisance, ecartTypePlaisance);
}

void afficherStatistiques(TypeBateau type, double somme, double moyenne, double mediane, double ecartType) {
	const char *labelType[] = {"voiliers", "bateaux de peche", "bateaux de plaisance"};
	printf(FORMAT_TAXES, labelType[type], somme, moyenne, mediane, ecartType);
}

