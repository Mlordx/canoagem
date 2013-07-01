%{
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"  /* para termos acesso ao tipo dos tokens que retornamos */

/* funções do flex que o bison necessita reconhecer: */
extern int yylex();
extern int yyparse();
extern FILE *yyin;

int seed = 1, linhas = 90, colunas = 90, it = 100, tamanhoMinimo = 30, TAM_MIN_BARREIRA = 1, TEMPO_INV = 5;
float fluxoRio = 1, PROB_OBST = 0, DIST_MIN_OBST = 1, PORC_MAX_BARREIRA = 0, MS_INV = 0.03;
 
void yyerror(const char *s);
%}

/* Bison pede ao flex para encontrar o próximo token. O flex, então, retorna
um objeto do tipo "yystype". O problema é que os tokens podem ser retornados
como um objeto de qualquer tipo arbitrário de dado. Sendo assim, criamos
uma "union" em linguagem C que cria objetos dos tipos que melhor se
adequam às nossas necessidades.                                              */
%union {
	int ival;
	float fval;
}

/* define os tokens não-terminais: */
%token ENDL
%token CABECALHO
/* define os tokens terminais, em maiúsculo(por convenção),
e os associa ao campo respectivo da union.                 */
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
	| TAMANHO_OB ENDL { printf("Tamanho minimo do obstaculo: %f\n", $1); TAM_MIN_BARREIRA = $1; }
	| PROB_OB ENDL { printf("Probabilidade de obstaculo: %f\n", $1); PROB_OBST = $1; }
	| MAX_OB ENDL { printf("Tamanho maximo do obstaculo: %f\n", $1); PORC_MAX_BARREIRA  = $1; }
	| DIS_OB ENDL { printf("Distancia minima entre obstaculos: %f\n", $1); DIST_MIN_OBST  = $1; }
	| MSINV ENDL { printf("MS entre frames de invulnerabilidade: %f\n", $1); MS_INV  = $1; }
	| TINV ENDL { printf("Tempo de invulnerabilidade: %f\n", $1); TEMPO_INV  = $1; }
	| ENDL
;

%%

void yyerror(const char *s) {
	printf("Parse error!  Entrada de parametros incorreta: %s\n", s);
	/* encerra programa devido a inconsistencia de parametros: */
	exit(-1);
}
