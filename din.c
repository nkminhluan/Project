#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct diem{
    char student_ID[1024];
    char sub_ID[1024];
    float diem_ID;
}dict;

typedef struct dssv{
    char student_ID[1024];
    char firstname[1024];
    char lastname[1024]; 
    char gender[1024];
    char date[1024];
    int classname;
    char country[1024];

}dict1;

void printvalues(char *filename,dict values[],int field_diem,dict1 values1[],int field_dssv);
void printvalues1(char *filenname,dict1 values1[],int field_dssv, char *user);
int str_remove(char *str);
void stringlowercase(char *s);

int countOccurrences(char * str, char * toSearch)
{
    int i, j, found, count;
    int stringLen, searchLen;

    stringLen = strlen(str);      // length of string
    searchLen = strlen(toSearch); // length of word to be searched

    count = 0;

    for(i=0; i <= stringLen-searchLen; i++)
    {
        /* Match word with string */
        found = 1;
        for(j=0; j<searchLen; j++)
        {
            if(str[i + j] != toSearch[j])
            {
                found = 0;
                break;
            }
        }

        if(found == 1)
        {
            count++;
        }
    }

    return count;
}


int count_columns(char *line)
{
    int cnt = 0;

    for (int i = 0; line[i]; i++)
    {
        if (line[i] == ',')
        {
            cnt++;
        }
    }

    return (cnt + 1);
}

char **read_csv(char *line, int *arr_len)
{
    int col_count = 0;

    *arr_len = count_columns(line);

    char **arr = (char **)malloc((*arr_len) * sizeof(char *));
    char *tmp = strdup(line);

    char *token = strtok(tmp, ",");
    while (token)
    {
        int len_field = strlen(token);
        int bytes_to_copy = token[len_field - 1] == '\n'
                            ? len_field
                            : (len_field + 1);
        char *col = (char *)malloc(sizeof(char) * bytes_to_copy);
        strncpy(col, token, bytes_to_copy);
        col[bytes_to_copy - 1] = 0;

        arr[col_count++] = col;

        token = strtok(NULL, ",");
    }

    free(tmp);

    return arr;
}

int main(int argc, char **argv)
{
    FILE *fp = fopen("dssv.csv", "r");

    if (!fp)
    {
        printf("Can't open file %s\n", argv[1]);
        return 0;
    }
    char str2[100];
    char buf[1024],search[1024];
    int row_count = 0,male=0,female=0;
    while (fgets(buf, 1024, fp))
    {
        if (++row_count == 1)
        {
            continue;
        }

        int arr_len = 0;
        char **arr = read_csv(buf, &arr_len);
        //printf("Subject ID: %s\n", arr[0]);
        //printf("Subject name: %s\n", arr[1]);
        //printf("%s\n", arr[3]);
          
        strcat(str2, arr[3]);
        strcat(str2," ");  
        //printf("Job title: %s\n\n", arr[3]);
        
    }
    //printf("%s",str2);


    char top[1024] = "top n";

    char cm[1024] = "count male";
    char cf[1024] = "count female";

    char user[1024];
    printf("Input: ");
    gets(user);
    //if(strcmp(user,cm)==0){
        //male = countOccurrences(str2, "Male");
        //printf("Total occurrences of '%s': %d", "Male", male);
    //}
    // if(strcmp(user,cf)==0){
    //     female = countOccurrences(str2, "Female");
    //     printf("Total occurrences of '%s': %d", "Female", female);
    // }


    FILE *fp1 = fopen("diem.csv","r");

    if (!fp1)
    {
        printf("Can't open file %s\n", argv[1]);
        return 0;
    }

    char buff[1024];
    int row_diem = 0;
    int field_diem = 0;
    int i;
    dict values[999];
    while(fgets(buff,1024, fp1)){

        field_diem = 0;
        row_diem++;
        if(row_diem==1)
        {
            continue;
        }
        char *field = strtok(buff,", ");

        while(field){ 
            if(field_diem==0){
                
                strcpy(values[i].student_ID,field);
            }
            if(field_diem==1){
                strcpy(values[i].sub_ID,field);
            }
            if(field_diem==2){
                values[i].diem_ID = atof(field);
            }
            field = strtok(NULL,", ");
            field_diem++;
        }
        i++;
    }

    FILE *fp2 = fopen("dssv.csv", "r");

    if (!fp2)
    {
        printf("Can't open file %s\n", argv[1]);
        return 0;
    }
    char buff_dssv[1024];
    int row_dssv = 0;
    int field_dssv = 0;
    int n=0;
    dict1 values1[999];
    while(fgets(buff_dssv,2000, fp2)){
        
        field_dssv = 0;
        row_dssv++;
        if(row_dssv==1)
        {
            continue;
        }
        char *field2 = strtok(buff_dssv,", ");
        
        while(field2){ 
            if(field_dssv==0){
                strcpy(values1[n].student_ID,field2);
            }
            if(field_dssv==1){
                strcpy(values1[n].firstname,field2);
            }
            if(field_dssv==2){
                strcpy(values1[n].lastname,field2);
            }
            if(field_dssv==3){
                strcpy(values1[n].gender,field2);
            }
            if(field_dssv==4){
                strcpy(values1[n].date,field2);
            }
            if(field_dssv==5){
                values1[n].classname = atoi(field2);
            }           
            if(field_dssv==6){
                strcpy(values1[n].country,field2);
            } 

            field2 = strtok(NULL,", ");
            field_dssv++;
        }
        //printf("%d",row_dssv);
        n++;
    }    


    char sortas[1024] = "sort asc";

    
    if(strstr(user,"count female")!=NULL){
        FILE* fp3=fopen("result.csv","w");
        if(!fp3){
            printf("Error opening");
        }
        fprintf(fp3,"Student ID,First name,Last name,Gender,Date of birth,Classname,Country\n");
        for(int i=0;i<row_dssv-1;i++){
            if(strcmp(values1[i].gender,"Female")==0){
                fprintf(fp3,"%s,%s,%s,%s,%s,%d,%s",values1[i].student_ID,values1[i].firstname,values1[i].lastname,values1[i].gender,values1[i].date,values1[i].classname,values1[i].country);
            }
        }
    
    }


    if(strstr(user,"count male")!=NULL){
        FILE* fp3=fopen("result.csv","w");
        if(!fp3){
            printf("Error opening");
        }
        fprintf(fp3,"Student ID,First name,Last name,Gender,Date of birth,Classname,Country\n");
        for(int i=0;i<row_dssv-1;i++){
            if(strcmp(values1[i].gender,"Male")==0){
                fprintf(fp3,"%s,%s,%s,%s,%s,%d,%s",values1[i].student_ID,values1[i].firstname,values1[i].lastname,values1[i].gender,values1[i].date,values1[i].classname,values1[i].country);
            }
        }
    
    }


    char listclass[1024] = "list";

    if(strstr(user,listclass)!=NULL){
        FILE* fp3=fopen("result.csv","w");
        if(!fp3){
            printf("Error opening");
        }
        fprintf(fp3,"Student ID,First name,Last name,Gender,Date of birth,Classname,Country\n");
        const char ch = '<';
        char *str;

        str = strchr(user, ch);
        
        //printf("Chuoi dang sau dau |%c| la: %s \n", ch, str+1);
        str = str+1;
        //printvalues1(values1,(row_dssv)-1);
        //printf("%s",str);
        
        int x = str_remove(str);
        //printf("%d",str_remove(str));
        //printvalues1(values1,(row_dssv)-1);
            for(int i=0;i<row_dssv-1;i++){
                if(x==values1[i].classname){
                    fprintf(fp3,"%s,%s,%s,%s,%s,%d,%s",values1[i].student_ID,values1[i].firstname,values1[i].lastname,values1[i].gender,values1[i].date,values1[i].classname,values1[i].country);
                
                }
            }
   }
    char searched[1024] = "search";
    
    if(strstr(user,searched)!=NULL){
        FILE* fp3=fopen("result.csv","w");
        if(!fp3){
            printf("Error opening");
        }
        fprintf(fp3,"Student ID,First name,Last name,Gender,Date of birth,Classname,Country\n");
        for(int i=0;i<row_dssv-1;i++){
            if(strcasestr(user,values1[i].lastname)!=NULL && (strcasestr(user,values1[i].firstname)!=NULL)){
                fprintf(fp3,"%s,%s,%s,%s,%s,%d,%s",values1[i].student_ID,values1[i].firstname,values1[i].lastname,values1[i].gender,values1[i].date,values1[i].classname,values1[i].country);
            }

        }
    }

    if(strcmp(user,top)==0){
        printvalues("result.csv",values, row_diem-1,values1,row_dssv-1);
        for(i=0;i<row_diem;i++){
            //printf("%s",values[i].student_ID);
            for(int j=0;j<row_dssv-1;j++){
                if(strstr(values[i].student_ID,values1[j].student_ID)==NULL){
                    printf("%s\n",values1[j].firstname);
                }
            }
        }
    }

    char sortde[100]="sort desc";
    if(strcmp(user,sortas)==0 || strcmp(user,sortde)==0){
        printvalues1("result.csv",values1,row_dssv-1,user);
      
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
int comparator(const void* p, const void* q)
{
    if (((struct diem *)p)->diem_ID == ((struct diem *)q)->diem_ID)
        return 0;
    return (((struct diem *)p)->diem_ID > ((struct diem *)q)->diem_ID) ? -1 : 1;
}

int comparatorname(const void* p, const void* q)
{
    return strcmp(((struct dssv*)p)->lastname,
                  ((struct dssv*)q)->lastname);
}
  
int comparatorname2(const void* p, const void* q)
{
    return strcmp(((struct dssv*)q)->lastname,
                  ((struct dssv*)p)->lastname);
}
  

void printvalues(char *filename,dict values[],int field_diem,dict1 values1[],int field_dssv){
    FILE* fp3=fopen(filename,"w");
    if(!fp3){
        printf("Error opening");
    }

    fprintf(fp3,"StudentId,Subject ID,Score,First name\n");
    //printf("StudentId,Subject ID,Score\n");
    qsort(values, field_diem, sizeof(struct diem), comparator);
    for(int i=0;i<field_diem;i++){
        for(int j=0;j<field_dssv;j++){ 
            if(strcmp(values[i].student_ID,values1[j].student_ID)==0){
                fprintf(fp3,"%s,%s,%.1f,%s\n",values[i].student_ID,values[i].sub_ID,values[i].diem_ID,values1[j].firstname);
            }
        }
        
    }
    fclose(fp3);
}

void printvalues1(char *filename,dict1 values1[],int field_dssv,char *user){
    FILE* fp3=fopen(filename,"w");
    if(!fp3){
        printf("Error opening");
    }
    
    //printf("%s",values1[2].firstname);
    fprintf(fp3,"StudentId,Firstname,Lastname,Gender,Date,Classname,Country\n");
    if(strcmp(user,"sort asc")==0){
        qsort(values1, field_dssv, sizeof(struct dssv), comparatorname);
    }
    if(strcmp(user,"sort desc")==0){
        qsort(values1, field_dssv, sizeof(struct dssv), comparatorname2);
    }
    for(int i=0;i<field_dssv;i++){
        
        fprintf(fp3,"%s,%s,%s,%s,%s,%d,%s",values1[i].student_ID,values1[i].firstname,values1[i].lastname,values1[i].gender,values1[i].date,values1[i].classname,values1[i].country);
    }
    
}

int str_remove(char *str){
        //char str[MAX_SIZE];
    int i, j, found, index;
    int stringLen, wordLen;
	char word[1024] = ">";

    /* Input string and word from user */
    //printf("Enter any string: ");
    //gets(str);
 
    stringLen = strlen(str);  // Length of string
    wordLen   = strlen(word); // Length of word

    /*
     * Run loop from start to end of string - word length
     */
    index = -1;
    for(i=0; i<stringLen - wordLen+1; i++)
    {
        // Match word at current position
        found = 1;
        for(j=0; j<wordLen; j++)
        {
            // If word is not matched
            if(str[i+j] != word[j])
            {
                found = 0;
                break;
            }
        }

        // If word is found then update index
        if(found == 1)
        {
            index = i;
        }
    }

    // If word not found
    if(index == -1)
    {
        printf("'%s'","not found.");
    }
    else
    {
        /*
         * Shift all characters from right to left
         */
        for(i=index; i <= stringLen - wordLen; i++)
        {
            str[i] = str[i + wordLen];
        }

    }
	//printf("String after removing last '%s': \n%s", word, str);
    int x = atoi(str);
    //printf("%d",x);
    return x;
}
void stringlowercase(char *s)
{
	int i;
 
    	for(i=0;s[i];i++)  
        {
          if(s[i]>=65 && s[i]<=90)
          s[i]+=32;
 	    }

}