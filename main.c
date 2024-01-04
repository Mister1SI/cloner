#include <sys/io.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/file.h>


int main() {
	const char* filename_prompt = "Enter the filename\n"; //19
	const char* new_filename_prompt = "Enter the new filename\n"; //23

	char filename_buf[512] = {0};
	char new_filename_buf[512] = {0};

	// allocate way too much memory (4MB)
	char* filebuf = calloc(4194304, 1);

	write(1, filename_prompt, 19);
	read(0, filename_buf, 512);

	// remove the newlines
	filename_buf[strcspn(filename_buf, "\n")] = 0;
	new_filename_buf[strcspn(new_filename_buf, "\n")] = 0;

	int fd = open(filename_buf, O_RDONLY);
	if(fd == -1) {
		char* msg = "Failed to open the file\n";
		write(1, msg, 24);
		return 1;
	}

	read(fd, filebuf, 4194304);
	int newfd = open(new_filename_buf, O_CREAT | O_WRONLY);
	write(newfd, filebuf, 4194304);

	close(fd);
	close(newfd);

	write(1, filename_buf, 512);
	write(1, new_filename_buf, 512);

	return 0;
}
