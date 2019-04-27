#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 150

struct node *A[MAXSIZE];

int top = -1;
struct node *root = NULL;

int ask_choice(char *ques)
{
    //without type-checking
    int ch;
    printf("%s :", ques);
    scanf("%d", &ch);

    return ch;
}

bool isEmpty()
{
    if (top == -1)
        return true;
    else
        return false;
}
struct node
{
    int info;
    struct node *right, *left;
};

struct node *pop()
{
    struct node *ptr;
    ptr = A[top];
    top--;
    return ptr;
}
void push(struct node *ptr)
{
    if (top >= MAXSIZE)
        printf("Stack FULL!!!!\nOVERFLOW\n");
    else
        A[++top] = ptr;
}
void inorder()
{
    top = -1;

    struct node *current, *ptr, *popNull;
    current = root;

    do
    {
        while (current != NULL)
        {

            push(current);
            current = current->left;
        }
        popNull = pop();
        if (popNull != NULL)
        {
            printf("%d\t", popNull->info);
            current = popNull->right;
        }
        else
            current = popNull;

    } while (popNull);
}
void postorder()
{
    top =-1;
    struct node *current = root, *useless;
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

        if (current->right != NULL && current->right == A[top])
        {
            useless = pop();
            push(current);
            current = current->right;
        }
        else
        {

            printf("%d\t", current->info);
            current = NULL;
        }
    } while (!isEmpty());
}
void preorder()
{
    top = -1;
    struct node *current = root;
    while (current)
    {
        printf("%d\t", current->info);
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
void create(int key)
{
    struct node *ptr;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->right = ptr->left = NULL;
    ptr->info = key;
    if (root == NULL)
    {
        root = ptr;
    }
    else
    {
        struct node *parent, *current;
        current = root;
        while (current)
        {
            parent = current;
            if (ptr->info > current->info)
            {
                current = current->right;
            }
            else
                current = current->left;
        }
        if (ptr->info > parent->info)
            parent->right = ptr;
        else
            parent->left = ptr;
    }
}

struct node *findMin(struct node *ptr)
{
    struct node *newPtr = ptr;
    while (newPtr->left != NULL)
        newPtr = newPtr->left;
    return newPtr;
}
void deleteNode(struct node **curent, int key)
{
    struct node *current = *curent;
    struct node *parent = current;

    if (current == NULL)
        return;

    while (current->info != key)
    {
        parent = current;
        if (current == NULL)
            return;
        if (key > current->info)
            current = current->right;
        else
            current = current->left;
        if (current == NULL)
        {
            printf("%d not found in tree \n", key);
            return;
        }
    }

    if (current->left == NULL && current->right == NULL) //leaf node
    {
        if (parent == current)
        {
            *curent = NULL;
        }
        else
        {
            if (key > parent->info)
                parent->right = NULL;
            else
                parent->left = NULL;
        }
        printf("%d Deleted!!!\n", current->info);
        free(current);
    }
    //one child
    else if (current->right == NULL)
    {
        if (parent == current)
        {
            printf("%d Deleted!!!\n", current->info);
            *curent = current->left;
        }
        else
        {
            if (parent->info > key)
                parent->left = current->left;
            else
                parent->right = current->left;
            printf("%d Deleted!!!\n", current->info);
            free(current);
        }
    }
    else if (current->left == NULL)
    {
        if (parent == current)
        {
            printf("%d Deleted!!!\n", current->info);
            *curent = current->right;
        }
        else
        {
            if (parent->info > key)
                parent->left = current->right;
            else
                parent->right = current->right;
            printf("%d Deleted!!!\n", current->info);
            free(current);
        }
    } //two children
    else if (current->left != NULL && current->right != NULL)
    {
        struct node *min;
        min = findMin(current->right);

        current->info = min->info;
        min->info = key;

        deleteNode(&current->right, key);

        // if (current->right == min)
        // {
        //     current->right = NULL;
        //     free(min);
        // }
        // else
        // {
        //     deleteNode(&current->right, key);
        // }
    }
    else
    {
        printf("%d not found in tree", key);
    }
}

void test()
{
    root = NULL;

    create(5);
    create(8);
    create(2);
    create(1);
    create(6);
    create(3);
    create(9);
    create(10);
    create(-5);
    create(0);

    /*
                             ---------------------5---------------------
                    --------2--------                           --------8--------
                ----1               3                           6               9----
                -5--                                                                  10
                    0
    */
    printf("                             -----------------5-------------------------\n");
    printf("                    --------2--------                           --------8--------\n");
    printf("                ----1               3                           6               9----\n");
    printf("                -5--                                                                  10\n");
    printf("                    0\n");

    struct node **root_ = &root;
    inorder();
    printf("\n");
    preorder();
    printf("\n");
    postorder();
    printf("\n");

    deleteNode(root_, 5);
    deleteNode(root_, 8);
    deleteNode(root_, 0);
    deleteNode(root_, 2);
    deleteNode(root_, 9);
    deleteNode(root_, 6);
    deleteNode(root_, 1);
    deleteNode(root_, 10);
    deleteNode(root_, -5);
    deleteNode(root_, 11);
    deleteNode(root_, 3);


    
}

void pgrm()
{
    int opt, x, traversal;

    while (1)
    {
        printf("1.Add nodes\n2.exit\n");
        scanf("%d", &opt);
        if (opt == 1)
            create(ask_choice("Enter the value you want to add"));
        else
            break;
    }

    while (1)
    {
        printf("1.Traversal\n2.Search\n3.Delete\n");
        scanf("%d", &opt);
        if (opt == 1)
        {
            printf("1.inorder Traversal\n2.preorder Traversal\n3.Postorder Traversal\n4.exit\n");
            scanf("%d", &traversal);
            if (traversal == 1)
            {
                inorder();
                printf("\n");
            }
            else if (traversal == 2)
            {
                preorder();
                printf("\n");
            }
            else if (traversal == 3)
            {
                postorder();
                printf("\n");
            }
            else
                break;
        }
        else if (opt == 3)
        {
            int a = ask_choice("Ples enter key to delete");
            deleteNode(root, a);
        }
        else
            break;
    }
}

int main()
{
    test();

    printf(".........................Test Complete......................................\n");
    getchar();
    system("cls");

    pgrm();
}