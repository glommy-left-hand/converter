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
    int inputDigit[digitNum];
    char inputStr[digitNum];
	u_int64_t weightNum[digitNum];
	u_int64_t MaxWeight = pow(2,digitNum-1);

    FILE *file = fopen("data.txt","r+") ;
    if(file == NULL){ printf("Error when open the file! File does not exist!\n"); return -1;}
       fgets(inputStr,digitNum+1,file);
    printf("input string :%20.20s",inputStr);
    if(digitNum > 20)printf("...");
    printf("\n");
    for(int i = 0; i< digitNum;i++){
        inputDigit[i] =(inputStr[i] == '0')?0:
                     (inputStr[i] == '1')?1:-1;
        if(inputDigit[i] == -1){ printf("Error input num,please check out!\n"); return -1;}
		weightNum[i] = MaxWeight;
		MaxWeight = MaxWeight >> 1;
    
    }
	u_int64_t result = 0;
	for(int i = 0; i < digitNum; i++){
        if(inputDigit[i] == 1){
            //due to the special addition
		    result = result | weightNum[i] ;
            //result += weightNum[i];
        }
	}
	printf("convert result %lu\n",result);
    return 0;
}
