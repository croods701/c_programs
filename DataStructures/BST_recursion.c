#include <stdio.h>
#include <stdlib.h>

#define New_Mem(type) ((type *)malloc(sizeof(type)))
#define NL printf("\n")
#define SEP '-'

//Utilities Function
int ask_choice(char *ques, int m, int n)
{
    int ch;
    printf("%s", ques);
    scanf("%d", &ch);
    while (ch < m || ch > n)
    {
        printf("%s", ques);
        scanf("%d", &ch);
    }
    return ch;
}

void draw_seprator(char sep, int len)
{
    for (int i = 0; i < len; i++)
    {
        putchar(sep);
    }
    printf("\n");
}

//BST structs
typedef struct BSTnode_t
{
    int key;
    struct BSTnode_t *right, *left;
} BSTnode;

//BST Functions
BSTnode *create_BSTnode(int key)
{
    BSTnode *new_node = New_Mem(BSTnode);
    new_node->key = key;
    new_node->right = NULL;
    new_node->left = NULL;

    return new_node;
}

BSTnode *min_BSTnode(BSTnode *root)
{
    BSTnode *temp_BSTnode = root;
    while (temp_BSTnode->left != NULL)
        temp_BSTnode = temp_BSTnode->left;
    return temp_BSTnode;
}

BSTnode *insert_key_BST(BSTnode *root, int key)
{
    if (root == NULL)
        return create_BSTnode(key);

    if (root->key > key)
        root->left = insert_key_BST(root->left, key);

    if (root->key < key)
        root->right = insert_key_BST(root->right, key);

    return root;
}

int delete_key_BST(BSTnode **root, int key)
{
    if (!root)
        return -2;

    BSTnode *current = *root;

    BSTnode *parent = current;

    while (current->key != key)
    {
        parent = current;
        if (current == NULL)
            return -1;
        if (key > current->key)
            current = current->right;
        else
            current = current->left;
        if (current == NULL)
            return -1;
    }

    if (current->left == NULL && current->right == NULL)
    {
        if (parent == current)
            *root = NULL;
        else if (parent->key > current->key)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(current);
    }

    else if (current->left == NULL)
    {
        if (current == parent)
            *root = current->right;
        else if (parent->key > key)
            parent->left = current->left;
        else
            parent->right = current->left;
        free(current);
    }

    else if (current->right == NULL)
    {
        if (current == parent)
            *root = current->left;
        else if (parent->key > key)
            parent->left = current->left;
        else
            parent->right = current->left;
        free(current);
    }

    else
    {
        BSTnode *min = min_BSTnode(current->right);
        current->key = min->key;
        min->key = key;
        delete_key_BST(&current->right, key);
    }
}

//For Hooks
typedef void (*callback)(void *context);

//Recursive Travesing Functions
int traverse_inorder_recursive(BSTnode *root, callback hook)
{
    if (root == NULL)
        return 0;
    traverse_inorder_recursive(root->left, hook);
    hook(root);
    traverse_inorder_recursive(root->right, hook);
}

void traverse_preorder_recursive(BSTnode *root, callback hook)
{
    if (root == NULL)
        return;
    hook(root);
    traverse_preorder_recursive(root->left, hook);
    traverse_preorder_recursive(root->right, hook);
}

int traverse_postorder_recursive(BSTnode *root, callback hook)
{
    if (root == NULL)
        return 0;
    traverse_postorder_recursive(root->left, hook);
    traverse_postorder_recursive(root->right, hook);
    hook(root);
}

//Callback function for print
void print_BSTnode(void *node)
{
    printf(" %d ", ((BSTnode *)node)->key);
}

//Recursive search
BSTnode *search_BST(BSTnode *root, int key)
{
    while (root)
    {
        if (root->key == key)
            return root;
        if (root->key > key)
            return search_BST(root->left, key);
        else
            return search_BST(root->right, key);
    }
    return NULL;
}

void print_welcome_message()
{
    draw_seprator(SEP, 40);
    printf("\t Welcome to BST Program\n");
    draw_seprator(SEP, 40);
    printf("1. Add Key \n");
    printf("2. Delete Key \n");
    printf("3. Search Key \n");
    printf("4. Travese BST \n");
    printf("5. Exit \n");
}

void print_traverse(BSTnode *root)
{
    draw_seprator(SEP, 40);
    printf("\t Travese Menu \n");
    draw_seprator(SEP, 40);

    printf("InOrder - ");
    traverse_inorder_recursive(root, &print_BSTnode);
    printf("\n");

    printf("PreOrder - ");
    traverse_preorder_recursive(root, &print_BSTnode);
    printf("\n");

    printf("PostOrder - ");
    traverse_postorder_recursive(root, &print_BSTnode);
    printf("\n");
}

void BST_program()
{
    BSTnode *myroot = NULL;
    int flag = 1;
    while (flag)
    {
        print_welcome_message();
        int ch = ask_choice("Enter your Choice :", 1, 5);
        switch (ch)
        {
        case 1:;
            int n = ask_choice("Enter no of keys you want to add :", -999999, 999999);
            printf("Enter keys in specific order(Left to right): ");
            for (int i = 0; i < n; i++)
            {
                if (myroot == NULL)
                    myroot = insert_key_BST(myroot, ask_choice("", -999999, 999999));
                else
                    insert_key_BST(myroot, ask_choice("", -999999, 999999));
            }
            break;

        case 2:;
            int key = ask_choice("Enter the key you want to remove :", -999999, 999999);
            int res = delete_key_BST(&myroot, key);
            if (res == -1)
                printf("Given key(%d) is not present in tree with root(%p) \n", key, myroot);
            else if (res == -2)
                printf("Tree with root(%p) is EMPTY", myroot);
            else
                printf("Sucessfuly deleted %d from tree. \n", key);
            break;

        case 3:;
            BSTnode *result = search_BST(myroot, ask_choice("Enter the key you want to search :", -99999, 99999));
            if (result != NULL)
                printf("Found Key in tree with root(%p) \n", res, myroot);
            else
                printf("Given key(%p) is not present in tree with root(%p) \n", res, myroot);
            break;

        case 4:
            if (myroot != NULL)
                print_traverse(myroot);
            break;

        case 5:
            flag = 0;
            break;

        default:
            break;
        }
        
    }
}

int main()
{
    BST_program();
}