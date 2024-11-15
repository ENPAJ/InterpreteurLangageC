//
// Created by Darkazanli on 27/10/2024.
//

#include <string.h>
#include <stdlib.h>

#include "tools.h"

Token tokens[100];  // Tableau des tokens
int token_index = 0;
int num_tokens = 0; // Nombre total de tokens après lexing

// Fonction pour concaténer deux chaînes
char* concat_strings(const char* str1, const char* str2) {
    char* result = malloc(strlen(str1) + strlen(str2) + 1); // Alloue la mémoire
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}