#include <stdio.h>
#include <string.h>
#include "function.c"
#include "lex.yy.c"


int main() {

 	struct SymbolTable symbolTable;
    initSymbolTable(&symbolTable);

    while (1) {
        int choice;
        char filename[20];

        printf("\n\033[0;32mEscolha um arquivo para analisar (1 a 9) ou 0 para sair: \033[0m");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                return 0;
            case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
                sprintf(filename, "teste%d.txt", choice);
                break;
            default:
                printf("n\033[0;32mEscolha Inválida. Escolha um arquivo para analisar (1 a 9) ou 0 para sair: \033[0m\n");
                continue;
        }


        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo: %s\n", filename);
            continue;
        }

        printf("Nome do arquivo: %s\n", filename);
        yyin = file;

		char identifier[20];
        int token;

        while ((token = yylex()) != 0) {
            const char* tokenName = (token >= 0 && token <= 41) ? tokenNames[token] : "UNKNOWN";

            if (token == 40) {  // "IDENTIFIER"
   
                strcpy(identifier, yytext); // copia o identifier para a variavel
                int id = getIdentifierID(&symbolTable, identifier);
                printf("Token: %3d, Token name: %10s, No arquivo: %5s, ID: %d\n", token, tokenName, yytext, id);
            } else {
                printf("Token: %3d, Token name: %10s, No arquivo: %5s\n", token, tokenName, yytext);
            }
        }
  		

		printf("\n\033[0;32mTabela de simbolo:  \033[0m\n");
		for(int i = 0; i < symbolTable.count; i++){
			printf("ID: %3d, Identifier: %s\n", symbolTable.id[i], symbolTable.identifiers[i]);
		}

		clearSymbolTable(&symbolTable);

		fclose(file);
    }
      return 0;
}