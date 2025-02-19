#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "sc16is750.h"

int main(int argc, char **argv){

	SC16IS750_t dev;
	
	if (argc < 4) {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address baudrate : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select baudrate : For SPI\n", argv[0]);
		return 1;
	}
	
	if (strcmp(argv[1], "I2C") == 0) {
		long i2c_address = strtol(argv[2], NULL, 16);
		printf("i2c_addressr=0x%x\n", (uint8_t)i2c_address);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, (uint8_t)i2c_address);
	} else if (strcmp(argv[1], "SPI") == 0) {
		long chip_select = strtol(argv[2], NULL, 10);
		printf("chip_select=%ld\n", chip_select);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, (uint8_t)chip_select);
	} else {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address baudrate : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select baudrate : For SPI\n", argv[0]);
		return 1;
	}

	// wiringPi Initialization
	if(wiringPiSetup() == -1) {
		printf("wiringPiSetup Fail\n");
		return 1;
	}

	// SC16IS750 Initialization
	long baudrate = strtol(argv[3], NULL, 10);
	printf("baudrate=%ld\n", baudrate);
	SC16IS750_begin(&dev, baudrate, 14745600UL); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		printf("device not found\n");
		return 1;
	} else {
		printf("device found\n");
	}
	printf("start serial communication\n");


	char buffer[64] = {0};
	int index = 0;

	SC16IS750_setTimeout(&dev, 500);

	while(1) {
		int16_t c = SC16IS750_readwithtimeout(&dev);
#if 0
		printf("SC16IS750_readwithtimeout=%d\n", c);
#endif
		if (c != -1) {
			if (index < sizeof(buffer)-1) {
				buffer[index++] = c;
				buffer[index] = 0;
			}
		} else {
			printf("[%s]\n",buffer);
			index = 0;
		}
	}
}

