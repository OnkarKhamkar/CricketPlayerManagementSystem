#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

void gotoxy(int,int);
void menu();
void add();
void view();
void search();
void update();
void delete_rec();
void search_name();
void search_jersey();

typedef struct players_record
{
    char name[20];
    char country[20];
    int jersey_no,match,run,wicket;
    float average;
}player;

void main()
{
    gotoxy(10,3);
    printf("-----Cricket Player Record Management System-----");
    gotoxy(10,8);
    printf("Press any key to continue.....");
    getch();
    menu();
}

void menu()
{
    int choice;
    system("cls");
    gotoxy(10,3);
    printf("-----MENU-----");
    gotoxy(10,5);
    printf("Enter your choice to perform following task");
    gotoxy(10,7);
    printf("1 : Add Record");
    gotoxy(10,8);
    printf("2 : View Record");
    gotoxy(10,9);
    printf("3 : Search Record");
    gotoxy(10,10);
    printf("4 : Update Record");
    gotoxy(10,11);
    printf("5 : Delete Record");
    gotoxy(10,12);
    printf("6 : Exit");
    gotoxy(10,15);
    printf("Enter your choice : ");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        add();
        break;

    case 2:
        view();
        break;

    case 3:
        search();
        break;

    case 4:
        update();
        break;

    case 5:
        delete_rec();
        break;

    case 6:
        exit(1);
        break;

    default:
        gotoxy(10,17);
        printf("Invalid Choice");
        gotoxy(10,18);
        printf("Press any key to continue.....");
        getch();
        menu();
    }
}

void add()
{
    FILE *fp;
    player ply;
    char another='y';
    system("cls");
    fp=fopen("record.txt","ab+");
    if(fp==NULL)
	{
        gotoxy(10,5);
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    while(another=='y')
    {
        gotoxy(10,3);
        printf("-----ADD RECORD-----");
        gotoxy(10,5);
        printf("Enter details of player");
        gotoxy(10,7);
        printf("Enter Name of the player: ");
        gets(ply.name);
        gotoxy(10,8);
        printf("Enter Nationality of the player: ");
        gets(ply.country);
        gotoxy(10,9);
        printf("Enter the Jersey Number: ");
        scanf("%d",&ply.jersey_no);
        gotoxy(10,10);
        printf("Enter the Matches Played: ");
        scanf("%d",&ply.match);
        gotoxy(10,11);
        printf("Enter Total runs: ");
        scanf("%d",&ply.run);
        gotoxy(10,12);
        printf("Enter total wickets: ");
        scanf("%d",&ply.wicket);
        fflush(stdin);
        fwrite(&ply,sizeof(ply),1,fp);
        gotoxy(10,15);
        printf(" Do you Want to add of another record? Then press 'y' else 'n'...");
        fflush(stdin);
        another=getch();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    gotoxy(10,6);
    printf("Record has been successfully added");
    gotoxy(10,8);
    printf("Press any key to continue.....");
    getch();
    menu();
}

void view()
{
    FILE *fp;
    int j;
    player ply;
    system("cls");
    gotoxy(6,3);
    printf("-----VIEW RECORD-----");
    gotoxy(6,5);
    printf("Player name   Nationality   Jersey No   Matches played   Total runs   Total wickets     Average");
    gotoxy(6,6);
    printf("------------------------------------------------------------------------------------------------");
    fflush(stdin);
    fp=fopen("record.txt","rb+");
    if(fp==NULL)
	{
        gotoxy(6,8);
        printf("Error opening file.");
        exit(1);
    }
    j=8;
    while(fread(&ply,sizeof(ply),1,fp)==1)
	{
        gotoxy(6,j);
        ply.average=ply.run/ply.match;
        printf("%-15s%-15s%-15d%-14d%-15d%-14d%-10.2f",ply.name,ply.country,ply.jersey_no,ply.match,ply.run,ply.wicket,ply.average);
        j++;
    }
    fclose(fp);
    gotoxy(6,j+3);
    printf("Press any key to continue.....");
    getch();
    menu();
}

void search()
{
	int ch;
    system("cls");
    gotoxy(10,3);
    printf("-----SEARCH MENU-----");
    gotoxy(10,5);
    printf("Enter your choice to perform following task");
    gotoxy(10,7);
    printf("1 : Search by Name");
    gotoxy(10,8);
    printf("2 : Search by Jersey number");
    gotoxy(10,10);
    printf("Enter your choice :");
    scanf("%d",&ch);
    switch(ch)
    {
    case 1:
        search_name();
        break;

    case 2:
        search_jersey();
        break;
        
    default:
        gotoxy(10,19);
        printf("Invalid Choice");
        gotoxy(10,20);
        printf("Please enter valid number");
        getch();
        search();
    }
}

void search_name()
{
	FILE *fp;
    player ply;
    int found=0;
    char plname[20];
    system("cls");
    gotoxy(10,3);
    printf("-----SEARCH RECORD BY NAME-----");
    gotoxy(10,5);
    printf("Enter name of player to be search: ");
    fflush(stdin);
    gets(plname);
    fp=fopen("record.txt","rb+");
    if(fp==NULL)
	{
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    while(fread(&ply,sizeof(ply),1,fp)==1)
	{
        if(strcmp(plname,ply.name)==0)
		{
			found=1;
			ply.average=0;
            gotoxy(10,8);
            printf("Name of the player : %s",ply.name);
            gotoxy(10,9);
            printf("Nationality of the player : %s",ply.country);
            gotoxy(10,10);
            printf("Jersey number : %d",ply.jersey_no);
            gotoxy(10,11);
            printf("Matches Played : %d",ply.match);
            gotoxy(10,12);
            printf("Total runs scored : %d",ply.run);
            gotoxy(10,13);
            printf("Total wickets taken : %d",ply.wicket);
            gotoxy(10,14);
            ply.average=ply.run/ply.match;
            printf("Career average : %.2f",ply.average);
        }
    }
    if(!found)
    {
    	gotoxy(10,8);
    	printf("Name not found in records.");
    	gotoxy(10,9);
    	printf("Please enter valid name.....");
    	getch();
    	search_name();
	}
    fclose(fp);
    gotoxy(10,17);
    printf("Search successful.....");
    gotoxy(10,19);
    printf("Press any key to continue.....");
    getch();
    menu();	
}

void search_jersey()
{
	FILE *fp;
    player ply;
    int j_no,found=0;
    system("cls");
    gotoxy(10,3);
    printf("-----SEARCH RECORD BY JERSEY NUMBER-----");
    gotoxy(10,5);
    printf("Enter jersey number of player to be search: ");
    fflush(stdin);
    scanf("%d",&j_no);
    fp=fopen("record.txt","rb+");
    if(fp==NULL)
	{
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    while(fread(&ply,sizeof(ply),1,fp)==1)
	{
        if(j_no==ply.jersey_no)
		{
			found=1;
			ply.average=0;
            gotoxy(10,8);
            printf("Name of the player : %s",ply.name);
            gotoxy(10,9);
            printf("Nationality of the player : %s",ply.country);
            gotoxy(10,10);
            printf("Jersey number : %d",ply.jersey_no);
            gotoxy(10,11);
            printf("Matches Played : %d",ply.match);
            gotoxy(10,12);
            printf("Total runs scored : %d",ply.run);
            gotoxy(10,13);
            printf("Total wickets taken : %d",ply.wicket);
            gotoxy(10,14);
            ply.average=ply.run/ply.match;
            printf("Career average : %.2f",ply.average);
        }
    }
    if(!found)
    {
    	gotoxy(10,8);
    	printf("Jersey number not found in records");
    	gotoxy(10,9);
    	printf("Please enter valid jersey number.....");
    	getch();
    	search_jersey();
	}
    fclose(fp);
    gotoxy(10,17);
    printf("Search successful.....");
    gotoxy(10,19);
    printf("Press any key to continue.....");
    getch();
    menu();
}

void update()
{
    char plname[20];
    int found=0;
    FILE *fp,*ft;
    player ply;
    system("cls");
    gotoxy(10,3);
    printf("-----UPDATE RECORD-----");
    gotoxy(10,5);
    printf("Enter name of player to update: ");
    fflush(stdin);
    gets(plname);
    fp=fopen("record.txt","rb+");
    if(fp==NULL)
	{
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    ft=fopen("temp.txt","wb+");
    if(ft==NULL)
	{
        gotoxy(10,7);
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    while(fread(&ply,sizeof(ply),1,fp)==1)
    {
        if(strcmp(plname,ply.name)==0)
		{
			found=1;
			fflush(stdin);
            gotoxy(10,8);
        	printf("Enter details of player:-");
        	gotoxy(10,9);
        	printf("Enter Name of the player: ");
        	gets(ply.name);
        	gotoxy(10,10);
        	printf("Enter Nationality of the player: ");
        	gets(ply.country);
        	gotoxy(10,11);
        	printf("Enter the Jersey Number: ");
        	scanf("%d",&ply.jersey_no);
        	gotoxy(10,12);
        	printf("Enter the Matches Played: ");
        	scanf("%d",&ply.match);
        	gotoxy(10,13);
        	printf("Enter Total runs: ");
        	scanf("%d",&ply.run);
        	gotoxy(10,14);
        	printf("Enter total wickets: ");
        	scanf("%d",&ply.wicket);
            fflush(stdin);
        }
        fwrite(&ply,sizeof(ply),1,ft);
    }
    fclose(fp);
    fclose(ft);
    if(found)
    {
    	ft=fopen("temp.txt","rb+");
    	fp=fopen("record.txt","wb+");
    	while(fread(&ply,sizeof(ply),1,ft))
    	{
    		fwrite(&ply,sizeof(ply),1,fp);
		}
    	fclose(fp);
    	fclose(ft);
	}
	else
	{
		gotoxy(10,10);
		printf("Name not found in records");
		gotoxy(10,11);
		printf("Please enter valid name.....");
		getch();
		update();
	}
    gotoxy(10,17);
    printf("Record updated successfully.");
    gotoxy(10,19);
    printf("Press any key to continue.....");
    getch();
    menu();
}

void delete_rec()
{
    char plname[20];
    int found=0;
    FILE *fp,*ft;
    player ply;
    system("cls");
    gotoxy(10,3);
    printf("----DELETE RECORD-----");
    gotoxy(10,5);
    printf("Enter name of player to delete record: ");
    fflush(stdin);
    gets(plname);
    fp=fopen("record.txt","rb+");
    if(fp==NULL)
	{
        gotoxy(10,6);
        printf("Error opening file");
        exit(1);
    }
    ft=fopen("temp.txt","wb+");
    if(ft==NULL)
	{
        gotoxy(10,7);
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    while(fread(&ply,sizeof(ply),1,fp)==1)
    {
        if(strcmp(plname,ply.name)==0)
		{
			found=1;
        }
        else
		{
			fwrite(&ply,sizeof(ply),1,ft);
		}
        
    }
    fclose(fp);
    fclose(ft);
    if(found==1)
    {
    	ft=fopen("temp.txt","rb+");
    	fp=fopen("record.txt","wb+");
    	while(fread(&ply,sizeof(ply),1,ft))
    	{
    		fwrite(&ply,sizeof(ply),1,fp);
		}
    	fclose(fp);
    	fclose(ft);
	}
	else
	{
		gotoxy(10,10);
		printf("Name not found in records");
		gotoxy(10,11);
		printf("Please enter valid name.....");
		getch();
		update();
	}
    gotoxy(10,10);
    printf("Record deleted successfully.");
    gotoxy(10,11);
    printf("Press any key to continue.....");
    getch();
    menu();
}


void gotoxy(int x,int y)
{
        COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
