# E-COMMERCE ORDER MANAGEMENT WITH DOUBLY LINKED LISTS

## PROBLEM

### Basic Concepts  
This practical assignment aims to manipulate nested structures in the C language through an e-commerce order management scenario.  
Each order can contain multiple items, and all orders are managed using a **doubly linked list**.

---

### Structure Definitions

```c
typedef struct Article {
    char nom[50];
    float prix_unitaire;
    int quantite;
} Article;

typedef struct Commande {
    int id;
    char date[11]; // DD/MM/YYYY
    Article articles[10];
    int nb_articles;
    struct Commande* precedent;
    struct Commande* suivant;
} Commande;
```

---

## FUNCTIONS TO IMPLEMENT

Implement a program that includes the following functions:

1. `Commande* creer_commande();`  
   Create an order with keyboard input (ID, date, items...).

2. `Commande* creer_commande_donnees(int id, char date[], Article articles[], int nb_articles);`  
   Create an order using predefined parameters.

3. `int longueur_liste(Commande* tete);`  
   Return the total number of orders in the list.

4. `Commande* inserer_position(Commande* tete, Commande* nouvelle, int position);`  
   Insert an order at a specific position (beginning, middle, or end).

5. `Commande* supprimer_position(Commande* tete, int position);`  
   Delete an order at a given position.

6. `Commande* supprimer_toutes_commandes_date(Commande* tete, char date[]);`  
   Delete all orders with a specific date.

7. `void afficher_commandes_direct(Commande* tete);`  
   Display orders in insertion order (from oldest to newest).

8. `void afficher_commandes_inverse(Commande* queue);`  
   Display orders in reverse order (from newest to oldest).

9. `Commande* rechercher_commande_par_id(Commande* tete, int id);`  
   Search for an order by its ID.

10. `Commande* inverser_liste(Commande* tete);`  
    Reverse the order of the doubly linked list.

11. `Commande* fusionner_listes(Commande* l1, Commande* l2);`  
    Merge two doubly linked lists of orders.

12. `Commande* inserer_ordonnee(Commande* tete, Commande* nouvelle);`  
    Insert an order into a list sorted by ascending date.

13. `void supprimer_doublons(Commande* tete);`  
    Remove duplicate orders (same ID and same date).

14. `int main()`  
    Write a main program that uses all the previously defined functions to test the correct functionality of the list.
