#include "stack.h"

void push(int content)///add first
{
    NodeT * newH = createNode(content);
    newH->next = stack;
    stack = newH;
}

void pop()///delete first
{
    if(stack!=NULL){
        stack=stack->next;
    }
}

NodeT * peekStack()
{
    return stack;
}

int isEmptyStack(){
    return stack == NULL;
}

//! auxiliary
void printStack()
{
    NodeT * aux=stack;
    while(aux!=NULL)
    {
        printf("%d ",aux->content );
        aux=aux->next;
    }
    printf("\n");
}
