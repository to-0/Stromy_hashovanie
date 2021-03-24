//
// Created by tomas on 20. 3. 2021.
//

#ifndef ZADANIE2_HASHOVANIE_MOJE_H
#define ZADANIE2_HASHOVANIE_MOJE_H

#endif //ZADANIE2_HASHOVANIE_MOJE_H
typedef struct element {
    int id;
    char name[50];
    char app_name[50];
    char email[50];
}ELEMENT;
long hash(char *a);
ELEMENT **create(int n);
int h_insert(ELEMENT *table[],ELEMENT *e, int *size);
void show_hash_table(ELEMENT *table[],int size);
void generate_hash_table();