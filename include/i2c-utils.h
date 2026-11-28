#define HORN_ON 0x01
#define HORN_OFF 0x00

#define BUZZER_ON 0x02
#define BUZZER_OFF 0x00

int init_io(int *i2c_file);
int horn(int i2c_file, unsigned char horn_command);
int buzzer(int i2c_file, unsigned char buzzer_command);
