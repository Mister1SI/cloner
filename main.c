#include <sys/io.h>
#include <string.h>

int main() {
	const char* filename_prompt = "Enter the filename\n"; //19
	const char* filesize_prompt = "Enter the filesize\n"; //19
	const char* new_filename_prompt = "Enter the new filename\n" //23

	char filename_buf[512] = {0};
	char filesize_buf[64] = {0};
	char new_filename_buf[512] = {0};

	char* filebuf = calloc(4194304, 1);

	write(1, filename_prompt, 19);
	read(0, filename_buf, 512);
	write(1, filesize_prompt, 19);
	read(0, filesize_buf, 64);
	
	int fd = open(filename_buf, O_RDONLY);
	if(fd == -1) {
		char* msg = "Failed to open the file\n";
		write(1, msg, 24);
		return 1;
	}

	read(fd, filebuf, 4194304);
	int newfd = open(new_filename_buf, O_CREAT);
	write(newfd, filebuf, 4194304);

	close(fd);
	close(newfd);

	write(1, filename_buf, 512);
	write(1, filesize_buf, 64);

	return 0;
}
