#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <fcntl.h>

void listFilesRecursively(char *path);

int isRegFile(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main() {

	char path[100] = ".";

	listFilesRecursively(path);

	return 0;

}


void listFilesRecursively(char *basePath) {

	char path[1000];
	struct dirent *ptr;
	DIR *dir = opendir(basePath);

	// Unable to open directory
	if (!dir)
		return;

	while ((ptr = readdir(dir)) != NULL) 
	{
		if (strcmp(ptr->d_name,".") != 0 && strcmp(ptr->d_name, "..") != 0)
		{

			if (isRegFile(ptr->d_name) == 0 && (fnmatch("*.git",basePath,0) == 0 || fnmatch("*.vscode",basePath,0) == 0)) 
				break;
					
			
			// create new path from our base path
			strcpy(path, basePath);
			strcat(path, "/");
			//printf("/");
			strcat(path, ptr->d_name);

			if (fnmatch("*git",path,0) != 0 && fnmatch("*vscode",path,0) != 0)			
				printf("%s\n",path);
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

			listFilesRecursively(path);

		}
	}
		closedir(dir);
}

