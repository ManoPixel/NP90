#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int caractere_to_int(char c){
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'z') {
        return (c - 'a') + 10;
    } else if (c >= 'A' && c <= 'Z') {
        return (c - 'A') + 36;
    } else if (c >= '!' && c <= '/') {
        return (c - '!') + 62;
    } else if (c >= ':' && c <= '@') {
        return (c - ':') + 77;
    } else if (c >= '[' && c <= '`') {
        return (c - '[') + 84;
    } else if (c >= '{' && c <= '~') {
        return (c - '{') + 90;
    } else {
        return -1;
    }
}

void initializeur(int taille, int essai[taille], int secret[taille], int grain){

    char choix;
    int valide = 0;

    do {
        printf("\nChoisissez le mode de depart\n[1]Commencer par que des 0");
        printf("\n[2]Commencer que par le plus grand caractere\n[3]Commencer que par le caractere au milieu");
        printf("\n[4]Commencer aleatoirement\n[5]Ecrivez votre mot de depart\nChoix: ");
        scanf(" %c", &choix);

        switch (choix) {
            case '1' :
                for (int i = 0; i<taille; i++) {
                    essai[i] = 0;
                }
                valide = 1;
                break;
            case '2' :
                for (int i = 0; i<taille; i++) {
                    essai[i] = grain-1;
                }
                valide = 1;
                break;
            case '3' :
                for (int i = 0; i<taille; i++) {
                    essai[i] = grain/2;
                }
                valide = 1;
                break;
            case '4' :
                for (int i = 0; i<taille; i++) {
                    essai[i] = rand()%grain;
                }
                valide = 1;
                break;
            case '5' : {
                char saisie[taille + 1];
                printf("\nEcrivez le mot de depart: ");
                scanf(" %s", saisie);

                valide = 1;
                for (int i = 0; i < taille; i++) {
                    essai[i] = caractere_to_int(saisie[i]);

                    if (essai[i] == -1 || essai[i] >= grain) {
                        valide = 0;
                        printf("\nDefault de saisie, le caractere '%c' ne fait pas partie du grain selectionne ou est mal saisi!", saisie[i]);
                        break;
                    }
                }
                break;
            }
            default :
                printf("\nDefault de saisie, veillez recommencer.");
        }
    } while(!valide);

    valide = 0;

    do {
        printf("\nChoisissez le code secret\n[1]Commencer par que des 0");
        printf("\n[2]Commencer que par le plus grand caractere\n[3]Commencer que par le caractere au milieu");
        printf("\n[4]Commencer aleatoirement\n[5]Ecrivez le code secret\nChoix: ");
        scanf(" %c", &choix);

        switch (choix) {
            case '1' :
                for (int i = 0; i<taille; i++) {
                    secret[i] = 0;
                }
                valide = 1;
                break;
            case '2' :
                for (int i = 0; i<taille; i++) {
                    secret[i] = grain-1;
                }
                valide = 1;
                break;
            case '3' :
                for (int i = 0; i<taille; i++) {
                    secret[i] = grain/2;
                }
                valide = 1;
                break;
            case '4' :
                for (int i = 0; i<taille; i++) {
                    secret[i] = rand()%grain;
                }
                valide = 1;
                break;
            case '5' : {
                char saisie[taille + 1];
                printf("\nEcrivez le code secret: ");
                scanf(" %s", saisie);

                valide = 1;
                for (int i = 0; i < taille; i++) {
                    secret[i] = caractere_to_int(saisie[i]);

                    if (secret[i] == -1 || secret[i] >= grain) {
                        printf("\nDefault de saisie, le caractere '%c' ne fait pas partie du grain selectionne ou est mal saisie!", saisie[i]);
                        valide = 0;
                        break;
                    }
                }
                break;
            }
            default :
                printf("\nDefault de saisie, veillez recommencer.");
        }
    } while (!valide);
}

int egal(int taille, int verification[taille], int code[taille]) {
    for (int i = 0; i<taille; i++) {
        if (verification[i] != code[i]) {
            return 0;
        }
    }
    return 1;
}

void augmente(int taille, int essai[taille], int grain){
    essai[taille-1]++; //On augmente le dernier chiffre

    if (essai[taille-1] <= (grain-1)) {
        //Tout est OK donc on n'a rien a gerer
        return;
    } else {
        //On a depasse notre taille de grain donc on doit propager la retenue
        int indice_retenue = taille-1;
        while (indice_retenue >= 0 && essai[indice_retenue] == grain) {
            essai[indice_retenue] = 0;
            indice_retenue--; //On remonte d'un rang

            if (indice_retenue >= 0) { //On evite d'ecrire sur essai[-1]
                essai[indice_retenue]++;
            }
        }
    }
}

void affiche_caractere(int c) {
    if (c >= 0 && c <= 9) {
        printf("%d", c); //Le chiffres
    } else if (c >= 10 && c <= 35) {
        printf("%c", 'a' + (c-10)); //Les minuscules
    } else if (c >= 36 && c <= 61) {
        printf("%c", 'A' + (c-36)); //Les majuscules
    } else if (c >= 62 && c <= 76) {
        printf("%c", '!' + (c-62)); //On commence les symboles a verifier sur la table ASCII
    } else if (c >= 77 && c <= 83) {
        printf("%c", ':' + (c-77));
    } else if (c >= 84 && c <= 89) {
        printf("%c", '[' + (c-84));
    } else if (c >= 90 && c <= 93) {
        printf("%c", '{' + (c-90));
    } else {
        printf("Erreur");
    }
}

void affiche(int taille, int tab[taille]) {
    printf("\n[");
    for (int i = 0; i<taille; i++) {
        affiche_caractere(tab[i]);
    }
    printf("]");
}

int main()
{
    char recommencer = 1;

    do {
        srand(time(NULL));

        int taille;
        printf("\nQuelle taille du code secret?: ");
        scanf(" %d", &taille);

        int* secret = malloc(sizeof(int)*taille);
        int* essai = malloc(sizeof(int)*taille);

        char choix = '0';
        int grain;

        printf("\nSelectionnez la taille du grain\n[1]Chiffres de 0 a 10(taille 10)\n[2]Chiffres et lettre minuscules (taille 36)");
        printf("\n[3]Chiffres, lettres minuscules et majuscules (taille 62)\n[4]Tous d'avant et symboles (taille 94)\nChoix: ");

        scanf(" %c", &choix);

        switch (choix) {
            case '1' :
                grain = 10;
                break;
            case '2' :
                grain = 36;
                break;
            case '3' :
                grain = 62;
                break;
            case '4' :
                grain = 94;
                break;
            default :
                printf("\nDefault de saisie, veillez recommencer.");
                free(essai);
                free(secret);
                continue;
        }

        initializeur(taille, essai, secret, grain);

        unsigned long long compteur = 0;

        printf("\nChoisissez le mode\n[1]Sans affichage mais mesure du temps\n[2]Avec affichage au fur et a mesure\nChoix: ");
        scanf(" %c", &choix);

        switch (choix) {
            case '1' : {
                clock_t debut = clock();
                while (!(egal(taille, essai, secret))){
                    augmente(taille, essai, grain);
                    compteur++;
                }
                clock_t fin = clock();

                double temps = (double)(fin-debut) / CLOCKS_PER_SEC;

                printf("\nLe mot secret etait: ");
                affiche(taille, secret);
                printf("\nOn s'est arrete sur: ");
                affiche(taille, essai);
                printf("\nOn a mit: %llu essais", compteur);
                printf(" et %.30f secondes", temps);
                printf("\n\nVous avez termine, veuillez vous recommencer?\n[1]Pour recommencer\nChoix: ");
                scanf(" %c", &choix);
                if (choix != '1') {
                    recommencer = 0;
                }
                free(essai);
                free(secret);
                break;
            }
            case '2' : {
                while (!(egal(taille, essai, secret))) {
                    affiche(taille, essai);
                    augmente(taille, essai, grain);
                    compteur++;
                }

                printf("\nLe mot secret etait: ");
                affiche(taille, secret);
                printf("\nOn s'est arrete sur: ");
                affiche(taille, essai);
                printf("\nOn a mit: %llu essais", compteur);
                printf("\n\nVous avez termine, veuillez vous recommencer?\n[1]Pour recommencer\nChoix: ");
                scanf(" %c", &choix);
                if (choix != '1') {
                    recommencer = 0;
                }
                free(essai);
                free(secret);
                break;
            }
            default :
                printf("\nDefault de saisie, veillez recommencer.");
                free(essai);
                free(secret);
        }

    } while (recommencer);

    return 0;
}
