%option noinput nounput always-interactive	
%{
#include "parser.tab.h"

%}
%%
[ \t]          ;
"PARAMETROS PARA O PROGRAMA." { return CABECALHO; }
"Seed: "[0-9]+           { sscanf(yytext, "%*s %d", &yylval.sval); return SEED; }
"linhas: "[0-9]+         { sscanf(yytext, "%*s %d", &yylval.lval); return NLINHAS; }
"colunas: "[0-9]+        { sscanf(yytext, "%*s %d", &yylval.cval); return NCOLUNAS; }
"iteracoes: "[0-9]+      { sscanf(yytext, "%*s %d", &yylval.ival); return ITERACOES; }
"minimo: "[0-9]+         { sscanf(yytext, "%*s %d", &yylval.tval); return TAMANHO; }
"padrao: "[0-9]+\.[0-9]+ { sscanf(yytext, "%*s %f", &yylval.fval); return FLUXO; }
\n             { return ENDL; }
.              ;
%%
