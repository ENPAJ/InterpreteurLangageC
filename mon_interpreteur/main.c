#include <stdio.h>
#include <string.h>

#include "variable.h"
#include "interpreter.h"

// Fonction principale, argc est le nombre d'arguments, argv est le tableau des arguments
int main(int argc, char* argv[]) {
    if (argc == 2) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", argv[1]);
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0; // Supprime le saut de ligne
            interpret(line);  // Interprète chaque ligne du fichier
        }

        fclose(file);
    } else {
        char input[256];
        printf("Entrez des commandes (ou 'exit' pour quitter) :\n");

        while (1) {
            printf("> ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = 0;

            if (strcmp(input, "exit") == 0) {
                break;
            }

            interpret(input);  // Interprète chaque commande utilisateur
        }
    }
    free_variables();  // Libère la mémoire des variables avant de quitter
    return 0;
}