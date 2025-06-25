#define DEBUG_MODE 0

#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbrePar 7
#define TKFechaPar 8
#define TKAtrib 9
#define TKPontoEVirgula 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKMais 13
#define TKDuploMais 14
#define TKProd 15
#define TKChar 16
#define TKSub 17
#define TKAbreColchete 18
#define TKFechaColchete 19
#define TKAtribMais 20
#define TKDouble 21
#define TKCteInt 22
#define TKElse 23
#define TKIf 24
#define TKString 25
#define TKBitNot 26
#define TKDiv 27
#define TKAtribDiv 28
#define TKPonto 29
#define TKAndLog 30
#define TKAtribAnd 31
#define TKAnd 32
#define TKConstChar 33
#define TKNot 34
#define TKNotEqual 35
#define TKOrLog 36
#define TKAtribOr 37
#define TKOr 38
#define TKLessThan 39
#define TKLessOrEqualThan 40 
#define TKGreaterThan 41
#define TKGreaterOrEqualThan 42 
#define TKXOR 43
#define TKXOREquals 44
#define TKLeftShift 45
#define TKAtribLeftShift 46
#define TKRightShift 47
#define TKAtribRightShift 48
#define TKPtrOpr 49
#define TKEquals 50
#define TKMod 51
#define TKAtribMod 52
#define TKSwitch 53
#define TKCase 54
#define TKDefault 55
#define TKDo 56
#define TKWhile 57
#define TKFor 58
#define TKEOF 59
#define TKStatic 60
#define TKConst 61
#define TKCteFloat 62
#define TKDuploMenos 63
#define TKAtribProd 64
#define TKAtribMenos 66

#define false 0
#define true 1

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

char tokens[100][30] = {
    "TKId",            // 1
    "TKVoid",          // 2
    "TKInt",           // 3
    "TKFloat",         // 4
    "TKVirgula",       // 5
    "TKDoisPontos",    // 6
    "TKAbrePar",       // 7
    "TKFechaPar",      // 8
    "TKAtrib",         // 9
    "TKPontoEVirgula", // 10
    "TKAbreChaves",    // 11
    "TKFechaChaves",   // 12
    "TKMais",          // 13
    "TKDuploMais",     // 14
    "TKProd",          // 15
    "TKChar",          // 16
    "TKSub",           // 17
    "TKAbreColchete",  // 18
    "TKFechaColchete", // 19
    "TKAtribMais",     // 20
    "TKDouble",        // 21
    "TKCteInt",        // 22
    "TKElse",          // 23
    "TKIf",            // 24
    "TKString",        // 25
    "TKBitNot",        // 26
    "TKDiv",           // 27
    "TKAtribDiv",      // 28
    "TKPonto",         // 29
    "TKAndLog",        // 30
    "TKAtribAnd",      // 31
    "TKAnd",           // 32
    "TKConstChar",     // 33
    "TKNot",           // 34
    "TKNotEqual",      // 35
    "TKOrLog",         // 36
    "TKAtribOr",       // 37
    "TKOr",            // 38
    "TKLessThan",      // 39
    "TKLessOrEqualThan", // 40
    "TKGreaterThan",   // 41
    "TKGreaterOrEqualThan", // 42
    "TKXOR",           // 43
    "TKXOREquals",     // 44
    "TKLeftShift",     // 45
    "TKLeftShiftAssign", //46
    "TKRightShift",     // 47
    "TKRightShiftAssign", //48
    "TKPtrOpr",          //49
    "TKEquals",          //50
    "TKMod",             //51
    "TKModAssign",       //52
    "TKSwitch",          //53
    "TKCase",            //54
    "TKDefault",         //55
    "TKDo",              //56
    "TKWhile",           //57
    "TKFor",              //58
    "TKEOF",              //59
    "TKEStatoc",              //60
    "TKConst",              //61
    "TKCteFloat",              //62
    "TKAtribProd",          //63
    "TKDuploMenos",              //64
};  

int pos = 0;

int tk;
char lex[500];
int lin=1, col=0, curr_col;
FILE *arqin;
char c; // �ltimo caracter lido do arquivo
FILE *arqout=fopen("Saida.txt","wt");


struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={{"void",TKVoid},
                  {"int",TKInt},
                  {"float",TKFloat},
                  {"char",TKChar},
                  {"double",TKDouble},
                  {"else",TKElse},
                  {"if",TKIf},
                  {"switch",TKSwitch},
                  {"case",TKCase},
                  {"default",TKDefault},
                  {"do",TKDo},
                  {"while",TKWhile},
                  {"for",TKFor},
                  {"fimtabela",TKEOF},
                  {"static",TKStatic},
                  {"const",TKConst}};


int palavra_reservada(char lex[])
{
    int postab=0;
    while (strcmp("fimtabela",lista_pal[postab].palavra)!=0)
    {
    if (strcmp(lex,lista_pal[postab].palavra)==0)
        return lista_pal[postab].tk;
    postab++;
    }
    return TKId;
}

void setColor(int color) {
    // Obtém o handle do console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Define a cor do texto (atributo)
    SetConsoleTextAttribute(hConsole, color);
}

void getToken(); // prot�tipos
void proxC();

// vari�veis globais para retrocesso

typedef struct contexto{long posglobal;
    int tkant;
    char cant;
    char lexant[20];
    int coluna;
} tcontexto;

tcontexto pilhacon[1000];
int topcontexto=0;
int backtrack_mode = 0;

tcontexto marcaPosToken() {
	pilhacon[topcontexto].posglobal=ftell(arqin);
	pilhacon[topcontexto].tkant=tk;
	pilhacon[topcontexto].cant=c;
    strcpy(pilhacon[topcontexto].lexant,lex);
    pilhacon[topcontexto].coluna=col;
    topcontexto++;
    return pilhacon[topcontexto-1];
    // backtrack_mode = 1; //indica que esta fazendo ma analise com o backtracking e nao deve exibir erros
}

void restauraPosToken() {
    topcontexto--;
	fseek(arqin,pilhacon[topcontexto].posglobal,SEEK_SET);
    c=pilhacon[topcontexto].cant;
	tk=pilhacon[topcontexto].tkant;
    strcpy(lex,pilhacon[topcontexto].lexant);
    col = pilhacon[topcontexto].coluna;

    backtrack_mode = 0; //indica que parou de fazer a analise do backtracking e pode voltar a mostrar erros
}

void proxC()
{
if (feof(arqin)) {
   c=-1;
//   printf("Chegou no fim de arquivo\n");
   return;
   }
fread(&c,1,1,arqin);
col++;
if (c=='\n'){ 
    lin++; col=0; curr_col=1;}
// else if (c==' ') col++;
//printf("Leu caracter %c\n",c);
}

void getToken2()
{
int estado=0,
    fim=0,
    posl=0;
    while (!fim)
    {
        if(c!=-1) lex[posl++]=c;
        switch(estado){
            case 0:
             curr_col = col;
            //  if (c =='\n') return;
             if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_')
                {proxC();estado=1;break;}
             if (c>='0' && c<='9')
                {
                    int floating_constant = 0;
                    while (c>='0' && c<='9'){
                        proxC();
                        if(c=='.'){
                            if (floating_constant != 0){
                                // goto erro_lexico;
                            }else{
                                lex[posl++] = c;
                                proxC();
                                floating_constant++;
                            }
                        }
                        if (c>='0' && c<='9')
                            lex[posl++] = c;

                    } 
                    lex[posl]='\0';
                    tk= floating_constant ? TKCteFloat : TKCteInt;
                    return;
                }
             if (c=='"')
                {
                proxC();
                while (c!='"')
				   {
				   lex[posl++]=c;
				   proxC();
				   }
                proxC();
                lex[posl]='\0';
                tk=TKString;
                return;
                }
             if (c=='\'')
                {
                proxC();
                while (c!='\'')
				   {
				   lex[posl++]=c;
				   proxC();
				   }
                lex[posl++]=c;
                lex[posl]='\0';
                tk=TKConstChar;
                proxC();
                return;
                }
             if (c=='='){
                proxC();
                if(c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKEquals;return;}
                else{lex[posl]='\0';tk=TKAtrib;/*printf("Reconheceu token TKAtrib\n");*/return;}
             }
             if (c=='%'){
                proxC();
                if(c == '>'){lex[posl++]='>';lex[posl]='\0';proxC();tk=TKFechaChaves;return;}
                else if(c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKAtribMod;return;}
                else {lex[posl]='\0';tk=TKMod;/*printf("Reconheceu token TKAtrib\n");*/return;}
             }
             if (c=='.'){lex[posl]='\0';proxC();tk=TKPonto;return; }
             if (c=='<'){
                proxC();
                if (c == '<'){ //shift
                    lex[posl++] = '<';
                    proxC();
                    if (c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKAtribLeftShift;return;}
                    else {lex[posl]='\0';tk=TKLeftShift;return;}
                }
                else if (c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKLessOrEqualThan;return;}
                else if (c == '%'){lex[posl++]='%';lex[posl]='\0';proxC();tk=TKAbreChaves;return;}
                else{ 
                    lex[posl]='\0';tk=TKLessThan;return; 
                }
             }
             if (c=='>'){
                proxC();
                if (c == '>'){ //shift
                    lex[posl++] = '>';
                    proxC();
                    if (c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKAtribRightShift;return;}
                    else {lex[posl]='\0';tk=TKRightShift;return;}
                }
                else if (c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKGreaterOrEqualThan;return;}
                else{ 
                    lex[posl]='\0';tk=TKGreaterThan;return; 
                }
             }
             if (c=='^')
             {
                proxC();
                if(c=='='){
                    lex[posl++]='='; lex[posl]='\0'; proxC(); tk=TKXOREquals; return;
                }
                else{lex[posl]='\0';tk=TKXOR;return; }
             }
             if (c=='+')
			    {
			    proxC();
				if (c=='+')
			       {
				   lex[posl++]='+';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKDuploMais;/*printf("Reconheceu token TKDuploMais\n");*/return;
				   }
				else if (c=='=')
			       {
				   lex[posl++]='=';
     			   lex[posl]='\0';
				   proxC();
				   tk=TKAtribMais;/*printf("Reconheceu token TKDuploMais\n");*/return;
				   }
                else
				   {
	               lex[posl]='\0';
				   tk=TKMais;/*printf("Reconheceu token TKSoma\n");*/return;
				   }
			    }
             if (c=='/'){
                proxC();
                if (c=='/'){ //é um comentário em linha - deve ignorar
                    while(c!='\n'){
                        proxC();
                    }
                }
                else if (c=='*'){ //é um comentário em multiplas linhas - deve ignorar
                    int ended = 0;
                    while(ended == 0){
                        proxC();
                        while(c!='*'){
                            proxC();
                        }
                        proxC();
                        if(c=='/'){
                            proxC();
                            posl = 0;
                            ended = 1;
                            break;
                        }
                    }
                    break;
                }
                else if (c=='='){ //atribuição com divisao
                    lex[posl++]='=';lex[posl]='\0';tk=TKAtribDiv;proxC();return;
                }
                else {
                    lex[posl]='\0';
                    tk=TKDiv;/*printf("Reconheceu token TKDiv\n");*/return;
                }
             }
             if (c=='&'){
                proxC();
                if(c=='&'){
                    lex[posl++]='&';
                    lex[posl]='\0';
                    proxC();
                    tk=TKAndLog;
                    return;
                }
                else if(c=='='){
                    lex[posl++]='=';
                    lex[posl]='\0';
                    proxC();
                    tk=TKAtribAnd;
                    return;
                }else{
                    lex[posl]='\0';
                    tk=TKAnd;
                    // proxC();
                    return;
                }
             }
             if (c=='|'){
                proxC();
                if(c=='|'){
                    lex[posl++]='|';
                    lex[posl]='\0';
                    tk=TKOrLog;
                    proxC();
                    return;
                }
                else if(c=='='){
                    lex[posl++]='=';
                    lex[posl]='\0';
                    tk=TKAtribOr;
                    proxC();
                    return;
                }else{
                    lex[posl]='\0';
                    tk=TKOr;
                    // proxC();
                    return;
                }
             }
             if (c=='!'){
                proxC();
                if(c=='='){
                    lex[posl++]='=';
                    lex[posl]='\0';
                    tk=TKNotEqual;
                    proxC();
                    return;
                }
                else {
                    lex[posl]='\0';
                    tk=TKNot;
                    return;
                }
             }
             if (c=='-'){
                proxC();
                if (c == '>'){lex[posl++]='>';lex[posl]='\0';proxC();tk=TKPtrOpr;/*printf("Reconheceu token TKSub\n");*/return;}
                else if (c == '-') {lex[posl++]='-';lex[posl]='\0';proxC();tk=TKDuploMenos;return;}
                else if (c == '=') {lex[posl++]='=';lex[posl]='\0';proxC();tk=TKAtribMenos;return;}
                else{lex[posl]='\0';tk=TKSub;/*printf("Reconheceu token TKSub\n");*/return;}
            }
            if (c=='*'){
                proxC();
                if (c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKAtribProd; return;}
                else{lex[posl]='\0';tk=TKProd;return;}
            }
             if (c=='['){lex[posl]='\0';proxC();tk=TKAbreColchete;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c==']'){lex[posl]='\0';proxC();tk=TKFechaColchete;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c=='('){lex[posl]='\0';proxC();tk=TKAbrePar;/*printf("Reconheceu token TKAbrePar\n");*/return;}
             if (c==')'){lex[posl]='\0';proxC();tk=TKFechaPar;/*printf("Reconheceu token FechaPar\n");*/return;}
             if (c=='{'){lex[posl]='\0';proxC();tk=TKAbreChaves;/*printf("Reconheceu token TKAbreChaves\n");*/return;}
             if (c=='}'){lex[posl]='\0';proxC();tk=TKFechaChaves;/*printf("Reconheceu token TKFechaChaves\n");*/return;}
             if (c==','){lex[posl]='\0';proxC();tk=TKVirgula;/*printf("Reconheceu token TKVirgula\n");*/return;}
             if (c==';'){lex[posl]='\0';proxC();tk=TKPontoEVirgula;/*printf("Reconheceu token TKPontoEVirgula\n");*/return;}
             if (c==':'){lex[posl]='\0';proxC();tk=TKDoisPontos;/*printf("Reconheceu token TKDoisPontos\n");*/return;}
             if (c=='~'){lex[posl]='\0';proxC();tk=TKBitNot;/*printf("Reconheceu token TKDoisPontos\n");*/return;}
             if (c==-1){
                printf("Arquivo acabando....");
                if (posl > 1) {  // já leu alguma coisa, finalize o token atual
                    printf("   ....   ");

                    lex[--posl] = '\0';  // remove o -1, termina string
                    if (estado == 1) {
                        tk = palavra_reservada(lex);
                    } else {
                        tk = TKId; // ou mantenha conforme a categoria apropriada
                    }
                    return;
                } else {  // nada foi lido, pode emitir TKEOF
                    printf("Acabou");
                    tk = TKEOF;
                    return;
                }
             }
             if (c==' ' || c=='\n' || c=='\t' || c=='\r') {proxC();posl--;break;}
             if (c=='\0') {tk=-1;return;}
            //  erro_lexico: //a beleza dos rotulos e do goto
             setColor(4);
             printf("Erro lexico: encontrou o caracter %c (%d) na linha %d\n",c,c,lin);
             fprintf(arqout,"Erro lexico: encontrou o caracter %c (%d) na linha %d\n",c,c,lin);
             setColor(7); //padrao (branco)
             exit(0);
             posl--;
             while (c!='\n') proxC();
             break;
      case 1:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' || c>='0' && c<='9') {proxC();break;}
             lex[--posl]='\0';
             int prev_tk = tk;
             tk=palavra_reservada(lex);
             if(TKId != tk){
                //setColor(2); //verde
                // col--;
            }
             else{
                //setColor(3); //azul
             }  
             //printf("reconheceu token %s\n",lex);
             return;
      } //switch
   }// while
}// fun��o

void getToken(){
    // printf("%s\n", tokens[tk-1]);
    getToken2();
    fprintf(arqout, "%s identified in '%s', at line %d and column %d\n", tokens[tk-1], lex, lin, curr_col);
}

int errored = 0;

void error(const char expected_token[]){
    if (errored == 0 && backtrack_mode == 0){
        setColor(4);
        printf("ERRO encontrado na linha %d, coluna %d: esperava token %s, mas encontrou %s em %s\n", lin, col, expected_token, tokens[tk-1], lex);
        fprintf(arqout,"ERRO encontrado na linha %d, coluna %d: esperava token %s, mas encontrou %s em %s\n", lin, col, expected_token, tokens[tk-1], lex);
        setColor(7);

        errored = 1;
    }
}

int expression();

int primary_expression(){
    // printf("  _%s_  ", tokens[tk-1]);
    if (DEBUG_MODE) printf("Primary expression\n");
    if (tk == TKId || tk == TKCteInt || tk == TKCteFloat || tk == TKConstChar){
        getToken(); //verifica aqui dentro porque ja comeca com o primeiro token lido. Entao esta sempre analisando "atrasado"
        return 1;
    }else if (tk == TKAbrePar){
        getToken();
        if(expression()){
            if(tk == TKFechaPar){
                getToken();
                return 1;
            }
        }
    }
    
    error("Identifier or Constant");
    return 0;
}

int assignment_expression();
int postfix_expression();
int pointer();

int argument_expression_list(){
    if (DEBUG_MODE) printf("argument_expression_list");
    int retorno = 0;
    if (expression()){
        retorno = 1;
        while(tk == TKVirgula){
            getToken();
            if(!expression())
            { retorno = 0; break; }
        }
    }

    return retorno;
}


int postfix_expression(){ 
    if (DEBUG_MODE) printf("POSTFIX\n");

    int retorno = 0;

    if (primary_expression()){
        retorno = 1;
        while (1){
            if (tk == TKAbreColchete){
                getToken();
                if (expression()){
                    if (tk == TKFechaColchete){
                        getToken();
                    } else {
                        error("]");
                        return 0;
                    }
                } else return 0;
            }
            else if (tk == TKAbrePar){
                // BACKTRACKING PROTEGENDO TODA A CHAMADA DE FUNÇÃO
                tcontexto cont = marcaPosToken();

                getToken(); // consome '('

                if (tk == TKFechaPar){
                    getToken(); // consome ')'
                    continue; // é uma chamada vazia, como funcao()
                }

                if (argument_expression_list()){
                    if (tk == TKFechaPar){
                        getToken();
                        continue; // chamada de função completa
                    } else {
                        error(")");
                        // restauraPosToken();
                        //testando localmente ao invés de usar pilha
                        fseek(arqin,cont.posglobal,SEEK_SET);
                        c=cont.cant;
                        tk=cont.tkant;
                        strcpy(lex,cont.lexant);
                        col = cont.coluna;
                        return 0;
                    }
                } else {
                    // argument_expression_list() falhou
                    // restauraPosToken();
                    fseek(arqin,cont.posglobal,SEEK_SET);
                    c=cont.cant;
                    tk=cont.tkant;
                    strcpy(lex,cont.lexant);
                    col = cont.coluna;
                    return 0;
                }
            }
            else if (tk == TKPonto){
                getToken();
                if (tk == TKId){
                    getToken();
                    continue;
                } else {
                    error("Identifier");
                    return 0;
                }
            }
            else if (tk == TKPtrOpr){
                getToken();
                if (tk == TKId){
                    getToken();
                    continue;
                } else {
                    error("Identifier");
                    return 0;
                }
            }
            else if (tk == TKDuploMais || tk == TKDuploMenos){
                getToken();
                continue;
            }
            else break;
        }
    }

    return retorno;
}

int unary_expression(){
    if (tk == TKAnd || tk == TKSub || tk == TKMais || tk == TKNot || tk == TKBitNot || tk == TKDuploMais || tk == TKDuploMenos || tk == TKProd){
        getToken();
        return unary_expression(); // chamada recursiva para o operando
    }

    return postfix_expression(); // caso não tenha operador unário, segue para expressão pós-fixada
}

//------------Outros tipos de expressão------------------

int multiplicative_expression(){
    if (DEBUG_MODE) printf("Multiplicative statement\n");
    // marcaPosToken();
    if (unary_expression()){
        while (tk == TKProd || tk == TKDiv || tk == TKMod){
            getToken();
            if(!unary_expression()){
                error("expression after one of the following: *, / or %");
                return 0;
            }
        }
        return 1;
    }
    // restauraPosToken();
    return 0;
}

int additive_expression(){
    if (DEBUG_MODE) printf("Additive statement\n");

    if (!multiplicative_expression()) return 0;

    while (tk == TKMais || tk == TKSub){
        getToken();
        if (!multiplicative_expression()){
            error("expression after one of the following: + or -");
            return 0;
        }
    }

    return 1;
}

int bitwise_shift(){
    if (!additive_expression()) return 0;

    while (tk == TKLeftShift || tk == TKRightShift){
        getToken();
        if (!additive_expression()) {
            error("expression after one of the following: << or >>");
            return 0;
        }
    }

    return 1;
}

int relational_operators(){
    if (!bitwise_shift()) return 0;

    while (tk == TKLessThan || tk == TKLessOrEqualThan || tk == TKGreaterThan || tk == TKGreaterOrEqualThan){
        getToken();
        if (!bitwise_shift()) {
            error("expression after one of the following: + or -");
            return 0;
        }
    }

    return 1;
}

int relational(){
    if (!relational_operators()) return 0;

    while (tk == TKEquals || tk == TKNotEqual){
        getToken();
        if (!relational_operators()) {
            error("expression after one of the following: == or !=");
            return 0;
        }
    }

    return 1;
}

int bitwise_and(){
    if (!relational()) return 0;

    while (tk == TKAnd){
        getToken();
        if (!relational()) {
            error("expression after &");
            return 0;
        }
    }

    return 1;
}

int bitwise_xor(){
    if (!bitwise_and()) return 0;

    while (tk == TKXOR){
        getToken();
        if (!bitwise_and()) {
            error("expression after ^");
            return 0;
        }
    }

    return 1;
}

int bitwise_or(){
    if (!bitwise_xor()) return 0;

    while (tk == TKOr){
        getToken();
        if (!bitwise_xor()) {
            error("expression after |");
            return 0;
        }
    }

    return 1;
}

int logical_and(){
    if (!bitwise_or()) return 0;

    while (tk == TKAndLog){
        getToken();
        if (!additive_expression()) {
            error("expression after &&");
            return 0;
        }
    }

    return 1;
}

int logical_or(){
    if (!logical_and()) return 0; //Doesn't call error() because it's not necessarily an error, as it could be that the code ended or simply this expression is not being a part of it

    while (tk == TKOrLog){
        getToken();
        if (!logical_and()) {
            error("expression after ||"); //This error will most likely never be called as well, since TKPontoEVirgula will generate an error first
            return 0;
        }
    }

    return 1;
}


int assignment_expression(){
    if (DEBUG_MODE) printf("Assignment statement\n");
    tcontexto cont = marcaPosToken();
    if (tk == TKId){
        getToken();
        if(tk == TKAtrib || tk ==TKAtribAnd || tk ==TKAtribDiv || tk ==TKAtribLeftShift
        ||  tk ==TKAtribMais ||  tk ==TKAtribMenos || tk ==TKAtribMod || tk ==TKAtribOr
        || tk ==TKAtribProd  || tk ==TKAtribRightShift){ 
            getToken();
            if(assignment_expression()){
                return 1;
            }
        }
    }

    // restauraPosToken();
    fseek(arqin,cont.posglobal,SEEK_SET);
    c=cont.cant;
    tk=cont.tkant;
    strcpy(lex,cont.lexant);
    col = cont.coluna;
    return logical_or(); 
}

int comma(){
    if (!assignment_expression()) return 0;

    while (tk == TKVirgula){
        getToken();
        if (!assignment_expression()){
            error("expression after ','");
            return 0;
        }
    }

    return 1;
}

int expression(){
    if (DEBUG_MODE) printf("Expression\n");
    if (comma()){return 1;}
    
    return 0;
}

/*int pointer(){
    if (tk == TKProd){
        getToken();
        while (tk == TKProd) getToken();
        return 1;
    }

    return comma();
}*/

int statement_list();
int statement();

int compound_statement(){
    if (DEBUG_MODE) printf("Compound statement\n");
    if (tk == TKAbreChaves){
        getToken();
        if(tk == TKFechaChaves){
            getToken();
            return 1;
        } 
        else if (statement_list()){
            if(tk == TKFechaChaves){
                getToken();
                return 1;
            }   
        }
        
        error("'}' (compound)");
    } else error("'{' (compound)");
    
    return 0;
}

int expression_statement(){
    if (DEBUG_MODE) printf("Expression statement\n");
    if (tk == TKPontoEVirgula){
        getToken();
        return 1;
    }else if (expression()){
        if (tk == TKPontoEVirgula){
            getToken();
            return 1;
        }
    }
    
    error("';' (expression)");
    return 0;
}

int iteration_statement(){ 
    if (DEBUG_MODE) printf("Iteration statement\n");
    if (tk == TKFor){
        getToken();
        if (tk == TKAbrePar){
            getToken();
            if(expression_statement()){
                if (expression_statement()){
                    expression();
                    if (tk == TKFechaPar){
                        getToken();
                        if (statement()){
                            return 1;
                        }
                    }else error("')' (iteration)");
                }else error("");
                
            }else error("')' (iteration)");
        }else error("'(' (iteration)");
    }else if (tk == TKWhile){
        getToken();
        if (tk == TKAbrePar){
            getToken();
            if (expression()){
                if(tk == TKFechaPar){
                    getToken();
                    if (statement()) return 1;
                }
            }
        }
    }else if (tk == TKDo){
        getToken();
        if (statement()){
            if (tk == TKWhile){
                getToken();
                if (tk == TKAbrePar){
                    getToken();
                    if (expression()){
                        if (tk == TKFechaPar){
                            getToken();
                            if (tk == TKPontoEVirgula){
                                getToken();
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    } 
    
    else error("'if' (iteration)");

    return 0;
}

/*POR AQUI TRABALHAR DEMAIS TIPOS DE STATEMENT: Do...While, While, For*/

int selection_statement(){ 
    if (DEBUG_MODE) printf("Selection statement\n");
    if (tk == TKIf){
        getToken();
        if (tk == TKAbrePar){
            getToken();
            if(expression()){
                if (tk == TKFechaPar){
                    getToken();
                    if (statement()){
                        return 1;
                    }
                }else error("')' (selection)");
            }else error("')' (selection)");
        }else error("'(' (selection)");
    }else error("'if' (selection)");

    return 0;
}

int declaration_specifiers(){
    //posso implementar com while pra tirar a recursão desnecessária, mas tira bastante a legibilidade - teria que separar em funções para cada especificador para ficar bom, mas acho desnecessário
    if (DEBUG_MODE) printf("Declaration Specifiers \n");
    if (tk == TKVoid || tk == TKInt || tk == TKFloat || tk == TKChar || tk == TKDouble){ //type_specifier
        getToken();
        return 1;
    }else if (tk == TKConst){ //type_qualifier
        getToken();
        declaration_specifiers();
        return 1;
    }else if (tk == TKStatic){ //storage_class_specifier
        getToken();
        declaration_specifiers();
        return 1;
    }

    return 0;
}

int declarator();

int direct_declarator(){
    if (DEBUG_MODE) printf("Direct Declarator\n");
    int retorno = 0;
    if (tk == TKId){
        getToken();
        retorno = 1;
        // return 1;
    }else if (tk == TKAbrePar){
        getToken();
        if (declarator()){
            if (tk == TKFechaPar){
                getToken();
                retorno = 1;
                // return 1;
            }else error(")");
        }else error("Declaration");
    }

    while (1){ //enquanto conseguir encontrar novas combinações
        if (tk == TKAbreColchete){ //vetores
            getToken();
            if (tk == TKFechaColchete){
                getToken();
                retorno = 1;
            }else if (postfix_expression()){ //teoricamente tinha que passar por umas 15 recursões antes de chegar aqui, mas também sou filho de Deus
                if (tk == TKFechaColchete){
                    getToken();
                    retorno = 1;
                }
            }
        } else if (tk == TKAbrePar){ //funçoes
            getToken();
            if (tk == TKFechaPar){
                getToken();
                retorno = 1;
            } 

            if (declaration_specifiers()){
                if (declarator()) {
                    retorno = 1;

                    // continua analisando possíveis parâmetros adicionais
                    while (tk == TKVirgula){
                        getToken();
                        if (declaration_specifiers()){
                            if (!declarator()) {
                                error("param declarator");
                                return 0;
                            }
                        } else{
                            error("param specifier");
                            return 0;
                        }
                    }

                    if (tk == TKFechaPar){
                        getToken();
                    } else {
                        error("')' na lista de parâmetros");
                        return 0;
                    }

                    compound_statement();
                } else restauraPosToken(); // declarator falhou
            } else restauraPosToken(); // specifier falhou 
        }
        else break;
    }

    return retorno;
}

int declarator(){
    if (DEBUG_MODE) printf("Declarator\n");
    if (tk == TKProd){ //*
        getToken();
        while(tk == TKProd) getToken();
        if (direct_declarator()) return 1;
    }else if (direct_declarator()) return 1;

    return 0;
}
int init_declarator(){
    if (DEBUG_MODE) printf("Init Declarator\n");
    if (declarator()){
        if (tk == TKAtrib){
            getToken();
            if (expression()) return 1; //initializer
        }       

        return 1;
    }
   
    return 0;
}

int init_declarator_list(){
    if (DEBUG_MODE) printf("Init Declarator List\n");
    int declared = 0;
    while (init_declarator()){
        declared = 1;
        if(tk == TKVirgula){
            getToken();
        } else break; //se não for virgula, não poderia continuar declarando
    }

    return declared;
}

int declaration(){
    if (DEBUG_MODE) printf("Declaration\n");
    if(declaration_specifiers()){
        if (tk == TKPontoEVirgula){getToken();return 1;}
        else if (init_declarator_list()){
            if (tk == TKPontoEVirgula){
                getToken();
                return 1;
            } 
        }
    }

    return 0;
}

int statement(){
    if (DEBUG_MODE) printf("Statement\n");
    if (tk == TKFechaChaves) {
        // se for o fim de um bloco, não é um statement e pode retornar imediatamente. Não precisa consumir no entanto, outra chamada irá cuidar disso. Essa verificação é só para evitar erros propagados
        return 0;
    }
    else if(tk == TKIf){
        if (selection_statement()){
            return 1;
        }
    }else if(tk == TKFor || tk == TKWhile || tk == TKDo){
        if (iteration_statement()){
            return 1;
        }
    }else if (tk == TKAbreChaves){
        if (compound_statement()){
            return 1;
        }
    }  
    
    // marcaPosToken();
    if (declaration()){
        return 1;
    }
    // restauraPosToken();

    // marcaPosToken();
    if (expression_statement()){
        return 1;
    }
    // restauraPosToken();
    
    
    return 0;
}

int statement_list() {
    if (DEBUG_MODE) printf("statement list");

    int success = 0;

    while (tk != TKEOF && statement()) {
        success = 1; // reconheceu pelo menos um statement
    }

    if (errored) return 0;
    return success;
}

int main()
{
	arqin=fopen("Fonte.cpp","rb");
	if (!arqin) {
        fprintf(arqout, "Erro na abertura do fonte.\n");
		printf("Erro na abertura do fonte.\n");
		return 0;
	}
	proxC(); // l� primeiro caracter do arquivo
	getToken(); // ja comeca com primeiro token
	/*while (c!=-1)
	{
        printf("%s identified in '%s', at line %d and column %d\n", tokens[tk-1], lex, lin, curr_col);
        fprintf(arqout, "%s identified in '%s', at line %d and column %d\n", tokens[tk-1], lex, lin, curr_col);
        setColor(7);
        // curr_col = col;
		getToken();
	}*/
    // if (P())
    if (statement_list())
        printf("Compilado com sucesso!");
    // else printf("Faca os ajustes no token %s (%s) e tente compilar novamente", tokens[tk-1], lex);
}