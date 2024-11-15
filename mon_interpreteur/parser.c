#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "ast.h"
#include "tools.h"

// Fonction pour analyser une expression complète (addition et soustraction)
ASTNode* parse_expr(int* index) {
    ASTNode* left = parse_term(index);

    while (tokens[*index].type == TOKEN_PLUS || tokens[*index].type == TOKEN_MINUS) {
        TokenType op = tokens[*index].type;
        (*index)++;
        ASTNode* right = parse_term(index);

        ASTNode* parent = create_node(op);
        parent->children.left = left;
        parent->children.right = right;
        left = parent; // Mettre à jour le nœud gauche
    }

    return left;
}

// Fonction pour analyser une expression de multiplication et division
ASTNode* parse_term(int* index) {
    ASTNode* node = NULL;

    // Traitement des différents types de termes
    if (tokens[*index].type == TOKEN_NUMBER) {
        node = create_node(TOKEN_NUMBER);
        node->value = tokens[*index].value;
        (*index)++;
    } else if (tokens[*index].type == TOKEN_STRING) {
        node = create_node(TOKEN_STRING);
        node->str_value = strdup(tokens[*index].str_value); // Duplication de la chaîne
        (*index)++;
    } else if (tokens[*index].type == TOKEN_IDENTIFIER) {
        node = create_node(TOKEN_IDENTIFIER);
        strcpy(node->identifier, tokens[*index].identifier);
        (*index)++;
    } else if (tokens[*index].type == TOKEN_LPAREN) {
        (*index)++;
        node = parse_expr(index);
        if (tokens[*index].type != TOKEN_RPAREN) {
            fprintf(stderr, "Erreur : parenthese fermante manquante\n");
            exit(1);
        }
        (*index)++;
    } else {
        fprintf(stderr, "Erreur : attente d'un nombre ou d'une variable\n");
        exit(1);
    }

    // Boucle pour traiter les opérations de multiplication, division, modulo, et comparaisons
    while (tokens[*index].type == TOKEN_MULTIPLY || tokens[*index].type == TOKEN_DIVIDE ||
           tokens[*index].type == TOKEN_MODULO || tokens[*index].type == TOKEN_LESS ||
           tokens[*index].type == TOKEN_GREATER) {
        TokenType op = tokens[*index].type;
        (*index)++;
        ASTNode* right = parse_term(index);

        // Crée un nœud parent pour l'opération
        ASTNode* parent = create_node(op);
        parent->children.left = node;
        parent->children.right = right;
        node = parent; // Mettre à jour le nœud courant
    }
    return node;
}