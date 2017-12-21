#include <stdio.h>

int MAXSIZE = 100;       
int stack[100];     
int top = -1;            

bool isEmpty() 
{
    if(top == -1)
        return true;
    else
        return false;
}
   
bool isFull() 
{
    if(top == MAXSIZE)
        return true;
    else
        return false;
}

int peek() 
{
    return stack[top];
}

int pop() 
{
    int number;
    
    if (top == - 1)
        printf ("Stack is empty.\n");
    else
    {
        number = stack[top];
        printf ("Popped element : %d\n", stack[top]);
        top--;
        return number;
    }
}

void push(int data) 
{
    if (!isFull()) 
    {
        top = top + 1;
        stack[top] = data;
    } 
    else
      printf("Couldn't insert data, stack is full.\n");
}