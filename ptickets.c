#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"
#include "grand.h"

int main(int argc, char** argv){

	int i;

	struct pstat procs;
	getpinfo(&procs);

	printf(0, "Process:  Running?  Tickets  Pid  Ticks\n");
	int totalticks = 0;
	for (i=0; i<NPROC; i++)
	{
		if (procs.inuse[i]){
			printf(0, "ps(%d):  %d  %d  %d  %d\n", i, procs.inuse[i], procs.tickets[i], procs.pid[i], procs.ticks[i]);
			totalticks += procs.ticks[i];
		}
	}
	printf(0, "Total ticks: %d\n", totalticks);

	int rand = next_random();
	printf(0, "\nTrying random: %d", rand);	
	rand = next_random();
	printf(0, "\nTrying random: %d", rand);	
	rand = next_random();
	printf(0, "\nTrying random: %d", rand);	

	//Now between range
	//This is inherently unfair
	rand = next_random() % 100;
	printf(0, "\nTrying random: %d", rand);	
	rand = next_random() % 100;
	printf(0, "\nTrying random: %d", rand);	
	rand = rand_range(1,10);
	printf(0, "\nTrying randrange(1,10): %d", rand);	
	exit();
}
