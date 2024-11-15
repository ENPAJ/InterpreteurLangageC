#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "eval.h"
#include "variable.h"
#include "tools.h"

// Fonction principale d'interprétation
void interpret(const char* input) {
    lexer(input);
    token_index = 0;

    while (tokens[token_index].type != TOKEN_EOF) {
        if (tokens[token_index].type == TOKEN_IDENTIFIER) {
            char* name = strdup(tokens[token_index].identifier);  // Sauvegarder le nom de la variable
            token_index++;
            if (tokens[token_index].type == TOKEN_ASSIGN) {
                token_index++;
                ASTNode* expr_ast = parse_expr(&token_index);  // Analyse l'expression à droite de '='

                // Évalue l'AST pour obtenir la valeur de l'expression
                if (expr_ast->type == TOKEN_STRING) {
                    // Si l'expression est une chaîne
                    add_variable(name, 0, expr_ast->str_value, 1); // Ajouter en tant que variable de chaîne
                } else {
                    int value = eval_ast(expr_ast);
                    add_variable(name, value, NULL, 0); // Ajouter en tant que variable entière
                }

                // Création du nœud d'assignation pour l'AST
                ASTNode* assign_node = create_node(TOKEN_ASSIGN);
                assign_node->children.left = create_node(TOKEN_IDENTIFIER); // Nœud pour l'identifiant
                strcpy(assign_node->children.left->identifier, name);
                assign_node->children.right = expr_ast;  // Nœud pour l'expression

                // Affiche l'AST au format Mermaid
                printf("\n"); // Ligne vide pour séparer l'affichage
                printf("graph TD\n");
                int count = 0;
                print_ast_mermaid(assign_node, stdout, &count);
                printf("\n"); // Ligne vide pour séparer l'affichage

                free(name);  // Libère la mémoire du nom de la variable

            } else {
                // Évaluation de l'expression au lieu d'une assignation
                token_index--;
                ASTNode* ast = parse_expr(&token_index);
                if (ast->type == TOKEN_STRING) {
                    printf("Resultat : %s\n", ast->str_value);  // Affiche la chaîne
                } else {
                    int value = eval_ast(ast); // Évalue l'AST
                    printf("Resultat : %d\n", value);  // Affiche le résultat de l'expression
                }

                // Afficher l'AST au format Mermaid
                printf("\n");
                printf("graph TD\n");
                int count = 0;
                print_ast_mermaid(ast, stdout, &count);  // Affiche l'AST
                printf("\n");

                free(name);
            }
        } else if (tokens[token_index].type == TOKEN_PRINT) {
            token_index++;
            ASTNode* ast = parse_expr(&token_index);
            if (ast->type == TOKEN_STRING) {
                printf("%s\n", ast->str_value);  // Affiche la chaîne
            } else if (ast->type == TOKEN_PLUS && ast->children.left->type == TOKEN_STRING && ast->children.right->type == TOKEN_STRING) {
                // Si on a une addition de chaînes
                char* result = concat_strings(ast->children.left->str_value, ast->children.right->str_value);
                printf("%s\n", result);
                free(result);
            } else {
                int value = eval_ast(ast); // Évalue l'AST
                if (value != 0) { // N'imprime que si ce n'est pas 0
                    printf("%d\n", value);
                }
            }

            // Crée et affiche l'AST pour l'opération d'impression
            ASTNode* print_node = create_node(TOKEN_PRINT);
            print_node->children.left = ast;

            // Affiche l'AST au format Mermaid
            printf("\n");
            printf("graph TD\n");
            int count = 0;
            print_ast_mermaid(print_node, stdout, &count);
            printf("\n");

        } else {
            // Évaluer les expressions directement
            ASTNode* ast = parse_expr(&token_index);
            if (ast->type == TOKEN_STRING) {
                printf("Resultat : %s\n", ast->str_value);  // Affiche la chaîne
            } else {
                int value = eval_ast(ast); // Évalue l'AST
                printf("Resultat : %d\n", value);  // Affiche le résultat de l'expression
            }

            // Afficher l'AST au format Mermaid
            printf("\n");
            printf("graph TD\n");
            int count = 0;
            print_ast_mermaid(ast, stdout, &count);  // Affiche l'AST
            printf("\n");
        }

        // Avancer l'index pour passer le point-virgule ou le signe égal
        if (tokens[token_index].type == TOKEN_SEMICOLON || tokens[token_index].type == TOKEN_ASSIGN) {
            token_index++;
        }
    }
}