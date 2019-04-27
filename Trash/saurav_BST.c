#include <stdio.h>
#include <stdlib.h>

#define New_Mem(type) ((type *)malloc(sizeof(type)))

//Utilities Function
int ask_choice(char *ques, int m, int n)
{
    int ch;
    printf("%s :", ques);
    scanf("%d", &ch);
    while (ch < m || ch > n)
    {
        printf("%s :", ques);
        scanf("%d", &ch);
    }

    return ch;
}

void clear()
{
    system("cls||clear");
}
void pause()
{
    fflush(stdin);
    fflush(stdin);
    getchar();
}

//BST structs
typedef struct BSTnode_t
{
    int key;
    struct BSTnode_t *right, *left;
} BSTnode;

//Stack implementation
#define MAX_LEN 20
BSTnode *STACK[MAX_LEN];
int TOP = -1;

BSTnode *push(BSTnode *node)
{
    if (TOP >= MAX_LEN)
        return NULL;
    else
        STACK[++TOP] = node;
    return node;
}

BSTnode *pop()
{
    if (TOP < 0)
        return NULL;
    return STACK[TOP--];
}

//BST Functions
BSTnode *create_BSTnode(int key)
{
    BSTnode *new_node = ((BSTnode *)malloc(sizeof(BSTnode)));
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

//Recursive Travesing Functions
int traverse_inorder_recursive(BSTnode *root)
{
    if (root == NULL)
        return 0;
    traverse_inorder_recursive(root->left);
    printf(" %d ", root->key);
    traverse_inorder_recursive(root->right);
}

void traverse_preorder_recursive(BSTnode *root)
{
    if (root == NULL)
        return;
    printf(" %d ", root->key);
    traverse_preorder_recursive(root->left);
    traverse_preorder_recursive(root->right);
}

int traverse_postorder_recursive(BSTnode *root)
{
    if (root == NULL)
        return 0;
    traverse_postorder_recursive(root->left);
    traverse_postorder_recursive(root->right);
    printf(" %d ", root->key);
}

//Travesing implemented using stack
int traverse_inorder_stack(BSTnode *root)
{
    TOP = -1;
    BSTnode *current, *pop_node;
    current = root;
    do
    {
        while (current != NULL)
        {

            push(current);
            current = current->left;
        }
        pop_node = pop();
        if (pop_node != NULL)
        {
            printf(" %d ", pop_node->key);
            current = pop_node->right;
        }
        else
            current = pop_node;

    } while (pop_node);
}

int traverse_preorder_stack(BSTnode *root)
{
    TOP = -1;
    BSTnode *current = root;
    while (current)
    {
        printf(" %d ", current->key);
        if (current->right != NULL)
            push(current->right);
        if (current->left != NULL)
            current = current->left;
        else
        {
            current = pop();
        }
    }
}

int traverse_postorder_stack(BSTnode *root)
{
    TOP = -1;
    BSTnode *current = root, *pop_ptr;
    do
    {
        while (current != NULL)
        {
            if (current->right != NULL)
                push(current->right);
            push(current);
            current = current->left;
        }
        current = pop();

        if (current->right != NULL && current->right == STACK[TOP])
        {
            pop_ptr = pop();
            push(current);
            current = current->right;
        }
        else
        {
            printf(" %d ", current->key);
            current = NULL;
        }
    } while (TOP != -1);
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
        {
            return search_BST(root->right, key);
        }
    }
    return NULL;
}


void print_welcome_message()
{
    printf("\t Welcome to BST Program\n");
    printf("1. Add Key \n");
    printf("2. Delete Key \n");
    printf("3. Search Key \n");
    printf("4. Travese BST \n");
    printf("5. Exit \n");
}

void print_traverse(BSTnode *root)
{
    printf("\t Travese Menu \n");

    printf("Recursive Functions..................... \n");
    printf("InOrder - ");
    traverse_inorder_recursive(root);
    printf("\n");

    printf("PreOrder - ");
    traverse_preorder_recursive(root);
    printf("\n");

    printf("PostOrder - ");
    traverse_postorder_recursive(root);
    printf("\n");
    printf("........................................ \n");

    printf("\n");

    printf("Stack Functions..................... \n");
    printf("InOrder - ");
    traverse_inorder_stack(root);
    printf("\n");

    printf("PreOrder - ");
    traverse_preorder_stack(root);
    printf("\n");

    printf("PostOrder - ");
    traverse_postorder_stack(root);
    printf("\n");
    printf("........................................ \n");
}

void BST_program()
{
    BSTnode *myroot = NULL;

    int flag = 1;
    while (flag)
    {
        print_welcome_message();
        int ch = ask_choice("Enter your Choice", 1, 5);

        switch (ch)
        {
        case 1:;
            if (myroot == NULL)
                myroot = insert_key_BST(myroot, ask_choice("Enter the Value you Want to add", -999999, 999999));
            else
                insert_key_BST(myroot, ask_choice("Enter the Value you Want to add", -999999, 999999));
            break;

        case 2:;
            int key = ask_choice("Enter the key you want to remove", -999999, 999999);
            int res = delete_key_BST(&myroot, key);
            if (res == -1)
                printf("Given key(%d) is not present in tree with root(%p) \n", key, myroot);
            else if (res == -2)
                printf("Tree with root(%p) is EMPTY", myroot);
            else
                printf("Sucessfuly deleted %d from tree. \n", key);
            break;

        case 3:;
            BSTnode *result = search_BST(myroot, ask_choice("Enter the key you want to search", -99999, 99999));
            if (result != NULL)
                printf("Found Key in tree with root(%p) \n", res, myroot);
            else
                printf("Given key(%p) is not present in tree with root(%p) \n", res, myroot);
            break;

        case 4:
            print_traverse(myroot);
            break;

        case 5:
            flag = 0;
            break;

        default:
            break;
        }
        pause();
        clear();
    }
}

int main()
{
    BST_program();
}
