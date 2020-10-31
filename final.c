/*
Go to the file directory and open the terminal
then type this command:
	gcc -o final final.c -lpthread
final and final.c are the file names.you can change those
then type this in the terminal:
	./final 10000 10 10
result will be saved inside the result.txt file
*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long tot_sum2;
long sum2[2500];

long tot_sum3;
long sum3[2500];


void *runner(void *param);
void *child_runner(void *param);
void *grand_runner(void *param);
void *append_file(char *str);
void *run_part2();
void *run_part3();

pthread_t tid[2600];
pthread_attr_t attr[2600];

pthread_t tid3[2600];
pthread_attr_t attr3[2600];

pthread_t maint[2];
pthread_attr_t mainattr[2];


int main(int argc,char* argv[])
{
	

	char *a = argv[1];
	char *b = argv[2];
	
	int arg2=atoi(b);
	int arg1=atoi(a);
	long i;
	long j;
	char argument[2500];
	int master = argc;
	char string[500];
	
	printf("Parent Thread is start executing\n");
	snprintf(string,2500,"Parent Thread is start executing\n");
	append_file(string);
	
	
	void *run_part3()
	{
	if(master == 3)
	{
	printf("Input valid input with three arguments");
	}
	else
	{
	
	char *c = argv[3];
	int arg3 = atoi(c);
	long temp = -arg3;
	
	for(i = 0;i<arg2*arg3+arg2 ; i=i+arg3+1)
	{
		temp +=arg3;
		snprintf(argument,2500,"%ld,%ld,%ld,%d,%d\n",i,(temp/arg3)*(arg1/arg2)+1,(temp/arg3+1)*(arg1/arg2),arg3,arg1/arg2);
	
		
		pthread_attr_init(&attr3[i]);
		
		pthread_create(&tid3[i],&attr3[i],child_runner,(void *)&argument);
		
		pthread_join(tid3[i],NULL);
	}	
	for (j =0 ; j<arg2*arg3+arg2 ; j=j+arg3+1)
	{
		tot_sum3+=sum3[j];
	}
	printf("Toatl sum = %ld\n",tot_sum3);
	snprintf(string,500,"Toatl sum = %ld\n",tot_sum3);
	append_file(string);
	printf("Parent end of execution\n");
	snprintf(string,500,"Parent end of execution\n");
	append_file(string);
	pthread_exit(NULL);
	

	}
	}
	
	
	void *run_part2(){
	
	
	for(i = 0;i<arg2 ; i++)
	{
		
		
		snprintf(argument,2500,"%ld,%ld,%ld\n",i,i*(arg1/arg2)+1,(i+1)*(arg1/arg2));
	
		pthread_attr_init(&attr[i]);
		
		pthread_create(&tid[i],&attr[i],runner,(void *)&argument);
		
		pthread_join(tid[i],NULL);
	}	
	for (j =0 ; j< arg2 ; j++)
	{
		
		tot_sum2+=sum2[j];
		}
	printf("Toatl sum = %ld\n",tot_sum2);
	snprintf(string,2500,"Toatl sum = %ld\n",tot_sum2);
	append_file(string);
	printf("Parent end of execution\n");
	snprintf(string,2500,"Parent end of execution\n");
	append_file(string);
	pthread_exit(NULL);

	
	}
	
	pthread_attr_init(&mainattr[0]);	
	pthread_create(&maint[0],&mainattr[0],run_part2,NULL);
	pthread_join(maint[0],NULL);
	pthread_attr_init(&mainattr[1]);
	pthread_create(&maint[1],&mainattr[1],run_part3,NULL);	
	pthread_join(maint[1],NULL);
	
	
} 

void *runner(void *param)
{
	char *str = (char *)param;
	
	int count =0;
	long idx;
	long start;
	long end;
	char *pt;
	char string[2500];
	
    	pt = strtok (str,",");
    	
    	while (pt != NULL) {
    	count++;
    	if (count == 1)
    	{
    	idx = atoi(pt);
    	}
    	else if (count == 2)
    	{
    	start = atoi(pt);
    	}
    	else
    	{
    	end = atoi(pt);
    	}
        pt = strtok (NULL, ",");
    	}
    	
	for (int i=start;i<=end; i++)
	{
		sum2[idx]+=i;
	}
	printf("Child Thread %ld\t child start = %ld\t end = %ld\t sum = %ld\n",idx,start,end,sum2[idx]);
	snprintf(string,2500,"Child Thread %ld\t child start = %ld\t end = %ld\t sum = %ld\n",idx,start,end,sum2[idx]);
	append_file(string);	
	pthread_exit(NULL);
}

void *child_runner(void *param)
{
	char *str = (char *)param;
	char arg[500];
	int temp=-1;
	int count =0;
	long idx;
	long start;
	long end;
	int arg3;
	int size;
	char *pt;
	char string[2500];
	
    	pt = strtok (str,",");
    	
    	while (pt != NULL) {
    	count++;
    	if (count == 1)
    	{
    	idx = atoi(pt);
    	}
    	else if (count == 2)
    	{
    	start = atoi(pt);
    	}
    	else if(count==3)
    	{
    	end = atoi(pt);
    	}
    	else if(count == 4)
    	{
    	arg3=atoi(pt);
    	}
    	else
    	{
    	size=atoi(pt);
    	}
        pt = strtok (NULL, ",");
    	}
    	
	for (long i=idx+1;i<=idx+arg3; i++)
	{
	temp+=1;
	
	snprintf(arg,2500,"%ld,%ld,%ld,%ld\n",start+(size/arg3)*temp,(start+(size/arg3)*temp)+(size/arg3)-1,idx,i);
	
	pthread_attr_init(&attr3[i]);
		
	pthread_create(&tid3[i],&attr3[i],grand_runner,(void *)&arg);
		
	pthread_join(tid3[i],NULL);
		
	}
	printf("Child Thread Number %ld\t child start = %ld\t end = %ld\t Child sum = %ld\n",idx,start,end,sum3[idx]);
	snprintf(string,2500,"Child Thread Number %ld\t child start = %ld\t end = %ld\t Child sum = %ld\n",idx,start,end,sum3[idx]);
	append_file(string);
	pthread_exit(NULL);
}

void *grand_runner(void *param)
{
	char *str = (char *)param;
	long grand_sum=0;
	int count =0;
	long idx;
	long start;
	long end;
	long i;
	long j;
	char *pt;
	char string[2500];
	
	pt = strtok (str,",");
	
	while (pt != NULL) {
    	count++;
    	if (count == 1)
    	{
    	start = atoi(pt);
    	}
    	else if (count == 2)
    	{
    	end= atoi(pt);
    	}
    	else if(count == 3)
    	{
    	idx = atoi(pt);
    	}
    	else
    	{
    	i = atoi(pt);
    	}
    	pt = strtok (NULL, ",");
    	}
	
	for (j=start;j<=end; j++){
		grand_sum += j;
	}	
	sum3[idx]+=grand_sum;
	printf("Child Thread Number %ld\t GrandChild Thread Number = %ld\t GrandChild Start = %ld\t GrandChild End = %ld\t Grand child sum = %ld\n",idx,i,start,end,grand_sum);
	snprintf(string,2500,"Child Thread Number %ld\t GrandChild Thread Number = %ld\t GrandChild Start = %ld\t GrandChild End = %ld\t Grand child sum = %ld\n",idx,i,start,end,grand_sum);
	append_file(string);
	pthread_exit(NULL);
	
}

void *append_file(char *str)

{
	FILE *fp;
	fp = fopen("result.txt", "a+");
	fprintf(fp,"%s",str);
	fclose(fp);

}
