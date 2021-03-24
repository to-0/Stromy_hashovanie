//
// Created by tomas on 20. 3. 2021.
//
#include "splay_tree.h"
#include "avl_tree.h"
#include "hashovanie_m.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Node *generate_avl(){
    struct Node *n;
    FILE *f = fopen("tree2.txt","r");
    if (f==NULL) return NULL;
    char line[150];
    char temp[50];
    int key;
    struct Node *avl_root = NULL;
    while (fgets(line,150,f)!=NULL){
        n = (NODE *)malloc(sizeof(NODE));
        char *point = strchr(line,',');
        int i = point-line; //zistim index prvej ciarky
        int length = strlen(line);
        strncpy(temp,line,i);
        int key;
        sscanf(temp,"%d",&(n->key));
        //printf("KEy:%d\n",n->key);
        char temp_line[50];
        strncpy(temp_line,line+i+1,length-i);
        strncpy(line,line+i+1,length-i); //seknem subor pokracujem iba so zvyskom

        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(temp,line,i);
        sscanf(temp,"%s",n->app_name);
        strncpy(line,line+i+1,length-i);

        point = strchr(line,',');
        i = point-line;
        length = strlen(line);
        strncpy(temp,line,i);
        sscanf(temp,"%s",n->name);
        strncpy(line,line+i+1,length-i);

        length = strlen(line);
        sscanf(line,"%s",n->email);
        n->left = NULL;
        n->right = NULL;
        n->height = 1;
        avl_root = Insert(avl_root,n);
    }
    return avl_root;
}
void test_stromy(){
    int keys[100000];
    int i;
    for(i = 0;i<100000;i++){ //vytvorim si pole klucov podla ktorych budem hladat aj v splay aj v avl aby som to vedel porovnat
        int num = (rand() %(500000 - 1000 + 1)) + 100;
        keys[i]=num;
    }
    clock_t start, end;
    double time;

    start = clock();
    NODE *root_splay = generate();
    NODE *search_node;
    for(i=0;i<100000;i++){
        search_node = search(keys[i],root_splay);
        if(search_node != NULL){
            printf("App name:%s  Last name:%s Email:%s  Key%d\n",search_node->app_name,
                    search_node->name, search_node->email,search_node->key);
        }
    }
    end =  clock();
    time = ((double) (end - start)) / CLOCKS_PER_SEC*1000;
    printf("%f\n",time);

    //AVL STROMY TEST
    struct Node *root_avl = generate_avl();
    preorder_avl(root_avl);
}


int main() {
    //root = generate();
   // preorder(root);
    printf("\npo prvom testovani\n");
    putchar('\n');
    //search(20,root);
    //preorder(root);
    //search(55,root);
    //preorder(root);
    ELEMENT **e = create(50);
    //printf("Tu\n");
    //generate_hash_table();
    test_stromy();
    return 0;
}