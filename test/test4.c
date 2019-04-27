#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *right, *left;
};
struct node *root = NULL;
void create()
{
    struct node *ptr;
    ptr = (struct node *)malloc(sizeof(struct node));
    ptr->right = ptr->left = NULL;
    printf("Enter the value you want to store in tree:\n");
    scanf("%d", &ptr->info);
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
void preorder(struct node *ptr)
{
    //NLR
    if (ptr == NULL)
        return;
    printf("%d\t", ptr->info);
    preorder(ptr->left);
    preorder(ptr->right);
}
void inorder(struct node *ptr)
{
    //LNR
    if (ptr == NULL)
        return;

    inorder(ptr->left);
    printf("%d\t", ptr->info);
    inorder(ptr->right);
}
void postorder(struct node *ptr)
{
    //LRN
    if (ptr == NULL)
        return;

    postorder(ptr->left);
    postorder(ptr->right);
    printf("%d\t", ptr->info);
}
void searchVal(int val)
{
    struct node *current, *parent;
    current = root;
    if (root == NULL)
    {
        printf("Tree is empty!!!!\n");
        return;
    }
    while (current)
    {
        parent = current;
        if (val == current->info)
        {
            printf("Value Found!!\n");
            return;
        }
        else if (val > current->info)
        {
            current = current->right;
        }
        else
            current = current->left;
    }
    printf("Value not found:::\n");
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
    {
        printf("Tree is EMPTY \n");
        return;
    }

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

        if (current->right == min)
        {
            current->right = NULL;
            free(min);
        }
        else
        {
            deleteNode(&current->right, key);
        }
    }
    else
    {
        printf("%d not found in tree", key);
    }
}

int main()
{
    int opt, x, traversal;
    while (1)
    {
        printf("1.Add nodes\n2.exit\n");
        scanf("%d", &opt);
        if (opt == 1)
            create();
        else
            break;
    }
    while (1)
    {
        printf("1.Traversal\n2.Search\n3.Delete Node\n4.Exit\n");
        scanf("%d", &opt);
        if (opt == 1)
        {
            printf("1.Preorder Traversal\n2.Inorder Traversal\n3.Postorder Traversal\n");
            scanf("%d", &traversal);
            if (traversal == 1)
            {
                preorder(root);
                printf("\n");
            }

            else if (traversal == 2)
            {
                inorder(root);
                printf("\n");
            }

            else
            {
                postorder(root);
                printf("\n");
            }
        }
        else if (opt == 2)
        {
            printf("Enter the value you want to search:\n");
            scanf("%d", &x);
            searchVal(x);
        }
        else if (opt == 3)
        {
            int key;
            printf("ENter the value you want to delete:\n");
            scanf("%d", &key);
            deleteNode(&root, key);
        }

        else
            break;
    }
}