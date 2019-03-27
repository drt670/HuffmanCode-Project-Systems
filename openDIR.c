#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

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

			int length = strlen(ptr->d_name);
			char *name = NULL;
			name = malloc(sizeof(char) * length);
			name = ptr->d_name;
			char *type = NULL;
			char c;
			int x = 0, y = 0;
			c = name[x];
			
			do {
				c = name[x];
				x++;
			} while (c != "." || name[x] != NULL);
		
			if (name[x] == NULL){
				printf("%s\n", ptr->d_name);
			} else {
			
			type = name;				

			if (strcmp(type,"txt") == 0)			
				printf("%s\n", ptr->d_name);
			}
			
			free(name);
			

			// create new path from our base path
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, ptr->d_name);

			listFilesRecursively(path);

		}
	}
		closedir(dir);
}

