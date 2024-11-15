#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "tools.h"

// Fonction pour créer un nœud de l'AST
ASTNode* create_node(TokenType type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    return node;
}

// Fonction pour afficher l'AST au format Mermaid
void print_ast_mermaid(ASTNode* node, FILE* out, int* count) {
    if (!node) return;

    int current_index = (*count)++; // Obtenir l'index courant
    char current_label = 'A' + current_index; // Convertir l'index en lettre

    // Affiche le nœud selon son type
    switch (node->type) {
        case TOKEN_NUMBER:
            fprintf(out, "    %c[\"%d\"]\n", current_label, node->value);
            break;
        case TOKEN_STRING:
            fprintf(out, "    %c[\"%s\"]\n", current_label, node->str_value);
            break;
        case TOKEN_IDENTIFIER:
            fprintf(out, "    %c[\"%s\"]\n", current_label, node->identifier);
            break;
        case TOKEN_ASSIGN:
            fprintf(out, "    %c[\"=\"]\n", current_label);
            break;
        case TOKEN_PLUS:
            fprintf(out, "    %c[\"+\"]\n", current_label);
            break;
        case TOKEN_MINUS:
            fprintf(out, "    %c[\"-\"]\n", current_label);
            break;
        case TOKEN_MULTIPLY:
            fprintf(out, "    %c[\"*\"]\n", current_label);
            break;
        case TOKEN_DIVIDE:
            fprintf(out, "    %c[\"/\"]\n", current_label);
            break;
        case TOKEN_MODULO:
            fprintf(out, "    %c[\"%%\"]\n", current_label);
            break;
        case TOKEN_LESS:
            fprintf(out, "    %c[\"<\"]\n", current_label);
            break;
        case TOKEN_GREATER:
            fprintf(out, "    %c[\">\"]\n", current_label);
            break;
        default:
            break;
    }

    // Liaison des enfants pour certains types de nœuds
    if (node->type == TOKEN_ASSIGN || node->type == TOKEN_PLUS || node->type == TOKEN_MINUS ||
        node->type == TOKEN_MULTIPLY || node->type == TOKEN_DIVIDE || node->type == TOKEN_MODULO ||
        node->type == TOKEN_LESS || node->type == TOKEN_GREATER) {

        int left_index = (*count); // Index pour le fils gauche
        print_ast_mermaid(node->children.left, out, count);
        fprintf(out, "    %c --> %c\n", current_label, 'A' + left_index); // Crée une liaison vers le fils gauche

        int right_index = (*count);
        print_ast_mermaid(node->children.right, out, count);
        fprintf(out, "    %c --> %c\n", current_label, 'A' + right_index);
    }
    // Gestion spécifique pour le nœud de type TOKEN_PRINT
    if (node->type == TOKEN_PRINT) {
        fprintf(out, "    %c[\"print\"]\n", current_label);
        int left_index = (*count);
        print_ast_mermaid(node->children.left, out, count);
        fprintf(out, "    %c --> %c\n", current_label, 'A' + left_index);
    }
}

// Libère la mémoire des variables et de l'AST
void free_ast(ASTNode* node) {
    if (!node) return;

    if (node->type == TOKEN_STRING) {
        free(node->str_value);
    }
    if (node->type == TOKEN_IDENTIFIER) {

    } else {
        free_ast(node->children.left);
        free_ast(node->children.right);
    }
    free(node);
}