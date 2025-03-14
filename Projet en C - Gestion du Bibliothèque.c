#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUVRAGES 100
#define MAX_ADHERENTS 100
#define MAX_LOCATIONS 100

typedef struct {
    int numero;
    char titre[50];
    int anneeEdition;
    char auteur[50];
    char domaine[50];
    int disponibilite;
} Ouvrage;

typedef struct {
    int numero;
    char nom[50];
    char prenom[50];
    char adresse[100];
    int anneeAdhesion;
} Adherent;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    Adherent adherent;
    Ouvrage ouvrage;
    Date datedajout;
    Date datesupressionPrevue;
} Location;

Ouvrage ouvrages[MAX_OUVRAGES];
int nbOuvrages = 0;

Adherent adherents[MAX_ADHERENTS];
int nbAdherents = 0;

Location locations[MAX_LOCATIONS];
int nbLocations = 0;

void afficherMenuPrincipal();
void gestionOuvrages();
void afficherMenuGestionOuvrages();
void ajoutOuvrage();
void modificationOuvrage();
void suppressionOuvrage();
void rechercheOuvrage();
void rechercheOuvrageParNumero();
void rechercheOuvrageParTitre();
void rechercheOuvrageParAuteur();
void listeOuvrages();
void afficherOuvrage(Ouvrage ouvrage);
void gestionAdherents();
void afficherMenuGestionAdherents();
void ajoutAdherent();
void modificationAdherent();
void suppressionAdherent();
void rechercheAdherent();
void rechercheAdherentParNumero();
void rechercheAdherentParNom();
void rechercheAdherentParPrenom();
void listeAdherents();
void afficherAdherent(Adherent adherent);
void gestionLocations();
void afficherMenuGestionLocations();
void empruntOuvrage();
void prolongementLocation();
void retourOuvrage();
void rechercheLocation();
void rechercheLocationParNumeroOuvrage();
void rechercheLocationParNumeroAdherent();
void rechercheLocationParOperation();
void rechercheLocationParDate();
void listeLocations();
void afficherLocation(Location location);
Date calculerDatesupressionPrevue(Date datedajout);
void viderTamponEntree();
void clearConsole();

int main() {
    int choix;

    do {
        afficherMenuPrincipal();
        printf("\nChoix : ");
        scanf("%d", &choix);
        viderTamponEntree();
        clearConsole();
        switch (choix) {
            case 1:
                gestionOuvrages();
                break;
            case 2:
                gestionAdherents();
                break;
            case 3:
                gestionLocations();
                break;
        }
    } while (choix != 4);

    return 0;
}

void afficherMenuPrincipal() {
    printf("\nMENU PRINCIPAL\n");
    printf("1. Gestion des Ouvrages\n");
    printf("2. Gestion des Adherents\n");
    printf("3. Gestion des Locations\n");
    printf("4. QUITTER\n");
}

void gestionOuvrages() {
    int choix;

    do {
        afficherMenuGestionOuvrages();
        printf("\nChoix : ");
        scanf("%d", &choix);
        viderTamponEntree() ;
        clearConsole();

        switch (choix) {
            case 1:
                ajoutOuvrage();
                break;
            case 2:
                modificationOuvrage();
                break;
            case 3:
                suppressionOuvrage();
                break;
            case 4:
                rechercheOuvrage();
                break;
            case 5:
                listeOuvrages();
                break;
        }
    } while (choix != 6);
}

void afficherMenuGestionOuvrages() {
    printf("\nMENU GESTION DES OUVRAGES\n");
    printf("1. Ajout d'un ouvrage\n");
    printf("2. Modification\n");
    printf("3. Suppression\n");
    printf("4. Recherche\n");
    printf("5. Liste des ouvrages\n");
    printf("6. MENU PRINCIPAL\n");
}

void ajoutOuvrage() {
    Ouvrage ouvrage;

    printf("\nAjout d'un ouvrage\n");

    printf("Numero : ");
    scanf("%d", &ouvrage.numero);
    viderTamponEntree();

    printf("Titre : ");
    fgets(ouvrage.titre, sizeof(ouvrage.titre), stdin);
    ouvrage.titre[strcspn(ouvrage.titre, "\n")] = '\0';

    printf("Annee d'edition : ");
    scanf("%d", &ouvrage.anneeEdition);
    viderTamponEntree();

    printf("Auteur : ");
    fgets(ouvrage.auteur, sizeof(ouvrage.auteur), stdin);
    ouvrage.auteur[strcspn(ouvrage.auteur, "\n")] = '\0';

    printf("Domaine : ");
    fgets(ouvrage.domaine, sizeof(ouvrage.domaine), stdin);
    ouvrage.domaine[strcspn(ouvrage.domaine, "\n")] = '\0';

    ouvrages[nbOuvrages] = ouvrage;
    nbOuvrages++;

    printf("L'ouvrage a ete ajoute avec succes.\n");

}

void modificationOuvrage() {
    Ouvrage ouvrage;
    int numero, i,a;

    printf("\nModification d'un ouvrage\n");
    printf("Numero de l'ouvrage à modifier : ");
    scanf("%d", &numero);

    viderTamponEntree();
    clearConsole();


    for (i = 0; i < nbOuvrages; i++) {
        if (ouvrages[i].numero == numero) {

            printf("Nouveau titre : ");
            fgets(ouvrage.titre, sizeof(ouvrage.titre), stdin);
            ouvrage.titre[strcspn(ouvrage.titre, "\n")] = '\0';

            printf("Nouvelle année d'edition : ");
            scanf("%d", &ouvrage.anneeEdition);
            viderTamponEntree();

            printf("Nouvel auteur : ");
            fgets(ouvrage.auteur, sizeof(ouvrage.auteur), stdin);
            ouvrage.auteur[strcspn(ouvrage.auteur, "\n")] = '\0';

            printf("Nouveau domaine : ");
            fgets(ouvrage.domaine, sizeof(ouvrage.domaine), stdin);
            ouvrage.domaine[strcspn(ouvrage.domaine, "\n")] = '\0';

            ouvrages[i] = ouvrage;

            printf("L'ouvrage a ete modifie avec succes.\n");
            return;
        }
    }

    printf("Aucun ouvrage avec le numero donne n'a ete trouve.\n");
}

void suppressionOuvrage() {
    int numero, i, j;
    char confirmation;

    printf("\nSuppression d'un ouvrage\n");
    printf("Numéro de l'ouvrage a supprimer : ");
    scanf("%d", &numero);
    viderTamponEntree();
    clearConsole();

    for (i = 0; i < nbOuvrages; i++) {
        if (ouvrages[i].numero == numero) {
            printf("Confirmez-vous la suppression de l'ouvrage (O/N) ? ");
            scanf("%c", &confirmation);
            viderTamponEntree();

            if (confirmation == 'O' || confirmation == 'o') {
                for (j = i; j < nbOuvrages - 1; j++) {
                    ouvrages[j] = ouvrages[j + 1];
                }
                nbOuvrages--;
                printf("L'ouvrage a ete supprime avec succes.\n");
            } else {
                printf("Suppression annulee.\n");
            }

            return;
        }
    }

    printf("Aucun ouvrage avec le numero donne n'a ete trouve.\n");
}

void rechercheOuvrage() {
    int choix;

    printf("\nRecherche d'un ouvrage\n");
    printf("1. Par numéro\n");
    printf("2. Par titre\n");
    printf("3. Par auteur\n");
    printf("4. Retour\n");

    printf("Choix : ");
    scanf("%d", &choix);
    viderTamponEntree();
    clearConsole();

    switch (choix) {
        case 1:
            rechercheOuvrageParNumero();
            break;
        case 2:
            rechercheOuvrageParTitre();
            break;
        case 3:
            rechercheOuvrageParAuteur();
            break;
        case 4:
            return;
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
            rechercheOuvrage();
    }
}

void rechercheOuvrageParNumero() {
    int numero, i, trouve = 0;

    printf("\nRecherche d'ouvrage par numero\n");
    printf("Numero de l'ouvrage : ");
    scanf("%d", &numero);
    viderTamponEntree();
    clearConsole();

    for (i = 0; i < nbOuvrages; i++) {
        if (ouvrages[i].numero == numero) {
            afficherOuvrage(ouvrages[i]);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Aucun ouvrage avec le numero donne n'a ete trouve.\n");
    }
}

void rechercheOuvrageParTitre() {
    char titre[50];
    int i, trouve = 0;

    printf("\nRecherche d'ouvrage par titre\n");
    printf("Titre de l'ouvrage : ");
    fgets(titre, sizeof(titre), stdin);
    titre[strcspn(titre, "\n")] = '\0';
    clearConsole();


    for (i = 0; i < nbOuvrages; i++) {
        if (strcmp(ouvrages[i].titre, titre) == 0) {
            afficherOuvrage(ouvrages[i]);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun ouvrage avec le titre donne n'a ete trouve.\n");
    }
}

void rechercheOuvrageParAuteur() {
    char auteur[50];
    int i, trouve = 0;

    printf("\nRecherche d'ouvrage par auteur\n");
    printf("Nom de l'auteur : ");
    fgets(auteur, sizeof(auteur), stdin);
    auteur[strcspn(auteur, "\n")] = '\0';
    clearConsole();

    for (i = 0; i < nbOuvrages; i++) {
        if (strcmp(ouvrages[i].auteur, auteur) == 0) {
            afficherOuvrage(ouvrages[i]);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun ouvrage avec l'auteur donne n'a ete trouve.\n");
    }
}

void listeOuvrages() {
    int i;

    printf("\nListe des ouvrages\n");

    if (nbOuvrages == 0) {
        printf("Aucun ouvrage enregistre.\n");

        return;

    }

    for (i = 0; i < nbOuvrages; i++) {
        afficherOuvrage(ouvrages[i]);
    }
}

void gestionAdherents() {
    int choix;

    do {
        afficherMenuGestionAdherents();
        printf("\nChoix : ");
        scanf("%d", &choix);
        viderTamponEntree();
        clearConsole();

        switch (choix) {
            case 1:
                ajoutAdherent();
                break;
            case 2:
                modificationAdherent();
                break;
            case 3:
                suppressionAdherent();
                break;
            case 4:
                rechercheAdherent();
                break;
            case 5:
                listeAdherents();
                break;
            case 6:
                return;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 6);
}

void afficherMenuGestionAdherents() {
    printf("\nMENU GESTION DES ADHERENTS\n");
    printf("1. Ajout d'un adhérent\n");
    printf("2. Modification\n");
    printf("3. Suppression\n");
    printf("4. Recherche\n");
    printf("5. Liste des adhérents\n");
    printf("6. MENU PRINCIPAL\n");

}

void ajoutAdherent() {
    Adherent adherent;

    printf("\nAjout d'un adherent\n");

    printf("Numero : ");
    scanf("%d", &adherent.numero);
    viderTamponEntree();

    printf("Nom : ");
    fgets(adherent.nom, sizeof(adherent.nom), stdin);
    adherent.nom[strcspn(adherent.nom, "\n")] = '\0';

    printf("Prenom : ");
    fgets(adherent.prenom, sizeof(adherent.prenom), stdin);
    adherent.prenom[strcspn(adherent.prenom, "\n")] = '\0';

    printf("Adresse : ");
    fgets(adherent.adresse, sizeof(adherent.adresse), stdin);
    adherent.adresse[strcspn(adherent.adresse, "\n")] = '\0';

    printf("Annee d'adhesion : ");
    scanf("%d", &adherent.anneeAdhesion);
    viderTamponEntree();

    adherents[nbAdherents] = adherent;
    nbAdherents++;

    printf("L'adherent a ete ajoute avec succes.\n");
}

void modificationAdherent() {
    Adherent adherent;
    int numero, i;

    printf("\nModification d'un adhérent\n");
    printf("Numero de l'adherent à modifier : ");
    scanf("%d", &numero);
    viderTamponEntree();

    for (i = 0; i < nbAdherents; i++) {
        if (adherents[i].numero == numero) {
            printf("Nouveau nom : ");
            fgets(adherent.nom, sizeof(adherent.nom), stdin);
            adherent.nom[strcspn(adherent.nom, "\n")] = '\0';

            printf("Nouveau prenom : ");
            fgets(adherent.prenom, sizeof(adherent.prenom), stdin);
            adherent.prenom[strcspn(adherent.prenom, "\n")] = '\0';

            printf("Nouvelle adresse : ");
            fgets(adherent.adresse, sizeof(adherent.adresse), stdin);
            adherent.adresse[strcspn(adherent.adresse, "\n")] = '\0';

            printf("Nouvelle annee d'adhesion : ");
            scanf("%d", &adherent.anneeAdhesion);
            viderTamponEntree();

            adherents[i] = adherent;

            printf("L'adherent a ete modifie avec succes.\n");
            return;
        }
    }

    printf("Aucun adherent avec le numero donne n'a ete trouve.\n");
}

void suppressionAdherent() {
    int numero, i, j;
    char confirmation;

    printf("\nSuppression d'un adherent\n");
    printf("Numero de l'adherent a supprimer : ");
    scanf("%d", &numero);
    viderTamponEntree();

    for (i = 0; i < nbAdherents; i++) {
        if (adherents[i].numero == numero) {
            printf("Confirmez-vous la suppression de l'adherent (O/N) ? ");
            scanf("%c", &confirmation);
            viderTamponEntree();

            if (confirmation == 'O' || confirmation == 'o') {
                for (j = i; j < nbAdherents - 1; j++) {
                    adherents[j] = adherents[j + 1];
                }
                nbAdherents--;
                printf("L'adherent ete supprime avec succes.\n");
            } else {
                printf("Suppression annulee.\n");
            }

            return;
        }
    }

    printf("Aucun adherent avec le numero donne n'a ete trouve.\n");
}

void rechercheAdherent() {
    int choix;

    printf("\nRecherche d'un adherent\n");
    printf("1. Par numero\n");
    printf("2. Par nom\n");
    printf("3. Par prenom\n");
    printf("4. Retour\n");

    printf("Choix : ");
    scanf("%d", &choix);
    viderTamponEntree();

    switch (choix) {
        case 1:
            rechercheAdherentParNumero();
            break;
        case 2:
            rechercheAdherentParNom();
            break;
        case 3:
            rechercheAdherentParPrenom();
            break;
        case 4:
            return;
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
            rechercheAdherent();
    }
}

void rechercheAdherentParNumero() {
    int numero, i, trouve = 0;

    printf("\nRecherche d'adherent par numero\n");
    printf("Numero de l'adherent : ");
    scanf("%d", &numero);
    viderTamponEntree();

    for (i = 0; i < nbAdherents; i++) {
        if (adherents[i].numero == numero) {
            afficherAdherent(adherents[i]);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Aucun adherent avec le numero donne n'a ete trouve.\n");
    }
}

void rechercheAdherentParNom() {
    char nom[50];
    int i, trouve = 0;

    printf("\nRecherche d'adherent par nom\n");
    printf("Nom de l'adherent : ");
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = '\0';

    for (i = 0; i < nbAdherents; i++) {
        if (strcmp(adherents[i].nom, nom) == 0) {
            afficherAdherent(adherents[i]);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun adhérent avec le nom donne n'a ete trouve.\n");
    }
}

void rechercheAdherentParPrenom() {
    char prenom[50];
    int i, trouve = 0;

    printf("\nRecherche d'adherent par prenom\n");
    printf("Prenom de l'adherent : ");
    fgets(prenom, sizeof(prenom), stdin);
    prenom[strcspn(prenom, "\n")] = '\0';

    for (i = 0; i < nbAdherents; i++) {
        if (strcmp(adherents[i].prenom, prenom) == 0) {
            afficherAdherent(adherents[i]);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun adherent avec le prenom donne n'a ete trouve.\n");
    }
}

void listeAdherents() {
    int i;

    printf("\nListe des adherents\n");

    if (nbAdherents == 0) {
        printf("Aucun adherent enregistre.\n");
        return;
    }

    for (i = 0; i < nbAdherents; i++) {
        afficherAdherent(adherents[i]);
    }
}

void afficherAdherent(Adherent adherent) {
    printf("\nNumero : %d\n", adherent.numero);
    printf("Nom : %s\n", adherent.nom);
    printf("Prenom : %s\n", adherent.prenom);
    printf("Adresse : %s\n", adherent.adresse);
    printf("Annee d'adhesion : %d\n", adherent.anneeAdhesion);
}

void gestionLocations() {
    int choix;

    do {
        afficherMenuGestionLocations();
        printf("\nChoix : ");
        scanf("%d", &choix);
        viderTamponEntree();

        switch (choix) {
            case 1:
                empruntOuvrage();
                break;
            case 2:
                prolongementLocation();
                break;
            case 3:
                retourOuvrage();
                break;
            case 4:
                rechercheLocation();
                break;
            case 5:
                listeLocations();
                break;
            case 6:
                return;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 5);
}

void afficherMenuGestionLocations() {
    printf("\nMENU GESTION DES LOCATIONS\n");
    printf("1. Emprunt d'un ouvrage\n");
    printf("2. Prolongement\n");
    printf("3. Retour d'un ouvrage\n");
    printf("4. Recherche\n");
    printf("5. Liste des locations\n");
    printf("6. MENU PRINCIPAL\n");
}

void prolongementLocation() {
    int numeroOuvrage, numeroAdherent, i;

    printf("\nProlongement d'une location\n");
    printf("Numero de l'ouvrage : ");
    scanf("%d", &numeroOuvrage);
    viderTamponEntree();

    printf("Numero de l'adherent : ");
    scanf("%d", &numeroAdherent);
    viderTamponEntree();

    for (i = 0; i < nbLocations; i++) {
        if (locations[i].ouvrage.numero == numeroOuvrage && locations[i].adherent.numero == numeroAdherent) {
            // Vérifier si la location est encore active
            if (locations[i].datesupressionPrevue.annee == 0) {
                // Calculer la nouvelle date de retour prévue
                locations[i].datesupressionPrevue = calculerDatesupressionPrevue(locations[i].datedajout);
                printf("La date de retour prevue a ete prolongee avec succes.\n");
            } else {
                printf("La location est deja terminee. Aucun prolongement n'est possible.\n");
            }
            return;
        }
    }

    printf("Aucune location correspondante n'a ete trouvee.\n");
}

void empruntOuvrage() {
    Location location;
    int numeroOuvrage, numeroAdherent, i;

    printf("\nEmprunt d'un ouvrage\n");

    printf("Numero de l'ouvrage : ");
    scanf("%d", &numeroOuvrage);
    viderTamponEntree();

    for (i = 0; i < nbOuvrages; i++) {
        if (ouvrages[i].numero == numeroOuvrage) {
            if (ouvrages[i].disponibilite == 0) {
                printf("L'ouvrage demande n'est pas disponible pour le moment.\n");
                return;
            }

            location.ouvrage = ouvrages[i];
            break;
        }
    }

    if (i == nbOuvrages) {
        printf("Aucun ouvrage avec le numero donne n'a ete trouve.\n");
        return;
    }

    printf("Numero de l'adherent : ");
    scanf("%d", &numeroAdherent);
    viderTamponEntree();

    for (i = 0; i < nbAdherents; i++) {
        if (adherents[i].numero == numeroAdherent) {
            location.adherent = adherents[i];
            break;
        }
    }

    if (i == nbAdherents) {
        printf("Aucun adherent avec le numero donne n'a ete trouve.\n");
        return;
    }

    printf("Date d'emprunt (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &location.datedajout.jour, &location.datedajout.mois, &location.datedajout.annee);
    viderTamponEntree();

    // Calcul de la date de retour prévue
    location.datesupressionPrevue = calculerDatesupressionPrevue(location.datedajout);

    // Mise à jour de la disponibilité de l'ouvrage
    ouvrages[i].disponibilite = 0;

    locations[nbLocations] = location;
    nbLocations++;

    printf("L'ouvrage a ete emprunte avec succes.\n");
}

Date calculerDatesupressionPrevue(Date datedajout) {
    Date datesupressionPrevue;

    // Ajouter 15 jours à la date d'emprunt
    datesupressionPrevue.jour = datedajout.jour + 15;
    datesupressionPrevue.mois = datedajout.mois;
    datesupressionPrevue.annee = datedajout.annee;

    // Vérifier si le mois dépasse 30 jours
    if (datesupressionPrevue.jour > 30) {
        datesupressionPrevue.jour -= 30;
        datesupressionPrevue.mois++;
    }

    // Vérifier si l'année dépasse 12 mois
    if (datesupressionPrevue.mois > 12) {
        datesupressionPrevue.mois -= 12;
        datesupressionPrevue.annee++;
    }

    return datesupressionPrevue;
}

void retourOuvrage() {
    int numeroOuvrage, i, j;

    printf("\nRetour d'un ouvrage\n");

    printf("Numero de l'ouvrage : ");
    scanf("%d", &numeroOuvrage);
    viderTamponEntree();

    for (i = 0; i < nbLocations; i++) {
        if (locations[i].ouvrage.numero == numeroOuvrage) {
            // Mise à jour de la disponibilité de l'ouvrage
            for (j = 0; j < nbOuvrages; j++) {
                if (ouvrages[j].numero == numeroOuvrage) {
                    ouvrages[j].disponibilite = 1;
                    break;
                }
            }

            // Suppression de la location
            for (; i < nbLocations - 1; i++) {
                locations[i] = locations[i + 1];
            }
            nbLocations--;

            printf("L'ouvrage a ete retourne avec succes.\n");
            return;
        }
    }

    printf("Aucune location avec l'ouvrage donne n'a ete trouvee.\n");
}

void rechercheLocation() {
    int choix;

    printf("\nRecherche d'une location\n");
    printf("1. Par numero d'ouvrage\n");
    printf("2. Par numero d'adherent\n");
    printf("3. Retour\n");

    printf("Choix : ");
    scanf("%d", &choix);
    viderTamponEntree();

    switch (choix) {
        case 1:
            rechercheLocationParNumeroOuvrage();
            break;
        case 2:
            rechercheLocationParNumeroAdherent();
            break;
        case 3:
            return;
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
            rechercheLocation();
    }
}

void rechercheLocationParNumeroOuvrage() {
    int numeroOuvrage, i, trouve = 0;

    printf("\nRecherche de location par numero d'ouvrage\n");
    printf("Numero de l'ouvrage : ");
    scanf("%d", &numeroOuvrage);
    viderTamponEntree();

    for (i = 0; i < nbLocations; i++) {
        if (locations[i].ouvrage.numero == numeroOuvrage) {
            afficherLocation(locations[i]);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucune location avec l'ouvrage donne n'a ete trouvee.\n");
    }
}

void rechercheLocationParNumeroAdherent() {
    int numeroAdherent, i, trouve = 0;

    printf("\nRecherche de location par numero d'adherent\n");
    printf("Numero de l'adherent : ");
    scanf("%d", &numeroAdherent);
    viderTamponEntree();

    for (i = 0; i < nbLocations; i++) {
        if (locations[i].adherent.numero == numeroAdherent) {
            afficherLocation(locations[i]);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucune location avec l'adherent donne n'a ete trouvee.\n");
    }
}

void listeLocations() {
    int i;

    printf("\nListe des locations\n");

    if (nbLocations == 0) {
        printf("Aucune location enregistree.\n");
        return;
    }

    for (i = 0; i < nbLocations; i++) {
        afficherLocation(locations[i]);
    }
}

void afficherLocation(Location location) {
    printf("\nOuvrage emprunte :\n");
    afficherOuvrage(location.ouvrage);

    printf("Adherent emprunteur :\n");
    afficherAdherent(location.adherent);

    printf("Date d'emprunt : %d/%d/%d\n", location.datedajout.jour, location.datedajout.mois, location.datedajout.annee);
    printf("Date de retour prevue : %d/%d/%d\n", location.datesupressionPrevue.jour, location.datesupressionPrevue.mois, location.datesupressionPrevue.annee);
}

void afficherOuvrage(Ouvrage ouvrage) {
    printf("Numero : %d\n", ouvrage.numero);
    printf("Titre : %s\n", ouvrage.titre);
    printf("Auteur : %s\n", ouvrage.auteur);
    printf("Disponibilite : %s\n", ouvrage.disponibilite ? "Disponible" : "Non disponible");
    printf("Domaine : %s\n", ouvrage.domaine);
    printf("Anneeedition : %d\n", ouvrage.anneeEdition);

}

void viderTamponEntree() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearConsole(){
    system("cls");
}