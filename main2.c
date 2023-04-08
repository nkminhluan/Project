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



int main()
{
    FILE *fp = fopen("dssv.csv", "r");

    if (!fp)
    {
        printf("Can't open file");
        return 0;
    }
    char str2[100];
    char buf[1024],search[1024];
    int row_count = 0,male=0,female=0;
    // while (fgets(buf, 1024, fp))
    // {
    //     if (++row_count == 1)
    //     {
    //         continue;
    //     }

    //     int arr_len = 0;
    //     char **arr = read_csv(buf, &arr_len);
        //printf("Subject ID: %s\n", arr[0]);
        //printf("Subject name: %s\n", arr[1]);
        //printf("%s\n", arr[3]);
          
        //strcat(str2, arr[3]);
        //strcat(str2," ");  
        //printf("Job title: %s\n\n", arr[3]);
        
    //}
    //printf("%s",str2);


    char top[1024] = "top n";
    char cm[1024] = "count male";
    char cf[1024] = "count female";
    char user[1024];
    //printf("Input: ");
    scanf("%[^\n]s", user);
    //gets(user);
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
        printf("Can't open file");
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
        i=i+1;
    }

    FILE *fp2 = fopen("dssv.csv", "r");

    if (!fp2)
    {
        printf("Can't open file");
        return 0;
    }
    char buff_dssv[1024];
    int row_dssv = 0;
    int field_dssv = 0;
    int n=0;
    dict1 values1[999];
    while(fgets(buff_dssv,1024, fp2)){
        
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
        n= n+1;
    }    

    char sortas[1024] = "sort asc";
    
    if(strstr(user,"count female")!=NULL){
        FILE* fp3=fopen("result.csv","w");
        if(!fp3){
            printf("Error opening");
        }
        fprintf(fp3,"Student ID,First name,Last name,Gender,Date of birth,Classname,Country\n");
        for(i=0;i<row_dssv-1;i++){
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
        for(i=0;i<row_dssv-1;i++){
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
            for(i=0;i<row_dssv-1;i++){
                if(x==values1[i].classname){
                    fprintf(fp3,"%s,%s,%s,%s,%s,%d,%s",values1[i].student_ID,values1[i].firstname,values1[i].lastname,values1[i].gender,values1[i].date,values1[i].classname,values1[i].country);
                
                }
            }
   }

    char searched[1024] = "search";
    if(strstr(user,searched)!=NULL){
        int found=0;
        FILE* fp3=fopen("result.csv","w");
        if(!fp3){
            printf("Error opening");
        }
        fprintf(fp3,"Student ID,First name,Last name,Gender,Date of birth,Classname,Country\n");
        for(i=0;i<row_dssv-1;i++){
            if(strcasestr(user,values1[i].lastname)!=NULL && (strcasestr(user,values1[i].firstname)!=NULL)){
                fprintf(fp3,"%s,%s,%s,%s,%s,%d,%s",values1[i].student_ID,values1[i].firstname,values1[i].lastname,values1[i].gender,values1[i].date,values1[i].classname,values1[i].country);
                found=found +1;
            }
        }
        if(found==0){
            printf("Not found");
        }
    }

    if(strcmp(user,top)==0){
        int j;
        printvalues("result.csv",values, row_diem-1,values1,row_dssv-1);
        for(i=0;i<row_diem;i++){
            //printf("%s",values[i].student_ID);
            for(j=0;j<row_dssv-1;j++){
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
    //fclose(fp3);
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
    return strcmp(((struct dssv*)p)->lastname,((struct dssv*)q)->lastname);
}
  
int comparatorname2(const void* p, const void* q)
{
    return strcmp(((struct dssv*)q)->lastname,((struct dssv*)p)->lastname);
}
  

void printvalues(char *filename,dict values[],int field_diem,dict1 values1[],int field_dssv){
    FILE* fp3=fopen(filename,"w");
    if(!fp3){
        printf("Error opening");
    }
    int i,j;
    fprintf(fp3,"StudentId,Subject ID,Score,First name\n");
    //printf("StudentId,Subject ID,Score\n");
    qsort(values, field_diem, sizeof(struct diem), comparator);
    for(i=0;i<field_diem;i++){
        for(j=0;j<field_dssv;j++){ 
            if(strcmp(values[i].student_ID,values1[j].student_ID)==0){
                fprintf(fp3,"%s,%s,%.1f,%s,%s\n",values[i].student_ID,values[i].sub_ID,values[i].diem_ID,values1[j].firstname,values1[j].lastname);
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
    int i;
   
    fprintf(fp3,"StudentId,Firstname,Lastname,Gender,Date,Classname,Country\n");
    if(strcmp(user,"sort asc")==0){
        qsort(values1, field_dssv, sizeof(struct dssv), comparatorname);
    }
    if(strcmp(user,"sort desc")==0){
        qsort(values1, field_dssv, sizeof(struct dssv), comparatorname2);
    }
    for(i=0;i<field_dssv;i++){
        
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

    index = -1;
    for(i=0; i<stringLen - wordLen+1; i++)
    {
        // Match word at current position
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
    int x = atoi(str);
    return x;
}
