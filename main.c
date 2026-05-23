#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
const char *keyword_names[] = {"INT", "KEYWORD", "SEPARATOR"};
int tokencount = 0;
typedef enum{
    INT,
    KEYWORD,
    SEPARATOR,
} TokenType;

typedef struct{
    TokenType type;
    char *value;
} Token;

Token generate_keyword(char *current, FILE* file){
    Token token;
    char *keyword = malloc(100 * sizeof(char));
    int i = 0;
    while(*current != EOF && isalpha(*current)){
        keyword[i] = *current;
        i++;
        *current = fgetc(file);
    }
    // char* target = "exit";
    if (!strcmp(keyword, "exit")){
        token.type = KEYWORD;
        token.value = "EXIT";
    }
    else{
        token.type = SEPARATOR;
    }
    return token;
}

Token generate_number(char *current, FILE* file){
    Token token;
    token.type = INT;
    char *value = malloc(100 * sizeof(char));
    int i = 0;
    while(*current != EOF && isdigit(*current)){
        value[i] = *current;
        i++;
        *current = fgetc(file);
    }
    token.value = value;
    return token;
}

// Printing all the tokens
// void printTokens(Token *tokens){

// }


// lexer converts the code into tokens
Token *lexer(FILE *file){
    char current = fgetc(file);
    Token *tokenarray = malloc(100*sizeof(Token));
    int i = 0;
    while(current != EOF){
        tokencount++;
        if(current == ';' || current == '(' || current == ')'){
            Token test_separator;
            test_separator.type = SEPARATOR;
            test_separator.value = malloc(2*sizeof(char));
            test_separator.value[0] = current;
            test_separator.value[1]='\0';
            tokenarray[i] = test_separator;
        }
        else if(isdigit(current)){
            // return all the consecutive numbers as one whole number
            // printf("FOUND DIGIT : %d\n", (int)(current - '0') );
            Token test_literal = generate_number(&current, file);
            tokenarray[i] = test_literal;
            i++;
            continue;
        }
        else if(isalpha(current)){
            // return all the consecutive characters as one whole string
            Token test_keyword = generate_keyword(&current, file);
            tokenarray[i] = test_keyword;
            i++;
            continue;
        }
        current = fgetc(file);
        i++;
    }
    return tokenarray;
}
int main(){
    FILE *file;
    file = fopen("test.unn", "r");
    Token *array = lexer(file);

    for(int i=0; i<5; i++){
        printf("%s", array[i].value);
    }
}
