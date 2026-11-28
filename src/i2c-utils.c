#include <i2c-driver.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define I2C_DEVICE_ADDRESS 0x20 

int init_io(int *i2c_file)
{
	unsigned char buffer[60] = {0};
    int result;

    // Open the I2C device
    *i2c_file = open_device(I2C_DEVICE_ADDRESS);
    if (*i2c_file < 0)
    {
        fprintf(stderr, "Failed to open I2C device.\n");
        return -1;
    }

    // set the pullups on for the top three bits of port B
    buffer[0] = 0x0C; // Address of the pull-up resistor configuration register for port B
    buffer[1] = 0xE0; // Set the top three bits to pull-up (1) and the rest to no pull-up (0)

    result = write_bytes(*i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port B pullups.\n");
        return -1;
    }

    // set the two lsbs of port B to output and the rest to input
    buffer[0] = 0x01; // Address of the direction register for port B
    buffer[1] = 0xFC; // Set the two lsbs to output and the rest to input

    result = write_bytes(*i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port B pullups.\n");
        return -1;
    }

    // invert the top three bits of port B
    buffer[0] = 0x03; // Address of the polarity inversion register
    buffer[1] = 0xE0; // top three bits inverted

    result = write_bytes(*i2c_file, buffer, 2);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to set port B polarity inversion.\n");
        return -1;
    }
}

int horn(int i2c_file, unsigned char horn_command)
{
    unsigned char buffer[60] = {0};
    int result;

    buffer[0] = 0x13; // address of GPIO B data register

    result = write_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to address during horn command.\n");
        return -1;
    }

    buffer[0] = ((buffer[0] & 0xFE) | horn_command); // Set the LSB to horn_command while keeping other bits unchanged

    result = write_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to turn execute horn command.\n");
        return -1;
    }

    return 0;
}

int buzzer(int i2c_file, unsigned char buzzer_command)
{
    unsigned char buffer[60] = {0};
    int result;

    buffer[0] = 0x13; // address of GPIO B data register

    result = write_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to address during buzzer command.\n");
        return -1;
    }

    buffer[0] = ((buffer[0] & 0xFD) | buzzer_command); // Set the second bit to buzzer_command while keeping other bits unchanged

    result = write_bytes(i2c_file, buffer, 1);
    if (result < 0)
    {
        fprintf(stderr, "Failed to write to turn execute buzzer command.\n");
        return -1;
    }

    return 0;
}