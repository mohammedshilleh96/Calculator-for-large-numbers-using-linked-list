#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//Basic Structure For A Single Number
typedef struct node * ptr;
struct node
{
    ptr previous;
    int data;
    ptr next;
};

typedef ptr list;
typedef ptr position;

//Comparing Functions For Faster Results
int isEqual(list , list);
int isGreater(list , list);
int isZero(list);
int numberLength(list);

list createListWithZeros(int);
list createNumber(char []);

//Helping Functions
void printList(list);
void printList22(list , FILE *);

/***********************************************************************************************************************/
/***********************************************************************************************************************/

int isZero(list l)
{
    position p = (position)malloc(sizeof(struct node));
    p = l->next;

    while(p!=l)
    {
        if(p->data != 0)
            return 0;

        p = p->next;
    }

    return 1;
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


int numberLength(list n)
{
    position p = (struct node *)malloc(sizeof(struct node));
    p = n->next;

    int counter = 0;

    while(p!=n)
    {
        counter++;
        p = p->next;
    }

    return counter;
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


int isGreater(list n1, list n2)
{

    position p1 = (struct node *)malloc(sizeof(struct node));
    position p2 = (struct node *)malloc(sizeof(struct node));

    int n1_length = numberLength(n1);
    int n2_length = numberLength(n2);

    if(n1_length > n2_length)
        return 1;
    else if (n2_length > n1_length)
        return 0;
    else
    {
        int flag = 0;

        p1 = n1->next;
        p2 = n2->next;

        while(p1!=n1 || p2!=n2)
        {

            if((p1->data) > (p2->data))
            {
                flag = 1;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return flag;
    }
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


int isEqual(list n1, list n2)
{
    position p1 = (struct node *)malloc(sizeof(struct node));
    position p2 = (struct node *)malloc(sizeof(struct node));

    int n1_length = numberLength(n1);
    int n2_length = numberLength(n2);

    p1 = n1->next;
    p2 = n2->next;

    if(n1_length != n2_length)
        return 0;
    while(p1!=n1 || p2!=n2)
    {
        if(p1->data != p2->data)
            return 0;
        p1 = p1->next;
        p2 = p2->next;
    }
    return 1;
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


list createNumber(char temp [])
{
    list l         = (list)malloc(sizeof(struct node));
    position digit = (position)malloc(sizeof(struct node));

    digit = l;
    int i = 0;
    int data = 0;

    if(temp[0] == '-')
        l->data = 1;
    else
        l->data = 0;

    if(isdigit((int)temp[0]))
        i = 0;
    else
        i = 1;


    l->next     = l;
    l->previous = l;

    while(temp[i] != '\0')
    {
        data = (int)(temp[i] - '0');

        struct node * node = (struct node *)malloc(sizeof(struct node));

        node->data     = data;
        node->previous = digit;
        node->next     = l;

        digit->next = node;
        digit = digit->next;
        i++;
    }
    l->previous = digit;
    digit->next = l;

    return l;
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


list createListWithZeros(int x)
{
    list l = (list)malloc(sizeof(struct node));
    l->next = NULL;
    position p = l;

    while(x != 0)
    {
        struct node * temp = (struct node *)malloc(sizeof(struct node));
        temp->data = 0;
        temp->next = l;
        temp->previous = p;
        p->next = temp;
        p = temp;
        x--;
    }
    l->previous = p;
    p->next = l;

    return l;
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


void printList(list l)
{
    if(l->data == 1)
        printf("-");

    else
        printf("+");

    if(l->next == NULL)
        return;

    position p = (struct node *)malloc(sizeof(struct node));
    p = l->next;

    while(p!=l)
    {
        printf("%d",p->data);
        p = p->next;
    }
}

void printList22(list l , FILE * in)
{

    if(l->data == 1)
        fprintf(in , "-");

    else
        fprintf(in , "+");

    if(l->next == NULL)
        return;

    position p = (struct node *)malloc(sizeof(struct node));
    p = l->next;

    while(p!=l)
    {
        fprintf(in , "%d", p->data);
        p = p->next;
    }

}
