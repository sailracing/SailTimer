#include <i2c-utils.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    int i2c_file;
    int result;

    // Initialize I2C
    result = init_io(&i2c_file);
    if (result < 0)
    {
        fprintf(stderr, "Failed to initialize I2C.\n");
        return -1;
    }

    // Turn on horn
    result = horn(i2c_file, HORN_ON);
    if (result < 0)
    {
        fprintf(stderr, "Failed to turn on horn.\n");
        return -1;
    }

    sleep(1); // Keep horn on for 1 second

    // Turn on buzzer
    result = buzzer(i2c_file, BUZZER_ON);
    if (result < 0)
    {
        fprintf(stderr, "Failed to turn on buzzer.\n");
        return -1;
    }

    sleep(1); // Keep buzzer on for 1 second

    // Turn off horn
    result = horn(i2c_file, HORN_OFF);
    if (result < 0)
    {
        fprintf(stderr, "Failed to turn off horn.\n");
        return -1;
    }

    sleep(1); // Wait for 1 second

    // Turn off buzzer
    result = buzzer(i2c_file, BUZZER_OFF);
    if (result < 0)
    {
        fprintf(stderr, "Failed to turn off buzzer.\n");
        return -1;
    }

    sleep(1); // Wait for 1 second

    return 0;
}