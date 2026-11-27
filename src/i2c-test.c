#include <i2c-driver.h>
#include <stdio.h>

#define I2C_DEVICE_ADDRESS 0x20 // Replace with your I2C device address

int main()
{
	unsigned char buffer[60] = {0};
    int i2c_file;
    int result;

    // Open the I2C device
    i2c_file = open_device(I2C_DEVICE_ADDRESS);
    if (i2c_file < 0)
    {
        fprintf(stderr, "Failed to open I2C device.\n");
        return 1;
    }

    buffer[0] = 0x0C; // Example data to write
    buffer[1] = 0xFF; // Example data to write

    result = write_bytes(i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port A pullups.\n");
        return 1;
    }

    buffer[0] = 0x0D; // Example data to write
    buffer[1] = 0xFF; // Example data to write

    result = write_bytes(i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port B pullups.\n");
        return 1;
    }

    buffer[0] = 0x13; // Example data to write

    result = write_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to read GPIO A.\n");
        return 1;
    }
    result = read_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to read from GPIO A.\n");
        return 1;
    }
    
    fprintf(stdout, "GPIO A value: 0x%02X\n", buffer[0]);

    // Close the I2C device
    close_device(i2c_file);

	return 0;
}