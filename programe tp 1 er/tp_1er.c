#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char num[10];
    char nom[20];
    char prenom[20];
    char adress[20];
    char numtlf[10];
    char motdepass[20];
    float solde;
} compte;

compte tab_compte[100];
int nb_compte = 0;

void sauvegarder_comptes() {
    FILE *f;
    int i;

    f = fopen("comptes.txt", "w");

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    for (i = 0; i < nb_compte; i++) {
        fprintf(f, "%s %s %s %.2f %s %s %s\n" ,tab_compte[i].nom, tab_compte[i].prenom, tab_compte[i].num, tab_compte[i].motdepass,&tab_compte[i].solde ,tab_compte[i].adress,tab_compte[i].numtlf);
    }

    fclose(f);
}

void charger_comptes() {
    FILE *f;
    char ligne[50];
    int i = 0;

    f = fopen("comptes.txt", "r");


    if (f == NULL) {
        printf("Aucun compte enregistre.\n");
        return;
    }

    while (fgets(ligne, 50, f) != NULL) {
        sscanf(ligne, "%s %s %s %s %s %s%s",tab_compte[i].nom, tab_compte[i].prenom, tab_compte[i].num, tab_compte[i].motdepass,&tab_compte[i].solde ,tab_compte[i].adress,tab_compte[i].numtlf);
        i++;
    }

    nb_compte = i;

    fclose(f);
}

int creation_compte() {
    if (nb_compte >= 100) {
        printf("Nombre maximum de comptes atteint.\n");
        return 0;
    }
 printf("Nom : ");
    scanf("%s", tab_compte[nb_compte].nom);

    printf("Prenom : ");
    scanf("%s", tab_compte[nb_compte].prenom);

    printf("Numero de compte : ");
    scanf("%s", tab_compte[nb_compte].num);
   printf("mot de pass : ");
    scanf("%s", tab_compte[nb_compte].motdepass);
   
    printf("Solde initial : ");
    scanf("%f", &tab_compte[nb_compte].solde);
 
     printf("adress : ");
    scanf("%s", tab_compte[nb_compte].adress);
     printf("numero de tlephone : ");
    scanf("%s", tab_compte[nb_compte].numtlf);

    nb_compte++;

    sauvegarder_comptes();

    printf("Compte cree avec succes.\n");

    return 1;
}

int connexion_compte() {
    char num[10];
    char mot_de_passe[20];
    int i;

    printf("Numero de compte : ");
    scanf("%s", num);

    printf("Mot de passe : ");
    scanf("%s", mot_de_passe);

    for (i = 0; i < nb_compte; i++) {
        if (strcmp(num, tab_compte[i].num) == 0) {
            return i;
        }
    }
    

    printf("Compte introuvable.\n");
    return -1;
}

void depot() {
    float montant;
    int i;

    printf("Montant du depot : ");
    scanf("%f", &montant);

      i = connexion_compte();

    if (i != -1) {
        tab_compte[i].solde += montant;
        sauvegarder_comptes();
        printf("Depot effectue avec succes.\n");
    }
}
// -----
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void tri() {
    FILE *file = fopen("comptes.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Count the number of lines in the file
    int count = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        count++;
    }
    rewind(file);

    // Allocate memory for the lines and read them into an array
    char **lines = malloc(count * sizeof(char *));
    if (lines == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        lines[i] = strdup(line);
        i++;
    }
    fclose(file);

    // Sort the lines using the qsort function
    qsort(lines, count, sizeof(char *), compare);

    // Write the sorted lines back to the file
    file = fopen("comptes.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        free(lines);
        return 1;
    }
    for (i = 0; i < count; i++) {
        fputs(lines[i], file);
        printf("%s", lines[i]); // Print the sorted line to the console
        free(lines[i]);
    }
    free(lines);
    fclose(file);

    return 0;
}

void retrait() {
    float montant;
    int i;

    printf("Montant du retrait : ");
    scanf("%f", &montant);

    i = connexion_compte();

    if (i != -1) {
        if (tab_compte[i].solde >= montant) {
            tab_compte[i].solde -= montant;
            sauvegarder_comptes();
            printf("Retrait effectue avec succes.\n");
        } else {
            printf("Solde insuffisant.\n");
        }
    }
}

void solde() {
    int i;

    i = connexion_compte();

    if (i != -1) {
        printf("%s %s\n", tab_compte[i].nom, tab_compte[i].prenom);
        printf("Solde : %.2f\n", tab_compte[i].solde);
    }
}
int reche () {
    char num[10];
    int i;

    printf("Numero de compte : ");
    scanf("%s", num);

    for (i = 0; i < nb_compte; i++) {
       if (strcmp(num, tab_compte[i].num) == 0) {
            printf("Compte trouve : \n");
            printf("Nom : %s\n", tab_compte[i].nom);
            printf("Prenom : %s\n", tab_compte[i].prenom);
            printf("Numero de compte : %s\n", tab_compte[i].num);
            printf("Mot de passe : %s\n", tab_compte[i].motdepass);
            printf("Solde : %.2f\n", tab_compte[i].solde);
            printf("Adresse : %s\n", tab_compte[i].adress);
            printf("Numero de telephone : %s\n", tab_compte[i].numtlf);
            return i;
        }
    }
   printf("Compte introuvable.\n");
    return -1;
}
void supprimer_compte(int index) {
    if (index >= 0 && index < nb_compte) {
        printf("Compte supprime : \n");
        printf("Nom : %s\n", tab_compte[index].nom);
        printf("Prenom : %s\n", tab_compte[index].prenom);
        printf("Numero de compte : %s\n", tab_compte[index].num);
        printf("Mot de passe : %s\n", tab_compte[index].motdepass);
        printf("Solde : %.2f\n", tab_compte[index].solde);
        printf("Adresse : %s\n", tab_compte[index].adress);
        printf("Numero de telephone : %s\n", tab_compte[index].numtlf);

        for (int i = index; i < nb_compte - 1; i++) {
            tab_compte[i] = tab_compte[i+1];
        }
        nb_compte--;
        sauvegarder_comptes();
        printf("Compte supprime avec succes.\n");
    } else {
        printf("Compte introuvable.\n");
    }
}
void modifier_compte(int index) {
    if (index >= 0 && index < nb_compte) {
        printf("Entrez les nouvelles valeurs pour le compte %s %s:\n", tab_compte[index].nom, tab_compte[index].prenom);
        printf("Nom : ");
        scanf("%s", tab_compte[index].nom);
        printf("Prenom : ");
        scanf("%s", tab_compte[index].prenom);
        printf("Numero de compte : ");
        scanf("%s", tab_compte[index].num);
        printf("Mot de passe : ");
        scanf("%s", tab_compte[index].motdepass);
        printf("Solde initial : ");
        scanf("%f", &tab_compte[index].solde);
        printf("Adresse : ");
        scanf("%s", tab_compte[index].adress);
        printf("Numero de telephone : ");
        scanf("%s", tab_compte[index].numtlf);
        sauvegarder_comptes();
        printf("Compte modifie avec succes.\n");
    } else {
        printf("Compte introuvable.\n");
    }
}
void inserer_compte_triee() {
    FILE *fichier = fopen("comptes.txt", "r+");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Lire tous les éléments du fichier dans un tableau en mémoire
    compte tab_comptes[100];
    int nb_comptes = 0;
    compte c;
    while (fscanf(fichier, "%s %s %s %s %s %f %s\n", c.nom, c.prenom, c.num, c.motdepass, &c.solde, c.adress, c.numtlf) != EOF) {
        tab_comptes[nb_comptes] = c;
        nb_comptes++;
    }

    // Trouver l'emplacement approprié pour insérer le nouvel élément
    printf("Nom : ");
    scanf("%s", c.nom);
    printf("Prenom : ");
    scanf("%s", c.prenom);
    for (int i = 0; i < nb_comptes; i++) {
        if (strcmp(tab_comptes[i].nom, c.nom) > 0 || (strcmp(tab_comptes[i].nom, c.nom) == 0 && strcmp(tab_comptes[i].prenom, c.prenom) > 0)) {
            // Insérer le nouvel élément à l'emplacement approprié
            for (int j = nb_comptes; j > i; j--) {
                tab_comptes[j] = tab_comptes[j-1];
            }
            tab_comptes[i] = c;
            nb_comptes++;
            break;
        }
    }

    // Réécrire tout le tableau dans le fichier
    rewind(fichier);
    for (int i = 0; i < nb_comptes; i++) {
        fprintf(fichier, "%s %s %s %s %s %f %s\n", tab_comptes[i].nom, tab_comptes[i].prenom, tab_comptes[i].num, tab_comptes[i].motdepass, &tab_comptes[i].solde, tab_comptes[i].adress, tab_comptes[i].numtlf);
    }

    fclose(fichier);
}

int main() {
    int choix,comsup,commodif;
   
    charger_comptes();

    while (1) {
        printf("1- Creation de compte\n");
        printf("2- Depot\n");
        printf("3- Retrait\n");
        printf("4- Solde\n");
        printf("5- tri par nom :\n");
        printf("6- recherche un compte par numero d compte \n");
        printf("7- supprime un compte par index \n");
        printf("8- modifier un compte par index\n");
        printf("9- Insérer un nouvel élément dans sa position (tri) selon le nom \n");
        printf("911- Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creation_compte();
                break;
            case 22:
                connexion_compte();
                break;
            case 2:
                depot();
                break;
            case 3:
                retrait();
                break;
            case 4:
                solde();
                break;
                case 5:
                tri() ;
                break;
            case 6:         
                reche();             
            break;
            case 7:         
scanf( "%d" ,&comsup );
                supprimer_compte(comsup);
            break;
            case 8:     
            scanf( "%d" ,&commodif);
    
                modifier_compte(commodif);             
            break;
            case 9:         
                inserer_compte_triee();             
            break;
                case 911:
                exit(0);
                break;
            default:
                printf("Choix invalide.\n");
        }
    }

// -------

    return 0;
}