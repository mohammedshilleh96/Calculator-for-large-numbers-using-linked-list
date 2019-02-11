#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// The structure for the list of all numbers
typedef struct nod * pointer;

struct nod {
    char data [1000];
    pointer next;
};

typedef pointer list2;
typedef pointer position2;


list2 ReadFromFile();
int isValidNumber(char []);

position2 top(list2);
void pop(list2);
void addLast(list2 , char []);
void printList2(list2 , char);

position2 rear; // points at the last node in the list of all numbers

/***********************************************************************************************************************/
/***********************************************************************************************************************/

list2 ReadFromFile ()
{
    list2 l = (list2)malloc(sizeof(struct nod));
    l->next = NULL;

    FILE * input;
    char line[100];
    int s;
    int i = 0;
    char name[40];
    system("CLS");
    printf("Please Enter File Path\n");
    gets(name);
    input = fopen(name ,"r");

    while(input == NULL)
    {
        printf("An Error Happened While Opening File\n");
        printf("Please Press Any key To Try Again\n");
        gets(name);
        input = fopen(name ,"r");
    }


    s = fgets(line , 100 , input);
    if( s == EOF )
    {
        printf("File Is Empty\n");
        printf("Press Any Key To Return To Menu");
        getchar();
    }
    else
    {
        strtok(line,"\n");
        while(s!=NULL)
        {
            if(isValidNumber(line))
            {
                addLast(l , line);
                i++;
            }
            s = fgets(line , 100 , input);
            strtok(line,"\n");
        }
        fclose(input);
        printf("\nWe Have Read Your File\n\n");
    }
    return l;
}

/***********************************************************************************************************************/
/***********************************************************************************************************************/

int isValidNumber(char new1 [])
{
    char l[100];

    if(isdigit(new1[0]))
    {
        l[0] = '+';
        l[1] = '\0';
        strcat(l , new1);
    }
    else
        strcpy(l , new1);

    strcat(l , "\0");


    int i = 1 ;

    //check the sign digit
    if(l[0] != '-')
        if(l[0] != '+')
            return 0;

    if (l[1] == '\0')
        return 0;

    while(l[i] != '\0')
    {
        if(!isdigit(l[i]))
            return 0;
        i++;
    }

    return 1;
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


void pop(list2 l){

    if(l == NULL)
        return;

    position2 p = (struct nod*)malloc(sizeof(struct nod));
    p = l->next;
    l->next = p->next;
    p->next = NULL;
    free(p);
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


position2 top(list2 l){

    return l->next;
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


void addLast(list2 l , char temp []){

    if(l == NULL)
        return;

    else
    {
        if (l->next == NULL)
            rear = l;

        struct nod * newnode = (struct nod*)malloc(sizeof(struct nod));
        strcpy(newnode->data , temp);
        newnode->next = NULL;
        rear->next = newnode;
        rear = rear->next;
    }
}


/***********************************************************************************************************************/
/***********************************************************************************************************************/


void printList2(list2 l , char x)
{
    position2 p = (position2)malloc(sizeof(struct nod));
    p = l->next;

    while(p!=NULL)
    {
        printf("%s\n%c\n",p->data,x);
        p = p->next;
    }
}

void fprintList2(list2 l , char x, FILE * in)
{
        position2 p = (struct nod *)malloc(sizeof(struct nod));
        p = l->next;

    while(p!=NULL)
    {
        fprintf(in , "%s\n%c\n",p->data,x);
        p = p->next;
    }
}
