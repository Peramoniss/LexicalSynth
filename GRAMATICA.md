Based on: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html#additive-expression


statement_list = statement_list statement | statement
statement = selection_statement |  compound_statement | expression_statement | declaration
selection_statement = TKIf TKAbrePar expression TKFechaPar statement
compound_statement = TKAbreChaves TKFechaChaves | TKAbreChaves statement TKFechaChaves
expression_statement = expression TKPontoEVirgula | TKPontoEVirgula
declaration = declaration_specifiers TKPontoEVirgula | declaration_specifiers init_declarator_list 
declaration_specifiers = (type_specifier | type_qualifier | storage_class_specifier) (declaration_specifiers | EMPTY)
init_declarator_list = 
expression = primary_expression additive_expression 
additive_expression = + primary_expression additive_expression | EMPTY
primary_expression = TKId | TKCteInt | TKConstChar