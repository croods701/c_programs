#include <stdio.h>
#include <stdlib.h>

#define New_Mem(type) ((type *)malloc(sizeof(type)))
#define NL printf("\n")
#define SEP '-'

//Utilities Function
int ask_choice(char *ques, int m, int n)
{
    int ch;
    printf("%s ", ques);
    scanf("%d", &ch);
    while (ch < m || ch > n)
    {
        printf("%s ", ques);
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

//For Hooks
typedef void (*callback)(void *context);
//Travesing implemented using stack
int traverse_inorder_stack(BSTnode *root, callback hook)
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
            hook(pop_node);
            current = pop_node->right;
        }
        else
            current = pop_node;

    } while (pop_node);
}

int traverse_preorder_stack(BSTnode *root, callback hook)
{
    TOP = -1;
    BSTnode *current = root;
    while (current)
    {
        hook(current);
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

int traverse_postorder_stack(BSTnode *root, callback hook)
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
            hook(current);
            current = NULL;
        }
    } while (TOP != -1);
}

//Callback function for print
void print_BSTnode(void *node)
{
    printf(" %d ", ((BSTnode *)node)->key);
}

void print_welcome_message()
{
    draw_seprator(SEP,40);
    printf("\t Welcome to BST Program\n");
    draw_seprator(SEP,40);
    printf("1. Add Key \n");
    printf("2. Travese BST \n");
    printf("3. Exit \n");
}

void print_traverse(BSTnode *root)
{
    draw_seprator(SEP,40);
    printf("\t BST Travese \n");
    draw_seprator(SEP,40);

    printf("InOrder - ");
    traverse_inorder_stack(root, &print_BSTnode);
    printf("\n");

    printf("PreOrder - ");
    traverse_preorder_stack(root, &print_BSTnode);
    printf("\n");

    printf("PostOrder - ");
    traverse_postorder_stack(root, &print_BSTnode);
    printf("\n");
}

void BST_program()
{
    BSTnode *myroot = NULL;

    int flag = 1;
    while (flag)
    {
        print_welcome_message();
        int ch = ask_choice("Enter your Choice :", 1, 3);

        switch (ch)
        {
        case 1:;
            int n = ask_choice("Enter no of keys you want to add :", -999999, 999999);
            printf("Enter keys in specific order(Left to right) :");
            for (int i = 0; i < n; i++)
            {
                if (myroot == NULL)
                    myroot = insert_key_BST(myroot, ask_choice("", -999999, 999999));
                else
                    insert_key_BST(myroot, ask_choice("", -999999, 999999));
            }
            break;

        case 2:
            NL;
            if (myroot != NULL)
                print_traverse(myroot);
            break;

        case 3:
            flag = 0;
            break;

        default:
            break;
        }
        NL;
    }
}

int main()
{
    BST_program();
}