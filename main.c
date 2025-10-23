#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996 6031)

/*
Règles UE et RCUE:
	-	Chaque semestre: 6 UE.
	-	Note > 10: Validé, et RCUE > 10 valides celles correspondants de l'année précédente

	a student can leave or be declared "defaillant"
	aucune note < 8, sinon quitte ajournée
	semestre pair : Note > 10 et plus dans la moitiée des RCUE.
*/

enum {NB_CARACTERES = 30, NB_ETUDIANTS_MAX = 100, NB_SEMESTRES = 6, NB_UE = 6, ADMIS = 10};


typedef struct {
	char nom[NB_CARACTERES];
	char prenom[NB_CARACTERES];
	char statut[NB_CARACTERES]; // Définition d'un type énuméré étudiant.
	int semestres;  // max 6 semestres
	int id;
	int UE;
	float note;
} Etudiant;

typedef struct {
	Etudiant liste_etudiants[NB_ETUDIANTS_MAX];
	int id_etudiant;
} IdEtudiant;

typedef struct {
	IdEtudiant liste_UE[NB_UE];
	float note;
} NotesUE;



Etudiant nouv_etudiant;
IdEtudiant id;
NotesUE notesUE;


int EXIT(char commande[NB_CARACTERES]) {
	if (strcmp(commande, "EXIT") == 0) {
		printf("Arret du programme... \n");
		abort(); // Arret programme après que l'utilisateur ait tapé "EXIT".
	}
	return 0;
}

int INSCRIRE(void) {
	char nom[NB_CARACTERES];
	char prenom[NB_CARACTERES];

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

	// vérifie si l'étudiant ne possède pas le même prenom et nom que l'ancien (majuscule ou min
	for (int j = 0; j < id.id_etudiant; ++j) {
		if (_stricmp(id.liste_etudiants[j].nom, nom) == 0 && (_stricmp(id.liste_etudiants[j].prenom, prenom) == 0)) {
			printf("Etudiant deja enregistre \n");
			return -1;
		}

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

int ETUDIANTS(void) {
	if (id.id_etudiant == 0) {
		printf("Aucun etudiant n'est enregistre.\n");
		return 0;
	}
	else {
		for (int i = 0; i < id.id_etudiant; ++i) {
			printf("%d - %s %s - S%d - %s\n", id.liste_etudiants[i].id, id.liste_etudiants[i].nom, id.liste_etudiants[i].prenom,
				id.liste_etudiants[i].semestres, id.liste_etudiants[i].statut);
		}
	}
	return 0;
}

int NOTE(void) {
	int id_etudiant = 0;
	// Vérifie si l'ID est valide.
	scanf("%d %d %f", &id_etudiant, &nouv_etudiant.UE, &notesUE.liste_UE->liste_etudiants[id_etudiant].note);
	for (int i = 0; i < id.id_etudiant; ++i) {
		if (id_etudiant == id.liste_etudiants[i].id) {
			printf("Note enregistree \n");
		}
		else {
			printf("Identifiant incorrect \n");
		}
	}
	return 0;
}


int CURSUS(void) {
	int id_etudiant;
	char status[3];
	scanf_s("%d", &id_etudiant);
	// Boucle qui vérifie si l'id étudiant correspond à celui du tableau (1 == 1).
	for (int i = 0; i < id.id_etudiant; ++i) {
		if (id_etudiant == id.liste_etudiants[i].id) {
			printf("%d %s %s\n", id.liste_etudiants[i].id, id.liste_etudiants[i].nom, id.liste_etudiants[i].prenom);
		}

		for (int j = 1; j < id.liste_etudiants[i].semestres; ++j) {
			for (int k = 1; k < id.liste_etudiants[i].UE; ++k) {
				for (int l = 1; l < notesUE.liste_UE->liste_etudiants[i].note; ++l) {
					if (notesUE.liste_UE->liste_etudiants[i].note >= ADMIS) {
						status[0] = "ADM";
					}
					else {
						status[0] = "AJ";
					}

					printf("- %dd (%s)\n", notesUE.liste_UE->liste_etudiants[l].note, status);
				}
			}
		}
	}
	return 0;
}




int main() {
	char commande[NB_CARACTERES];
	int recommencer = 1;

	do {
		printf("Entrez une commande parmis celles qui sont disponibles, en MAJUSCULE obligatoire ! \n");
		printf("ETUDIANTS CURSUS INSCRIRE NOTE EXIT JURY BILAN  \n");
		scanf("%32s", commande);

		if (strcmp(commande, "ETUDIANTS") == 0) {
			ETUDIANTS();
		}
		else if (strcmp(commande, "CURSUS") == 0) {
			CURSUS();
		}
		else if (strcmp(commande, "INSCRIRE") == 0) {
			INSCRIRE();
		}
		else if (strcmp(commande, "EXIT") == 0) {
			EXIT(commande);
		}
		else if (strcmp(commande, "JURY") == 0 ) {
			printf("Organisation du jury... \n");
		}
		else if (strcmp(commande, "BILAN") == 0) {
			printf("Affichage du bilan des étudiants... \n");
		}
		else if (strcmp(commande, "NOTE") == 0) {
			NOTE();
		}
		else {
			printf("Commande inconnue. Veuillez reessayer.\n");
		}
	} while (1);
	return 0;
}







