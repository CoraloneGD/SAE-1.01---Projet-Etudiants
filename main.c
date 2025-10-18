#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#pragma warning (disable: 4996 6031)

enum {NB_CARACTERES = 30, NB_ETUDIANTS_MAX = 100, NB_SEMESTRES = 6};


typedef struct {
	char nom[NB_CARACTERES];
	char prenom[NB_CARACTERES];
	char statut[NB_CARACTERES]; // Définition d'un type énuméré étudiant.
	int semestres;
	int id;
} Etudiant;

typedef struct {
	Etudiant liste_etudiants[NB_ETUDIANTS_MAX];
	int id_etudiant;
} IdEtudiant;

Etudiant nouv_etudiant;
IdEtudiant id;
Etudiant l_e[NB_ETUDIANTS_MAX];



int main() {
	char commande[NB_CARACTERES];
	int recommencer = 1;

	do {
		printf("Entrez une commande parmis celles qui sont disponibles, en MAJUSCULE obligatoire ! \n");
		printf("ETUDIANTS CURSUS INSCRIRE EXIT JURY BILAN \n");
		scanf_s("%32s", commande, (unsigned)sizeof(commande));

		if (strcmp(commande, "ETUDIANTS") == 0) {
			return 0;
		}
		else if (strcmp(commande, "CURSUS") == 0) {
			printf("Affichage du cursus d'un etudiant... \n");
		}
		else if (strcmp(commande, "INSCRIRE") == 0) {
			INSCRIRE();
		}
		else if (strcmp(commande, "EXIT") == 0) {
			EXIT(commande);
		}
		else if (strcmp(commande, "JURY") == 0) {
			printf("Organisation du jury... \n");
		}
		else if (strcmp(commande, "BILAN") == 0) {
			printf("Affichage du bilan des étudiants... \n");
		}
		else {
			printf("Commande inconnue. Veuillez reessayer.\n");
		}
	} while (1);
}

int EXIT(char commande[NB_CARACTERES]) {
	if (strcmp(commande, "EXIT") == 0) {
		printf("Arret du programme... \n");
		EXIT(0);
		abort(); // Arret programme après que l'utilisateur ait tapé "EXIT".
	}
}

int INSCRIRE(void) {
	char nom[NB_CARACTERES];
	char prenom[NB_CARACTERES];

	printf("Quel est le nom et prenom de l'etudiant ?\n");
	if (scanf("%29s %29s", nom, prenom) != 2) {
		printf("Lecture invalide. Inscription annulee.\n");
		// vider le buffer au cas où l'utilisateur tape n'importe quoi
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
		return -1;
	}

	// Vérifier la limite max d'étudiants
	if (id.id_etudiant >= NB_ETUDIANTS_MAX) {
		printf("Limite d'etudiants atteinte (%d). Inscription refusee.\n", NB_ETUDIANTS_MAX);
		return -1;
	}

	// Copier les données du nouvel étudiant
	strncpy(nouv_etudiant.nom, nom, NB_CARACTERES - 1);
	nouv_etudiant.nom[NB_CARACTERES - 1] = '\0'; // sécurité pour bien terminer la chaîne

	strncpy(nouv_etudiant.prenom, prenom, NB_CARACTERES - 1);
	nouv_etudiant.prenom[NB_CARACTERES - 1] = '\0';

	strncpy(nouv_etudiant.statut, "Inscrit", NB_CARACTERES - 1);
	nouv_etudiant.statut[NB_CARACTERES - 1] = '\0';

	nouv_etudiant.semestres = 0;

	// Générer un ID unique
	int nouvel_id = id.id_etudiant;
	int id_existe = 1;

	while (id_existe) {
		id_existe = 0;
		for (int i = 0; i < id.id_etudiant; ++i) {
			if (id.liste_etudiants[i].id == nouvel_id) {
				// si l'ID existe déjà, on passe au suivant
				id_existe = 1;
				nouvel_id++;
				break;
			}
		}
	}

	// Assigner l'ID et ajouter à la liste
	nouv_etudiant.id = nouvel_id;
	id.liste_etudiants[id.id_etudiant] = nouv_etudiant;
	id.id_etudiant++;

	printf("Inscription enregistree (%d)\n", nouvel_id);
	return 0;
}

	
//int ETUDIANTS(int id_etudiant, char prenom[NB_CARACTERES], char nom[NB_CARACTERES], char statut) {
//	// Fonction qui regroupe la liste des étudiants dans un tableau
//	// Etudiant liste_etudiant[NB_ETUDIANTS_MAX]; Tableau avec un limite de 100 etudiants --> à changer
//	printf("Voici tous les etudiants enregistres au sein de l'IUT : %c \n");
//	for (int i = 0; i != id_etudiant; ++i) {
//
//	}
//
//
//
//}
	
	
	
	
	
	
	
	
	
	
//	printf("Quel est le nom et prénom du nouvel étudiant ? : \n");
//	scanf("%s%s", nom, prenom); // Nom et prenom deux chars ne dépassant pas 30	caractères, sans espaces
//	Etudiant nouvel_etudiant.nom = nom;
//	Etudiant nouvel_etudiant.prenom = prenom;
//	 // Etudiant idEtu + 1 a changer, faux
//	nouvel_etudiant.etudiant;
//	printf("Inscription enregistrée");
//	// Mettre une condition si le nb etudiant dépasse 100, refuse toute inscription !! + Si le nom + prenom est le même 
//	if (nouvel_etudiant > NB_ETUDIANTS_MAX) {
//		printf("Limite etudiante dépassée \n");
//	}
//	else {
//		printf("Inscription enregistree \n");
//	}
//	return 0;
//}