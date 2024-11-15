//
// Created by Darkazanli on 27/10/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

// Déclaration de la fonction pour analyser une expression complète (addition et soustraction)
ASTNode* parse_expr(int* index);

// Déclaration de la fonction pour analyser les termes (multiplication et division)
ASTNode* parse_term(int* index);

#endif //PARSER_H
