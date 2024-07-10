#include <furi_hal.h>

int gpio_blink_main(void* p) {
    UNUSED(p);

    furi_hal_gpio_init_simple(&gpio_ext_pa7, GpioModeOutputPushPull);
    furi_hal_gpio_write(&gpio_ext_pa7, true);
    furi_delay_ms(1000);
    furi_hal_gpio_write(&gpio_ext_pa7, false);
    furi_delay_ms(1000);

    furi_hal_gpio_init_simple(&gpio_ext_pa7, GpioModeAnalog);

    return 0;
}