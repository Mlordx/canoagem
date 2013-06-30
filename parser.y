%{
#include <stdio.h>
#include <stdlib.h>

#include "parametros.h"
#include "parser.tab.h"  /* to get the token types that we return */

/* stuff from flex that bison needs to know about: */
extern int yylex();
extern int yyparse();
extern FILE *yyin;
 
void yyerror(const char *s);
%}

/* Bison fundamentally works by asking flex to get the next token, which it
returns as an object of type "yystype".  But tokens could be of any
arbitrary data type!  So we deal with that in Bison by defining a C union
holding each of the types of tokens that Flex could return, and have Bison
use that union instead of "int" for the definition of "yystype": */
%union {
	int sval;
	int lval;
	int cval;
	int ival;
	int tval;
	float fval;
}

/* define the constant-string tokens: */
%token ENDL
%token CABECALHO
/* define the "terminal symbol" token types I'm going to use (in CAPS
by convention), and associate each with a field of the union: */
%token <sval> SEED
%token <lval> NLINHAS
%token <cval> NCOLUNAS
%token <ival> ITERACOES
%token <tval> TAMANHO
%token <fval> FLUXO

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
	| ENDL
;

%%

int main() {	
	FILE *myfile = fopen("entradaFlex", "r");
	yyin = myfile;
	do{
		yyparse();
	} while (!feof(yyin));
	return 0;
}

void yyerror(const char *s) {
	printf("Parse error!  Entrada de parametros incorreta: %s\n", s);
	/* might as well halt now: */
	exit(-1);
}
