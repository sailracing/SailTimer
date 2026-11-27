#include <stdio.h>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

	int file_i2c;
	int length;
	unsigned char buffer[60] = {0};

	
	//----- OPEN THE I2C BUS -----
int open_device(int device_address)
{

	int file_i2c;

	if ((file_i2c = open("/dev/i2c-1", O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		fprintf(stderr, "Failed to open the i2c bus\n");
		return -1;
	}

	if (ioctl(file_i2c, I2C_SLAVE, device_address) < 0)
	{
		fprintf(stderr, "Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return -1;
	}
		return file_i2c;
}

int read_bytes(int file_i2c, char *buffer, int length)
{

	if (read(file_i2c, buffer, length) != length)
	{
		fprintf(stderr, "Failed to read from the i2c bus.\n");
		return -1;
	}
	return 0;
}	


int write_bytes(int file_i2c, char *buffer, int length)
	{
	if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		fprintf(stderr, "Failed to write to the i2c bus.\n");
		return -1;
	}
	return 0;
}

int close_device(int file_i2c)
{
	if (close(file_i2c) < 0)
	{
		fprintf(stderr, "Failed to close the i2c bus.\n");
		return -1;
	}
	return 0;
}