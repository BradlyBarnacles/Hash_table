#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    struct node* next;
    char* key;
    char* val;
}node;

int hash(char* string){
    int a = 45;
    int b = 110;
    int total = 83;
    int i = 0;
    while (string[i] != '\0'){
        total = (total*b + a*(int)string[i])%256;
        i++;
    }
    return total;
}

void add_item(struct node** dict, char* key, char* val){
    struct node* ptr = dict[hash(key)];
    while (ptr != NULL){
        if (strcmp(ptr->key,key) == 0){
            free(ptr->val);
            ptr->val = malloc(strlen(val));
            strcpy(ptr->val, val);
            return;
        }
        ptr =  ptr->next;
    }
    struct node* new_node;
    new_node = malloc(sizeof(node));
    new_node->val = malloc(strlen(val));
    strcpy(new_node->val, val);

    new_node->key = malloc(strlen(key));
    strcpy(new_node->key, key);

    new_node->next = dict[hash(key)];
    dict[hash(key)] = new_node;
    return;
}

char* find_item(struct node** dict, char* key){
    struct node* ptr = dict[hash(key)];
    while (ptr != NULL){
        if (strcmp(ptr->key,key) == 0){
            return ptr->val;
        }
        ptr =  ptr->next;
    }
    return "oops";
}

int main(){
    int size = 8;
    int option;
    char* key;
    key = malloc(1000);
    char* val;
    val = malloc(1000);
    struct node* dict[256];
    for (int i = 0; i<256; i++){
        dict[i] = NULL;
    }

    while (option != 4){
        printf("menu\n1) add entry\n2) find key \n3) check hash\nchoose option> ");
        scanf("%d", &option);
        if (option == 1){
            printf("choose a key> ");
            scanf("%s", key);
            printf("choose a value> ");
            scanf("%s", val);
            add_item(dict, key, val);
            printf("item %s:%s added\n", key, val);

        }
        else if (option == 2){
            printf("choose a key> ");
            scanf("%s", key);

            val = find_item(dict, key);
            printf("key %s had value %s\n", key, val);
        }
        else if (option == 3){
            printf("choose a key> ");
            scanf("%s", key);
            printf("key %s has hash %d\n", key, hash(key));
        }
    }
}

