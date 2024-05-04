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
} cart;

cart tab_cart[100];
int nb_cart = 0;

void sauvegarder_carts() {
    FILE *f;
    int i;

    f = fopen("carts.txt", "w");

    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    for (i = 0; i < nb_cart; i++) {
        fprintf(f, "%s %s %s %.2f %s %s %s\n" ,tab_cart[i].nom, tab_cart[i].prenom, tab_cart[i].num, tab_cart[i].motdepass,&tab_cart[i].solde ,tab_cart[i].adress,tab_cart[i].numtlf);
    }

    fclose(f);
}

void charger_carts() {
    FILE *f;
    char ligne[50];
    int i = 0;

    f = fopen("carts.txt", "r");


    if (f == NULL) {
        printf("Aucune cart enregistre.\n");
        return;
    }

    while (fgets(ligne, 50, f) != NULL) {
        sscanf(ligne, "%s %s %s %s %s %s%s",tab_cart[i].nom, tab_cart[i].prenom, tab_cart[i].num, tab_cart[i].motdepass,&tab_cart[i].solde ,tab_cart[i].adress,tab_cart[i].numtlf);
        i++;
    }

    nb_cart = i;

    fclose(f);
}

int creation_cart() {
    if (nb_cart >= 100) {
        printf("Nombre maximum de carts atteint.\n");
        return 0;
    }
 printf("Nom : ");
    scanf("%s", tab_cart[nb_cart].nom);

    printf("Prenom : ");
    scanf("%s", tab_cart[nb_cart].prenom);

    printf("Numero de cart : ");
    scanf("%s", tab_cart[nb_cart].num);
   printf("mot de pass : ");
    scanf("%s", tab_cart[nb_cart].motdepass);
   
    printf("Solde initial : ");
    scanf("%f", &tab_cart[nb_cart].solde);
 
     printf("adress : ");
    scanf("%s", tab_cart[nb_cart].adress);
     printf("numero de tlephone : ");
    scanf("%s", tab_cart[nb_cart].numtlf);

    nb_cart++;

    sauvegarder_carts();

    printf("cart cree avec succes.\n");

    return 1;
}

int connexion_cart() {
    char num[10];
    char mot_de_passe[20];
    int i;

    printf("Numero de cart : ");
    scanf("%s", num);

    printf("Mot de passe : ");
    scanf("%s", mot_de_passe);

    for (i = 0; i < nb_cart; i++) {
        if (strcmp(num, tab_cart[i].num) == 0) {
            return i;
        }
    }
    

    printf("cart introuvable.\n");
    return -1;
}

void depot() {
    float montant;
    int i;

    printf("Montant du depot : ");
    scanf("%f", &montant);

      i = connexion_cart();

    if (i != -1) {
        tab_cart[i].solde += montant;
        sauvegarder_carts();
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
    FILE *file = fopen("carts.txt", "r");
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
    file = fopen("carts.txt", "w");
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

    i = connexion_cart();

    if (i != -1) {
        if (tab_cart[i].solde >= montant) {
            tab_cart[i].solde -= montant;
            sauvegarder_carts();
            printf("Retrait effectue avec succes.\n");
        } else {
            printf("Solde insuffisant.\n");
        }
    }
}

void solde() {
    int i;

    i = connexion_cart();

    if (i != -1) {
        printf("%s %s\n", tab_cart[i].nom, tab_cart[i].prenom);
        printf("Solde : %.2f\n", tab_cart[i].solde);
    }
}
int reche () {
    char num[10];
    int i;

    printf("Numero de cart : ");
    scanf("%s", num);

    for (i = 0; i < nb_cart; i++) {
       if (strcmp(num, tab_cart[i].num) == 0) {
            printf("cart trouve : \n");
            printf("Nom : %s\n", tab_cart[i].nom);
            printf("Prenom : %s\n", tab_cart[i].prenom);
            printf("Numero de cart : %s\n", tab_cart[i].num);
            printf("Mot de passe : %s\n", tab_cart[i].motdepass);
            printf("Solde : %.2f\n", tab_cart[i].solde);
            printf("Adresse : %s\n", tab_cart[i].adress);
            printf("Numero de telephone : %s\n", tab_cart[i].numtlf);
            return i;
        }
    }
   printf("cart introuvable.\n");
    return -1;
}
void supprimer_cart(int index) {
    if (index >= 0 && index < nb_cart) {
        printf("cart supprime : \n");
        printf("Nom : %s\n", tab_cart[index].nom);
        printf("Prenom : %s\n", tab_cart[index].prenom);
        printf("Numero de cart : %s\n", tab_cart[index].num);
        printf("Mot de passe : %s\n", tab_cart[index].motdepass);
        printf("Solde : %.2f\n", tab_cart[index].solde);
        printf("Adresse : %s\n", tab_cart[index].adress);
        printf("Numero de telephone : %s\n", tab_cart[index].numtlf);

        for (int i = index; i < nb_cart - 1; i++) {
            tab_cart[i] = tab_cart[i+1];
        }
        nb_cart--;
        sauvegarder_carts();
        printf("cart supprime avec succes.\n");
    } else {
        printf("cart introuvable.\n");
    }
}
void modifier_cart(int index) {
    if (index >= 0 && index < nb_cart) {
        printf("Entrez les nouvelles valeurs pour le cart %s %s:\n", tab_cart[index].nom, tab_cart[index].prenom);
        printf("Nom : ");
        scanf("%s", tab_cart[index].nom);
        printf("Prenom : ");
        scanf("%s", tab_cart[index].prenom);
        printf("Numero de cart : ");
        scanf("%s", tab_cart[index].num);
        printf("Mot de passe : ");
        scanf("%s", tab_cart[index].motdepass);
        printf("Solde initial : ");
        scanf("%f", &tab_cart[index].solde);
        printf("Adresse : ");
        scanf("%s", tab_cart[index].adress);
        printf("Numero de telephone : ");
        scanf("%s", tab_cart[index].numtlf);
        sauvegarder_carts();
        printf("cart modifie avec succes.\n");
    } else {
        printf("cart introuvable.\n");
    }
}
void inserer_cart_triee() {
    FILE *fichier = fopen("carts.txt", "r+");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    // Lire tous les éléments du fichier dans un tableau en mémoire
    cart tab_carts[100];
    int nb_carts = 0;
    cart c;
    while (fscanf(fichier, "%s %s %s %s %s %f %s\n", c.nom, c.prenom, c.num, c.motdepass, &c.solde, c.adress, c.numtlf) != EOF) {
        tab_carts[nb_carts] = c;
        nb_carts++;
    }

    // Trouver l'emplacement approprié pour insérer le nouvel élément
    printf("Nom : ");
    scanf("%s", c.nom);
    printf("Prenom : ");
    scanf("%s", c.prenom);
    for (int i = 0; i < nb_carts; i++) {
        if (strcmp(tab_carts[i].nom, c.nom) > 0 || (strcmp(tab_carts[i].nom, c.nom) == 0 && strcmp(tab_carts[i].prenom, c.prenom) > 0)) {
            // Insérer le nouvel élément à l'emplacement approprié
            for (int j = nb_carts; j > i; j--) {
                tab_carts[j] = tab_carts[j-1];
            }
            tab_carts[i] = c;
            nb_carts++;
            break;
        }
    }

    // Réécrire tout le tableau dans le fichier
    rewind(fichier);
    for (int i = 0; i < nb_carts; i++) {
        fprintf(fichier, "%s %s %s %s %s %f %s\n", tab_carts[i].nom, tab_carts[i].prenom, tab_carts[i].num, tab_carts[i].motdepass, &tab_carts[i].solde, tab_carts[i].adress, tab_carts[i].numtlf);
    }

    fclose(fichier);
}

int main() {
    int choix,comsup,commodif;
   
    charger_carts();

    while (1) {
        printf("1- Creation de cart\n");
        printf("2- Depot\n");
        printf("3- Retrait\n");
        printf("4- Solde\n");
        printf("5- tri par nom :\n");
        printf("6- recherche une cart par numero d cart \n");
        printf("7- supprime une cart par index \n");
        printf("8- modifier une cart par index\n");
        printf("9- Insérer un nouvel élément dans sa position (tri) selon le nom \n");
        printf("911- Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creation_cart();
                break;
            case 22:
                connexion_cart();
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
                supprimer_cart(comsup);
            break;
            case 8:     
            scanf( "%d" ,&commodif);
    
                modifier_cart(commodif);             
            break;
            case 9:         
                inserer_cart_triee();             
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
