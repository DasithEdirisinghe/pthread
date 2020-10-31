#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tot_sum;
void *runner(void *param);
int sum[100];
void *grand_runner(void *param);

pthread_t tid[60];
	
pthread_attr_t attr[60];



int main(int argc,char* argv[])
{
	

	char *a = argv[1];
	char *b = argv[2];
	char *c = argv[3];
	
	int arg3 = atoi(c);
	int arg2=atoi(b);
	int arg1=atoi(a);
	int i;
	int j;
	int temp = -arg3;
	char argument[100];
	
	printf("Parent Thread is start executing\n");
	
	for(int i = 0;i<arg2*arg3+arg2 ; i=i+arg3+1)
	{
		temp +=arg3;
		snprintf(argument,100,"%d,%d,%d,%d,%d\n",i,(temp/arg3)*(arg1/arg2)+1,(temp/arg3+1)*(arg1/arg2),arg3,arg1/arg2);
	
		
		pthread_attr_init(&attr[i]);
		
		pthread_create(&tid[i],&attr[i],runner,(void *)&argument);
		
		pthread_join(tid[i],NULL);
	}	
	for (int j =0 ; j<arg2*arg3+arg2 ; j=j+arg3+1)
	{
		tot_sum+=sum[j];
	}
	printf("Toatl sum = %d\n",tot_sum);
	printf("Parent end of execution\n");
	pthread_exit(NULL);
	
	return 0;
} 
void *runner(void *param)
{
	char *str = (char *)param;
	char arg[50];
	int temp=-1;
	int count =0;
	int idx;
	int start;
	int end;
	int arg3;
	int size;
	char *pt;
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
    	
	for (int i=idx+1;i<=idx+arg3; i++)
	{
	temp+=1;
	
	snprintf(arg,50,"%d,%d,%d,%d\n",start+(size/arg3)*temp,(start+(size/arg3)*temp)+(size/arg3)-1,idx,i);
	
	
	pthread_attr_init(&attr[i]);
		
	pthread_create(&tid[i],&attr[i],grand_runner,(void *)&arg);
		
	pthread_join(tid[i],NULL);
		
	}
	printf("Child Thread Number %d\t child start = %d\t end = %d\t Child sum = %d\n",idx,start,end,sum[idx]);	
	pthread_exit(NULL);
}
void *grand_runner(void *param)
{
	char *str = (char *)param;
	int grand_sum=0;
	int count =0;
	int idx;
	int start;
	int end;
	int i;
	int j;
	char *pt;
	
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
	sum[idx]+=grand_sum;
	printf("Child Thread Number %d\t GrandChild Thread Number = %d\t GrandChild Start = %d\t GrandChild End = %d\t Grand child sum = %d\n",idx,i,start,end,grand_sum);
	pthread_exit(NULL);
	
}
