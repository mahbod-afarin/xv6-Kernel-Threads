#include "types.h"
#include "user.h"
#include "mmu.h"
#include "spinlock.h"
#include "x86.h"

struct lock_t
{
	uint lock;
};

void thread_create(void*(*sr)(void*), void *arg)
{
	void* np = malloc(PGSIZE*2);
	int tp;
	tp = clone(np, PGSIZE*2);
	if(tp==0)
	{
		(*sr)(arg);
		exit();		
	}
}

void lock_init(struct lock_t *lk)
{
	lk -> lock = 0;
}
void lock_acquire(struct lock_t *lk)
{
	while(xchg(&lk->lock,1) != 0);
}
void lock_release(struct lock_t *lock)
{
	xchg(&lock->lock,0);
}
