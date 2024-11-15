//
// Created by Darkazanli on 27/10/2024.
//

#ifndef VARIABLE_H
#define VARIABLE_H

// Structure pour une variable
typedef struct Variable {
    char* name;
    union {
        int int_value;
        char* str_value; // Valeur pour les chaînes de caractères
    };
    struct Variable* next; // Pointeur vers la prochaine variable dans la liste
    int is_string; // Indique si la variable est de type chaîne
} Variable;

// Ajoute une nouvelle variable
void add_variable(const char* name, int value, const char* str_value, int is_string);

// Trouve une variable par son nom
Variable* find_variable(const char* name);

void free_variables();

#endif //VARIABLE_H
