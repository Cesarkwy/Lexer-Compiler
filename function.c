#include <stdio.h>
#include <string.h>

#define MAX_IDENTIFIERS 100
#define MAX_IDENTIFIER_LENGTH 20

struct SymbolTable {
    char identifiers[MAX_IDENTIFIERS][MAX_IDENTIFIER_LENGTH];
    int id[MAX_IDENTIFIERS];
    int count;
};

void initSymbolTable(struct SymbolTable* table) {
    table->count = 0;
}

int getIdentifierID(struct SymbolTable* table, const char* identifier) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->identifiers[i], identifier) == 0) {
            return table->id[i];
        }
    }

    if (table->count < MAX_IDENTIFIERS) {
        strcpy(table->identifiers[table->count], identifier);
        table->id[table->count] = table->count + 1;  // ID único
		table->count++;
        return table->count;
    }

    return -1;
}

void clearSymbolTable(struct SymbolTable* table) {
    table->count = 0;
}


// Mapeamento dos nomes dos tokens
const char* tokenNames[] = {
    "UNKNOWN",
    "PROGRAM",
    "DECLARE",
    "BEGIN",
    "END",
    "IF",
    "THEN",
    "ELSE",
    "DO",
    "FOR",
    "WHILE",
    "READ",
    "WRITE",
    "NOT",
    "AND",
    "OR",
    "MOD",
    "SEMICOLON",
    "ASSIGN",
    "LPAREN",
    "RPAREN",
    "LBRACKET",
    "RBRACKET",
    "COMMA",
    "COLON",
    "GT",
    "LT",
    "GE",
    "LE",
    "NE",
    "EQ",
    "PLUS",
    "MINUS",
    "MULT",
    "DIV",
    "SHIFTLEFT",
    "SHIFTRIGHT",
    "TRIPLELEFT",
    "TRIPLERIGHT",
    "INT_LITERAL",
    "IDENTIFIER",
    "STRING_LITERAL"
};