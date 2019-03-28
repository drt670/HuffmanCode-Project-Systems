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
			
			// checks to see if reg file, and if so checks to see if .git or .vscode is in the string to break the loop
			if (isRegFile(ptr->d_name) == 0 && (fnmatch("*.git",basePath,0) == 0 || fnmatch("*.vscode",basePath,0) == 0)) 
				break;
					
			
			// create new path from our base path
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, ptr->d_name);

			// checks to see if path includes git or vscode, if not prints out path
			if (fnmatch("*git",path,0) != 0 && fnmatch("*vscode",path,0) != 0 && (fnmatch("*.txt",path,0) == 0 || fnmatch("*.c",path,0) == 0 || 				    fnmatch("*.h",path,0) == 0 || fnmatch("*.md",path,0) == 0))			
				printf("%s\n",path);
			
			listFilesRecursively(path);

		}
	}
		closedir(dir);
}

