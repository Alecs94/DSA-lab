#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
    int data;
    struct nod *left;
    struct nod *right;
} NodeT;
typedef struct node
{
    int data;
    struct node *next;
} NodeL;
NodeL *head,*tail;
NodeT* CreateNode(int data)
{
    NodeT*p=(NodeT*)malloc(sizeof(NodeT));
    p->data=data;
    p->left=NULL;
    p->right=NULL;
    return p;
}

NodeT* CreateBinTree()
{
    NodeT *p;
    char* content=(char*)malloc(sizeof(char));
    scanf("%s",content);
    if(strcmp(content,"*")==0)
        return NULL;
    else
    {
        p=CreateNode(atoi(content));
        p->left=CreateBinTree();
        p->right=CreateBinTree();
    }
    return p;
}
void addlast(int code)
{
    NodeL* p=(NodeL*)malloc(sizeof(NodeL));
    p->data=code;
    if(head==NULL)
    {
        head=p;
        tail=p;
        p->next=NULL;
    }
    else if(tail!=NULL)
    {
        p->next=NULL;
        tail->next=p;
        tail=p;

    }
}
void getListFromTree(NodeT* root)
{
    if(root!=NULL)
    {
        addlast(root->data);
        getListFromTree(root->left);
        getListFromTree(root->right);
    }
    else
        addlast(-1337);            //! Using -1337 instead of a star, because of type conversion from int to char
}
void printlist()
{
    NodeL* aux=head;
    while(aux!=NULL)  // aux!=NULL    {
    {
        if(aux->data==-1337) //! Couldn't print directly a star, so elements assigned with this value are the stars
            printf("* ");
        else
            printf("%d ",aux->data );
        aux=aux->next;

    }
    printf("\n");
}
NodeT* getTreeFromList()
{
    NodeT *p;
    int content;
    content=head->data;
    head=head->next;
    if(content==-1337)
        return NULL;
    else
    {
        p=CreateNode(content);
        p->left=getTreeFromList();
        p->right=getTreeFromList();
    }
    return p;
}
void printElement (NodeT *root)
{
        printf("%d",root->data);
}
void prettyPrint(NodeT *root,int recLevel) //! root, index, length, reccurence level
{
    if(root==NULL)
    {
        recLevel--; //! reached leaf, must decrement recurence level
        return;
    }
    recLevel++; //! otherwise increment it
    prettyPrint(root->right,recLevel); //! keep going right in the tree
    int j=0;

    //! print spaces for the appropriate recurence level
    for(j=0; j<recLevel-1; j++)
    {
        printf("     ");
    }
    //! then print value
    printElement(root);

    //! print  a new line
    printf("\n");

    prettyPrint(root->left,recLevel); //! keep going left in the tree
}
int main()
{
    NodeT *root=CreateBinTree();
    //prettyPrint(root,0);
    getListFromTree(root);
    printlist();
    root = getTreeFromList();
    prettyPrint(root,0);
    return 0;
}
