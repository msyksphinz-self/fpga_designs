#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
  FILE* fp;
  while(1) {
	fp = fopen("/proc/myled", "w");
	if(fp == NULL) {
	  printf("Cannot open /proc/myled for write\n");
	  return -1;
	}
	fputs("0x0F\n", fp);
	fclose(fp);
	sleep(1);
	fp = fopen("/proc/myled", "w");
	if(fp == NULL) {
	  printf("Cannot open /proc/myled for write\n");
	  return -1;
	}
	fputs("0x00\n", fp);
	fclose(fp);
	sleep(1);
  }
  return 0;
}
