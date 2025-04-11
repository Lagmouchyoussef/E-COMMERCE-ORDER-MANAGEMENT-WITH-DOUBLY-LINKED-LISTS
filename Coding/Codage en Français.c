#include <stdio.h>
#include <stdlib.h>

typedef struct Article {
    char nom[50];
    float prix_unitaire;
    int quantite;
} Article;

typedef struct Commande {
    int id;
    char date[11]; 
    Article articles[10];
    int nb_articles;
    struct Commande* precedent;
    struct Commande* suivant;
} Commande;

// 1. Créer une commande par saisie utilisateur
Commande* creer_commande() {
    Commande* nouvelle = (Commande*)malloc(sizeof(Commande));
    if (!nouvelle) return NULL;

    printf("ID de la commande : ");
    scanf("%d", &nouvelle->id);

    printf("Date (JJ/MM/AAAA) : ");
    scanf("%s", nouvelle->date);

    printf("Nombre d'articles : ");
    scanf("%d", &nouvelle->nb_articles);

    for (int i = 0; i < nouvelle->nb_articles; i++) {
        printf("Nom de l'article %d : ", i + 1);
        scanf("%s", nouvelle->articles[i].nom);

        printf("Prix unitaire : ");
        scanf("%f", &nouvelle->articles[i].prix_unitaire);

        printf("Quantité : ");
        scanf("%d", &nouvelle->articles[i].quantite);
    }

    nouvelle->precedent = NULL;
    nouvelle->suivant = NULL;
    return nouvelle;
}

// 2. Créer une commande avec données prédéfinies
Commande* creer_commande_donnees(int id, char date[], Article articles[], int nb_articles) {
    Commande* nouvelle = (Commande*)malloc(sizeof(Commande));
    if (!nouvelle) return NULL;

    nouvelle->id = id;
    strcpy(nouvelle->date, date);
    nouvelle->nb_articles = nb_articles;

    for (int i = 0; i < nb_articles; i++) {
        nouvelle->articles[i] = articles[i];
    }

    nouvelle->precedent = NULL;
    nouvelle->suivant = NULL;
    return nouvelle;
}

// 3. Calculer la longueur de la liste
int longueur_liste(Commande* tete) {
    int count = 0;
    while (tete) {
        count++;
        tete = tete->suivant;
    }
    return count;
}

// 4. Insérer une commande à une position donnée
Commande* inserer_position(Commande* tete, Commande* nouvelle, int position) {
    if (position == 0 || !tete) {
        nouvelle->suivant = tete;
        if (tete) tete->precedent = nouvelle;
        return nouvelle;
    }

    Commande* courant = tete;
    for (int i = 0; i < position - 1 && courant->suivant; i++) {
        courant = courant->suivant;
    }

    nouvelle->suivant = courant->suivant;
    if (courant->suivant) courant->suivant->precedent = nouvelle;

    courant->suivant = nouvelle;
    nouvelle->precedent = courant;

    return tete;
}

// 5. Supprimer une commande à une position donnée
Commande* supprimer_position(Commande* tete, int position) {
    if (!tete) return NULL;

    if (position == 0) {
        Commande* temp = tete;
        tete = tete->suivant;
        if (tete) tete->precedent = NULL;
        free(temp);
        return tete;
    }

    Commande* courant = tete;
    for (int i = 0; i < position && courant; i++) {
        courant = courant->suivant;
    }

    if (!courant) return tete;

    if (courant->precedent) courant->precedent->suivant = courant->suivant;
    if (courant->suivant) courant->suivant->precedent = courant->precedent;

    free(courant);
    return tete;
}

// 6. Supprimer toutes les commandes d'une date donnée
Commande* supprimer_toutes_commandes_date(Commande* tete, char date[]) {
    Commande* courant = tete;
    while (courant) {
        Commande* suivant = courant->suivant;
        if (strcmp(courant->date, date) == 0) {
            if (courant->precedent) courant->precedent->suivant = courant->suivant;
            else tete = courant->suivant;

            if (courant->suivant) courant->suivant->precedent = courant->precedent;
            free(courant);
        }
        courant = suivant;
    }
    return tete;
}

// 7. Afficher les commandes dans l'ordre direct
void afficher_commandes_direct(Commande* tete) {
    while (tete) {
        printf("Commande ID: %d | Date: %s | Articles: %d\n", tete->id, tete->date, tete->nb_articles);
        tete = tete->suivant;
    }
}

// 8. Afficher les commandes dans l'ordre inverse
void afficher_commandes_inverse(Commande* queue) {
    while (queue && queue->suivant) queue = queue->suivant;
    while (queue) {
        printf("Commande ID: %d | Date: %s | Articles: %d\n", queue->id, queue->date, queue->nb_articles);
        queue = queue->precedent;
    }
}

// 9. Rechercher une commande par ID
Commande* rechercher_commande_par_id(Commande* tete, int id) {
    while (tete) {
        if (tete->id == id) return tete;
        tete = tete->suivant;
    }
    return NULL;
}

// 10. Inverser la liste
Commande* inverser_liste(Commande* tete) {
    Commande* courant = tete;
    Commande* temp = NULL;

    while (courant) {
        temp = courant->precedent;
        courant->precedent = courant->suivant;
        courant->suivant = temp;
        courant = courant->precedent;
    }

    return temp ? temp->precedent : NULL;
}

// 11. Fusionner deux listes
Commande* fusionner_listes(Commande* l1, Commande* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    Commande* courant = l1;
    while (courant->suivant) courant = courant->suivant;

    courant->suivant = l2;
    l2->precedent = courant;

    return l1;
}

// 12. Insérer dans une liste triée par date
Commande* inserer_ordonnee(Commande* tete, Commande* nouvelle) {
    if (!tete || strcmp(nouvelle->date, tete->date) < 0) {
        nouvelle->suivant = tete;
        if (tete) tete->precedent = nouvelle;
        return nouvelle;
    }

    Commande* courant = tete;
    while (courant->suivant && strcmp(courant->suivant->date, nouvelle->date) < 0) {
        courant = courant->suivant;
    }

    nouvelle->suivant = courant->suivant;
    if (courant->suivant) courant->suivant->precedent = nouvelle;
    courant->suivant = nouvelle;
    nouvelle->precedent = courant;

    return tete;
}

// 13. Supprimer les doublons
void supprimer_doublons(Commande* tete) {
    for (Commande* i = tete; i && i->suivant; i = i->suivant) {
        Commande* j = i->suivant;
        while (j) {
            Commande* suivant = j->suivant;
            if (i->id == j->id && strcmp(i->date, j->date) == 0) {
                if (j->precedent) j->precedent->suivant = j->suivant;
                if (j->suivant) j->suivant->precedent = j->precedent;
                free(j);
            }
            j = suivant;
        }
    }
}

// 14. Fonction principale
int main() {
    Commande* liste = NULL;

    Commande* c1 = creer_commande();

    Article articles[] = { {"Souris", 50.0, 1}, {"Clavier", 120.0, 1} };
    Commande* c2 = creer_commande_donnees(2, "05/04/2025", articles, 2);

    liste = inserer_position(liste, c1, 0);
    liste = inserer_position(liste, c2, 1);

    printf("\nCommandes en ordre direct :\n");
    afficher_commandes_direct(liste);

    Commande* recherche = rechercher_commande_par_id(liste, 2);
    if (recherche) printf("\nCommande trouvée : ID = %d\n", recherche->id);

    liste = inverser_liste(liste);
    printf("\nCommandes après inversion :\n");
    afficher_commandes_direct(liste);

    liste = supprimer_position(liste, 0);

    printf("\nCommandes après suppression :\n");
    afficher_commandes_direct(liste);

    return 0;
}
