#include <eerawr.h>

int main(int argc, char *argv[]) {
	uint8_t IOPins[8] = 
			{IO_PIN_0, IO_PIN_1, IO_PIN_2, IO_PIN_3,
				IO_PIN_4, IO_PIN_5, IO_PIN_6, IO_PIN_7},
		controlPins[3] = 
			{ROM_OUTPUT_ENABLE, ROM_WRITE_ENABLE, ROM_CHIP_ENABLE},
		*io, *control, arg, wByte, tempByte,
		operation, filename;
	struct shiftRegister sr;
	uint16_t address, tempAddr, max;
	bool addrGiven, charPrint;
	char *endptr;
	FILE *fp;

	addrGiven = false;
	charPrint = false;

	operation = NOP;
	filename = 0;
	max = MAX_ADDRESS;

	for(arg = 1; arg < argc; arg++) {
		if(!strcmp(argv[arg], "-a")) {
			if(argc <= arg + 1)
				usage();

			addrGiven = true;

			address = strtol(argv[++arg], &endptr, 0);
		}

		else if(!strcmp(argv[arg], "-f")) {
			if(argc <= arg + 1)	
				usage();


			filename = ++arg;
		}

		else if(!strcmp(argv[arg], "-m")) {
			if(argc <= arg + 1)
				usage();

			max = strtol(argv[++arg], &endptr, 0);
		}

		else if(!strcmp(argv[arg], "-c")) {
			charPrint = true;
		}

		else if(!strcmp(argv[arg], "-h")) {
			help();
		}

		else if(!strcmp(argv[arg], "read")) {
			operation = READBYTE;
		}

		else if(!strcmp(argv[arg], "write")) {
			if(argc <= arg + 1)
				usage();

			operation = WRITEBYTE;

			wByte = strtol(argv[++arg], &endptr, 0);
		}

		else if(!strcmp(argv[arg], "readall")) {
			/* if an address wasn't given we read (everything) from address 0 */
			if(!addrGiven) {
				addrGiven = true;

				address = 0;
			}

			operation = READALL;
		}

		else if(!strcmp(argv[arg], "writefile")) {
			/* if an address wasn't given we read (everything) from address 0 */
			if(!addrGiven) {
				addrGiven = true;

				address = 0;
			}

			operation = WRITEFILE;
		}

		else {
			printf("argument \"%s\" not recognized!\n", argv[arg]);
			usage();
		}
	}

	if(!addrGiven) {
		puts("address not defined, assuming address 0x0");
		address = 0x0;
	}

	io = (uint8_t *)(&IOPins);
	control = (uint8_t *)(&controlPins);

	srInitGpioControl();

	sr = initShiftRegister(15,
			DATA_PIN, CLOCK_PIN, LATCH_PIN,
			RESET_PIN, ENABLE_PIN, true);

	srWriteValue(sr, address);
	srUpdateOutput(sr);
	srDelay(1);

	bcm2835_gpio_fsel(*(control+2), BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(*(control+2), LOW);

	switch(operation) {
		case READBYTE:
			inputMode(io, *control);

			if(charPrint)
				printf("'%c'\n", readIO(io));
			else
				printf("0x%X\n", readIO(io));

			break;

		case WRITEBYTE:
			outputMode(io, control);

			writeIO(io, *(control + 1), *(control + 2), wByte);

			break;

		case READALL:
			inputMode(io, *control);

			/* This means that we aren't writing to a file */
			if(filename == 0) {
				if(!charPrint)  {
					for(; address < max;) {
						printf("\n0x%04X: ", address);

						tempAddr = address+0x10;

						for(; address < tempAddr; address++) {
							srWriteValue(sr, address);
							srUpdateOutput(sr);
							bcm2835_delayMicroseconds(1);
							printf("0x%02X ", readIO(io));

							bcm2835_delayMicroseconds(1);
						}
					} 
				}

				else {
					for(; address < max; address++) {
						srWriteValue(sr, address);
						srUpdateOutput(sr);
						bcm2835_delayMicroseconds(1);
						printf("%c", readIO(io));

						bcm2835_delayMicroseconds(1);
					} 
				}

			}

			else {
				fp = fopen(argv[filename], "wb");

				if(fp == NULL) {
					return EXIT_FAILURE;
				}
				
				for(; address < max; address++) {
					srWriteValue(sr, address);
					srUpdateOutput(sr);
					bcm2835_delayMicroseconds(1);

					tempByte = readIO(io);

					fwrite(&tempByte, 1, sizeof(uint8_t), fp);

					bcm2835_delayMicroseconds(1);
				}

				fclose(fp);
			}

			break;
		
		case WRITEFILE:
			if(filename == 0)
				return EXIT_FAILURE;

			fp = fopen(argv[filename], "rb");

			if(fp == NULL) {
				return EXIT_FAILURE;
			}

			outputMode(io, control);

			for(; address < MAX_ADDRESS; address++) {
				tempByte = fread(&wByte, 1, sizeof(uint8_t), fp);

				srWriteValue(sr, address);
				srUpdateOutput(sr);
				bcm2835_delayMicroseconds(1);

				printf("Writing 0x%02X to 0x%04X", wByte, address);
				writeIO(io, *(control + 1), *(control + 2), wByte);

				if(tempByte != 1)
					break;

				bcm2835_delayMicroseconds(1);

				printf("\r\r\r\r\r\r\r\r\r\r\r\r", wByte, address);
			}

			printf("\nSuccesfully written contents of file %s to the eeprom!\n", argv[filename]);

			fclose(fp);

			break;

		case NOP:
			puts("Please provide the program with a command!");
			usage();

		default:
			puts("Please provide the program with a valid command!");
			usage();
	}


	bcm2835_close();

	return EXIT_SUCCESS;
}
