#include <eerawr.h>

bool inputMode(uint8_t *io, uint8_t *control) {
	uint8_t i;

	for(i = 0; i < 8; i++) {
		bcm2835_gpio_fsel(*(io+i), BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_set_pud(*(io+i), BCM2835_GPIO_PUD_DOWN);
	}

	bcm2835_gpio_fsel(*(control + 0), BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(*(control + 0), LOW);

	bcm2835_gpio_fsel(*(control + 1), BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(*(control + 1), HIGH);

	bcm2835_gpio_fsel(*(control + 2), BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(*(control + 2), LOW);

	return true;
}

uint8_t readIO(uint8_t *io, uint8_t *control) {
	uint8_t i, in;

	in = 0;

	bcm2835_delayMicroseconds(20);
	

	for(i = 0; i < 8; i++) {
		in |= (bcm2835_gpio_lev(*(io+i)) << i);
	}

	bcm2835_delayMicroseconds(10);

	return in;
}
