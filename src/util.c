#include "eerawr.h"
#include <stdarg.h>

void usage(void) {
        printf("usage: eerawr read/write DATA/readall/writefile [-a ADDRESS] [-m MAX] [-f FILE] [-c] [-h]\n"
                "For more help run shiftctrl using the -h argument\n");
        
        exit(EXIT_FAILURE);
}

void help(void) {
	puts("eerawr - eeprom read and write");

        printf("usage: eerawr read/write DATA/readall/writefile [-a ADDRESS] [-m MAX] [-f FILE] [-c] [-h]\n\n");
	printf("commands:\n"
		"read\t\tReads a byte from the ADDRESS\n"
		"write DATA\tWrites byte DATA to the ADDRESS\n"
		"readall\t\tReads all of the data in the ROM from ADDRESS to MAX\n"
		"\t\tby default the program reads from 0 to the max address of the eeprom\n"
		"writefile\tWrites the FILE's contents to the ROM\n"
		"\n");

	printf("options:\n"
		"-a ADDRESS\tDefines the ADDRESS\n"
		"-m MAX\t\tDefines the MAX address\n"
		"-f FILE\t\tDefines the FILE's name, if the FILE is defined when using readall\n"
		"\t\tthen the contents of the eeprom are written to the FILE and if defined when\n"
		"\t\tusing the writefile command then it writes the FILE's contents to the ROM\n"
		"-c\t\tPrint read bytes as characters\n"
		"-h\t\tPrints out this help message\n"
		"\n");

	puts("Made by Victor <theshoutingparrot@protonmail.com>, 2021");

	exit(EXIT_SUCCESS);
}


void die(const char *fmt, ...) {
        va_list vargs;

        va_start(vargs, fmt);
        vfprintf(stderr, fmt, vargs);

        va_end(vargs);

        if(*(fmt+strlen(fmt)-1) == ':') {
                fputc(' ', stderr);
                perror(NULL);
        }

        else
		fputc('\n', stderr);

	exit(EXIT_FAILURE);
}
