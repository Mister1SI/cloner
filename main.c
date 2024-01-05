#include <sys/io.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>

int main() {
	const char* filename_prompt = "Enter the filename\n"; //19
	const char* new_filename_prompt = "Enter the new filename\n"; //23

	char filename_buf[512] = {0};
	char new_filename_buf[512] = {0};

	write(1, filename_prompt, 19);
	read(0, filename_buf, 512);
	write(1, new_filename_prompt, 23);
	read(0, new_filename_buf, 512);

	// remove the newlines
	filename_buf[strcspn(filename_buf, "\n")] = 0;
	new_filename_buf[strcspn(new_filename_buf, "\n")] = 0;

	int fd = open(filename_buf, O_RDONLY, 00644);
	if(fd == -1) {
		char* msg = "Failed to open the file\n";
		write(1, msg, 24);
		return 1;
	}

	struct stat st;
	fstat(fd, &st);
	long filesize = (long) st.st_size;

	char* filebuf = calloc(filesize, 1);

	read(fd, filebuf, filesize);
	int newfd = open(new_filename_buf, O_CREAT | O_WRONLY, 00644);
	write(newfd, filebuf, filesize);

	// dont be bad
	free(filebuf);

	close(fd);
	close(newfd);

	return 0;
}
