#include <stdio.h>
#include <stdlib.h>

#include "eval.h"
#include "ast.h"
#include "variable.h"
#include "tools.h"

// Évalue une expression complète (addition et soustraction) à partir de l'AST
int eval_ast(ASTNode* node) {
    if (node->type == TOKEN_NUMBER) {
        return node->value;
    }
    if (node->type == TOKEN_STRING) {
        printf("%s", node->str_value);
        return 0;
    }
    if (node->type == TOKEN_IDENTIFIER) {
        Variable* var = find_variable(node->identifier);
        if (var) {
            if (var->is_string) {
                printf("%s", var->str_value);
                return 0;
            }
            return var->int_value;
        } else {
            fprintf(stderr, "Erreur : variable non definie '%s'\n", node->identifier);
            exit(1);
        }
    }
    // si c'est une opération d'addition entre deux chaînes, on fait une concaténation
    if (node->type == TOKEN_PLUS) {
        if (node->children.left->type == TOKEN_STRING && node->children.right->type == TOKEN_STRING) {
            // Concatène deux chaînes
            char* left_value = node->children.left->str_value;
            char* right_value = node->children.right->str_value;
            char* result = concat_strings(left_value, right_value);
            printf("%s\n", result);
            return 0;
        }
    }

    // Évaluation des opérations
    int left_value = eval_ast(node->children.left);
    int right_value = eval_ast(node->children.right);

    // Détermine l'opération à effectuer selon le type de noeud
    switch (node->type) {
        case TOKEN_PLUS:
            return left_value + right_value;
        case TOKEN_MINUS:
            return left_value - right_value;
        case TOKEN_MULTIPLY:
            return left_value * right_value;
        case TOKEN_DIVIDE:
            if (right_value == 0) {
                fprintf(stderr, "Erreur : Division par zero\n");
                exit(1);
            }
            return left_value / right_value;
        case TOKEN_MODULO:
            if (right_value == 0) {
                fprintf(stderr, "Erreur : Modulo par zero\n");
                exit(1);
            }
            return left_value % right_value;
        case TOKEN_LESS:
            return left_value < right_value;
        case TOKEN_GREATER:
            return left_value > right_value;
        default:
            fprintf(stderr, "Erreur : type de noeud inconnu\n");
            exit(1);
    }
}