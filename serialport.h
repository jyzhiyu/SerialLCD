#ifndef SERIALPORT
#define SERIALPORT

void Serial1Begin(void);
char Serial1Read(void);
void Serial1Write(char c);
unsigned char Serial1Available(void);
void Serial1End(void);

#endif
