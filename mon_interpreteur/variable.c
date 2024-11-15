#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "variable.h"

Variable* vars = NULL;  // Pointeur vers la liste des variables

// Fonction pour ajouter une variable
void add_variable(const char* name, int value, const char* str_value, int is_string) {
    Variable* new_var = malloc(sizeof(Variable));
    new_var->name = strdup(name);
    new_var->is_string = is_string;
    if (is_string) {
        new_var->str_value = strdup(str_value);
    } else {
        new_var->int_value = value;
    }
    new_var->next = vars;
    vars = new_var;
}

// Trouve une variable par son nom
Variable* find_variable(const char* name) {
    Variable* current = vars;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Libère la mémoire des variables
void free_variables() {
    Variable* current = vars;
    while (current) {
        Variable* next = current->next;
        free(current->name);
        if (current->is_string) {
            free(current->str_value); // Libère la chaîne si c'est une variable de type chaîne
        }
        free(current);
        current = next; // Passe à la variable suivante
    }
}