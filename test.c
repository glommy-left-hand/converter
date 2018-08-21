/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月21日 星期二 11时30分28秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
void *thread(void *argv){
    int *c = (int*)argv;
    printf("get parameter %d\n",*c);
 //  *(int *)argv = 100;
   c[0] = 100;
    pthread_exit(NULL);
}
int main(){
    pthread_t tmpid;
    int passid[1] = {102};
    pthread_create(&tmpid,NULL,thread,(void *)passid);
    pthread_join(tmpid,NULL);
    printf("now passid is %d\n",passid[0]);
    return 0;

}
