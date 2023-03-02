#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int main() {
    char *str = NULL;
    size_t size = 0;
    int read;
    List *list = init_history();
    while (1) {
        printf(">");
        read = getline(&str, &size, stdin);
        if (read == -1 || strcmp(str, "Exit\n") == 0) {
            break; // end of file reached
        }else if( str[0] == '!'){
            int i = 1;
            char *num = malloc(4);
            while( str[i] >= '0' && str[i] <= '9' ){
                num[i - 1] = str[i];
                i++;
            }
            printf("Index = %s",num);
            num[i] = '\0';
            int indx = atoi(num); //converting the string num into the indx
            free(num);//deallocating memory for next check
            printf("\nRetreaving history at %d\n index[%d]: ",indx ,indx); 
            printf("%s \n",get_history(list, indx));           
        }else if( strcmp(str,"History\n") == 0){
            printf("Retreaving all History\n"); 
            print_history(list);
            printf("\n");
        }else if( strcmp(str,"Clear\n") == 0){
            printf("Clearing all History\n"); 
            free_history(list);
            list = init_history();
            printf("...History Cleared\n");
        }
        char **tokens = tokenize(str);
        for(int i = 0; tokens[i] != NULL; i++){
            add_history(list, tokens[i]);
        }
    }
    return 0;
}