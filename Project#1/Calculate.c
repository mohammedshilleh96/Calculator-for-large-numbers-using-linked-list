#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Data.c"
#include "Number.c"

            /*Addition Functions*/
   /****************************************/
  /**/ list additionCases(list , list); /**/
 /**/ list addition(list , list , int);/**/
/****************************************/

            /*Subtraction Functions*/
    /******************************************/
   /**/ list subtractionCases(list , list);/**/
  /**/ list tenComplement(list);          /**/
 /**/ list nineComplement(list);         /**/
/******************************************/


             /*Multiplication Functions*/
    /***********************************************/
   /**/ list multiplicationCases(list , list);  /**/
  /**/ list multiplyConstantToList(list , int);/**/
 /**/ list multiply(list , list);             /**/
/***********************************************/

                /*Division Functions*/
     /*****************************************/
    /**/ list divisionCases(list , list);  /**/
   /**/ list Div(list , list);            /**/
  /**/ void append(position , int , int);/**/
 /**/ void AddZeroToTheLeft(list l);    /**/
/*****************************************/

int checkDivision(list , list);
/******************************************************************************************************************************/
/*************************************** Addition Functions ******************************************************************/
/****************************************************************************************************************************/

// Determines How To implement Addition & The Sign Of The Result
list additionCases(list N1 , list N2)
{
    list result = (list)malloc(sizeof(struct node));

    if (N1 == NULL || N2 == NULL)
        printf("\nThere is no data\n");

    else if (N1->data == 1 && N2->data == 1)
    {
        result = addition(N1 , N2 , 1);
        result->data = 1;
    }
    else if (N1->data == 1)
    {
        //-N1 + N2

        if(isGreater(N2 , N1))
        {
            N2 = tenComplement(N2);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 0;
        }
        else
        {
            N1 = tenComplement(N1);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 1;
        }
    }
    else if (N2->data == 1)
    {
        //N1 + -N2
        if(isGreater(N1 , N2))
        {
            N1 = tenComplement(N1);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 0;
        }
        else
        {
            N2 = tenComplement(N2);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 1;
        }
    }
    else
    {
        result = addition(N1 , N2 , 0);
        result->data = 0;
    }
    return result;
}

/***********************************************/

// Add Two Lists Together & If The Flag Equals 1 It Will Ignore The Overflow
list addition(list N1 , list N2 , int flag)
{
    position p1 = (position)malloc(sizeof(struct node));
    position p2 = (position)malloc(sizeof(struct node));

    list result = (list)malloc(sizeof(struct node));

    p1  = N1->previous;
    p2  = N2->previous;



    int d1    = 0;
    int d2    = 0;
    int carry = 0;
    int sum   = 0;
    int data  = 0;

   int counter = 0;

    while((p1!=N1) || (p2!=N2))
    {
        if(p1 == N1)
        {
            d1 = 0;
            d2 = p2->data;
            p2 = p2->previous;
        }

        else if(p2 == N2)
        {
            d2 = 0;
            d1 = p1->data;
            p1 = p1->previous;
        }

        else
        {
            d1 = p1->data;
            p1 = p1->previous;

            d2 = p2->data;
            p2 = p2->previous;
        }

        sum = d1 + d2 + carry;

        if (sum<=9)
        {
            data = sum;
            carry = 0;
        }
        else
        {
            data = sum%10;
            carry = sum/10;
        }

        struct node * temp = (struct node *)malloc(sizeof(struct node));
        if(counter == 0)
            {
                result->previous   = temp;
                temp->data         = data;
                temp->previous     = result;
                temp->next         = result;
                result->next       = temp;
                counter = 1;
            }

        else
        {
                temp->data              = data;
                temp->previous          = result;
                temp->next              = result->next;
                result->next->previous  = temp;
                result->next            = temp;
        }
    }

    if(flag == 0 && carry != 0)
    {
        struct node * temp      = (struct node *)malloc(sizeof(struct node));
        temp->data              = carry;
        temp->previous          = result;
        temp->next              = result->next;
        result->next->previous  = temp;
        result->next            = temp;
    }
    // printList(result);
    return result;
}


/******************************************************************************************************************************/
/************************************ Subtraction Functions ******************************************************************/
/****************************************************************************************************************************/

// Determines How To implement Subtraction & The Sign Of The Result
list subtractionCases(list N1 , list N2)
{
    list result = (list)malloc(sizeof(struct node));

    if (N1 == NULL || N2 == NULL)
        printf("\nThere is no data\n");

    else if (N1->data == 1 && N2 ->data == 1) // -N1 + N2
    {
        if(isGreater(N1 , N2))
        {
            N1 = tenComplement(N1);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 1;
        }
        else
        {
            N2 = tenComplement(N2);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 0;
        }

    }
    else if (N1->data == 1)
    {
        result = addition(N1 , N2 , 0);
        result->data = 1;
    }
    else if (N2->data == 1)
    {
        result = addition(N1 , N2 , 0);
        result->data = 0;
    }
    else
    {
        if(isGreater(N1 , N2))
        {
            N1 = tenComplement(N1);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 0;
        }
        else
        {
            N2 = tenComplement(N2);
            result = addition(N1 , N2 , 1);
            result = tenComplement(result);
            result->data = 1;
        }
    }
    return result;
}

/***********************************************/

// Returns The 9's Complement For A Number
list nineComplement(list l)
{

    position p = l->next;
    int x = 0;
    while(p!=l)
    {
        x = p->data;
        switch (x)
        {
        case 0:
            x = 9;
            break;

        case 1:
            x = 8;
            break;

        case 2:
            x = 7;
            break;

        case 3:
            x = 6;
            break;

        case 4:
            x = 5;
            break;

        case 5:
            x = 4;
            break;

        case 6:
            x = 3;
            break;

        case 7:
            x = 2;
            break;

        case 8:
            x = 1;
            break;

        case 9:
            x = 0;
            break;
        }
        p->data = x;
        p = p->next;
    }
    return l;
}

/***********************************************/

// Returns The 10's Complement For A Number
list tenComplement(list l)
{

//check if it zero in the main using a function
    list l1 = nineComplement(l);

    position p = l1->previous;
    int carry = 1;
    int d1 = p->data;
    while(p!=l1)
    {
        d1 = d1 + carry;
        if(d1 <=9)
        {
            p->data = d1;
            break;
        }
        else
        {
            p->data = 0;
            carry = 1;
        }
        p = p->previous;
        d1 = p->data;
    }
    return l1;
}


/******************************************************************************************************************************/
/************************************ Multiplication Functions ***************************************************************/
/****************************************************************************************************************************/

// Determines How To implement Multiplication & The Sign Of The Result
list multiplicationCases(list N1 , list N2)
{
    list result = (list)malloc(sizeof(struct node));

    if((N1->data == 1 && N2->data == 1)){
        result = multiply(N1 , N2);
        result->data = 0;
    }

    else if ((N1->data == 0) && (N2->data == 0)){
        result = multiply(N1 , N2);
        result->data = 0;
    }

    else
    {
        result = multiply(N1 , N2);
        result->data = 1;
    }
    return result;
}


/***********************************************/

// Multiplies Two List Together
list multiply(list N1 , list N2)
{
    int length = numberLength(N1) + numberLength(N2);
    list result = createListWithZeros(length);


    position p  = N2->previous;
    int data = p->data;


    while(p!=N2)
    {
        result = additionCases(result , multiplyConstantToList(N1 , data));
        AddZeroToTheLeft(N1);
        p = p->previous;
        data = p->data;
    }
    return result;
}


/***********************************************/

// Multiplies A List By A Single Digit Number (0 - 9)
list multiplyConstantToList(list l , int x)
{
    list result = (list)malloc(sizeof(struct node));
    position p = (position)malloc(sizeof(struct node));

    p = l->previous;
    result->next = NULL;

    int counter = 0;


    int sum = 0;
    int carry = 0;
    int digit = 0;


    while(p!=l)
    {
        sum = p->data * x + carry;
        if(sum <= 9)
        {
            digit = sum;
            carry = 0;
        }
        else
        {
            digit = sum%10;
            carry = sum/10;
        }

        struct node * newnode = (struct node *)malloc(sizeof(struct node));
        if(counter == 0)
        {

            newnode->data = digit;
            newnode->next = result;
            newnode->previous = result;

            result->next = newnode;
            result->previous = newnode;
            result->data = 0;
            counter = 1;
            p = p->previous;
        }
        else
        {
            newnode->data              = digit;
            newnode->previous          = result;
            newnode->next              = result->next;
            result->next->previous     = newnode;
            result->next               = newnode;
            p = p->previous;
        }
    }
    if(carry != 0)
    {
        struct node * newnode = (struct node *)malloc(sizeof(struct node));
        newnode->data = carry;
        newnode->next = result->next;
        newnode->previous = result;
        result->next->previous     = newnode;
        result->next = newnode;
    }

    return result;

}


/******************************************************************************************************************************/
/************************************ Division Functions *********************************************************************/
/****************************************************************************************************************************/

int checkDivision(list N1 , list N2){

    if (isGreater(N2 , N1))
        return 0;

    else if (isZero(N2))
        return 1;

    else if (isZero(N1))
        return 2;

    else if (isEqual(N1 , N2))
        return 3;

    else
        return 4;

}

// Determines How To implement Division & The Sign Of The Result
list divisionCases(list N1 , list N2)
{
    list result = (list)malloc(sizeof(struct node));

    if((N1->data == 1 && N1->data == 1) || (N1->data == 0 && N1->data == 0))
        {
            result = Div(N1 , N2);
            result->data = 0;
        }

    else
        {
            result = Div(N1 , N2);
            result->data = 1;
        }
    return result;
}

/***********************************************/

// Divides the first list by the second list (L1/L2)
list Div(list l1,list l2)
{

    position p1 = l1->previous ;
    position p2 = l2->previous ;
    list result = (list)malloc(sizeof(struct node));
    long long num1=0,num2=0;

    double c = 0;
    double s = 0;

    while(p1 != l1 )
    {
        s = pow(10.0,c);
        num1 = num1 + (p1->data)*s;
        c++;
        p1=p1->previous;
    }

    c = 0;

    while(p2 != l2)
    {
        s = pow(10.0,c);
        num2 = num2 + (p2->data)*pow(10,c);
        c++;
        p2=p2->previous;
    }

    long n=num1/num2;

    int temp=0;
    int flag = 0;

    while (1)
    {
        temp=n%10;
        append(result ,temp ,flag);
        flag++;

        n=n/10;

        if (n == 0)
            break;

    }

    return result;
}

/***********************************************/

// Adds A Digit After The Most Significant Digit
void append(position p, int x , int flag){
if(flag != 0)
    {
        struct node * temp = (struct node*)malloc(sizeof(struct node));
        temp->data = x;
        temp->next = p->next;
        temp->previous = p;
        temp->next->previous = temp;
        p->next = temp;
    }
    else
    {
        struct node * temp = (struct node*)malloc(sizeof(struct node));
        temp->data = x;
        temp->next = p;
        temp->previous = p;
        p->previous = temp;
        p->next = temp;
    }
}

/***********************************************/

// Adds A Zero After The Least Significant Digit
void AddZeroToTheLeft(list l)
{
    struct node * temp = (struct node*)malloc(sizeof(struct node));
    temp->data = 0;
    temp->next = l;
    temp->previous = l->previous;
    l->previous->next = temp;
    l->previous = temp;
}

/***********************************************/
