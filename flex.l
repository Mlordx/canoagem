%option noinput nounput always-interactive	
%{
#include "parser.h"

%}
%%
[ \t]          ;
"PARAMETROS PARA O PROGRAMA." { return CABECALHO; }
"Seed: "[0-9]+           { sscanf(yytext, "Seed: %d", &yylval.ival); return SEED; }
"Linhas: "[0-9]+         { sscanf(yytext, "Linhas: %d", &yylval.ival); return NLINHAS; }
"Colunas: "[0-9]+        { sscanf(yytext, "Colunas: %d", &yylval.ival); return NCOLUNAS; }
"Iteracoes: "[0-9]+      { sscanf(yytext, "Iteracoes: %d", &yylval.ival); return ITERACOES; }
"Tamanho minimo do rio: "[0-9]+         { sscanf(yytext, "Tamanho minimo do rio: %d", &yylval.ival); return TAMANHO; }
"Tamanho minimo do obstáculo: "[0-9]+         { sscanf(yytext, "Tamanho minimo do obstáculo: %d", &yylval.ival); return TAMANHO_OB; }
"Fluxo: "[0-9]+\.[0-9]+ { sscanf(yytext, "Fluxo: %f", &yylval.fval); return FLUXO; }
"Probabilidade de obstáculo: "[0-9]+\.[0-9]+ { sscanf(yytext, "Probabilidade de obstáculo: %f", &yylval.fval); return PROB_OB; }
"Tamanho max do obstáculo: "[0-9]+\.[0-9]+ { sscanf(yytext, "Tamanho max do obstáculo: %f", &yylval.fval); return MAX_OB; }
"Distância mínima entre obstáculos: "[0-9]+\.[0-9]+ { sscanf(yytext, "Distância mínima entre obstáculos: %f", &yylval.fval); return DIS_OB; }
"Tempo de invunerabilidade: "[0-9]+ { sscanf(yytext, "Tempo de invunerabilidade: %d", &yylval.ival); return TINV; }
"MS entre frames durante invunerabilidade: "[0-9]+\.[0-9]+ { sscanf(yytext, "MS entre frames durante invunerabilidade: %f", &yylval.fval); return MSINV; }
\n             { return ENDL; }
.              ;
%%



