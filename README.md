# pthread

# Overview

This is a freelancing project which was done and its based on multithreading.

The writeup document give a brief understanidng about how the code works.

I use C as the main programming language.I have used pthread library.

Main function of this program is to solve a problem using multithreading.So I have used child threads and grandchild threads in order to solve the problem.

Maximum number of child and grandchild threads which can run simultaneously is 50 respectively.

# Here are the commands:

1.Go to the relavant file directory and open terminal (Linux based OS is prefered and make sure the gcc compiler has installed)

2.Type this command in the terminal:

    gcc -o final final.c -lpthread
    
3.final.c is the source file name and final is the executable file name. You can change those names.

4.Then type this in the terminal:

	./final 10000 10 10
  
5.The command line arguments can be changed upto (./final 1000000 50 50 )

6.Result will be saved inside the result.txt file

# Something extra

I globally initialized some variables as those are used globally.
	
	Eg : tot_sum2 sum2[]

initialize the seperate 2 pthreads for main two part of our program run_part2 and run_part3 methods as,
	
	pthread_t tid[2600];
	pthread_attr_t attr[2600];

	pthread_t tid3[2600];
	pthread_attr_t attr3[2600];

Other than children and grandchildren threads there must be 2 separate threads to run,  run_part2 and run_part3 methods.Those are initialized as functions.
	
	pthread_t maint[2];
	pthread_attr_t mainattr[2];

Inside the main method those threads are initialized and created as follows.
	
	pthread_attr_init(&mainattr[0]);	
	pthread_create(&maint[0],&mainattr[0],run_part2,NULL);
	pthread_join(maint[0],NULL);
	pthread_attr_init(&mainattr[1]);
	pthread_create(&maint[1],&mainattr[1],run_part3,NULL);	
	pthread_join(maint[1],NULL);
