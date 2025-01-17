#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
//For lock
#include "spinlock.h"
#include "pstat.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//To get lock working
struct ptable_struct{
	struct spinlock lock;
	struct proc proc[NPROC];
};
extern struct ptable_struct ptable;


int sys_settickets(void)
{
	int numtickets;
	argint(0,&numtickets);
	if (numtickets<=0) return -1; //Fail if tickets error

	acquire(&ptable.lock);
	myproc()->tickets = numtickets;
	release(&ptable.lock);

	return numtickets;
}

int sys_getpinfo(void)
{

	struct pstat *procs;
	
	if (argptr(0, (void*)&procs, sizeof(*procs))<0) return -1;

	acquire(&ptable.lock);

//	struct proc *p;
	int p;
	for (p = 0; p < NPROC; p++)
	{

		if (ptable.proc[p].state == UNUSED) 
		{
			procs->inuse[p] = 0;
		}
		else
		{
			procs->inuse[p] = 1;
		}
		
		procs->tickets[p]=ptable.proc[p].tickets;
		procs->pid[p]=ptable.proc[p].pid;
		procs->ticks[p]=ptable.proc[p].ticks;
	}	

	release(&ptable.lock);	
	return 0;
}

