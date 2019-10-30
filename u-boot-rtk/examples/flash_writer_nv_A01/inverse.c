#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fd_rfile, *fd_wfile;
	unsigned char buffer[4];
	
	if (argc < 3)
	{
		printf("usage : inverse input_binary_file output_binary_file!!\n");
		return 0;
	}
	
	fd_rfile = fopen(argv[1], "rb");
	fd_wfile = fopen(argv[2], "wb+");
	
	
	while (fread (buffer, 4, 1, fd_rfile) != 0)
	{
		fwrite (&buffer[3], 1, 1, fd_wfile);
		fwrite (&buffer[2], 1, 1, fd_wfile);
		fwrite (&buffer[1], 1, 1, fd_wfile);
		fwrite (&buffer[0], 1, 1, fd_wfile);
	}

	
	fclose(fd_rfile);
	fclose(fd_wfile);
	
	return 0;
}
