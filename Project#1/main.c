#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calculate.c"

int isValidChoice(char []);

char lastOperation;
int main()
{
    // This program is designed to perform basic mathematical operations (add , sub , multiply , div) on very very large integers
    // The input can be either from the user or from the screen
    // When dealing with files we first move all data into array of string. But we must find the array length first
    // Then we check if every line is a valid number or not and move the new valid numbers to new array of the old size

    printf("  This Program Is Used To Perform Mathematical Operations On Large Integers\n");
    printf("  Please Enter The Number Before The Operation To Perform It\n\n");
    printf("\n\n\n\nPress Any Key To Go To Menu...");
    getchar();
    system("CLS");

    int flag = 0;
    int choice = 0;
    char temp [100];

    list N1     = (list)malloc(sizeof(struct node));
    list N2     = (list)malloc(sizeof(struct node));
    list result = (list)malloc(sizeof(struct node));

    list2 validNumbers = (list2)malloc(sizeof(struct nod));

    FILE* in = fopen("C:\\Users\\Mohammed Shilleh\\Desktop\\Output.txt" , "w");
    N1->next = N1;
    N1->previous = N1;

    N2->next = N2;
    N2->previous = N2;

    result->next = result;
    result->previous = result;

    do
    {
        //User Interface
        printf("\n\n\t\t1. Read From The Input File\n");
        printf("\n\n\t\t2. Add\n");
        printf("\n\n\t\t3. Subtract\n");
        printf("\n\n\t\t4. Multiply\n");
        printf("\n\n\t\t5. Divide\n");
        printf("\n\n\t\t6. Print Result To The Output File\n");
        printf("\n\n\t\t7. Exit\n");

        //Read The choice As a String And Determine Validity
        gets(temp);
        choice = isValidChoice(temp);


        switch (choice)
        {
        case 1: //Reading the file
        {
            system("CLS");
            validNumbers = ReadFromFile();

            printf("Press Any Key To Return To Menu...");
            getchar();
            break;
        }

        case 2: //Addition
        {
            system("CLS");
            if (validNumbers->next == NULL)
                printf("\nYou Must Read The File First Or There Is No Valid Data In Your File\n");
            else
            {
                N1 = createNumber(top(validNumbers)->data);
                pop(validNumbers);


                while(validNumbers->next != NULL)
                {
                    N2 = createNumber(top(validNumbers)->data);
                    pop(validNumbers);

                    result = additionCases(N1 , N2);

                    N1 = result;
                }
                printf("\n\nThe Result is:\n");
                printList(result);
            }
            lastOperation = '+';
            printf("\n\nPress Any Key To Return To Menu...");
            getchar();
            break;
        }
        case 3: //Subtraction
        {
            system("CLS");
            if (validNumbers->next == NULL)
                printf("\nYou Must Read The File First Or There Is No Valid Data In Your File\n");
            else
            {
                N1 = createNumber(top(validNumbers)->data);
                pop(validNumbers);


                while(validNumbers->next != NULL)
                {
                    N2 = createNumber(top(validNumbers)->data);
                    pop(validNumbers);

                    result = subtractionCases(N1 , N2);

                    N1 = result;
                }
                printf("\n\nThe Result is:\n");
                printList(result);
            }
            lastOperation = '-';
            printf("\n\nPress Any Key To Return To Menu...");
            getchar();
            break;
        }

        case 4: //Multiplication
        {
            system("CLS");
            if (validNumbers->next == NULL)
                printf("\nYou Must Read The File First Or There Is No Valid Data In Your File\n");
            else
            {
                N1 = createNumber(top(validNumbers)->data);
                pop(validNumbers);



                while(validNumbers->next != NULL)
                {
                    N2 = createNumber(top(validNumbers)->data);
                    pop(validNumbers);


                    result = multiplicationCases(N1 , N2);

                    N1 = result;
                }
                printf("\n\nThe Result is:\n");
                printList(result);
            }
            lastOperation = '*';
            printf("\n\nPress Any Key To Return To Menu...");
            getchar();
            break;
        }

        case 5: //Division
        {
            system("CLS");
            if (validNumbers->next == NULL)
                printf("\nYou Must Read The File First Or There Is No Valid Data In Your File\n");
            else
            {
                N1 = createNumber(top(validNumbers)->data);
                pop(validNumbers);


                while(validNumbers->next != NULL)
                {
                    N2 = createNumber(top(validNumbers)->data);
                    pop(validNumbers);

                    int cases = checkDivision(N1 , N2);
                    switch(cases)
                    {
                        case 0: result = createNumber("0");
                                break;

                        case 1: flag = 1;
                                printf("Division By Zero\n");
                                break;

                        case 2: result = createNumber("0");
                                break;

                        case 3: result = createNumber("1");
                                break;

                        case 4: result = divisionCases(N1 , N2);
                                break;
                    }
                    if(flag == 1)
                        break;
                    N1 = result;
                }
                if(flag != 1)
                    {
                        printf("\n\nThe Result is:\n");
                        printList(result);
                    }
            }
            lastOperation = '/';
            printf("\n\nPress Any Key To Return To Menu...");
            getchar();
            break;
        }
        case 6:  // print to file
            {
                if (flag == 1)
                    fprintf(in , "Division By Zero");
                else
                    printList22(result , in);
            printf("\nDone\n");
            printf("\n\nPress Any Key To Return To Menu....\n");
            getchar();
            break;
            }


        system("CLS");
        }
        system("CLS");
    }
    while(choice != 7);
    system("CLS");
    printf("\tThis Program Is Designed By The Awesome Engineer:\n");
    printf("\t\t\tMohammed Shilleh\n");
    printf("\t\t\t   ID: 1140844\n");
    return 0;
}


/*****************************************************************************************************************************/

int isValidChoice(char l [])
{
    if (isdigit(l[0]) && (((int)(l[0] - '0') == 9) || ((int)(l[0]-'0')) == 8 || ((int)(l[0]-'0') == 0)))
        return 0;
    else if ((int)(l[1]) == 0)
        return (int)(l[0]-'0');
    else
        return 0;
}

/******************************************************************************************************************************/




