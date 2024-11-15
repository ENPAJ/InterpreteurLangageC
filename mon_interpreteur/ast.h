//
// Created by Darkazanli on 27/10/2024.
//

#ifndef AST_H
#define AST_H

#include "tools.h"

// Structure pour un nœud de l'AST
typedef struct ASTNode {
    TokenType type;
    union {
        int value;
        char* str_value;
        char identifier[32];

        // Structure pour les opérations binaires avec enfants gauche et droit
        struct {
            // Pointeurs vers les sous-arbres
            struct ASTNode* left;
            struct ASTNode* right;
        } children;
    };
} ASTNode;

// Déclaration des fonctions pour gérer l'AST
ASTNode* create_node(TokenType type);
void print_ast_mermaid(ASTNode* node, FILE* out, int* count);
void free_ast(ASTNode* node);

#endif //AST_H
