#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100 // Maximum string size

void str_remove(char *str);
int main(int argc, char **argv) {
    char user[128];
	printf("Nhap chuoi");
	gets(user);
	const char ch = '<';
	char *str;

	str = strchr(user, ch);

	
	printf("Chuoi dang sau dau |%c| la: %s \n", ch, str+1);
	str  = str+1;

    str_remove(str);
    return 0;
}

void str_remove(char *str){
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
    printf("%d",x);
}
