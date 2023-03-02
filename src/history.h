#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef _HISTORY_
#define _HISTORY_

typedef struct s_Item {
  int id;
  char *str;
  struct s_Item *next;
} Item;

typedef struct s_List {
  struct s_Item *root;
} List;

/* Initialize the linked list to keep the history. */
List* init_history() {
    List *list = (List*)malloc(sizeof(List));
    list->root = NULL;
    return list;
}
/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str){
    Item *node = (Item*) malloc(sizeof(Item));
    int indx = 0;
    node->str = str;
    node->next = NULL;
    if (list->root == NULL) {
        list->root = node;
        list->root->id = indx;
    } else {
        Item *current = list->root;
        indx++;
        while (current->next != NULL) {
            current = current->next;
            indx++;
        }
        current->next = node;
        current->next->id = indx;
    }

}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id){
  Item *current = list->root;
  int indx = 0;
  while( current != NULL && indx != id){
    current = current->next;
    indx++;
  }
  if(indx == id ){
    return current->str;
  }
  printf("\nID not in history");
  return NULL;
}

/*Print the entire contents of the list. */
void print_history(List *list){
  Item *current = list->root;
  while( current != NULL){
    printf("\nHistory[%d]: %s", current->id, current->str);
    current = current->next;
  }
}

/*Free the history list and the strings it references. */
void free_history(List *list){
  Item *current = list->root;
  while(current != NULL){
    Item *next = current->next;
    free(current->str);
    free(current);
    current = next;
  }
  free(list);
}
#endif
