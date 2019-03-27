#include <stdio.h>
#include <dirent.h>

int main() {

	struct dirent *ptr;

	DIR *open = opendir("."):

	if(open == NULL {
		printf("could not open current directory);
		return 0;
	}

	while ((ptr = readdir(open)) != NULL)
		printf("%s\n", ptr->d_name);

	closedir(open);
	return 0;
}
