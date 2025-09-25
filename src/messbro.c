// ---- Preprocessing Directives ---- :
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// ---- Function Prototypes ---- :
void Mess_Menu_Update(void);
void Mess_Menu(void);
char* Cust_fgets(char *str, int size, FILE *STREAM);
char *WeekDayNumtoWeekDayName(int day);
char *MealTime(int mealtm);
char *OpenFile(const char *weekday, int tm);

// ---- Global Declarations ---- :
typedef struct
{
    char items[100];
} Mess;

Mess Menu[7][3];

// ---- Main Function ---- :
int main(int argc, char *argv[])
{
    if(argc!=1 && (strcmp(argv[1], "update")==0))
    {
        Mess_Menu_Update();
    }
    else
    {
	printf("\n\t++++++++++++++++++");
	printf("\n\t|     MessBro    |");
	printf("\n\t++++++++++++++++++");
	printf("\n\n");
	Mess_Menu();
	printf("\n* Sometimes menu items may change.");
    }
    return 0;
}

// ---- Function Definitions ---- :
// -- Mess_Menu_Update -- :
// This function let's the user update the menu of the mess.
void Mess_Menu_Update(void)
{
    int i, j;
    FILE *fp;
    fp=fopen("messmenu.txt", "w");	//Opening the file to write.
    if(fp == NULL)
    {
        perror("File opening failed!");	//Printing error if the an error occurred to open file.
        exit(1);
    }
    for(i=0;i<7;i++)
    {
        fprintf(fp, "%s\n", WeekDayNumtoWeekDayName(i));
        for(j=0;j<3;j++)
        {
            printf("\n%s %s items : ", WeekDayNumtoWeekDayName(i), MealTime(j));
            Cust_fgets(Menu[i][j].items, sizeof(Menu[i][j].items), stdin);
            fprintf(fp, "%d,%s: %s\n", j, MealTime(j), Menu[i][j].items);
        }
    }
    fclose(fp);
}

// -- Mess_Menu -- :
//This function acquires the local time and day to print the Mess items according to it.
void Mess_Menu(void)
{
    int i, Time=0;
    char day[3];
    time_t now=time(NULL);	//Acquiring the time.
    char *tm_info=asctime(localtime(&now));	//Coverting the time to ASCII Time.
    for(i=0;tm_info[i]!='\0';i++)
    {
        if(i<3)
        {
            day[i]=tm_info[i];	//Extracts the day.
        }
        if(i==11 || i==12)
        {
            Time=(Time*10)+(tm_info[i]-'0');	//Extracts the time.
        }
    }
    day[3]='\0';
    if(strcmp(day, "Sun")==0)
    {
        OpenFile("Sunday", Time);
    }
    else if(strcmp(day, "Mon")==0)
    {
        OpenFile("Monday", Time);
    }
    else if(strcmp(day, "Tue")==0)
    {
        OpenFile("Tuesday", Time);
    }
    else if(strcmp(day, "Wed")==0)
    {
        OpenFile("Wednesday", Time);
    }
    else if(strcmp(day, "Thu")==0)
    {
        OpenFile("Thursday", Time);
    }
    else if(strcmp(day, "Fri")==0)
    {
        OpenFile("Friday", Time);
    }
    else
    {
        OpenFile("Saturday", Time);
    }
}

// -- Cust_fgets -- :
//This function simulates the usage of fgets with an additional feature to strip off the newline character at the end.
char* Cust_fgets(char *str, int size, FILE *STREAM)
{
    if(fgets(str, size, STREAM) == NULL)
    {
    	return NULL;
    }
    str[strcspn(str, "\n")]=0;
    return str;
}

// -- WeekDayNumtoWeekDayName -- :
// This function returns name of the week day according to the number passed 
char *WeekDayNumtoWeekDayName(int day)
{
    switch(day)
    {
        case 0:
            return "Sunday";
        case 1:
            return "Monday";
        case 2:
            return "Tuesday";
        case 3:
            return "Wednesday";
        case 4:
            return "Thursday";
        case 5:
            return "Friday";
        case 6:
            return "Saturday";  
    }
}

// -- MealTime -- :
// This function returns the meal times according to the number passed.
char *MealTime(int mealtm)
{
    switch(mealtm)
    {
        case 0:
            return "Breakfast";
        case 1:
            return "Lunch";
        case 2:
            return "Dinner";     
    }
}

// -- OpenFile -- :
//This function retrieves the data that is the mess menu items on a specific day and at specific time.
char *OpenFile(const char *weekday, int tm)
{
    char buffer[99];
    FILE *fp;
    fp=fopen("messmenu.txt", "r");
    while((Cust_fgets(buffer, sizeof(buffer), fp)!=NULL))
    {
	    if(strcmp(weekday, buffer)==0)
	    {		
		    if(tm>=0 && tm<=10)
	    	{
		        Cust_fgets(buffer, sizeof(buffer), fp);
		        printf("\nToday's %s\n\n", buffer);
		    }
		    else if(tm>10 && tm<=14)
		    {
		        Cust_fgets(buffer, sizeof(buffer), fp);
		        Cust_fgets(buffer, sizeof(buffer), fp);
		        printf("\nToday's %s\n\n", buffer);
		    }
		    else
		    {
		        Cust_fgets(buffer, sizeof(buffer), fp);
		        Cust_fgets(buffer, sizeof(buffer), fp);
		        Cust_fgets(buffer, sizeof(buffer), fp);
		        printf("\nToday's %s\n\n", buffer);
		    }
	    }
    }
    fclose(fp);
}
