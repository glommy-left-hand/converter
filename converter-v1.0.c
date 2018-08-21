/*************************************************************************
    > File Name       : converter.c
    > Author          : ZhenLiu
    > Mail            : m18223255496@163.com
    > Created Time    : 2018年08月20日 星期一 18时33分22秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
int main(int argc,char *argv[])
{
    int digitNum = atoi(argv[1]);
    char inputStr[digitNum];
    FILE *file = fopen("data.txt","r+") ;
    if(file == NULL){ printf("Error when open the file! File does not exist!\n"); return -1;}
       fgets(inputStr,digitNum+1,file);
    printf("input string :%20.20s",inputStr);
    if(digitNum > 20)printf("...");
    printf("\n");
    for(int i = 0; i< digitNum;i++){
        if(inputStr[i] != '0' && inputStr[i]!='1'){ printf("Error input num,please check out!\n"); return -1;}    
    }
	u_int64_t result = 0;
	result = strtol(inputStr,NULL,2);
	printf("convert result %lu\n",result);
    return 0;
}
