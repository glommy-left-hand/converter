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
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define Int(X) (X - '0') /**************/

int addLargeNum(int *addition1,int *addition2,int num);
int powLargeNum(int *result,int base,int frequency,int num);
int multiLargeNum(int * multiplication1,int *multiplication2,int base,int num); 
int multiLargeNumHelp(int *result,int multiplication2,int num);
int *multiBigInteger(const char *num1, const char *num2);
void *convertThread(void *parameters);
void printfLargeNum(int *result,int totalLen);

struct convertParm{
    int *digit;
    int *result;
    int totalLen;
    int digitLen;
    int startPos;
    int threadLen;
};


int main(int argc,char *argv[])
{
    int digitNum = atoi(argv[1]);
    int inputDigit[digitNum];
    char inputStr[digitNum];
	int weightNum[digitNum];


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
    int threadNum=digitNum/10000;
    threadNum+=(digitNum%10000==0)?0:1;
    int **tmpresult;
    tmpresult =(int **) malloc(threadNum * sizeof(int *));
    for(int i =0;i<threadNum;i++)
        tmpresult[i] =  (int *)malloc (digitNum * sizeof(int ));
    pthread_t tidp[threadNum];
    int ddd[digitNum];
    struct convertParm b[threadNum];
    printf("down in here threadNum:%d \n",threadNum);   
    for(int i =0;i<threadNum;i++){
       // b[i] = (struct convertParm *)malloc(sizeof(struct convertParm));  
        b[i].digit = inputDigit;
        b[i].result = tmpresult[i];
        b[i].totalLen = digitNum;
        b[i].startPos = i * 10000;
        if(i == threadNum-1)
        {
            b[i].threadLen = digitNum - i*10000;
        }else
            b[i].threadLen = 10000;
        printf("start to create thread\n");
        pthread_create(&tidp[i], NULL, convertThread, (void*)&b[i]);
    }
    int result[digitNum];for(int i =0;i<digitNum;i++)result[i] =0;
    for(int i =threadNum-1;i>=0;i--){
        pthread_join(tidp[i], NULL);
        addLargeNum(result,tmpresult[i],digitNum);
        // printf("\nthread %d result :\n",i);
        // printfLargeNum(tmpresult[i],digitNum);
    }
    printf("\ntotal result :");
    printfLargeNum(result,digitNum);
    printf("\n");

    
    for(int i =0;i<threadNum;i++)
        free((void *)tmpresult[i]); 
    free((void *)tmpresult);
    return 0;
}

void *convertThread(void *parameters){
    struct convertParm *ConvertParm;
    ConvertParm = (struct convertParm *)parameters;
    int *inputDigit = ConvertParm->digit;
    int totalLen = ConvertParm->totalLen;
    int *result = ConvertParm->result; 
    int startPos = ConvertParm->startPos;
    int threadLen = ConvertParm->threadLen;
    int weightNum[ConvertParm->totalLen];

    for(int i = 0; i < totalLen;i++){
        weightNum[i] = 0;
        result[i] = 0;
    }

    weightNum[totalLen - 1]= 1;
    powLargeNum(weightNum,2,totalLen- startPos - threadLen,totalLen);

    for(int i = startPos+threadLen-1;i >= startPos;i--){
        //printf("%d ",inputDigit[i]);
        if(inputDigit[i] == 1)
            if(addLargeNum(result,weightNum,totalLen) == -1){
                printf("overflow\n");
                break;
            }
        multiLargeNumHelp(weightNum,2,totalLen);
    }
    // printf("\nthread result: ");

    // bool startIsZero = true;
    // printfLargeNum(result,totalLen); 
    // printf("\nend thread");



}
void printfLargeNum(int *result,int totalLen){
    bool startIsZero = true;
    for(int i =0;i<totalLen;i++){
        if(startIsZero)
            startIsZero = (result[i] == 0)?true:false;
        if(startIsZero)continue;
        printf("%d",result[i]);
    }  
    printf("\n");
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

int multiLargeNum(int *result,int *multiplication2,int base,int num){
 
    return 0;
}
int multiLargeNumHelp(int *result,int multiplication2,int num){
    int multiCarry = 0;
     for(int i = num-1;i >= 0; i--){
        int tmpMulti;
        if(multiplication2 == 2)
            tmpMulti =  (result[i] << 1) + multiCarry;
        else tmpMulti = result[i] * multiplication2 + multiCarry;
        multiCarry = tmpMulti / 10;
        result[i] = tmpMulti % 10;
    }
    if(multiCarry !=0)
    return -1;
    return 0;
}

int powLargeNum(int *result,int base,int frequency,int num){
    if(frequency == 0)   return 0;
    int multiCarry = 0;
    for(int i = num-1;i >= 0; i--){
        int tmpMulti = (base ==2)?(result[i] <<1) + multiCarry: 
                        result[i] * base + multiCarry;
        multiCarry = tmpMulti / 10;
        result[i] = tmpMulti % 10;
    }
    if(multiCarry !=0)return -1;
    return powLargeNum(result,base,frequency-1,num);
}
