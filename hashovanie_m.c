//
// Created by tomas on 20. 3. 2021.
//

#include "hashovanie_moje.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
long hash(char* a) {
    int len = strlen(a);
    long h = 0;
    for (int i = 0; i < len; i++) {
        h = 31*h + (int)a[i];
    }
    return h;
}
ELEMENT *create(int n){
    ELEMENT *e = (ELEMENT *)calloc(n*2+1,sizeof(ELEMENT));
    return e;
}
ELEMENT *insert(ELEMENT table[],ELEMENT *e,int *size){
    long h = hash(e->app_name);
    int i  = h % *size;
    if(table[i]->app_name==NULL){

    }
}