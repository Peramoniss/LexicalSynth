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
*/
float v[15][20][15][20];
int a, b, c = 5;
char c, d, e = '9';
int **(*b) = 7;
double a = 1.23, b = 1.579;
float g = d = 3;

h = 6 + 8 * 3 + 9 - 7 / 2;
h += 6 * 8;
h = 6 / 8;
h = 6 - 8;
g = 3 * 6 + 8;

int funcao(int ca[], char tt){
    int a = c;
    a = b;
	funcao(&a,b+6/7-2*9);
	funcao(b+6*7-2);
    funcao(funcao(&a[5]), b+6*5/3+9-2*7); //devo conseguir lidar com endereços?
	c = b;
};

a += (a + b);
a -= (a - b);
a /= (a / b);
a *= (a * b);
a %= (a % b);
a >>= (a << b);
a <<= (a >> b);

a = a || b && a;
a = a & b | c ^ d;

a = a == b;
a = a != b;
a = **a, b = b;
a = - - -a;
a = - --&~!a ;

a[54](a - b);

if(a > b | a < b){
    b = 0;
}
// if(?{@

{
	a = b;
	b = a;
}

//preciso implementar para permitir declarações dentro do for?
for (i = 3, j = 5; i < 15, j < 8; i++, j+=6){
	int k = i+5;
	a = i;
	b = j;
	a = b = i = j = k;
}

while (i < 15){
	a = i;
	b = j + 5;
}

do{
	a = i;
	b = j + 5;
} while (i < 15);

if(a=b){
    a = 0;
    b = 0;
}