int open_device(int device_address);
int read_bytes(int file_i2c, char *buffer, int length);
int write_bytes(int file_i2c, char *buffer, int length);
int close_device(int file_i2c);
