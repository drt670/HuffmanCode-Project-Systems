#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <fcntl.h>

static char perms_buff[30];

const char *get_perms(mode_t mode) 
{ 
char ftype = '?'; 
if (S_ISREG(mode)) ftype = '-'; 
if (S_ISLNK(mode)) ftype = 'l'; 
if (S_ISDIR(mode)) ftype = 'd'; 
if (S_ISBLK(mode)) ftype = 'b'; 
if (S_ISCHR(mode)) ftype = 'c'; 
if (S_ISFIFO(mode)) ftype = '|'; 
sprintf(perms_buff, "%c%c%c%c%c%c%c%c%c%c %c%c%c", 
ftype, 
mode & S_IRUSR ? 'r' : '-', 
mode & S_IWUSR ? 'w' : '-', 
mode & S_IXUSR ? 'x' : '-', 
mode & S_IRGRP ? 'r' : '-', 
mode & S_IWGRP ? 'w' : '-', 
mode & S_IXGRP ? 'x' : '-', 
mode & S_IROTH ? 'r' : '-', 
mode & S_IWOTH ? 'w' : '-', 
mode & S_IXOTH ? 'x' : '-', 
mode & S_ISUID ? 'U' : '-', 
mode & S_ISGID ? 'G' : '-', 
mode & S_ISVTX ? 'S' : '-'); 
return (const char *)perms_buff; 
} 

void listFilesRecursively(char *path);

int main() {

	char path[100] = ".";

	listFilesRecursively(path);

	return 0;

}


void listFilesRecursively(char *basePath) {

	char path[1000];
	struct dirent *ptr;
	DIR *dir = opendir(basePath);

	struct stat statbuf;
	struct passwd *pwd;

	// Unable to open directory
	if (!dir)
		return;

	while ((ptr = readdir(dir)) != NULL) 
	{
		if (strcmp(ptr->d_name,".") != 0 && strcmp(ptr->d_name, "..") != 0)
		{

			if (stat(ptr->d_name, &statbuf) == -1)
        			continue;			

			 printf("%10.10s", get_perms (statbuf.st_mode));
   			 printf("%4d", statbuf.st_nlink);

			/*
			if (fnmatch("*.txt",ptr->d_name,0) == 0) 
				printf("%s\n",ptr->d_name);

			if (fnmatch("*.c",ptr->d_name,0) == 0) 
				printf("%s\n",ptr->d_name);
		
			if (fnmatch("*.h",ptr->d_name,0) == 0) 
				printf("%s\n",ptr->d_name);

			if (fnmatch("*.md",ptr->d_name,0) == 0) 
				printf("%s\n",ptr->d_name);
			*/

			// create new path from our base path
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, ptr->d_name);
			//printf("%s", ptr->d_name);

			listFilesRecursively(path);

		}
	}
		closedir(dir);
}

