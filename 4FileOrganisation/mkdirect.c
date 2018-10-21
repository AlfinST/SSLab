#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>

int main(int argc, char **argv)
{
int pid = getpid();
FILE * fPointer = fopen("new.txt","w+");
char dirName[NAME_MAX+1];
char *prefix = "that.rooms.";

snprintf(dirName, NAME_MAX + 1,"%s%d", prefix, pid);

printf("%s\n",dirName);

struct stat st = {0};
if (stat(dirName, &st) == -1) {
if(mkdir(dirName, 0755) != -1)
{
	char libPath[PATH_MAX+1];
	snprintf(libPath, PATH_MAX + 1, "%s/library.txt", dirName);
	FILE *fLib = fopen(libPath , "w+");
	fclose(fLib);
}
else	
{
	perror("mkdir: ");
}
}
return 0;
}

 // #include <sys/stat.h>
 //       #include <sys/types.h>

 //       int mkdir(const char *pathname, mode_t mode);
