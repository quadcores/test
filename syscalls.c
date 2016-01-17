#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>

#define SYS_QUADOPEN 323
#define SYS_QUADOPEN_WITH_INODE 324
#define FILENAME "/media/quad/mybtrfs/dontdelete"
#define HASH "65e84be33532fb784c48129675f9eff3a682b27168c0ea744b2cf58ee02337c5"

int main(void) {

    int ret;
    char buf;
	char out[1000];
	
	int i = 0;

    //Open a file of BTRFS to access the fops structure and the path.mnt for the other file that will be retrieved from the hash
    ret = syscall(SYS_QUADOPEN, -100, FILENAME, 00000000, 0);
    printf("\nThe value returned by syscall SYS_QUADOPEN is :: %d",ret);

    //This is the system call that will open the file directly given its hash, and not by searching the path while retrieving the file
    ret = syscall(SYS_QUADOPEN_WITH_INODE, -100, HASH, 00000000, 0);
    printf("\nThe value returned by syscall SYS_QUADOPEN_WITH_INODE is :: %d\n",ret);
	printf("\nI am reading file :: %s", FILENAME);
	
	while (read(ret, &buf, 1) > 0)
	{
		out[i] = buf;
		i++;
	}

	out[i] = '\0';

	printf("\nContents read are :: %s",out);
	printf("\nI am exiting file given by the hash :: %s", HASH);

	close(ret);
	printf("\nThe file is closed\n\n");

    return 0;	
}
