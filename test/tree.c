#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node* createnode(int value)
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=value;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}

struct node* createtree(struct node *h,int n)
{
    struct node *newnode,*curnode;
    int val;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&val);
        newnode=createnode(val);
        if(h==NULL)
        {
            h=newnode;
            curnode=newnode;
        }
        else
        {
            int set=0;
            curnode=h;
            while(set==0)
            {
                if((newnode->data<curnode->data)&&(curnode->left==NULL))
                {
                    curnode->left=newnode;
                    set=1;
                }
                if((newnode->data>=curnode->data)&&(curnode->right==NULL))
                {
                    curnode->right=newnode;
                    set=1;
                }
                if((newnode->data<curnode->data)&&(curnode->left!=NULL))
                    curnode=curnode->left;
                if((newnode->data>=curnode->data)&&(curnode->right!=NULL))
                    curnode=curnode->right;
            }
        }
    }
    return h;
}

void inorder(struct node *t)
{
    if(t==NULL)
        return ;
    inorder(t->left);
    printf("%d ",t->data);
    inorder(t->right);
}

int main()
{
    int n;
    struct node *root=NULL;
    scanf("%d",&n);
    root=createtree(root,n);
    printf("inorder is\n");
    inorder(root);
    return 0;
}