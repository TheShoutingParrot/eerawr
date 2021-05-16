#include <eerawr.h>

bool outputMode(uint8_t *io, uint8_t *control) {
	uint8_t i;

	bcm2835_gpio_fsel(*control, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(*control, HIGH);

	bcm2835_delay(1);

	bcm2835_gpio_fsel(*(control+1), BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(*(control+1), HIGH);

	bcm2835_delay(1);

	bcm2835_gpio_fsel(*(control+2), BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_write(*(control+2), HIGH);

	bcm2835_delay(1);

	for(i = 0; i < 8; i++) {
		bcm2835_gpio_fsel(*(io+i), BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_set_pud(*(io+i), BCM2835_GPIO_PUD_DOWN);
	}

	return true;
}

void writeIO(uint8_t *io, uint8_t we, uint8_t ce, uint8_t byte) {
	uint8_t i, in;

	in = 0;

	bcm2835_gpio_write(ce, LOW);

	bcm2835_delay(1);

	bcm2835_gpio_write(we, LOW);

	bcm2835_delay(1);

	for(i = 0; i < 8; i++) {
		bcm2835_gpio_write(*(io+i), ((byte & (1 << i))));
	}

	bcm2835_delay(1);

	bcm2835_gpio_write(we, HIGH);

	bcm2835_delay(1);

	bcm2835_gpio_write(ce, HIGH);
}
