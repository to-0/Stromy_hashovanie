#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    int key;
    char name[50];
    struct node *left;
    struct node *right;
    struct node *parent;
}NODE;
NODE *root = NULL;
void preorder(NODE *curr){
    if(curr==NULL)
        return;
    printf("%d ",curr->key);
    preorder(curr->left);
    preorder(curr->right);
}
void write_tree(NODE *n){
    if(n!=NULL){
        putchar('(');
    }
    if(n==NULL){
        //putchar(')');
        return;
    }
    printf("%d",n->key);
    write_tree(n->left);
    if(n->right == NULL){
        putchar(')');
        return;
    }
    write_tree(n->right);
    putchar(')');
}
void rotate_right(NODE **n){ //otacam okolo n
    NODE *left_child = (*n)->left; //zoberiem childa
    NODE *child_right = left_child->right;

    NODE *temp = *n; //ulozim si aj n podla ktoreho idem rotovat
    *n = left_child; //childa posuniem hore
    (*n)->parent = temp->parent;
    (*n)->right  = temp; //parenta doprava
    temp->left =  child_right; //na lavu stranu parenta napojim to co mal child  napravo
    if(temp->parent!=NULL){ //ak ten node predtym mal nejakeho rodica, musim este z toho rodica napojit
        if(temp->key < temp->parent->key){
            temp->parent->left = *n;
        }
        else temp->parent->right = *n;
    }
    temp->parent = *n;


}
void rotate_left(NODE **n){ //otacam okolo
    NODE *right_child = (*n)->right; //zoberiem   praveho childa
    NODE *child_left = right_child->left; // ulozim si jeho lavu cast
    NODE *temp = *n; //ulozim si aj n podla ktoreho idem rotovat
    *n = right_child; //childa posuniem hore namiesto n
    (*n)->parent = temp->parent; //nastavim jeho parenta na parenta toho za ktoreho som ho vymenil
    (*n)->left  = temp; //predosle n hodim doprava, to bol ten predosly parent
    temp->right =  child_left; //na lavu stranu byvaleho parenta napojim to co mal child  napravo
    if(temp->parent!=NULL){ //ak ten node predtym mal nejakeho rodica, musim este z toho rodica napojit
        if(temp->key < temp->parent->key){
            temp->parent->left = *n;
        }
        else temp->parent->right = *n;
    }
    temp->parent = *n; //nastavim jeho parenta na nove n
}
NODE *splay(NODE **n){
    printf("Idem splayovat: %d\n",(*n)->key);
    while((*n)->parent!=NULL){
        NODE *parent;
        parent = (*n)->parent;
        if((*n)->parent->parent == NULL){ //mam iba jedneho parenta
            printf("Ma iba jedneho parenta a to:%d\n",(*n)->parent->key);
            if(parent->key > (*n)->key){ //moj node je nalavo od parenta cize tocim doprava
                rotate_right(&parent);
            }
            else rotate_left(&parent);
        }
        else{ //mam parenta aj grandparenta
            NODE *grandparent = parent->parent;
            printf("Mam parenta:%d aj grandparenta: %d\n",parent->key,grandparent->key);
            if(parent->key > (*n)->key && grandparent->key > parent->key){ //rovna ciara smerom doprava, node n je uplne vlavo
                printf("\n prva rotacia \n");
                rotate_right(&grandparent);
                preorder(grandparent);
                rotate_right(&parent);
                printf("\n druha rotacia \n");
                preorder(parent);
            }
            else if(parent->key < (*n)->key && grandparent->key < parent->key)//rovno smerom dolava, node n je uplne vpravo
            {
                rotate_left(&grandparent);
                printf("\n prva rotacia \n");
                preorder(grandparent);
                rotate_left(&parent);
                printf("\n druha rotacia \n");
                preorder(parent);
            }
            else if(parent->key > (*n)->key && grandparent->key < parent->key){ //
                rotate_right(&parent);
                printf("\n prva rotacia \n");
                preorder(grandparent);
                rotate_left(&grandparent);
                printf("\n druha rotacia \n");
                preorder(grandparent);
            }
            else{
                rotate_left(&parent);
                printf("\n prva rotacia \n");
                preorder(grandparent);
                rotate_right(&grandparent);
                printf("\n druha rotacia \n");
                preorder(grandparent);
            }
        }
    }
    root = *n;
}

void insert(NODE *cur,NODE **n){
    printf("Root: %d cur:%d\n",root->key,cur->key);
    if(root==NULL){

    }
    if(cur->key > (*n)->key){ // node je mensi ako sucasny cize idem smerom dolava
        if(cur->left ==NULL) {
            (*n)->parent = cur;
            cur->left = *n;
            printf("Before splay:\n");
            preorder(root);
            putchar('\n');
            splay(n);
            printf("After splay:\n");
            preorder(root);
            putchar('\n');
        }
        else
            insert(cur->left,n);
    }
    else{
        if(cur->right ==NULL){
            (*n)->parent = cur;
            printf("Nastavil som parenta %d na cur: %d\n",(*n)->key,cur->key);
            cur->right = *n;
            printf("Before splay\n");
            preorder(root);
            putchar('\n');
            splay(n);
            printf("After splay:\n");
            preorder(root);
            putchar('\n');
        }
        else
            insert(cur->right,n);
    }
}
NODE *generate(){
    NODE *n;
    FILE *f = fopen("tree.txt","r");
    if (f==NULL) return NULL;
    char line[50];
    int key;
    while (fscanf(f,"%s %d",line,&key)==2){
        if(root ==NULL){
            root = (NODE *)malloc(sizeof(NODE));
            root->key = key;
            root->parent = NULL;
            strcpy(root->name,line);
            root->left = NULL;
            root->right = NULL;
        }
        else{
            n = (NODE *)malloc(sizeof(NODE));
            n->key = key;
            strcpy(n->name,line);
            n->left = NULL;
            n->right = NULL;
            insert(root,&n);
        }
    }
    return root;
}
int main() {
    root = generate();
    preorder(root);
    putchar('\n');
    write_tree(root);
   // rotate_right(&(root->left));
    //putchar('\n');
    //preorder(root);
    return 0;
}
