#include "types.h"
#include "user.h"
#include "stat.h"
#include "thread.h"

struct lock_t *lock;
int round = 0, j = 0;
int ThreadNum, PassNum;

void* PassThreads(void *k)
{
	int i = (int)k;
	while(round < PassNum)
	{
		lock_acquire(lock);
		if(round == PassNum) {break;}
		if(i == j)
		{
			round++;
			printf(1, "Pass number no: %d, Thread %d is passing the token to thread ", round, i);
			j++;
			if(j == ThreadNum)
				j = 0 ;	
			printf(1," %d\n",j);
			lock_release(lock);
		 	sleep(1);
		}
		else
		{
			lock_release(lock);
			sleep(1);
		}
	}
	printf(1,"Simulation of Frisbee game has finished, %d rounds were played in total!\n", round);
    sleep(10000);
    exit();
}

int main(int argc, char *argv[])
{
	int i = 0;
	ThreadNum = atoi(argv[1]);
	PassNum = atoi(argv[2]);
	lock_init(lock);
	for(i = 0; i<ThreadNum; i++)
	{
		thread_create(PassThreads, (void *)i);
	}
    wait();
	exit();
}