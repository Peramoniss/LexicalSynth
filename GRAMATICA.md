Based on: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html#additive-expression


statement = selection_statement |  compound_statement | expression_statement
selection_statement = TKIf TKAbrePar expression TKFechaPar statement
compound_statement = TKAbreChaves TKFechaChaves | TKAbreChaves statement TKFechaChaves
expression_statement = expression TKPontoEVirgula | TKPontoEVirgula
primary_expression = TKId | TKCteInt | TKConstChar
expression = primary_expression additive_expression 
additive_expression = + primary_expression additive_expression | EMPTY