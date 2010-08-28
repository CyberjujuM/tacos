#include <stdio.h>
#include <time.h>
#include <process.h>

void ps()
{
	process_t* aux = get_process_list(FIRST_PROCESS);

	const int clk_per_ms = CLOCKS_PER_SEC / 1000;
	long int ms;
	int s;
	int m;
	int h;

	printf("pid\tname\t\ttime\t\t%CPU\tstate\n");   
	while(aux!=NULL)
	{
			
			/* Calcul du temps d'execution du processus */
			ms = aux->user_time / clk_per_ms;
			s = ms / 1000;
			
			m = s / 60;
			s = s % 60;
			h = m / 60;
			m = m % 60;
			
			/*if (aux->process == active_process) {
					printf("*");
			}*/
			
			printf("%d\t%s\t\t%dh %dm %ds\t%d\%\t",aux->pid, aux->name, h, m ,s, (int)(((float)aux->last_sample/(float)CPU_USAGE_SAMPLE_RATE)*100.f));
			
			switch(aux->state)
			{
					case PROCSTATE_IDLE:
							printf("IDLE\n");
							break;
					case PROCSTATE_RUNNING:
							printf("RUNNING\n");
							break;
					case PROCSTATE_WAITING:
							printf("WAITING\n");
							break;
					case PROCSTATE_TERMINATED:
							printf("TERMINATED\n");
							break;
					default:
							break;
			}
			
			aux = get_process_list(NEXT_PROCESS);
	}
	return 0;
}

int main(int argc __attribute__ ((unused)), char** argv __attribute__ ((unused)))
{

	while(1)
	{
		printf("\033[1;1H");
		ps();
		//sleep(1);
	}
}