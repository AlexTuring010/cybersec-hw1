#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv){
	int fd;
	uint32_t add, drops;

	fd = open("/dev/urandom", O_RDONLY);
	if(fd == -1){
		puts("Open error on /dev/urandom. Contact an admin.\n");
		return -1;
	}

	if(read(fd, &drops, sizeof(int)) != sizeof(int)){
		puts("Read error. Contact an admin.\n");
		return -1;
	}
	close(fd);
	
	if(drops == 0)
		drops = 1;

	printf("Welcome to this baby's first challenge!\n");
	printf("Let's start you off with a sippy cup.\n\n");

	printf("  _  \n");  
	printf("c(_)D\n\n");

	printf("The sippy cup starts off with %u drops.\n", drops);
	printf("Look on the bright side - you can add more drops of water!\n");

	fflush(stdout);
	
	while(drops != 0){
		printf("You need to finish drinking your sippy cup!\n");
		printf("You still have %u drops of water left. You should have none!\n", drops);
		printf("How many drops of water do you want to add?\n");
		fflush(stdout);
		int read = scanf("%u", &add);
		if (read != 1) exit(1);
		if(add <= 0){
			puts("You need to add some drops of water.\n");
		}else{
			printf("Alright. Adding %u drops of water.\n", add);
			fflush(stdout);
			drops += add;
		}
	}
	
	puts("All gone! Here's your flag.\n");
	fflush(stdout);
	system("/bin/cat ./flag.txt");

  return 0;
}
