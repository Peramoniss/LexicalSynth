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
#define TKLeftShiftAssign 46
#define TKRightShift 47
#define TKRightShiftAssign 48
#define TKPtrOpr 49
#define TKEquals 50
#define TKMod 51
#define TKModAssign 52
#define TKSwitch 53
#define TKCase 54
#define TKDefault 55
#define TKDo 56
#define TKWhile 57
#define TKFor 58
#define TKEOF 59


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
    "TKEOF"              //59
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
                  {"fimtabela",TKEOF}};


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
               char lexant[20];} tcontexto;

tcontexto pilhacon[1000];
int topcontexto=0;

void marcaPosToken() {
	pilhacon[topcontexto].posglobal=ftell(arqin);
	pilhacon[topcontexto].tkant=tk;
	pilhacon[topcontexto].cant=c;
    strcpy(pilhacon[topcontexto].lexant,lex);
    topcontexto++;
}

//Implemente aqui a sua funcao restauraPosToken()

void restauraPosToken() {
    topcontexto--;
	fseek(arqin,pilhacon[topcontexto].posglobal,SEEK_SET);
    c=pilhacon[topcontexto].cant;
	tk=pilhacon[topcontexto].tkant;
    strcpy(lex,pilhacon[topcontexto].lexant);
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
                while (c>='0' && c<='9') proxC();
                lex[posl]='\0';
                tk=TKCteInt;
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
                else if(c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKModAssign;return;}
                else {lex[posl]='\0';tk=TKMod;/*printf("Reconheceu token TKAtrib\n");*/return;}
             }
             if (c=='.'){lex[posl]='\0';proxC();tk=TKPonto;return; }
             if (c=='<'){
                proxC();
                if (c == '<'){ //shift
                    lex[posl++] = '<';
                    proxC();
                    if (c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKLeftShiftAssign;return;}
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
                    if (c == '='){lex[posl++]='=';lex[posl]='\0';proxC();tk=TKRightShiftAssign;return;}
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
                    tk=TKAnd;
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
                    tk=TKAndLog;
                    // proxC();
                    return;
                }
             }
             if (c=='|'){
                proxC();
                if(c=='|'){
                    lex[posl++]='|';
                    lex[posl]='\0';
                    tk=TKOr;
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
                    tk=TKOrLog;
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
                else{lex[posl]='\0';tk=TKSub;/*printf("Reconheceu token TKSub\n");*/return;}
            }
             if (c=='*'){lex[posl]='\0';proxC();tk=TKProd;/*printf("Reconheceu token TKAbrePar\n");*/return;}
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

             //se nao encontrou nenhum dos tokens
             //setColor(4); //vermelho
             printf("Erro lexico: encontrou o caracter %c (%d) na linha %d\n",c,c,lin);
             fprintf(arqout,"Erro lexico: encontrou o caracter %c (%d) na linha %d\n",c,c,lin);
             posl--;
             setColor(7); //padrao (branco)
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
    getToken2();
    printf("%s\n", tokens[tk-1]);
}

void error(const char expected_token[]){
    setColor(4);
    printf("ERRO encontrado na linha %d, coluna %d: esperava token %s, mas encontrou %s\n", lin, col, expected_token, tokens[tk-1]);
    setColor(7);
}

int primary_expression(){
    // printf("  _%s_  ", tokens[tk-1]);
    printf("Primary expression\n");
    if (tk == TKId || tk == TKCteInt || tk == TKConstChar){
        getToken(); //verifica aqui dentro porque ja comeca com o primeiro token lido. Entao esta sempre analisando "atrasado"
        return 1;
    }
    
    return 0;
}

int additive_expression(){
    printf("Additive statement\n");
    //printf("????  _%s_  ", tokens[tk-1]);
    if (primary_expression()){
        if (tk == TKMais){
            getToken();
            if(primary_expression()){
                if(additive_expression()){
                    return 1;
                }
            }
        }else{
            return 1;
        }    
    }

    return 0; //SUBSTITUIR POR PRÓXIMA NA CADEIA    
}

int assignment_expression();

int expression(){
    printf("Expression\n");
    if (assignment_expression()){return 1;}
    
    return 0;
}

int assignment_expression(){
    printf("Assignment statement\n");
    marcaPosToken();
    if (tk == TKId){
        getToken();
        if(tk == TKAtrib){
            getToken();
            if(assignment_expression()){
                return 1;
            }
        }
    }

    restauraPosToken();
    return additive_expression();
}

int statement();

int compound_statement(){
    printf("Compound statement\n");
    if (tk == TKAbreChaves){
        getToken();
        if(tk == TKFechaChaves){
            getToken();
            return 1;
        } 
        if (statement()){
            if(tk == TKFechaChaves){
                getToken();
                return 1;
            }   
        }

        else error("'}'");
    } else error("'{'");
    
    return 0;
}

int expression_statement(){
    printf("Expression statement\n");
    if (tk == TKPontoEVirgula){
        return 1;
    }else if (expression()){
        if (tk == TKPontoEVirgula){
            getToken();
            return 1;
        }
    }
    
    error("';'");
    return 0;
}

int selection_statement(){ 
    printf("Selection statement\n");
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
                }else error("')'");
            }else error("')'");
        }else error("'('");
    }else error("'if'");

    return 0;
}

int statement(){
    printf("Statement\n");
    if(tk == TKIf){
        if (selection_statement()){
            return 1;
        }
    }else if (tk == TKAbreChaves){
        if (compound_statement()){
            return 1;
        }
    }
    else if (expression_statement()){
        return 1;
    }
    
    return 0;
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
    if (statement())
        printf("Compilado com sucesso!");
    else printf("Faca os ajustes no token %s (%s) e tente compilar novamente", tokens[tk-1], lex);
}