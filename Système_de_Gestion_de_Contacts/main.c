#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CONTACTS 100

// Color codes
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

struct contact {
    char name[100];
    char numero[100];
    char email[100];
    int id;
};

// ==== Prototypes ====
void ajouter_contact(struct contact contacts[], int *nbContact);
void afficher_contacts(struct contact contacts[], int nbContact);
int rechercher_contact(struct contact contacts[], int nbContact, int id, char *nom);
void modifier_contact(struct contact contacts[], int nbContact);
void supprimer_contact(struct contact contacts[], int *nbContact);
int generate_user_id(struct contact contacts[], int nbContact);
int id_exists(struct contact contacts[], int nbContact, int id);
void pause_and_clear();

// ==== MAIN ====
int main() {
    struct contact contacts[MAX_CONTACTS];
    int nbContacts = 0;
    int choix;

    srand(time(NULL)); 

    do {
        printf("\n%s===== Système de Gestion de Contacts =====%s\n", CYAN, RESET); 
        printf("%s1.%s Ajouter un contact\n", GREEN, RESET); 
        printf("%s2.%s Modifier un contact\n", YELLOW, RESET); 
        printf("%s3.%s Supprimer un contact\n", RED, RESET); 
        printf("%s4.%s Afficher tous les contacts\n", BLUE, RESET); 
        printf("%s5.%s Rechercher un contact\n", MAGENTA, RESET); 
        printf("%s6.%s Quitter\n", CYAN, RESET); 
        printf("👉 Choisissez une option : ");
        scanf("%d", &choix);
        getchar(); // consume newline left by scanf

        switch (choix) {
            case 1: ajouter_contact(contacts, &nbContacts); 
            pause_and_clear(); 
            break;
            case 2: modifier_contact(contacts, nbContacts); 
            pause_and_clear(); 
            break;
            case 3: supprimer_contact(contacts, &nbContacts); 
            pause_and_clear(); 
            break;
            case 4: afficher_contacts(contacts, nbContacts);
            pause_and_clear(); 
            break;
            case 5: {
                int id;
                char nom[100];
                printf("🔎 Entrer l'ID : ");
                scanf("%d", &id);
                getchar();
                printf("🔎 Entrer le nom complet : ");
                scanf(" %[^\n]", nom);

                int pos = rechercher_contact(contacts, nbContacts, id, nom);
                if (pos != -1) {
                    printf("%s✅ Contact trouvé :%s\n", GREEN, RESET);
                    printf("Nom     : %s\n", contacts[pos].name);
                    printf("Numéro  : %s\n", contacts[pos].numero);
                    printf("Email   : %s\n", contacts[pos].email);
                    printf("ID      : %d\n", contacts[pos].id);
                } else {
                    printf("%s❌ Contact introuvable.%s\n", RED, RESET);
                }
                pause_and_clear(); 
                break;
            }
            case 6: printf("%s👋 Au revoir !%s\n", CYAN, RESET); 
            break;
            default: printf("%s⚠️ Option invalide.%s\n", RED, RESET);
            pause_and_clear(); 
        }
    } while (choix != 6);

    return 0;
}

// ==== Ajouter Contact ====
void ajouter_contact(struct contact contacts[], int *nbContact) {
    if (*nbContact >= MAX_CONTACTS) {
        printf("%s⚠️ La liste est pleine !%s\n", RED, RESET);
        return;
    }

    printf("📝 Nom complet : ");
    scanf(" %[^\n]", contacts[*nbContact].name);
    printf("📞 Numéro : ");
    scanf(" %[^\n]", contacts[*nbContact].numero);
    printf("📧 Email : ");
    scanf(" %[^\n]", contacts[*nbContact].email);

    // generate unique ID
    contacts[*nbContact].id = generate_user_id(contacts, *nbContact);

    printf("%s✅ Contact ajouté avec succès ! ID = %d%s\n", GREEN, contacts[*nbContact].id, RESET);
    (*nbContact)++;
    getchar();
}

// ==== Afficher Contacts ====
void afficher_contacts(struct contact contacts[], int nbContact) {
    if (nbContact == 0) {
        printf("%s⚠️ Aucun contact.%s\n", RED, RESET);
        return;
    }

    for (int i = 0; i < nbContact; i++) {
        printf("\n%s---- Contact %d ----%s\n", CYAN, i + 1, RESET);
        printf("👤 Nom     : %s\n", contacts[i].name);
        printf("📞 Numéro  : %s\n", contacts[i].numero);
        printf("📧 Email   : %s\n", contacts[i].email);
        printf("🆔 ID      : %d\n", contacts[i].id);
    }
}

// ==== Rechercher Contact ====
int rechercher_contact(struct contact contacts[], int nbContact, int id, char *nom) {
    for (int i = 0; i < nbContact; i++) {
        if (contacts[i].id == id && strcmp(contacts[i].name, nom) == 0) {
            return i; // found
        }
    }
    return -1; // not found
}

// ==== Modifier Contact ====
void modifier_contact(struct contact contacts[], int nbContact) {
    int id;
    char nom[100];
    printf("✏️ Entrer l'ID du contact à modifier: ");
    scanf("%d", &id);
    getchar();
    printf("✏️ Entrer le nom complet du contact à modifier: ");
    scanf(" %[^\n]", nom);

    int pos = rechercher_contact(contacts, nbContact, id, nom);
    if (pos == -1) {
        printf("%s❌ Contact introuvable.%s\n", RED, RESET);
        return;
    }

    printf("Nouveau nom complet : ");
    scanf(" %[^\n]", contacts[pos].name);
    printf("Nouveau numéro : ");
    scanf(" %[^\n]", contacts[pos].numero);
    printf("Nouvel email : ");
    scanf(" %[^\n]", contacts[pos].email);

    printf("%s✅ Contact modifié avec succès !%s\n", GREEN, RESET);
}

// ==== Supprimer Contact ====
void supprimer_contact(struct contact contacts[], int *nbContact) {
    int id;
    char nom[100];
    printf("🗑️ Entrer l'ID du contact à supprimer: ");
    scanf("%d", &id);
    getchar();
    printf("🗑️ Entrer le nom complet du contact à supprimer: ");
    scanf(" %[^\n]", nom);

    int pos = rechercher_contact(contacts, *nbContact, id, nom);
    if (pos == -1) {
        printf("%s❌ Contact introuvable.%s\n", RED, RESET);
        return;
    }

    for (int i = pos; i < *nbContact - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    (*nbContact)--;

    printf("%s✅ Contact supprimé avec succès !%s\n", GREEN, RESET);
}

// ==== Génération ID Unique ====
int generate_user_id(struct contact contacts[], int nbContact) {
    int id;
    do {
        id = rand() % 900000000 + 100000000; 
    } while (id_exists(contacts, nbContact, id));
    return id;
}

// ==== Vérifier si ID existe ====
int id_exists(struct contact contacts[], int nbContact, int id) {
    for (int i = 0; i < nbContact; i++) {
        if (contacts[i].id == id) return 1;
    }
    return 0;
}

// Function to pause until Enter is pressed
void pause_and_clear() {
    printf("\n\033[33mAppuyez sur Entrée pour continuer...\033[0m");
    getchar();
    system("clear || cls");
}