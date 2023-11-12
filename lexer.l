%{
#include <stdio.h>
#include <string.h>
%}

%option noyywrap

%{
#define PROGRAM 1
#define DECLARE 2
#define BEGIN 3
#define END 4
#define IF 5
#define THEN 6
#define ELSE 7
#define DO 8
#define FOR 9
#define WHILE 10
#define READ 11
#define WRITE 12
#define NOT 13
#define AND 14
#define OR 15
#define MOD 16
#define SEMICOLON 17
#define ASSIGN 18
#define LPAREN 19
#define RPAREN 20
#define LBRACKET 21
#define RBRACKET 22
#define COMMA 23
#define COLON 24
#define GT 25
#define LT 26
#define GE 27
#define LE 28
#define NE 29
#define EQ 30
#define PLUS 31
#define MINUS 32
#define MULT 33
#define DIV 34
#define SHIFTLEFT 35
#define SHIFTRIGHT 36
#define TRIPLELEFT 37
#define TRIPLERIGHT 38
#define INT_LITERAL 39
#define IDENTIFIER 40
#define STRING_LITERAL 41

%}

%%

"program"       { return PROGRAM; }
"declare"       { return DECLARE; }
"begin"         { return BEGIN; }
"end"           { return END; }
"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"do"            { return DO; }
"for"           { return FOR; }
"while"         { return WHILE; }
"read"          { return READ; }
"write"         { return WRITE; }
"not"           { return NOT; }
"and"           { return AND; }
"or"            { return OR; }
"mod"           { return MOD; }

[ \t\n]          ;  // Ignora espaços em branco e quebras de linha
";"             { return SEMICOLON; }
":="            { return ASSIGN; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
","             { return COMMA; }
":"             { return COLON; }
">"             { return GT; }
"<"             { return LT; }
">="            { return GE; }
"<="            { return LE; }
"<>"            { return NE; }
"="             { return EQ; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }
"<<"            { return SHIFTLEFT; }
">>"            { return SHIFTRIGHT; }
"<<<"           { return TRIPLELEFT; }
">>>"           { return TRIPLERIGHT; }

[0-9]+          { return INT_LITERAL; }
[a-zA-Z][a-zA-Z0-9]*  { return IDENTIFIER; }
\"[^\"]*\"       { return STRING_LITERAL; }

.               { fprintf(stderr, "Caractere inesperado: %s\n", yytext); }

%%


int main() {
	int choice;
    char filename[20];

    printf("Escolha um arquivo para analisar (1 a 7): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            sprintf(filename, "teste%d.txt", choice);
            break;
        default:
            printf("Escolha inválida. Escolha um número de 1 a 7.\n");
            return 1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return 1;
    }
printf("Nome do arquivo: %s\n", filename);

	yyin = file;

    int token;

    while ((token = yylex()) != 0) {

        const char* tokenName = (token >= 0 && token <= 41) ? tokenNames[token] : "UNKNOWN";

        printf("%d (%s) %s\n", token, tokenName, yytext);
    }

	fclose(file);
    return 0;
}