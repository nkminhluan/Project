
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 1000


typedef struct student 
{
	int student_id;
	char first_name[50];
	char last_name[50];
	char gender[50];
	char day_of_birth[50];
	char class_name[50];
	char country[50];
}STUDENT;
typedef struct score
{
	int student_id;
	int subject_id;
	float score;
}SCORE;
void display(struct score list[80], int s);
void bsortDesc(struct score list[80], int s);
int row_count(const char* filename)
{
	FILE *fp;
    int count = 0;  
    char c;  
    
    fp = fopen(filename, "r");
   
    if (fp == NULL)
    {
        printf("Cannot open it");
        return 0;
    }
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') 
            count++;

    return count;
}
void read_score_csv(SCORE score[], const char* path)
{
	FILE* fp = fopen(path, "r");
  
    if (!fp)
        printf("Can't open file\n");
  
    else 
	{
      
        char buffer[1024];
  
        int row = 0;
        int column = 0;
  
        while (fgets(buffer,1024, fp)) 
		{
			
			if (row == 0)
			{
				row++;
                continue;
			}
			column = 0;

            //printf("%d\n", row);
            // Splitting the data
            char* value = strtok(buffer, ",");
  
            while (value) 
			{
                // Column 1
                if (column == 0) 
				{
                    //printf("Student ID :");
                    //printf("%s", value);
                    score[row-1].student_id = atoi(value);
                	value = strtok(NULL, ",");
                }
  
                // Column 2
                if (column == 1) 
				{
                    //printf("\tFirst name :");
                    //printf("%s", value);
                    score[row-1].subject_id = atoi(value);
                	value = strtok(NULL, ",");
                }
  
                // Column 3
                if (column == 2) 
				{
                    //printf("\tLast name :");
                    //printf("%s", value);
                    score[row-1].score = atof(value);
                	value = strtok(NULL, ",");
                }
                column++;
            }
            //printf("\n");
            row++;
        }
    }

    fclose(fp);
}

void read_student_list(STUDENT student[], const char* path)
{
	FILE* fp = fopen(path, "r");
  
    if (!fp)
        printf("Can't open file\n");
  
    else 
	{
    
        char buffer[MAX];
  
        int row = 0;
        int column = 0;
  
        while (fgets(buffer,MAX, fp)) 
		{
			
			if (row == 0)
			{
				row++;
                continue;
			}
			column = 0;
            char* value = strtok(buffer, ", ");
            while (value) 
			{
                // Column 1 
                if (column == 0) 
				{
                    student[row-1].student_id = atoi(value);
                	value = strtok(NULL, ", ");
                }
  
                // Column 2
                if (column == 1) 
				{

                    strcpy(student[row-1].first_name, value);
                	value = strtok(NULL, ", ");
                }
  
                // Column 3
                if (column == 2) 
				{

                    strcpy(student[row-1].last_name, value);
                	value = strtok(NULL, ", ");
                }
                if (column == 3) {

                    strcpy(student[row-1].gender, value);
                	value = strtok(NULL, ", ");
                }
                if (column == 4) 
				{

                    strcpy(student[row-1].day_of_birth, value);
                	value = strtok(NULL, ", ");       
                }
                if (column == 5) {

                    strcpy(student[row-1].class_name, value);
               	 	value = strtok(NULL, ", ");      
                }
                if (column == 6) {

                    strcpy(student[row-1].country, value);
                	value = strtok(NULL, ", ");    
                }
                column++;
            }
            
            row++;
        }
    }
}
int main()
{   int score_rows;
    score_rows = row_count("diem.csv")-1;
    SCORE score_array[score_rows];
    read_score_csv(score_array, "diem.csv");
    int valuesmale,valuesfemale;
    int student_rows = row_count("dssv.csv")-1;
    char input[100];
    STUDENT student_array[student_rows];
    read_student_list(student_array, "dssv.csv");
    gets(input);
    FILE *ngan = fopen("result.csv","w");
    //fprintf(ngan,"Student ID,First name,Last name,Gender,Date of birth,Classname,Country\n");
    int i=0;
    char male[MAX] = "count male";
    char female[MAX] = "count female";

    if(strstr(input,"count male")!=NULL){
        int male;
        for(i=0;i<student_rows+1;i++){
            valuesmale = strcmp(student_array[i].gender,"Male");
            if(valuesmale==0){
                male = male + 1 ;
                //fprintf(ngan,"%d,%s,%s,%s,%s,%s,%s",student_array[i].student_id,student_array[i].first_name,student_array[i].last_name,student_array[i].gender,student_array[i].day_of_birth,student_array[i].class_name,student_array[i].country);
            }
        }
        fprintf(ngan,"%d",male);
    }
    int female1=0;
    if(strstr(input,"count female")!=NULL){
        for(i=0;i<student_rows+1;i++){
            valuesfemale = strcmp(student_array[i].gender,"Female");
            if(valuesfemale==0){
                female1++; 
                //fprintf(ngan,"%d,%s,%s,%s,%s,%s,%s",student_array[i].student_id,student_array[i].first_name,student_array[i].last_name,student_array[i].gender,student_array[i].day_of_birth,student_array[i].class_name,student_array[i].country);
            }
        }
        fprintf(ngan,"%d",female1);
    }


    char list[MAX] = "list";
    char *valueslist;
    if(strstr(input,"list")!=NULL){
        for(i=0;i<student_rows;i++){
        valueslist = strstr(input,student_array[i].class_name);
            if(valueslist!=NULL){
                fprintf(ngan,"%d,%s,%s,%s,%s,%s,%s",student_array[i].student_id,student_array[i].first_name,student_array[i].last_name,student_array[i].gender,student_array[i].day_of_birth,student_array[i].class_name,student_array[i].country);
            }
        }
    }


    char str[MAX][MAX],s[MAX];
    char searchname[MAX] = "sort asc";
    struct student t;
    if(strstr(input,searchname)!=NULL){
        for(i=0;i<student_rows+1;i++){
            //strcpy(str[i],student_array[i]);
            for(int j=i+1;j<student_rows;j++){
                if(strcmp(student_array[i].first_name,student_array[j].first_name)>0){
                    t=student_array[i];
                    student_array[i]=student_array[j];
                    student_array[j]=t;
                }
  
            }
            fprintf(ngan,"%d,%s,%s,%s,%s,%s,%s",student_array[i].student_id,student_array[i].first_name,student_array[i].last_name,student_array[i].gender,student_array[i].day_of_birth,student_array[i].class_name,student_array[i].country);
        }
    }

    // Column
    // char score[MAX]="top n";
    // if(strstr(input,score)!=NULL){
    //     bsortDesc(score_array,score_rows);
    //     display(score_array,score_rows);
    // }

   char search[MAX] = "search";
    if (strstr(input,search)!=NULL){
        for(i=0;i<student_rows;i++){
            if(strcasestr(input,student_array[i].last_name)!=NULL && (strcasestr(input,student_array[i].first_name)!=NULL)){
                fprintf(ngan,"%d,%s,%s,%s,%s,%s,%s",student_array[i].student_id,student_array[i].first_name,student_array[i].last_name,student_array[i].gender,student_array[i].day_of_birth,student_array[i].class_name,student_array[i].country);
            }
      
	    }
	}
    return 0;
}

void display(struct score list[80], int s)
{
    FILE *ngan = fopen("result.csv","w");
    int i;
    fprintf(ngan,"Student ID,Subject ID,Score\n");
    for (i = 0; i < s; i++)
    {
        fprintf(ngan,"%d,%d,%.1f\n", list[i].student_id, list[i].subject_id, list[i].score);
    } 
}

void bsortDesc(struct score list[80], int s)
{
    int i, j;
    struct score temp;
    
    for (i = 0; i < s - 1; i++)
    {
        for (j = 0; j < (s - 1-i); j++)
        {
            if (list[j].score < list[j + 1].score)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            } 
        }
    }
}

