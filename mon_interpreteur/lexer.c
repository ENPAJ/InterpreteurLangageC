#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "tools.h"

// Lexer : Transforme l'entrée en tokens
void lexer(const char* input) {
    token_index = 0;  // Réinitialise l'index des tokens
    num_tokens = 0;   // Réinitialise le nombre de tokens
    const char* p = input;
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }
        if (isdigit(*p)) {
            Token token;
            token.type = TOKEN_NUMBER;
            token.value = strtol(p, (char**)&p, 10);
            tokens[num_tokens++] = token;
            continue;
        }
        if (*p == '"') { // Détection des chaînes de caractères
            p++;
            Token token;
            token.type = TOKEN_STRING;
            token.str_value = malloc(256); // Allocation pour la chaîne
            char* str_ptr = token.str_value;
            while (*p && *p != '"') {
                *str_ptr++ = *p++;
            }
            *str_ptr = '\0'; // Terminer la chaîne
            if (*p == '"') p++; // Passer le guillemet de fermeture
            tokens[num_tokens++] = token;
            continue;
        }
        if (isalpha(*p)) {
            Token token;
            token.type = TOKEN_IDENTIFIER;
            int len = 0;
            while (isalnum(*p) && len < 31) {
                token.identifier[len++] = *p++;
            }
            token.identifier[len] = '\0';
            if (strcmp(token.identifier, "print") == 0) {
                token.type = TOKEN_PRINT;
            }
            tokens[num_tokens++] = token;
            continue;
        }
        // Traitement des symboles uniques
        switch (*p) {
            case '=':
                tokens[num_tokens++].type = TOKEN_ASSIGN; p++; break;
            case '+':
                tokens[num_tokens++].type = TOKEN_PLUS; p++; break;
            case '-':
                tokens[num_tokens++].type = TOKEN_MINUS; p++; break;
            case '*':
                tokens[num_tokens++].type = TOKEN_MULTIPLY; p++; break;
            case '/':
                tokens[num_tokens++].type = TOKEN_DIVIDE; p++; break;
            case '%':
                tokens[num_tokens++].type = TOKEN_MODULO; p++; break;
            case '<':
                tokens[num_tokens++].type = TOKEN_LESS; p++; break;
            case '>':
                tokens[num_tokens++].type = TOKEN_GREATER; p++; break;
            case '(':
                tokens[num_tokens++].type = TOKEN_LPAREN; p++; break;
            case ')':
                tokens[num_tokens++].type = TOKEN_RPAREN; p++; break;
            case ';':
                tokens[num_tokens++].type = TOKEN_SEMICOLON; p++; break;
            default:
                fprintf(stderr, "Erreur : caractere non reconnu '%c'\n", *p);
                exit(1);
        }
    }
    tokens[num_tokens++].type = TOKEN_EOF;  // Marqueur de fin de fichier
}