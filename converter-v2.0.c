/*************************************************************************
    > File Name       : converter.c
    > Author          : ZhenLiu
    > Mail            : m18223255496@163.com
    > Created Time    : 2018年08月20日 星期一 18时33分22秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int addLargeNum(int *addition1,int *addition2,int num);
int doubleLargeNum(int * multiplication1,int num); 

int main(int argc,char *argv[])
{
    int digitNum = atoi(argv[1]);
    int inputDigit[digitNum];
    char inputStr[digitNum];
	int weightNum[digitNum];
    int result[digitNum];

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

    }

    for(int i =0;i<digitNum;i++){
        result[i] = 0;
        weightNum[i] = 0;
    }
    weightNum[digitNum-1] = 1;
    
    for(int i = digitNum-1;i >= 0;i--){
        if(inputDigit[i] == 1)
            if(addLargeNum(result,weightNum,digitNum) == -1){
                printf("overflow\n");
                return -1;
            }
        doubleLargeNum(weightNum,digitNum);
    }
    printf("\nresult       : ");
    bool startIsZero = true;
    for(int i =0;i<digitNum;i++){
        if(startIsZero)
            startIsZero = (result[i] == 0)?true:false;
        if(startIsZero)continue;
        printf("%d",result[i]);
    }   
    printf("\n");
    return 0;
}
int addLargeNum(int *addition1,int *addition2,int num){
    int addCarry=0;
    for(int i = num-1;i >=0 ; i--){
        int tmpAddition = (addition1[i] + addition2[i] + addCarry)%10;
        addCarry = (addition1[i] + addition2[i] + addCarry)/10;
        addition1[i] = tmpAddition;
    }
    if(addCarry == 0)
        return 0;
    else
        return -1; 
}
int doubleLargeNum(int *result,int num){
    int multiCarry = 0;
     for(int i = num-1;i >= 0; i--){
        int tmpMulti = (result[i] << 1) + multiCarry;
        multiCarry = tmpMulti / 10;
        result[i] = tmpMulti % 10;
    }
    if(multiCarry !=0)
    return -1;
    return 0;
}
