// Declarações e referências a variáveis int, float, char e double, bem como pointers e arrays de qualquer quantidade de dimensões (vetores, matrizes...).
/*
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKChar 16
#define TKDouble 21
#define TKProd 15 (*, significa pointer nesse caso)
#define TKAbreColchete 18
#define TKFechaColchete 19 (para vetores)

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

*/
float v[15][20][15][20];
int a, b, c = 5;
char c, d, e = '9';
int **(*b) = 7;
double a = 1.23, b = 1.579;
float g = d = 3;

h = 6 + 8;
h = 6 * 8;
h = 6 / 8;
h = 6 - 8;
// g = 3 * 6 + 8;

int funcao(int ca[], char tt){
    int a = c;
    a = b;
	funcao(&a,b+6/7-2*9);
	funcao(b+6*7-2);
    funcao(funcao(&a[5]), b+6*5/3+9-2*7); //devo conseguir lidar com endereços?
	c = b;
};

if(a=b){
    // a /= 0;
    b = 0;
}
// if(?{@

if(a=b){
    a = 0;
    b = 0;
}