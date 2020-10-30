#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tot_sum2;
int sum2[100];

int tot_sum3;
int sum3[100];


void *runner(void *param);
void *child_runner(void *param);
void *grand_runner(void *param);
void *append_file(char *str);
void *run_part2();
void *run_part3();

pthread_t tid[60];
pthread_attr_t attr[60];

pthread_t tid3[60];
pthread_attr_t attr3[60];

pthread_t maint[2];
pthread_attr_t mainattr[2];


int main(int argc,char* argv[])
{
	

	char *a = argv[1];
	char *b = argv[2];
	
	int arg2=atoi(b);
	int arg1=atoi(a);
	int i;
	int j;
	char argument[100];
	int master = argc;
	char string[500];
	
	printf("Parent Thread is start executing\n");
	snprintf(string,500,"Parent Thread is start executing\n");
	append_file(string);
	
	
	void *run_part3()
	{
	
	char *c = argv[3];
	int arg3 = atoi(c);
	int temp = -arg3;
	
	for(int i = 0;i<arg2*arg3+arg2 ; i=i+arg3+1)
	{
		temp +=arg3;
		snprintf(argument,100,"%d,%d,%d,%d,%d\n",i,(temp/arg3)*(arg1/arg2)+1,(temp/arg3+1)*(arg1/arg2),arg3,arg1/arg2);
	
		
		pthread_attr_init(&attr3[i]);
		
		pthread_create(&tid3[i],&attr3[i],child_runner,(void *)&argument);
		
		pthread_join(tid3[i],NULL);
	}	
	for (int j =0 ; j<arg2*arg3+arg2 ; j=j+arg3+1)
	{
		tot_sum3+=sum3[j];
	}
	printf("Toatl sum = %d\n",tot_sum3);
	snprintf(string,500,"Toatl sum = %d\n",tot_sum3);
	append_file(string);
	printf("Parent end of execution\n");
	snprintf(string,500,"Parent end of execution\n");
	append_file(string);
	pthread_exit(NULL);
	

	}
	
	
	void *run_part2(){
	
	
	for(int i = 0;i<arg2 ; i++)
	{
		
		
		snprintf(argument,100,"%d,%d,%d\n",i,i*(arg1/arg2)+1,(i+1)*(arg1/arg2));
	
		pthread_attr_init(&attr[i]);
		
		pthread_create(&tid[i],&attr[i],runner,(void *)&argument);
		
		pthread_join(tid[i],NULL);
	}	
	for (int j =0 ; j< arg2 ; j++)
	{
		
		tot_sum2+=sum2[j];
		}
	printf("Toatl sum = %d\n",tot_sum2);
	snprintf(string,500,"Toatl sum = %d\n",tot_sum2);
	append_file(string);
	printf("Parent end of execution\n");
	snprintf(string,500,"Parent end of execution\n");
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
	int idx;
	int start;
	int end;
	char *pt;
	char string[500];
	
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
	printf("Child Thread %d\t child start = %d\t end = %d\t sum = %d\n",idx,start,end,sum2[idx]);
	snprintf(string,500,"Child Thread %d\t child start = %d\t end = %d\t sum = %d\n",idx,start,end,sum2[idx]);
	append_file(string);	
	pthread_exit(NULL);
}

void *child_runner(void *param)
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
	char string[500];
	
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
	
	pthread_attr_init(&attr3[i]);
		
	pthread_create(&tid3[i],&attr3[i],grand_runner,(void *)&arg);
		
	pthread_join(tid3[i],NULL);
		
	}
	printf("Child Thread Number %d\t child start = %d\t end = %d\t Child sum = %d\n",idx,start,end,sum3[idx]);
	snprintf(string,500,"Child Thread Number %d\t child start = %d\t end = %d\t Child sum = %d\n",idx,start,end,sum3[idx]);
	append_file(string);
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
	char string[500];
	
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
	printf("Child Thread Number %d\t GrandChild Thread Number = %d\t GrandChild Start = %d\t GrandChild End = %d\t Grand child sum = %d\n",idx,i,start,end,grand_sum);
	snprintf(string,500,"Child Thread Number %d\t GrandChild Thread Number = %d\t GrandChild Start = %d\t GrandChild End = %d\t Grand child sum = %d\n",idx,i,start,end,grand_sum);
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
