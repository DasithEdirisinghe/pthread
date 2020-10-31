#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(int argc,char* argv[])
{
	string s1="HHHHEEEE";
	string r = s1.substr(2,6);
	char arg[100];
	snprintf(arg,100,"%d %d %d\n",5,6,10);
	printf("%s\n",arg);
	
	int x,y= atoi(arg);
	printf("%d %d\n",x,y);
	
}
