#include "Bateaux.h"

void afficherBateaux(const Bateau *b) {
   printf(FORMAT_BATEAU"%s\n", "Nom", b->nomBateau);
   printf(FORMAT_BATEAU"%s\n", "Genre", typeBateauChar[b->type]);
   switch (b->type) {
      case VOILIER:
         printf(FORMAT_BATEAU"%d\n", "Voilure [m2]", b->genre.voilier.surfaceVoilure);
         printf(FORMAT_BATEAU"%.2f\n", "Taxe", calculerVoilierTaxe(b));
         break;
      case MOTEUR_PECHE:
         printf(FORMAT_BATEAU"%d\n", "Moteurs [CV]", b->genre.moteur.puissance);
         printf(FORMAT_BATEAU"%d\n", "Peche [t]", b->genre.moteur.typeBateauMoteur.typePeche.tonnes_poissons);
         printf(FORMAT_BATEAU"%.2f\n", "Taxe", calculerPecheTaxe(b));
         break;
      case MOTEUR_PLAISANCE:
         printf(FORMAT_BATEAU"%d\n", "Moteurs [CV]", b->genre.moteur.puissance);
         printf(FORMAT_BATEAU"%d\n", "Longueur [m]", b->genre.moteur.typeBateauMoteur.typePlaisance.longueur);
         printf(FORMAT_BATEAU"%s\n", "Proprietaire", b->genre.moteur.typeBateauMoteur.typePlaisance.nomProprietaire);
         printf(FORMAT_BATEAU"%.2f\n", "Taxe", calculerPlaisanceTaxe(b));
         break;
   }
   printf("\n");
}

int compare (const void * a, const void * b) {
   int ret = 0;
   double const *pa = a;
   double const *pb = b;
   double diff = *pa - *pb;
   if (diff > 0) {
      ret = 1;
   }
   else if (diff < 0) {
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

double calculerVoilierTaxe(const Bateau* b) {
   double taxe = TAXE_BASE_VOILIER;
   if (b->genre.voilier.surfaceVoilure >= TAXE_LIMITE_VOILIER)
      taxe += TAXE_SPECIFIQUE_VOILIER;
   return taxe;
}

double calculerPecheTaxe(const Bateau* b){
   double taxe = TAXE_BASE_MOTEUR;
   if (b->genre.moteur.typeBateauMoteur.typePeche.tonnes_poissons >= TAXE_LIMITE_PECHE)
      taxe += TAXE_SPECIFIQUE_PECHE;
   return taxe;
}

double calculerPlaisanceTaxe(const Bateau* b){
   double taxe = TAXE_BASE_MOTEUR;
   if (b->genre.moteur.puissance < TAXE_LIMITE_PLAISANCE)
      taxe += TAXE_SPECIFIQUE_PLAISANCE;
   else
      taxe += b->genre.moteur.typeBateauMoteur.typePlaisance.longueur * TAXE_PLAISANCE_MULTIPLIEUR;
   return taxe;
}

double calculerMediane(const double taxes[], const unsigned types[], size_t taille, TypeBateau type, size_t nbBateau) {
   double taxesSel[nbBateau];
   size_t cpt = 0;
   for (size_t i = 0; i < taille; ++i) {
      if (types[i] == type) {
         taxesSel[cpt] = taxes[i];
         ++cpt;
      }
   }

   qsort(taxesSel, nbBateau, sizeof(double), compare);
   double mediane = 0.;
   if(nbBateau % 2){
      mediane = taxesSel[nbBateau/2];
   } else {
      mediane = (taxesSel[(nbBateau + 1) / 2] + taxesSel[(nbBateau - 1) / 2]) / 2;
   }
   return mediane;
}

double calculerEcartType(const double taxes[], const unsigned types[], size_t taille, double moyenne, TypeBateau type){
   double ecartType = 0.;
   double cpt = 0;
   for (size_t i = 0; i < taille; ++i) {
      if (types[i] == type) {
         double diff = taxes[i] - moyenne;
         ecartType += pow(diff, 2);
         ++cpt;
      }
   }
   return sqrt(ecartType / cpt);
}

void calculTaxes(Bateau *bateau, size_t taillePort) {

   unsigned typeBateau[taillePort];

   double taxes[taillePort], taxe = 0.;
   double sommeTaxesVoilier = 0, sommeTaxesPeche = 0, sommeTaxesPlaisance = 0;
   unsigned nbVoilier = 0, nbPeche = 0, nbPlaisance = 0;

   for (size_t i = 0; i < taillePort; ++i) {

      typeBateau[i] = bateau[i].type;

      switch (bateau[i].type) {
         case VOILIER:
            taxe = calculerVoilierTaxe(bateau + i);
            sommeTaxesVoilier += taxe;
            taxes[i] = taxe;
            ++nbVoilier;
            break;
         case MOTEUR_PECHE:
            taxe = calculerPecheTaxe(bateau + i);
            sommeTaxesPeche += taxe;
            taxes[i] = taxe;
            ++nbPeche;
            break;
         case MOTEUR_PLAISANCE:
            taxe = calculerPlaisanceTaxe(bateau + i);
            sommeTaxesPlaisance += taxe;
            taxes[i] = taxe;
            ++nbPlaisance;
            break;
         default:
            break;
      }
   }

   double moyenneVoilier = (double)sommeTaxesVoilier/(double)nbVoilier;
   double moyennePeche = (double)sommeTaxesPeche/(double)nbPeche;
   double moyennePlaisance = (double)sommeTaxesPlaisance/(double)nbPlaisance;

   double medianeVoilier = calculerMediane(taxes,typeBateau,taillePort,VOILIER,nbVoilier);
   double medianePeche = calculerMediane(taxes,typeBateau,taillePort,MOTEUR_PECHE,nbPeche);
   double medianePlaisance = calculerMediane(taxes,typeBateau,taillePort,MOTEUR_PLAISANCE,nbPlaisance);

   double ecartTypeVoilier = calculerEcartType(taxes, typeBateau, taillePort, moyenneVoilier, VOILIER);
   double ecartTypePeche = calculerEcartType(taxes, typeBateau, taillePort, moyennePeche, MOTEUR_PECHE);
   double ecartTypePlaisance = calculerEcartType(taxes, typeBateau, taillePort, moyennePlaisance, MOTEUR_PLAISANCE);

   afficheTaxes(VOILIER, sommeTaxesVoilier, moyenneVoilier, medianeVoilier, ecartTypeVoilier);
   afficheTaxes(MOTEUR_PECHE, sommeTaxesPeche, moyennePeche, medianePeche, ecartTypePeche);
   afficheTaxes(MOTEUR_PLAISANCE, sommeTaxesPlaisance, moyennePlaisance, medianePlaisance, ecartTypePlaisance);
}

double afficheTaxes(TypeBateau type, double somme, double moyenne, double mediane, double ecartType) {
   printf(FORMAT_TAXES, typeBateauChar[type], somme, moyenne, mediane, ecartType);
}

