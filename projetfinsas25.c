#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char mot[50];
    int occurences;
    int longueur;
    int positions[100];
    int nb_positions;
} Mot;

void swap(Mot *a, Mot *b) {
    Mot temp = *a;
    *a = *b;
    *b = temp;
}

void trier_alphabetique(Mot mots[], int nb_mots) {
    for (int i = 0; i < nb_mots - 1; i++) {
        for (int j = i + 1; j < nb_mots; j++) {
            if (strcmp(mots[i].mot, mots[j].mot) > 0) {
                swap(&mots[i], &mots[j]);
            }
        }
    }
}

void trier_par_frequence(Mot mots[], int nb_mots) {
    for (int i = 0; i < nb_mots - 1; i++) {
        for (int j = i + 1; j < nb_mots; j++) {
            if (mots[i].occurences < mots[j].occurences) {
                swap(&mots[i], &mots[j]);
            }
        }
    }
}

void trier_par_longueur(Mot mots[], int nb_mots) {
    for (int i = 0; i < nb_mots - 1; i++) {
        for (int j = i + 1; j < nb_mots; j++) {
            if (mots[i].longueur > mots[j].longueur) {
                swap(&mots[i], &mots[j]);
            }
        }
    }
}

int est_palindrome(const char *mot) {
    int L = strlen(mot);
    for (int i = 0; i < L / 2; i++) {
        if (mot[i] != mot[L - 1 - i]) return 0;
    }
    return 1;
}

void analyser_palindromes(Mot mots[], int nb_mots) {
    int pal_found = 0;
    printf("\n-- Palindromes --\n");
    for (int i = 0; i < nb_mots; i++) {
        if (est_palindrome(mots[i].mot)) {
            pal_found = 1;
            printf("%s | Occurrences: %d | Positions: ",
                   mots[i].mot, mots[i].occurences);
            for (int p = 0; p < mots[i].nb_positions; p++)
                printf("%d ", mots[i].positions[p]);
            printf("\n");
        }
    }
    if (!pal_found) {
        printf("Aucun palindrome trouve.\n");
    }
}

void analyser_anagrammes(Mot mots[], int nb_mots) {
    char sig[500][50];
    int used[500] = {0};

    for (int i = 0; i < nb_mots; i++) {
        char temp[50];
        strcpy(temp, mots[i].mot);
        int len = strlen(temp);
        for (int x = 0; x < len - 1; x++) {
            for (int y = x + 1; y < len; y++) {
                if (temp[x] > temp[y]) {
                    char c = temp[x];
                    temp[x] = temp[y];
                    temp[y] = c;
                }
            }
        }
        strcpy(sig[i], temp);
    }

    printf("\n-- Anagrammes --\n");
    int any_group = 0;

    for (int i = 0; i < nb_mots; i++) {
        if (used[i]) continue;
        int group_count = 0;
        for (int j = i; j < nb_mots; j++) {
            if (strcmp(sig[i], sig[j]) == 0) group_count++;
        }
        if (group_count > 1) {
            any_group = 1;
            printf("Groupe : ");
            for (int j = i; j < nb_mots; j++) {
                if (strcmp(sig[i], sig[j]) == 0) {
                    printf("%s(%d) ", mots[j].mot, mots[j].occurences);
                    used[j] = 1;
                }
            }
            printf("\n");
        }
    }
    if (!any_group) {
        printf("Aucun groupe d'anagrammes trouve.\n");
    }
}

void afficher_nuage_mots(Mot mots[], int nb_mots) {
    int max_freq = 0;
    for (int i = 0; i < nb_mots; i++) {
        if (mots[i].occurences > max_freq) max_freq = mots[i].occurences;
    }

    printf("\n-- Nuage de mots --\n");
    for (int i = 0; i < nb_mots; i++) {
        int stars = (mots[i].occurences * 50) / (max_freq == 0 ? 1 : max_freq);
        if (stars < 1) stars = 1;
        printf("%-15s ", mots[i].mot);
        for (int s = 0; s < stars; s++) putchar('*');
        printf(" (%d)\n", mots[i].occurences);
    }
}


int main() {
    int choix;
    char texte[2000];
    char nettoye[2000];
    Mot mots[50];
    int nb_mots = 0;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Saisir un texte et analyser\n");
        printf("2. Afficher le dictionnaire\n");
        printf("3. Rechercher un mot (exact)\n");
        printf("4. Rechercher un mot (partiel)\n");
        printf("5. Trier les mots\n");
        printf("6. Statistiques\n");
        printf("7. Analyses avancees\n");
        printf("8. Quitter\n");

        printf("Entre ton choix : ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        if (choix == 1) {
            printf("Entrez un texte :\n");
            fgets(texte, sizeof(texte), stdin);

            int i = 0, j = 0;
            while (texte[i] != '\0') {
                if (isalpha((unsigned char)texte[i]))
                    nettoye[j++] = tolower((unsigned char)texte[i]);
                else
                    nettoye[j++] = ' ';
                i++;
            }
            nettoye[j] = '\0';

            nb_mots = 0;
            int pos = 0;
            int position = 1;
            char mot_temp[50];

            for (int k = 0;; k++) {
                if (isalpha((unsigned char)nettoye[k])) {
                    if (pos < 50 - 1)
                        mot_temp[pos++] = nettoye[k];
                } else if (pos > 0) {
                    mot_temp[pos] = '\0';
                    pos = 0;

                    int found = 0;
                    for (int m = 0; m < nb_mots; m++) {
                        if (strcmp(mots[m].mot, mot_temp) == 0) {
                            mots[m].occurences++;
                            if (mots[m].nb_positions < 100)
                                mots[m].positions[mots[m].nb_positions++] = position;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && nb_mots < 50) {
                        strcpy(mots[nb_mots].mot, mot_temp);
                        mots[nb_mots].occurences = 1;
                        mots[nb_mots].longueur = strlen(mot_temp);
                        mots[nb_mots].nb_positions = 1;
                        mots[nb_mots].positions[0] = position;
                        nb_mots++;
                    }
                    position++;
                }
                if (nettoye[k] == '\0') break;
            }
            printf("Analyse complete.\n");
        }

        else if (choix == 2) {
            if (nb_mots == 0) 
            {
                printf("Aucun texte analyse.\n");
            }
            else {
                for (int i = 0; i < nb_mots; i++) {
                    printf("%s | Occurrences: %d | Longueur: %d | Positions: ",
                           mots[i].mot, mots[i].occurences, mots[i].longueur);
                    for (int j = 0; j < mots[i].nb_positions; j++)
                        printf("%d ", mots[i].positions[j]);
                    printf("\n");
                }
            }
        }

        else if (choix == 3) {
            if (nb_mots == 0) 
            { 
                printf("Aucun texte analyse.\n"); continue; 
            }
            char mot_cherche[50];
            printf("Mot a chercher : ");
            fgets(mot_cherche, sizeof(mot_cherche), stdin);
            mot_cherche[strcspn(mot_cherche, "\n")] = 0;
            for (int i = 0; mot_cherche[i]; i++)
                mot_cherche[i] = tolower((unsigned char)mot_cherche[i]);

            int found = 0;
            for (int i = 0; i < nb_mots; i++) {
                if (strcmp(mots[i].mot, mot_cherche) == 0) {
                    printf("%s | Occurrences: %d | Longueur: %d | Positions: ",
                           mots[i].mot, mots[i].occurences, mots[i].longueur);
                    for (int j = 0; j < mots[i].nb_positions; j++)
                        printf("%d ", mots[i].positions[j]);
                    printf("\n");
                    found = 1;
                    break;
                }
            }
            if (!found) 
            {
                printf("Mot non trouve.\n");
            } 
            }

        else if (choix == 4) {
            if (nb_mots == 0) { printf("Aucun texte analyse.\n"); continue; }
            char mot_partiel[50];
            printf("Partie du mot a chercher : ");
            fgets(mot_partiel, sizeof(mot_partiel), stdin);
            mot_partiel[strcspn(mot_partiel, "\n")] = 0;
            for (int i = 0; mot_partiel[i]; i++)
                mot_partiel[i] = tolower((unsigned char)mot_partiel[i]);

            int found = 0;
            for (int i = 0; i < nb_mots; i++) {
                if (strstr(mots[i].mot, mot_partiel) != NULL) {
                    printf("%s | Occurrences: %d | Longueur: %d | Positions: ",
                           mots[i].mot, mots[i].occurences, mots[i].longueur);
                    for (int j = 0; j < mots[i].nb_positions; j++)
                        printf("%d ", mots[i].positions[j]);
                    printf("\n");
                    found = 1;
                }
            }
            if (!found) printf("Aucun mot correspondant.\n");
        }

        else if (choix == 5) {
            if (nb_mots == 0) { printf("Aucun texte analyse.\n"); continue; }
            int sous_choix;
            printf("1. Alphabetique\n2. Frequence\n3. Longueur\n");
            scanf("%d", &sous_choix);
            while (getchar() != '\n');

            if (sous_choix == 1) trier_alphabetique(mots, nb_mots);
            else if (sous_choix == 2) trier_par_frequence(mots, nb_mots);
            else if (sous_choix == 3) trier_par_longueur(mots, nb_mots);

            for (int i = 0; i < nb_mots; i++) {
                printf("%s | Occurrences: %d | Longueur: %d\n",
                       mots[i].mot, mots[i].occurences, mots[i].longueur);
            }
        }

        else if (choix == 6) {
            if (nb_mots == 0) { printf("Aucun texte analyse.\n"); continue; }
            int total_mots = 0, somme_longueurs = 0;
            int max_longueur = mots[0].longueur, min_longueur = mots[0].longueur;
            int max_freq = mots[0].occurences;
            char mot_plus_long[50], mot_plus_court[50], mot_plus_frequent[50];
            strcpy(mot_plus_long, mots[0].mot);
            strcpy(mot_plus_court, mots[0].mot);
            strcpy(mot_plus_frequent, mots[0].mot);

            for (int i = 0; i < nb_mots; i++) {
                total_mots += mots[i].occurences;
                somme_longueurs += mots[i].longueur * mots[i].occurences;
                if (mots[i].longueur > max_longueur) {
                    max_longueur = mots[i].longueur;
                    strcpy(mot_plus_long, mots[i].mot);
                }
                if (mots[i].longueur < min_longueur) {
                    min_longueur = mots[i].longueur;
                    strcpy(mot_plus_court, mots[i].mot);
                }
                if (mots[i].occurences > max_freq) {
                    max_freq = mots[i].occurences;
                    strcpy(mot_plus_frequent, mots[i].mot);
                }
            }

            float diversite = (float)nb_mots / total_mots;
            float moyenne = (float)somme_longueurs / total_mots;

            printf("\nStatistiques globales :\n");
            printf("Nombre total de mots : %d\n", total_mots);
            printf("Nombre de mots uniques : %d\n", nb_mots);
            printf("Diversite lexicale : %.2f\n", diversite);
            printf("Longueur moyenne des mots : %.2f\n", moyenne);
            printf("Mot le plus long : %s (%d lettres)\n", mot_plus_long, max_longueur);
            printf("Mot le plus court : %s (%d lettres)\n", mot_plus_court, min_longueur);
            printf("Mot le plus frequent : %s (%d fois)\n", mot_plus_frequent, max_freq);
        }

        else if (choix == 7) {
            if (nb_mots == 0) { printf("Aucun texte analyse.\n"); continue; }
            analyser_palindromes(mots, nb_mots);
            analyser_anagrammes(mots, nb_mots);
            afficher_nuage_mots(mots, nb_mots);
        }

        else if (choix == 8) {
            printf("Fin du programme.\n");
            break;
        }

        else printf("Choix invalide.\n");
    }

    return 0;
}
