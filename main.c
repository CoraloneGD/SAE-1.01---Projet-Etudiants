#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996 6031)

enum { NB_CARACTERES = 30, NB_ETUDIANTS_MAX = 100, NB_SEMESTRES = 6, NB_UE = 6, ADMIS = 10 };

typedef struct {
    char nom[NB_CARACTERES];
    char prenom[NB_CARACTERES];
    char statut[NB_CARACTERES];
    int semestres;
    int id;
    float note[NB_SEMESTRES][NB_UE];
} Etudiant;

typedef struct {
    Etudiant liste_etudiants[NB_ETUDIANTS_MAX];
    int nombre_etudiant;
} IdEtudiant;

// Initialiser toutes les notes à -1 (vide)
void init_tableau_notes(Etudiant *e) {
    for (int i = 0; i < NB_SEMESTRES; ++i)
        for (int j = 0; j < NB_UE; ++j)
            e->note[i][j] = -1.0f;
}

// Vérifier si l'utilisateur tape "EXIT"
int EXIT(char *commande) {
    if (strcmp(commande, "EXIT") == 0) {
        printf("Arret du programme... \n");
        abort();
    }
    return 0;
}

// Inscrire un nouvel étudiant
int INSCRIRE(IdEtudiant *id, Etudiant *nouv_etudiant) {
    char nom[NB_CARACTERES], prenom[NB_CARACTERES];

    if (scanf("%29s %29s", nom, prenom) != 2) {
        printf("Lecture invalide. Inscription annulee.\n");
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return -1;
    }

    if (id->nombre_etudiant >= NB_ETUDIANTS_MAX) {
        printf("Limite d'etudiants atteinte.\n");
        return -1;
    }

    // Vérifie doublons
    for (int j = 0; j < id->nombre_etudiant; ++j) {
        if (_stricmp(id->liste_etudiants[j].nom, nom) == 0 &&
            _stricmp(id->liste_etudiants[j].prenom, prenom) == 0) {
            printf("Etudiant deja enregistre\n");
            return -1;
        }
    }

    strncpy(nouv_etudiant->nom, nom, NB_CARACTERES - 1);
    nouv_etudiant->nom[NB_CARACTERES - 1] = '\0';
    strncpy(nouv_etudiant->prenom, prenom, NB_CARACTERES - 1);
    nouv_etudiant->prenom[NB_CARACTERES - 1] = '\0';
    strncpy(nouv_etudiant->statut, "Inscrit", NB_CARACTERES - 1);
    nouv_etudiant->statut[NB_CARACTERES - 1] = '\0';
    nouv_etudiant->semestres = 0;
    init_tableau_notes(nouv_etudiant);

    // Générer ID
    int nouvel_id = id->nombre_etudiant;
    nouv_etudiant->id = nouvel_id;

    id->liste_etudiants[id->nombre_etudiant] = *nouv_etudiant;
    id->nombre_etudiant++;

    printf("Inscription enregistree (%d)\n", nouvel_id);
    return 0;
}

// Afficher tous les étudiants
int ETUDIANTS(IdEtudiant *id) {
    if (id->nombre_etudiant == 0) {
        printf("Aucun etudiant n'est enregistre.\n");
        return 0;
    }
    for (int i = 0; i < id->nombre_etudiant; ++i) {
        printf("%d - %s %s - S%d - %s\n",
            id->liste_etudiants[i].id,
            id->liste_etudiants[i].nom,
            id->liste_etudiants[i].prenom,
            id->liste_etudiants[i].semestres,
            id->liste_etudiants[i].statut);
    }
    return 0;
}

// Saisir une note
int NOTE(IdEtudiant *id) {
    int id_etudiant, sem, nbUe;
    float note_val;
    if (scanf("%d %d %d %f", &id_etudiant, &sem, &nbUe, &note_val) != 4) {
        printf("Erreur de saisie.\n");
        return -1;
    }
    if (id_etudiant < 0 || id_etudiant >= id->nombre_etudiant ||
        sem < 0 || sem >= NB_SEMESTRES ||
        nbUe < 0 || nbUe >= NB_UE) {
        printf("Paramètres invalides.\n");
        return -1;
    }
    id->liste_etudiants[id_etudiant].note[sem][nbUe] = note_val;
    return 0;
}

// Afficher le cursus d’un étudiant
int CURSUS(IdEtudiant *id) {
    int id_etudiant;
    if (scanf("%d", &id_etudiant) != 1 ||
        id_etudiant < 0 || id_etudiant >= id->nombre_etudiant) {
        printf("ID invalide.\n");
        return -1;
    }

    Etudiant *e = &id->liste_etudiants[id_etudiant];
    printf("%d %s %s\n", e->id, e->nom, e->prenom);

    char status[5];
    char note_txt[10];

    for (int j = 0; j < NB_SEMESTRES; ++j) {
        for (int k = 0; k < NB_UE; ++k) {
            if (e->note[j][k] == -1.0f) {
                strcpy(note_txt, "*");
                strcpy(status, "*");
            } else if (e->note[j][k] >= ADMIS) {
                snprintf(note_txt, sizeof(note_txt), "%.2f", e->note[j][k]);
                strcpy(status, "ADM");
            } else {
                snprintf(note_txt, sizeof(note_txt), "%.2f", e->note[j][k]);
                strcpy(status, "AJR");
            }
            printf("S%d - %s (%s)  ", j, note_txt, status);
        }
        printf("\n");
    }

    return 0;
}

int main() {
    char commande[NB_CARACTERES];
    Etudiant nouv_etudiant = { 0 };
    IdEtudiant id = { .nombre_etudiant = 0 };

    do {
        printf("Entrez une commande (MAJUSCULE obligatoire): \n");
        printf("ETUDIANTS CURSUS INSCRIRE NOTE EXIT JURY BILAN\n");
        scanf("%32s", commande);

        if (strcmp(commande, "ETUDIANTS") == 0) {
            ETUDIANTS(&id);
        } else if (strcmp(commande, "CURSUS") == 0) {
            CURSUS(&id);
        } else if (strcmp(commande, "INSCRIRE") == 0) {
            INSCRIRE(&id, &nouv_etudiant);
        } else if (strcmp(commande, "NOTE") == 0) {
            NOTE(&id);
        } else if (strcmp(commande, "EXIT") == 0) {
            EXIT(commande);
        } else if (strcmp(commande, "JURY") == 0) {
            printf("Organisation du jury...\n");
        } else if (strcmp(commande, "DEMISSION") == 0) {
            printf("Affichage du bilan des étudiants...\n");
        } else {
            printf("Commande inconnue. Veuillez reessayer.\n");
        }
    } while (1);

    return 0;
}
