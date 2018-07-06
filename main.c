#include <stdio.h>
#include <stdlib.h>
typedef struct Firma
{
    char number[14];
    char name[40];
    double profit;
    char date[11];
    struct Firma *next;
}firma;

firma *head = NULL;

void printMenu();
void readFromFile(char *fileName);
void rewriteFile(char *fileName);
void insert();
void printList();
void updateInformation(char *newNum, char *fileName);
void printCriteria(char *newNum);
void report();


int main()
{
    char filename[20];
    int choice;
    char num[13];
    printf("Enter file name from which you want to read the list: ");
    gets(filename);
    readFromFile(filename);
    printf("Your list is: \n");
    printList();

    do
    {
        printMenu();
        scanf("%d", &choice);
        switch(choice)
        {
            case 1: insert();
                    printf("List after insertion: \n");
                    printList();
                    break;
            case 2: printf("Enter the number: ");
                    fflush(stdin);
                    gets(num);
                    updateInformation(num,filename);
                    break;
            case 3: printf("Report for all companies 5 years ago: \n");
                    report();
                    break;
            case 4: printf("Enter the number: ");
                    fflush(stdin);
                    gets(num);
                    printf("The company with that number is: \n");
                    printCriteria(num);
                    break;
            case 5: printf("Googbye :) \n");
                    break;
            default: printf("Wrong operation! \n");
        }
    }while(choice != 5);
    rewriteFile(filename);
    return 0;
}



void printMenu()//printira menuto
{
    printf("\n\n");
    printf("__________|MENU|_________\n");
    printf("1.|Add new company      |\n");
    printf("2.|Update information   |\n");
    printf("3.|Report               |\n");
    printf("4.|Print information    |\n");
    printf("5.|Exit                 |\n");
    printf("__|_____________________|\n");
    printf("YOUR CHOICE: ");
}

void readFromFile(char *fileName) //chete ot faila
{
    FILE *fp;
    int size1, size2, size3;
    firma *newNode = NULL;
    if((fp = fopen(fileName,"rb")) == NULL)
    {
        printf("Error opening file!");
        return;
    }
    while(1)
    {
        firma *newNode = malloc(sizeof(firma));
        firma *temp = head;
        if(fread(&size1,sizeof(int),1,fp) != 1)
        {
            break;
        }
        if(fread(newNode->number,1,size1,fp) != size1)
        {
            break;
        }
        if(fread(&size2,sizeof(int),1,fp) != 1)
        {
            break;
        }
        if(fread(newNode->name,1,size2,fp) != size2)
        {
            break;
        }
        if(fread(&newNode->profit,8,1,fp) != 1)
        {
            break;
        }
        if(fread(&size3,sizeof(int),1,fp) != 1)
        {
            break;
        }
        if(fread(newNode->date,1,size3,fp) != size3)
        {
            break;
        }
        if(head==NULL)
        {
          newNode->next=NULL;
          head=newNode;
        }
        else
        {
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            newNode->next=NULL;
            temp->next=newNode;
        }
    }
    fclose(fp);
}

void rewriteFile(char *fileName)
{
    FILE *fp;
    firma *temp = head;
    int size1, size2, size3;

    if((fp=fopen(fileName,"wb")) == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    while(temp != NULL)
    {
       size1 = sizeof(temp->number);
       if(fwrite(&size1,sizeof(int),1,fp)!=1)
       {
           break;
       }
       if(fwrite(temp->number,1,size1,fp)!=size1)
       {
           break;
       }
       size2=sizeof(temp->name);
       if(fwrite(&size2,sizeof(int),1,fp)!=1)
       {
           break;
       }
       if(fwrite(temp->name,1,size2,fp)!=size2)
       {
           break;
       }
       if(fwrite(&temp->profit,8,1,fp)!=1)
       {
           break;
       }
       size3 = sizeof(temp->date);
       if(fwrite(&size3,sizeof(int),1,fp)!=1)
       {
           break;
       }
       if(fwrite(temp->date,1,size3,fp)!=size3)
       {
           break;
       }

      temp=temp->next;
    }
    fclose(fp);
}

void insert()
{
    firma *newNode = (firma*)malloc(sizeof(firma));
    printf("Enter company's tax number: ");
    fflush(stdin);
    gets(newNode->number);
    printf("Enter company's name: ");
    gets(newNode->name);
    printf("Enter company's profit for last 5 years: ");
    scanf("%lf",&newNode->profit);
    fflush(stdin);
    printf("Enter company's date of registration(yyyy.dd.mm): ");
    gets(newNode->date);

    firma *temp=head;
    if(head==NULL)
    {
        newNode->next=NULL;
        head=newNode;
        return;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    newNode->next=NULL;
    temp->next=newNode;
}

void printList()
{
    firma *temp = head;
    if(head==NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    while(temp != NULL)
    {
        printf("%s\t",temp->number);
        printf("%s\t",temp->name);
        printf("%g\t",temp->profit);
        printf("%s\t\n",temp->date);
        temp=temp->next;
    }

}

void updateInformation(char *newNum, char *fileName) //aktyalizaciq na informaciqta za firma
{
    firma *temp = head;
    double newProfit;
    while(temp != NULL)
    {
        if(!strcmp(temp->number, newNum))
        {
            printf("Last company's profit: %g\n", temp->profit);
            printf("Enter NEW company's profit for 5 years ago: ");
            scanf("%lf",&newProfit);
            temp->profit = newProfit;

            printf("Companies after updating: \n");
            printf("%s\t",temp->number);
            printf("%s\t",temp->name);
            printf("%g\t",temp->profit);
            printf("%s\t\n",temp->date);

            rewriteFile(fileName);
        }
        temp=temp->next;
    }
}

void printCriteria(char *newNum)
{
    firma *temp = head;
    while(temp != NULL)
    {
        if(!strcmp(newNum,temp->number))
        {
            printf("%s\t",temp->number);
            printf("%s\t",temp->name);
            printf("%g\t",temp->profit);
            printf("%s\t\n",temp->date);
        }
        temp=temp->next;
    }
}

void report()
{
    firma *temp = head;
    double start, end, nProfit;
    temp = temp->next;

    printf("\nEnter start: ");
    scanf("%lf", &start);
    printf("Enter end: ");
    scanf("%lf", &end);
    printf("\n");

    while(temp != NULL)
    {
        nProfit = (temp->profit)/5;
        if((nProfit>start) && (nProfit<end))
        {
            printf("%s\t",temp->number);
            printf("%s\t",temp->name);
            printf("%g\t",temp->profit);
            printf("%s\t\n",temp->date);

        }
        temp = temp->next;
    }
}