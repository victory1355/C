#include <unistd.h>
#include <stdio.h>


int main()
{
	char path[100];
	char *p;
	getcwd(path, sizeof(path));
	//getwd(path);
	//char *p;
	//p = get_current_dir_name();
	printf("%s\n", path);
	
	
	
	return 0;	
}