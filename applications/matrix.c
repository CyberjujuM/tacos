#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <process.h>

int main(int argc __attribute__ ((unused)), char* argv[] __attribute__ ((unused)))
{
	int i;
	printf("\033[40m\033[32m\033[0j");
	while(1) {
		int c1 = (int)(78.0*(float)rand()/(RAND_MAX+1.0));
		int c2 = (int)(78.0*(float)rand()/(RAND_MAX+1.0));
		char caractere1 = 33 + ((unsigned int)rand())%80;
		char caractere2 = 33 + ((unsigned int)rand())%80;
		if (c2 < c1) {
			int b = c1;
			c1 = c2;
			c2 = b - c2;
		} else {
			c2 -= c1;
		}

		while(c1--) printf(" ");
		printf("%c", caractere1);

		while(c2--) printf(" ");
		printf("%c\n", caractere2);

		// usleep plante, mais en même temps, il n'utilise même pas de syscall...
		//usleep(1000);
		for(i = 0; i < 100000; i++);
	}
}
