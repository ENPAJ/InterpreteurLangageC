//
// Created by Darkazanli on 27/10/2024.
//

#ifndef TOOLS_H
#define TOOLS_H

// Enumération des types de tokens
typedef enum {
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,
    TOKEN_PRINT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MODULO,
    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

// Structure pour représenter un token
typedef struct {
    TokenType type;
    int value;
    char* str_value; // Nouvelle valeur pour les chaînes
    char identifier[32];
} Token;

extern Token tokens[];  // Tableau des tokens
extern int token_index;
extern int num_tokens; // Nombre total de tokens après lexing

// Fonction pour concaténer deux chaînes
char* concat_strings(const char* str1, const char* str2);

#endif //TOOLS_H
