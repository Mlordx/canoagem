%{
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"  /* to get the token types that we return */

/* stuff from flex that bison needs to know about: */
extern int yylex();
extern int yyparse();
extern FILE *yyin;

int seed = 1, linhas = 90, colunas = 90, it = 100, tamanhoMinimo = 30, TAM_MIN_BARREIRA = 1, TEMPO_INV = 5;
float fluxoRio = 1, PROB_OBST = 0, DIST_MIN_OBST = 1, PORC_MAX_BARREIRA = 0, MS_INV = 0.03;
 
void yyerror(const char *s);
%}

/* Bison fundamentally works by asking flex to get the next token, which it
returns as an object of type "yystype".  But tokens could be of any
arbitrary data type!  So we deal with that in Bison by defining a C union
holding each of the types of tokens that Flex could return, and have Bison
use that union instead of "int" for the definition of "yystype": */
%union {
	int ival;
	float fval;
}

/* define the constant-string tokens: */
%token ENDL
%token CABECALHO
/* define the "terminal symbol" token types I'm going to use (in CAPS
by convention), and associate each with a field of the union: */
%token <ival> SEED
%token <ival> NLINHAS
%token <ival> NCOLUNAS
%token <ival> ITERACOES
%token <ival> TAMANHO
%token <fval> FLUXO
%token <ival> TAMANHO_OB
%token <fval> MSINV
%token <ival> TINV
%token <fval> MAX_OB
%token <fval> DIS_OB
%token <fval> PROB_OB

%%

programa: 
	inicio parametros ENDL { printf("\n = = = = Fim da verificacao. = = = =\n\n"); }
	;
inicio: 
	CABECALHO { printf("\n\n = = = = Inicio da verificacao! = = = = \n\n"); }
	;
parametros: 
	parametros parametro
	| parametro
	;
parametro: 
	SEED ENDL { printf("Seed escolhida: %d\n", $1); seed = $1; } 
	| NLINHAS ENDL { printf("Numero de linhas: %d\n", $1); linhas = $1; }
	| NCOLUNAS ENDL { printf("Numero de colunas: %d\n", $1); colunas = $1; }
	| ITERACOES ENDL { printf("Numero de iteracoes: %d\n", $1); it = $1; }
	| TAMANHO ENDL { printf("Tamanho de margem minimo: %d\n", $1); tamanhoMinimo = $1; }
	| FLUXO ENDL { printf("Fluxo inicial: %f\n", $1); fluxoRio = $1; }
	| TAMANHO_OB ENDL { printf("HUE1: %f\n", $1); TAM_MIN_BARREIRA = $1; }
	| PROB_OB ENDL { printf("Fluxo inicial: %f\n", $1); PROB_OBST = $1; }
	| MAX_OB ENDL { printf("Fluxo inicial: %f\n", $1); PORC_MAX_BARREIRA  = $1; }
	| DIS_OB ENDL { printf("Fluxo inicial: %f\n", $1); DIST_MIN_OBST  = $1; }
	| MSINV ENDL { printf("MS inv: %f\n", $1); MS_INV  = $1; }
	| TINV ENDL { printf("Tempo inv: %f\n", $1); TEMPO_INV  = $1; }
	| ENDL
;

%%

/* int main() {	
	FILE *myfile = fopen("entradaFlex", "r");
	yyin = myfile;
	do{
		yyparse();
	} while (!feof(yyin));
	return 0;
} */

void yyerror(const char *s) {
	printf("Parse error!  Entrada de parametros incorreta: %s\n", s);
	/* might as well halt now: */
	exit(-1);
}
