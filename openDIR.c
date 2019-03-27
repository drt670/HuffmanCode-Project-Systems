#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

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

	// Unable to open directory
	if (!dir)
		return;

	while ((ptr = readdir(dir)) != NULL) 
	{
		if (strcmp(ptr->d_name,".") != 0 && strcmp(ptr->d_name, "..") != 0)
		{
			printf("%s\n", ptr->d_name);

			// create new path from our base path
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, ptr->d_name);

			listFilesRecursively(path);

		}
	}
		closedir(dir);
}

