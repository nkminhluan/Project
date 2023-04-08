#include <stdio.h>
#include <string.h>
typedef struct key_value{
    char id[100];
    char timestamp[100];
    float score;
}dict;
int main()
{
    // Substitute the file_path string
    // with full path of CSV file
    FILE* fp = fopen("diem.csv", "r");
    if(!fp){
        printf("Cannot open file");
    }
    char buff[1024];
    int row_count = 0;
    int fiel_count = 0;
    dict values[999];
    FILE* fp2 = fopen("result.csv", "w");
    int i;
    while(fgets(buff, sizeof(buff), fp)){
        fprintf(fp2,"%s", buff);
    }
}