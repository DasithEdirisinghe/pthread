#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int tot_sum;
void *runner(void *param);
int sum[100];

int main(int argc,char* argv[])
{

	char *a = argv[1];
	char *b = argv[2];
	int arg2=atoi(b);
	int arg1=atoi(a);
	int i;
	int j;
	char argument[100];
	
	pthread_t tid[arg2];
	
	pthread_attr_t attr[arg2];
	
	
	printf("Parent Thread is start executing\n");
	
	for(int i = 0;i<arg2 ; i++)
	{
		
		
		snprintf(argument,100,"%d,%d,%d\n",i,i*(arg1/arg2)+1,(i+1)*(arg1/arg2));
	
		pthread_attr_init(&attr[i]);
		
		pthread_create(&tid[i],&attr[i],runner,(void *)&argument);
		
		pthread_join(tid[i],NULL);
	}	
	for (int j =0 ; j< arg2 ; j++)
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
	
	int count =0;
	int idx;
	int start;
	int end;
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
    	else
    	{
    	end = atoi(pt);
    	}
        pt = strtok (NULL, ",");
    	}
    	
	for (int i=start;i<=end; i++)
	{
		sum[idx]+=i;
	}
	printf("Child Thread %d\t child start = %d\t end = %d sum = %d\n",idx,start,end,sum[idx]);	
	pthread_exit(NULL);
}
