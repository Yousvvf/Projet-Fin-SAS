#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trier_alphabetique(char mots[][50], int occurences[], int longueurs[], int positions[][100], int nb_positions[], int nb_mots) {
    for (int i = 0; i < nb_mots - 1; i++) {
        for (int j = i + 1; j < nb_mots; j++) {
            if (strcmp(mots[i], mots[j]) > 0) {
                char temp[50];
                strcpy(temp, mots[i]);
                strcpy(mots[i], mots[j]);
                strcpy(mots[j], temp);

                int temp_occ = occurences[i];
                occurences[i] = occurences[j];
                occurences[j] = temp_occ;

                int temp_len = longueurs[i];
                longueurs[i] = longueurs[j];
                longueurs[j] = temp_len;

                int temp_pos[100];
                int temp_nb_pos = nb_positions[i];
                nb_positions[i] = nb_positions[j];
                nb_positions[j] = temp_nb_pos;

                for (int k = 0; k < 100; k++) {
                    temp_pos[k] = positions[i][k];
                    positions[i][k] = positions[j][k];
                    positions[j][k] = temp_pos[k];
                }
            }
        }
    }
} // fin (trier alphabetique)

void trier_par_frequence(char mots[][50], int occurences[], int longueurs[], int positions[][100], int nb_positions[], int nb_mots) {
    for (int i = 0; i < nb_mots - 1; i++) {
        for (int j = i + 1; j < nb_mots; j++) {
            if (occurences[i] < occurences[j]) {
                char temp[50];
                strcpy(temp, mots[i]);
                strcpy(mots[i], mots[j]);
                strcpy(mots[j], temp);

                int temp_occ = occurences[i];
                occurences[i] = occurences[j];
                occurences[j] = temp_occ;

                int temp_len = longueurs[i];
                longueurs[i] = longueurs[j];
                longueurs[j] = temp_len;

                int temp_pos[100];
                int temp_nb_pos = nb_positions[i];
                nb_positions[i] = nb_positions[j];
                nb_positions[j] = temp_nb_pos;

                for (int k = 0; k < 100; k++) {
                    temp_pos[k] = positions[i][k];
                    positions[i][k] = positions[j][k];
                    positions[j][k] = temp_pos[k];
                }
            }
        }
    }
} // Fin (trier par frequence)

void trier_par_longueur(char mots[][50], int occurences[], int longueurs[], int positions[][100], int nb_positions[], int nb_mots) {
    for (int i = 0; i < nb_mots - 1; i++) {
        for (int j = i + 1; j < nb_mots; j++) {
            if (longueurs[i] > longueurs[j]) {
                char temp[50];
                strcpy(temp, mots[i]);
                strcpy(mots[i], mots[j]);
                strcpy(mots[j], temp);

                int temp_occ = occurences[i];
                occurences[i] = occurences[j];
                occurences[j] = temp_occ;

                int temp_len = longueurs[i];
                longueurs[i] = longueurs[j];
                longueurs[j] = temp_len;

                int temp_pos[100];
                int temp_nb_pos = nb_positions[i];
                nb_positions[i] = nb_positions[j];
                nb_positions[j] = temp_nb_pos;

                for (int k = 0; k < 100; k++) {
                    temp_pos[k] = positions[i][k];
                    positions[i][k] = positions[j][k];
                    positions[j][k] = temp_pos[k];
                }
            }
        }
    }
} // fin (trier par longueur)





int main() {
    int choix;
    char texte[2000];
    char nettoye[2000];
    char mots[500][50];
    int occurences[500];
    int longueurs[500];
    int positions[500][100];      
    int nb_positions[500];       
    int nb_mots = 0;

    while (1) 
    {
        printf("\n=== MENU ===\n");
        printf("1. Saisir un texte et analyser\n");
        printf("2. Afficher tous les mots\n");
        printf("3. Rechercher un mot exact\n");
        printf("4. Rechercher un mot partiel\n");
        printf("5. Trier les mots\n");
        printf("6. Statistiques globales\n");
        printf("7. Analyser\n");
        printf("8. Quitter le programme\n");

        printf("Entre ton choix : ");
        scanf("%d", &choix);
        while (getchar() != '\n');

        if (choix == 1) 
        {
            printf("Entrez un texte :\n");
            fgets(texte, sizeof(texte), stdin);

            int i = 0, j = 0;
            while (texte[i] != '\0') 
            {
                if (isalpha(texte[i])) 
                {
                    nettoye[j++] = tolower(texte[i]);
                } 
                else 
                {
                    nettoye[j++] = ' ';
                }
                i++;
            }
            nettoye[j] = '\0';

            nb_mots = 0;
            char mot[50];
            int pos = 0;
            int position = 1;

            for (int k = 0; ; k++) 
            {
                if (isalpha(nettoye[k])) 
                {
                    mot[pos++] = nettoye[k];
                } 
                else if (pos > 0) 
                {
                    mot[pos] = '\0';
                    pos = 0;

                    int existe = 0;
                    for (int m = 0; m < nb_mots; m++) 
                    {
                        if (strcmp(mots[m], mot) == 0) 
                        {
                            occurences[m]++;
                            positions[m][nb_positions[m]++] = position;
                            existe = 1;
                            break;
                        }
                    }

                    if (!existe) 
                    {
                        strcpy(mots[nb_mots], mot);
                        occurences[nb_mots] = 1;
                        longueurs[nb_mots] = strlen(mot);
                        positions[nb_mots][0] = position;
                        nb_positions[nb_mots] = 1;
                        nb_mots++;
                    }

                    position++;
                }

                if (nettoye[k] == '\0') break;
            }

            printf(" Analyse terminee.\n");
        } // fin de choix 1

        else if (choix == 2) 
        {
            if (nb_mots == 0) 
            {
                printf(" Aucun texte analyse. Choisissez l'option 1 d'abord.\n");
            } 
            else 
            {
                printf("\n Dictionnaire des mots :\n");
                for (int i = 0; i < nb_mots; i++) {
                    printf("%s | Occurrences: %d | Longueur: %d | Positions: ",
                           mots[i], occurences[i], longueurs[i]);
                    for (int j = 0; j < nb_positions[i]; j++) 
                    {
                        printf("%d ", positions[i][j]);
                    }
                    printf("\n");
                }
            }
        } // fin de choix 2

        else if (choix == 3) 
{
            if (nb_mots == 0) 
            {
                printf("Aucun texte analyse. Choisissez d'abord l'option 1.\n");
            } 
            else 
    {
        char recherche[50];
        printf(" Entrez le mot a rechercher : ");
        fgets(recherche, sizeof(recherche), stdin);
        recherche[strcspn(recherche, "\n")] = '\0';

        for (int i = 0; recherche[i]; i++) 
        {
            recherche[i] = tolower(recherche[i]);
        }

        int trouve = 0;
        for (int i = 0; i < nb_mots; i++) 
        {
            if (strcmp(mots[i], recherche) == 0) 
            {
                printf("\n Mot trouve : %s\n", mots[i]);
                printf("Occurrences : %d\n", occurences[i]);
                printf("Longueur : %d\n", longueurs[i]);
                printf("Positions : ");
                for (int j = 0; j < nb_positions[i]; j++) 
                {
                    printf("%d ", positions[i][j]);
                }
                printf("\n");
                trouve = 1;
                break;
            }
        }

        if (!trouve) {
            printf(" Mot non trouve dans le texte.\n");
        }
    }
} // fin de choix 3

    else if (choix == 4)
    {
        if (nb_mots == 0) 
        {
                printf("Aucun texte analyse. Choisissez d'abord l'option 1.\n");
        }
        else
        {
            char mot_partiel[50];
            printf(" Entrez un mot : ");
            fgets(mot_partiel, sizeof(mot_partiel), stdin);
            mot_partiel[strcspn(mot_partiel, "\n")] = '\0';
            
            for (int i = 0; mot_partiel[i]; i++) 
            {
                mot_partiel[i] = tolower(mot_partiel[i]);
            }
            
            for (int i = 0; i < nb_mots; i++) 
            {
                if (strstr(mots[i], mot_partiel) != NULL) 
                {
                    printf("%s | Occurrences: %d | Longueur: %d | Positions: ", mots[i], occurences[i], longueurs[i]);
                    for (int j = 0; j < nb_positions[i]; j++) 
                    {
                    printf("%d ", positions[i][j]);
                    }
                    printf("\n");
                }
            }
        }   
    } //fin de choix 4

    else if (choix == 5)
    {
           if (nb_mots == 0) 
        {
                printf("Aucun texte analyse. Choisissez d'abord l'option 1.\n");
        }

        else
        {
                int sous_choix;

                printf("\n choisissez le type de tri : \n");
                printf("1. Tri alphabetique \n");
                printf("2. Tri par frequence (decroissante)\n");
                printf("3. Tri par longueur (croissante)\n");

                printf("Votre choix : ");
                scanf("%d", &sous_choix);
                
                if (sous_choix == 1) {
                    trier_alphabetique(mots, occurences, longueurs, positions, nb_positions, nb_mots);
                    printf("\nMots tries alphabétiquement :\n");
                }
                else if (sous_choix == 2) {
                    trier_par_frequence(mots, occurences, longueurs, positions, nb_positions, nb_mots);
                    printf("\nMots tries par fréquence :\n");
                }
                else if (sous_choix == 3) {
                    trier_par_longueur(mots, occurences, longueurs, positions, nb_positions, nb_mots);
                    printf("\nMots tries par longueur :\n");
                }
                else 
                {
                    printf("choix invalide \n");
                }
                for (int i = 0; i < nb_mots; i++) 
                {
                    printf("%s | Occurrences: %d | Longueur: %d | Positions: ", mots[i], occurences[i], longueurs[i]);
                    for (int j = 0; j < nb_positions[i]; j++) 
                {
                    printf("%d ", positions[i][j]);
                }
                printf("\n");
        }
            
        
    }
        
} // fin de choix 5

     else if (choix == 6)
{
    if (nb_mots == 0)
    {
        printf("Aucun texte analyse. Choisissez d'abord l'option 1.\n");
    }
    else
    {
        int total_mots = 0;
        int somme_longueurs = 0;
        int max_longueur = longueurs[0];
        int min_longueur = longueurs[0];
        int max_freq = occurences[0];

        char mot_plus_long[50];
        char mot_plus_court[50];
        char mot_plus_frequent[50];

        strcpy(mot_plus_long, mots[0]);
        strcpy(mot_plus_court, mots[0]);
        strcpy(mot_plus_frequent, mots[0]);

        for (int i = 0; i < nb_mots; i++)
        {
            total_mots += occurences[i];
            somme_longueurs += longueurs[i] * occurences[i];

            if (longueurs[i] > max_longueur)
            {
                max_longueur = longueurs[i];
                strcpy(mot_plus_long, mots[i]);
            }

            if (longueurs[i] < min_longueur)
            {
                min_longueur = longueurs[i];
                strcpy(mot_plus_court, mots[i]);
            }

            if (occurences[i] > max_freq)
            {
                max_freq = occurences[i];
                strcpy(mot_plus_frequent, mots[i]);
            }
        }

        float diversite = (float)nb_mots / total_mots;
        float moyenne = (float)somme_longueurs / total_mots;

        printf("\n Statistiques globales :\n");
        printf("Nombre total de mots : %d\n", total_mots);
        printf("Nombre de mots uniques : %d\n", nb_mots);
        printf("Diversite lexicale : %.2f\n", diversite);
        printf("Longueur moyenne des mots : %.2f\n", moyenne);
        printf("Mot le plus long : %s (%d lettres)\n", mot_plus_long, max_longueur);
        printf("Mot le plus court : %s (%d lettres)\n", mot_plus_court, min_longueur);
        printf("Mot le plus frequent : %s (%d fois)\n", mot_plus_frequent, max_freq);
    }
}

    else if (choix == 7)
    {
        
    }
    

    

    
    
        
}
}
