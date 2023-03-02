#include <stdlib.h>
#include <stdio.h>
#ifndef _TOKENIZER_
#define _TOKENIZER_

int space_char(char c){
   if(c == ' ' || c == '\t' || c == '\n' ){
      return 1;
   }
   return 0;
}
int non_space_char(char c){
   if(c == ' ' || c == '\t'|| c == '\0' || c == '\n'){
      return 0;
   }
   return 1;
}
char *word_start(char *str){
   char *p = str;
   while(non_space_char(*p) == 0 && *p != '\0'){
      p++;
   }
   return p;
}
/* Returns a pointer terminator char following *word */
char *word_terminator(char *word) {
    char *p = word;
    while (!space_char(*p) && *p != '\0') {
        p++;
    }
    return p;
}


/* Counts the number of words in the string argument. */
int count_words(char *str){
    int count = 0;
    str = word_start(str);
    while(*str != '\0' ){
        str = word_terminator(str);
        count++;
        str = word_start(str);
    }
    return count;
}

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len){
    char *outStr = (char*)malloc(len + 1); 
    for (int i = 0; i < len; i++) {
        outStr[i] = inStr[i];
    }
    outStr[len] = '\0'; 
    return outStr;
}


/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str){
    short wordCount = count_words(str);
    char **words = (char**)malloc((wordCount+1) * sizeof(char *));
    for(int i = 0; i < wordCount; i++){
        char *curr = word_start(str);
        str = word_terminator(curr);
        words[i] = copy_str(curr, str - curr);
    }
    words[wordCount] = NULL;
    return words;
    
}
/* Prints all tokens. */
void print_tokens(char **tokens){
    for(int i = 0; tokens[i] != NULL; i++){
        printf("\nTokens[%d]: %s\n",i,tokens[i]);
    }
    
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens){
    int i = 0;
    while(tokens[i] != NULL){
        free(tokens[i]);
        i++;
    }
    free(tokens);
}


#endif
