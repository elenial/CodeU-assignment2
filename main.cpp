#include <cstdio>
#include <struct.h>
#include <climits>
using namespace std;

struct node {
    int key;
    node *left;
    node *right;
};

void insert(int key, node *root, node *last) {
    
}

bool found(int key, node *root) {
    if (root->left == NULL && root->right == NULL) 
        return key == root->key;
    else if (root -> left == NULL) 
        return found(key, root->right);
    else if (root -> right == NULL)
        return found(key, root->left);
    else 
        return found(key, root->left) || found(key, root->right);
}

void printancestors(int key, node *root) {
    if (found(key, root->left)) {
        printf("%d ", root->key);
        printancestors(key, root->left);
    } else if (found(key, root->right)) {
        printf("%d ", root->key);
        printancestors(key, root->right);
    } else 
        throw "Key doesn't exist in this tree";
}

void lowestcommonancestor(int key1, int key2, node *root) {
    
}



int main()
{
   
    return 0;
}

