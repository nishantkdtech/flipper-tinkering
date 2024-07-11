#include <frui_hal.h>
#include <math.h>

/* Flipper Light Sensor */

#define BH1750_ADDRESS 0x23 // I2C address of BH1750 sensor

int read_light_value() {
  uint8_t data[2];
  i2c_master_begin(I2C_MASTER_NORMAL);
  i2c_master_start(BH1750_ADDRESS, I2C_MASTER_TRANSMITTER, true);
  i2c_master_write(0x10); // Continuous H-Resolution Mode command
  i2c_master_stop();

  frui_delay(120); // Wait for measurement (refer to BH1750 datasheet)

  i2c_master_begin(I2C_MASTER_NORMAL);
  i2c_master_start(BH1750_ADDRESS, I2C_MASTER_RECEIVER, true);
  i2c_master_read(data, 2, false);
  i2c_master_stop();

  return (data[1] << 8) | data[0]; // Combine high and low bytes
}

float calculate_lux(int raw_value) {
  // Adjust conversion factor based on your BH1750 model (refer to datasheet)
  const float conversion_factor = 1.2;
  return raw_value / conversion_factor;
}

int light_sense_main(void) {
  while (true) {
    int raw_value = read_light_value();
    float lux = calculate_lux(raw_value);

    frui_draw_text(0, 0, "Light Level:");
    char buffer[10];
    dtostrf(lux, 2, 2, buffer); // Format lux value with 2 decimals
    frui_draw_text(0, 10, buffer);
    frui_draw_text(0, 20, "Lux");

    frui_delay(500); // Update every half second
  }

  return 0;
}
