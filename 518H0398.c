#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct dssv 
{
	int student_id;
	char first_name[1024];
	char last_name[1024];
	char gender[1024];
	char date[1024];
	char class[1024];
	char country[1024];
}struct_student;

typedef struct monhoc
{
	int subject;
	char subject_name[1024];
	int credit;
}struct_subject;

typedef struct diem
{
	int student_id;
	int subject;
	float score;
}struct_score;

typedef struct student_avg_score
{
	int student_id;
	float score;
}STD_AVG_SCORE;

void searchstudent(char* user,struct_student stu_arr[],const int rows_csv_stu);
void searching(char* user, struct_student stu_arr[], int rows_csv_stu);
const int count_csv(char* files)
{
	FILE *fp;
    int count = 0;  
    char c;  
    
    fp = fopen(files, "r");
    
    if (!fp)
    {
        printf("Khong mo duoc file %s", files);
        return 0;
    }
  
    
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') 
            count++;
  
    
    fclose(fp);
    return count;
}

void read_subject_csv(struct_subject monhoc[], const char* path)
{
	FILE* fp = fopen(path, "r");
  	
    if (!fp)
        printf("Khong mo duoc file\n");
  
    else 
	{
        char bufer_subject[1024];
        int row_subject = 0,column_subject = 0;
        while (fgets(bufer_subject,1024, fp)) 
		{
			if (row_subject == 0)
			{
				row_subject++;
                continue;
			}
			column_subject = 0;
            char* values_subject = strtok(bufer_subject, ",");
            while (values_subject) 
			{
                if (column_subject == 0) 
				{
                    monhoc[row_subject-1].subject = atoi(values_subject);
                	values_subject = strtok(NULL, ",");
                }
   
                if (column_subject == 1) 
				{
                    strcpy(monhoc[row_subject-1].subject_name, values_subject);
                	values_subject = strtok(NULL, ",");
                }
  
                if (column_subject == 2) 
				{
                    monhoc[row_subject-1].credit = atoi(values_subject);
                	values_subject = strtok(NULL, ",");
                }
                column_subject++;
            }
            row_subject++;
        }
    }
    fclose(fp);
}

void read_score_csv(struct_score diem[], const char* path)
{
	FILE* fp = fopen(path, "r");
  
    if (!fp)
        printf("Can't open file\n");
  
    else 
	{
        char bufer_score[1024];
        int row_score = 0;
        int column_score = 0;
        while (fgets(bufer_score,1024, fp)) 
		{
			if (row_score == 0)
			{
				row_score++;
                continue;
			}
			column_score = 0;
            char* values_score = strtok(bufer_score, ",");
  
            while (values_score) 
			{
                if (column_score == 0) 
				{
                    diem[row_score-1].student_id = atoi(values_score);
                	values_score = strtok(NULL, ",");
                }
                if (column_score == 1) 
				{
                    diem[row_score-1].subject = atoi(values_score);
                	values_score = strtok(NULL, ",");
                }
                if (column_score == 2) 
				{
                    diem[row_score-1].score = atof(values_score);
                	values_score = strtok(NULL, ",");
                }
                column_score++;
            }
            //printf("\n");
            row_score++;
        }
    }
    // Close the file
    fclose(fp);
}

void read_student_csv(struct_student dssv[], const char* path)
{
	FILE* fp = fopen(path, "r");
  
    if (!fp)
        printf("Can't open file\n");
  
    else 
	{
        char bufer_dssv[1024];
  
        int row_dssv = 0;
        int column_dssv = 0;
  
        while (fgets(bufer_dssv,1024, fp)) 
		{
			
			if (row_dssv == 0)
			{
				row_dssv++;
                continue;
			}
			
			column_dssv = 0;

            char* values_dssv = strtok(bufer_dssv, ",");
  
            while (values_dssv) 
			{

                if (column_dssv == 0) 
				{
                    dssv[row_dssv-1].student_id = atoi(values_dssv);
                	values_dssv = strtok(NULL, ",");
                }
                if (column_dssv == 1) 
				{
                    strcpy(dssv[row_dssv-1].first_name, values_dssv);
                	values_dssv = strtok(NULL, ",");
                }
                if (column_dssv == 2) 
				{
                    strcpy(dssv[row_dssv-1].last_name, values_dssv);
                	values_dssv = strtok(NULL, ",");
                }
                if (column_dssv == 3) {

                    strcpy(dssv[row_dssv-1].gender, values_dssv);
                	values_dssv = strtok(NULL, ",");
                }
                if (column_dssv == 4) 
				{
                    strcpy(dssv[row_dssv-1].date, values_dssv);
                	values_dssv = strtok(NULL, ",");       
                }
                if (column_dssv == 5) 
				{
                    strcpy(dssv[row_dssv-1].class, values_dssv);
               	 	values_dssv = strtok(NULL, ",");      
                }
                if (column_dssv == 6) 
				{
                    strcpy(dssv[row_dssv-1].country, values_dssv);
                	values_dssv = strtok(NULL, ",");    
                }
                column_dssv++;
            }

            row_dssv++;
        }
    }
    fclose(fp);
}

void list(char* class, struct_student stu_arr[], int rows_csv_stu)
{
	FILE* fp = fopen("result.csv", "w");
    int list =0;
	for (int i=0;i<rows_csv_stu;i++)
	{
		if (strcmp(stu_arr[i].class, class)==0)
		{   list++;
			fprintf(fp, "%d,%s,%s,%s,%s,%s,%s", stu_arr[i].student_id, stu_arr[i].first_name, 
			stu_arr[i].last_name, stu_arr[i].gender, stu_arr[i].date, stu_arr[i].class, stu_arr[i].country);
		}
	}
    if(list==0){
        fprintf(fp,"Not found");
    }
	fclose(fp);
}
void count(char* gender, struct_student stu_arr[], int rows_csv_stu)
{
	FILE* fp = fopen("result.csv", "w");
    int count =0,i=0;
	for (i=0;i<rows_csv_stu;i++)
	{
		if (strcmp(stu_arr[i].gender, gender)==0)
		{
            count++;
			//fprintf(fp, "%d,%s,%s,%s,%s,%s,%s", stu_arr[i].student_id, stu_arr[i].first_name, 
			//stu_arr[i].last_name, stu_arr[i].gender, stu_arr[i].date, stu_arr[i].class, stu_arr[i].country);
		}
	}
    fprintf(fp,"%d",count);
	fclose(fp);
}
void searching(char* user, struct_student stu_arr[], int rows_csv_stu){
        FILE* fp3 = fopen("result.csv","w");
        int found =0,i=0;
        for(i=0;i<=rows_csv_stu;i++){
            if(strstr(user,stu_arr[i].last_name)!=NULL && (strstr(user,stu_arr[i].first_name)!=NULL)){
                fprintf(fp3,"%d,%s,%s,%s,%s,%s,%s",stu_arr[i].student_id,stu_arr[i].first_name,stu_arr[i].last_name,stu_arr[i].gender,stu_arr[i].date,stu_arr[i].class,stu_arr[i].country);
                found++;
            }
    
        }
        if(found==0){
            fprintf(fp3,"Not found");   
        }
        
}
void swap(STD_AVG_SCORE *x, STD_AVG_SCORE *y)
{
    STD_AVG_SCORE temp = *x;
    *x = *y;
    *y = temp;
}
  

void bubble_sort(STD_AVG_SCORE std_avg_score[], int n)
{   
    int i=0;
   	for (i = 0; i < n-1; i++)
       // Last i elements are already in place   
       	for (int j = 0; j < n-i-1; j++) 
        	if (std_avg_score[j].score < std_avg_score[j+1].score)
        		swap(&std_avg_score[j], &std_avg_score[j+1]);
}

void top(struct_score scr_arr[], const int rows_csv_score, struct_student stu_arr[], const int rows_csv_stu, int n)
{
	FILE* fp = fopen("result.csv", "w");
	STD_AVG_SCORE std_avg_score[rows_csv_stu];
	
	int num_subject = rows_csv_score/rows_csv_stu;
	int k = 0,i = 0;
    int j =i;
	for (i=0;i<rows_csv_score-num_subject;i+=num_subject)
	{
		std_avg_score[k].score = 0;
		std_avg_score[k].student_id = scr_arr[i].student_id;
		for (j=i;j<i+num_subject;j++)
			std_avg_score[k].score += scr_arr[j].score;
		k++;
	}

	bubble_sort(std_avg_score, rows_csv_stu);
	for (k=0;k<n;k++)
	{
		for(i=0;i<rows_csv_stu;i++)
		{
			if (std_avg_score[k].student_id == stu_arr[i].student_id)
			{
				fprintf(fp, "%d,%s,%s,%s,%s,%s,%s", stu_arr[i].student_id, stu_arr[i].first_name, 
				stu_arr[i].last_name, stu_arr[i].gender, stu_arr[i].date, stu_arr[i].class, stu_arr[i].country);	
				break;
			}
		}
	}
	
	fclose(fp);
}

int str_remove(char *str){

    int i, j, found, index;
    int stringLen, wordLen;
	char word[1024] = ">";

 
    stringLen = strlen(str);  // Length of string
    wordLen   = strlen(word); // Length of word

    index = -1;
    for(i=0; i<stringLen - wordLen+1; i++)
    {
        found = 1;
        for(j=0; j<wordLen; j++)
        {
           
            if(str[i+j] != word[j])
            {
                found = 0;
                break;
            }
        }

        if(found == 1)
        {
            index = i;
        }
    }
    if(index == -1)
    {
        printf("'%s'","not found.");
    }
    else
    {
        for(i=index; i <= stringLen - wordLen; i++)
        {
            str[i] = str[i + wordLen];
        }

    }
    return 0;
}
int struct_cmp_by_product(const void *a, const void *b) 
{ 
    struct dssv *ia = (struct dssv *)a;
    struct dssv *ib = (struct dssv *)b;
    return strcmp(ia->first_name,ib->first_name);
}
int reverse(const void *a, const void *b) 
{ 
    struct dssv *ia = (struct dssv *)a;
    struct dssv *ib = (struct dssv *)b;
    return strcmp(ib->first_name, ia->first_name);
}

void printlist(char *user,struct_student stu_arr[],const int rows_csv_stu){
    if(strstr(user,"list")!=NULL){
        const char ch = '<';
        char *str;
        str = strchr(user, ch);
    //printf("Chuoi dang sau dau |%c| la: %s \n", ch, str+1);
        str = str+1;
        str_remove(str);
        list(str, stu_arr, rows_csv_stu);
    }
}

void searchstudent(char* user,struct_student stu_arr[],const int rows_csv_stu){
    if(strstr(user,"search")!=NULL){
        FILE* fp3=fopen("result.csv","w");
        searching(user,stu_arr,rows_csv_stu);
	}

}

void topn(char* user,struct_student stu_arr[],struct_score scr_arr[],const int rows_csv_stu,const int rows_csv_score){
    if(strstr(user,"top")!=NULL){
        FILE* fp3=fopen("result.csv","w");
        char *date = malloc(10);
        char *day = NULL;
        char *month=NULL;
        strcpy(date,user);
        day=strtok(date," ");
        month = strtok(NULL," ");
        top(scr_arr, rows_csv_score, stu_arr, rows_csv_stu, atoi(month));
    }
}
void countmale(char* user,struct_student stu_arr[],const int rows_csv_stu){ 
    if((strcmp(user,"count Female")==0) || (strcmp(user,"count female")==0)){
        count("Female", stu_arr, rows_csv_stu);
    }
}
void countfemale(char* user,struct_student stu_arr[],const int rows_csv_stu){
    if((strcmp(user,"count Male")==0) || (strcmp(user,"count male")==0)){
        count("Male", stu_arr, rows_csv_stu);
    }
}
int main()
{
    // read dssv csv
    const int rows_csv_stu = count_csv("dssv.csv");
    struct_student stu_arr[rows_csv_stu];
    read_student_csv(stu_arr, "dssv.csv");
    // read score csv
    const int rows_csv_score = count_csv("diem.csv");
    struct_score scr_arr[rows_csv_score];
    read_score_csv(scr_arr, "diem.csv");
    // read subject csv
    // const int subject_rows = count_csv("dsmh.csv")-1;
    // struct_subject subject_array[subject_rows];
    // read_subject_csv(subject_array, "dsmh.csv");
    char user[1024];
    scanf("%[^\n]s", user);

    countmale(user,stu_arr,rows_csv_stu);
    countfemale(user,stu_arr,rows_csv_stu);
    printlist(user,stu_arr,rows_csv_stu);
    searchstudent(user,stu_arr,rows_csv_stu);
    topn(user,stu_arr,scr_arr, rows_csv_stu,rows_csv_score);

            
    if(strstr(user,"sort asc")!=NULL){ 
        FILE *fp3=fopen("result.csv","w");
        qsort(stu_arr,rows_csv_stu,sizeof(struct dssv),struct_cmp_by_product);
        for(int i=0;i<rows_csv_stu;i++){
            fprintf(fp3, "%d,%s,%s,%s,%s,%s,%s", stu_arr[i].student_id, stu_arr[i].first_name, 
				stu_arr[i].last_name, stu_arr[i].gender, stu_arr[i].date, stu_arr[i].class, stu_arr[i].country);
        }
    }
    
    if(strstr(user,"sort desc")!=NULL){ 
        FILE *fp3=fopen("result.csv","w");
        qsort(stu_arr,rows_csv_stu,sizeof(struct dssv),reverse);
        for(int i=0;i<rows_csv_stu;i++){
            fprintf(fp3, "%d,%s,%s,%s,%s,%s\n", stu_arr[i].student_id, stu_arr[i].first_name, 
                stu_arr[i].last_name, stu_arr[i].gender, stu_arr[i].date, stu_arr[i].class);
        }
    }
    return 0;
}




