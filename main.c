#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef enum{
    SEMI,
    OPEN_PAREN,
    CLOSE_PAREN,
} TypeSeperator;

typedef enum{
    EXIT,
    DEFAULT,
} TypeKeyword;

typedef enum{
    INT,
    FLOAT,
} TypeLiteral;

typedef struct {
  TypeKeyword type;
} TokenKeyword;

typedef struct {
  TypeLiteral type;
  int value;
} TokenLiteral;

typedef struct {
  TypeSeperator type;
} TokenSeperator;

TokenKeyword generate_keyword(char *current, FILE* file){
    TokenKeyword token;
    char *keyword = malloc(100 * sizeof(char));
    int i = 0;
    while(*current != EOF && isalpha(*current)){
        keyword[i] = *current;
        i++;
        *current = fgetc(file);
    }
    char* target = "exit";
    if (!strcmp(keyword, target)){
        token.type = EXIT;
    }
    else{
        token.type = DEFAULT;
    }

    return token;
}

TokenLiteral generate_literal(char *current, FILE* file){
    TokenLiteral token;
    token.type = INT;
    char *value = malloc(100 * sizeof(char));
    printf("FOUND NUMBER : ");
    int i = 0;
    while(*current != EOF && isdigit(*current)){
        value[i] = *current;
        i++;
        *current = fgetc(file);
    }
    token.value = atoi(value);
    return token;
}

// lexer converts the code into tokens
void lexer(FILE *file){
    char current = fgetc(file);

    while(current != EOF){
        if(current == ';'){
            printf("FOUND SEMICOLON\n");
        }
        else if (current == '(') {
            printf("FOUND OPEN PAREN\n");
        }
        else if(current == ')'){
            printf("FOUND CLOSED PAREN\n");
        }
        else if(isdigit(current)){
            // return all the consecutive numbers as one whole number
            // printf("FOUND DIGIT : %d\n", (int)(current - '0') );
            TokenLiteral token = generate_literal(&current, file);
            printf("%d", token.value);
            continue;
        }
        else if(isalpha(current)){
            // return all the consecutive characters as one whole string
            // generate_string(&current, file);
            TokenKeyword token = generate_keyword(&current, file);
            printf("%d", token.type);
            continue;
        }
        current = fgetc(file);
    }
}
int main(){
    FILE *file;
    file = fopen("test.unn", "r");
    lexer(file);
}
