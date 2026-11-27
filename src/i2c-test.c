#include <i2c-driver.h>
#include <time.h>
#include <stdio.h>

#define I2C_DEVICE_ADDRESS 0x20 

int main()
{
	unsigned char buffer[60] = {0};
    int i2c_file;
    int result;
    int i;

    // Open the I2C device
    i2c_file = open_device(I2C_DEVICE_ADDRESS);
    if (i2c_file < 0)
    {
        fprintf(stderr, "Failed to open I2C device.\n");
        return 1;
    }

    // set the pullups on for the top three bits of port B
    buffer[0] = 0x0C; // Address of the pull-up resistor configuration register for port B
    buffer[1] = 0xE0; // Set the top three bits to pull-up (1) and the rest to no pull-up (0)

    result = write_bytes(i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port B pullups.\n");
        return 1;
    }

    // set the two lsbs of port B to output and the rest to input
    buffer[0] = 0x01; // Address of the direction register for port B
    buffer[1] = 0xFC; // Set the two lsbs to output and the rest to input

    result = write_bytes(i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port B pullups.\n");
        return 1;
    }

    // invert the top three bits of port B
    buffer[0] = 0x03; // Address of the polarity inversion register
    buffer[1] = 0xE0; // top three bits inverted

    result = write_bytes(i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port B polarity inversion.\n");
        return 1;
    }

    buffer[0] = 0x13; // address of GPIO B data register

    result = write_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to read GPIO B.\n");
        return 1;
    }
    result = read_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to read from GPIO B.\n");
        return 1;
    }
    
    buffer[0] = buffer[0] >> 5; // shift the top three bits down to the bottom three bits
    
    fprintf(stdout, "Switch values: 0X%02X\n", buffer[0]);

    for(int i = 0; i < 3; i++)
    {
    
        // test the outputs
        buffer[0] = 0x13; // address of GPIO B data register
        buffer[1] = 0x03; // set the two lsbs to high
        result = write_bytes(i2c_file, buffer, 2);
        if (result < 0)
        {
            fprintf(stderr, "Failed to write to outputs of GPIO B.\n");
            return 1;
        }

        sleep(1); // wait for 1 second

        // turn off the outputs
        buffer[0] = 0x13; // address of GPIO B data register
        buffer[1] = 0x00; // set the two lsbs to low
        result = write_bytes(i2c_file, buffer, 2);
        if (result < 0)
        {
            fprintf(stderr, "Failed to write to outputs of GPIO B.\n");
            return 1;
        }

        sleep(1); // wait for 1 second

    }

    // Close the I2C device
    close_device(i2c_file);

	return 0;
}