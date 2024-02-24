#include <stdio.h>
#include "StrList.h"

#define TRUE 1
#define FALSE 0
#define STARTING_SIZE 100

void input(char**);

int main()
{
    StrList* StrList = StrList_alloc();
	int i = 0, loop = TRUE, option = 1;
    char* sentence;
    char* inputString =  (char*)malloc(STARTING_SIZE * sizeof(char));
	char* token;

	while (option != 0 && loop == TRUE){
        scanf("%d", &option);
		switch (option) {
            case 0:
                loop = FALSE;
                break;
            case 1:
                scanf("%d ",&i);
				input(&sentence);
                token = strtok(sentence, " ");
                while( token != NULL && i--){
                    StrList_insertLast(StrList, token);
                	token = strtok(NULL, " ");
                }
				free(sentence);
                break;
            case 2:
                scanf("%d",&i);
                scanf("%s",inputString);
                StrList_insertAt(StrList,inputString,i);
                break;
            case 3:
                StrList_print(StrList);
                break;
            case 4:
                printf("%zu\n",StrList_size(StrList));
                break;
            case 5:
                scanf("%d",&i);
                StrList_printAt(StrList,i);
                break;
           case 6:
                printf("%d\n",StrList_printLen(StrList));
                break;
            case 7:
                scanf("%s",inputString);
                printf("%d\n",StrList_count(StrList,inputString));
                break;
            case 8:
                scanf("%s",inputString);
                StrList_remove(StrList, inputString);
                break;
            case 9:
                scanf("%d",&i);
                StrList_removeAt(StrList,i);
                break;
            case 10:
                StrList_reverse(StrList);
                break;
            case 11:
                StrList_free(StrList);
                StrList = StrList_alloc();
                break;
            case 12:
                StrList_sort(StrList);
                break;
            case 13:
                StrList_isSorted(StrList)?printf("true\n"):printf("false\n");
                break;
            default:
                continue;
        }
    }
    StrList_free(StrList);
    free(inputString);
    return 0;
}

void input(char **inputString)
{
	char inputChar = '0';
	int size = STARTING_SIZE, len = 0;

	*inputString =  (char*)malloc(STARTING_SIZE * sizeof(char));
	while(inputChar!='\n' && inputChar!=EOF)
	{
		inputChar = getchar();
		if(len>(size-1))
		{
			size*=2;
			*inputString = (char*)realloc(*inputString,size);
		}
		if(inputChar!='\n' && inputChar!=EOF) 
        {
            (*inputString)[len++] = inputChar;
        }
	}
    (*inputString)[len-1] = '\0';
}
