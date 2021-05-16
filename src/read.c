#include <eerawr.h>

bool inputMode(uint8_t *io, uint8_t enable) {
	uint8_t i;

	for(i = 0; i < 8; i++) {
		bcm2835_gpio_fsel(*(io+i), BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_set_pud(*(io+i), BCM2835_GPIO_PUD_DOWN);
	}

	bcm2835_gpio_fsel(enable, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(enable, LOW);

	return true;
}

uint8_t readIO(uint8_t *io) {
	uint8_t i, in;

	in = 0;

	for(i = 0; i < 8; i++) {
		in |= (bcm2835_gpio_lev(*(io+i)) << i);
	}

	return in;
}
