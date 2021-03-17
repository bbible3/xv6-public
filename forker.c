#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"

int main()
{
	int numcycles = 100000; //Was 100
	int pid = fork(); //Fork child 1
	int t1 = 10;
	int t2 = 20;
	int t3 = 30;
	int testevery = 10000;
	if (pid < 0)
	{
		printf(1, "Error forking first child.\n");
	}
	else if (pid == 0)
	{
		//Welcome to Child 1
		settickets(t1);
		while (1==1) continue;
		//for (int x=0; x<numcycles; x++) {  }
			//printf(1, "Child 1: pid%d, iter%d\n", pid, x);
	}
	else
	{
		pid = fork(); //FOrk child 2
		if (pid < 0)
		{
			printf(1, "Error forking second child.\n");
		}
		else if (pid == 0)
		{
			//Welcome to Child 2
			settickets(t2);
			while (1==1) continue;
			//for (int x=0; x<numcycles; x++) { }
				//printf(1, "Child 2: pid%d, iter%d\n", pid, x);
		}
		else
		{
			pid = fork(); //Fork child 3
			if (pid < 0)
			{
				printf(1, "Error forking third child.\n");
			}
			else if (pid == 0)
			{
				//Welcome to Child 3
				settickets(t3);
				while (1==1) continue;
				//for (int x=0; x<numcycles; x++) { }
					//printf(1, "Child 3: pid%d, iter%d\n", pid, x);
			}
			else
			{


				//int testevery = 10;
				int thistest = 0;
				for (int parentticks = 0; parentticks < numcycles; parentticks++)
				{
					thistest++;
					if (thistest == testevery)
					{
						thistest = 0;

						int i;

						struct pstat procs;
						getpinfo(&procs);

						printf(0, "Process:  Running?  Tickets  Pid  Ticks\n");
						int totalticks = 0;
						for (i=0; i<NPROC; i++)
						{
							if (procs.inuse[i]){
								printf(0, "ps(%d):  %d  %d  %d  %d\n", i, procs.inuse[i], procs.tickets[i], procs.pid[i], procs.ticks[i]);
							}
							totalticks += procs.ticks[i];
						}
						printf(0, "Total ticks: %d\n", totalticks);

					}
				}
				kill(3);
				kill(4);
				kill(5);
				printf(1, "Parent Waiting\n");
				int i;
				for (i=0; i<3; i++)
				{
					wait();
				}
				printf(1, "Children completed\n");
//				while (1==1) printf(1, "Parent Executing\n");
				printf(1, "Parent exiting.\n");
			}
		}
	}

	exit();
}
