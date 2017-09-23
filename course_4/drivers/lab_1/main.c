#include "aduc812.h"
#include "led.h"
#include "max.h"

void delay (unsigned long ms) {
  volatile unsigned long i = 0, j = 0;

  for (j = 0; j < ms; j++) {
    for (i = 0; i < 50; i++);
  }
}

unsigned char dip() {
  return read_max(EXT_LO);
}

void main(void) {
  unsigned char animation_counter = 0x07;

  while (1) {
    unsigned char dip_value = dip();

    if (dip_value == 0x11) {
      // Анимация
      leds(0x00); // Обнуляем всё

      // Отрисовываем правую часть
      led(animation_counter, 1);

      // Отрисовываем левую часть
      led(0x07 - animation_counter, 1);
      if (animation_counter == 0x00) {
        led(0x07, 1);
      } else {
        led(animation_counter + 1, 1);
      }

      // Увеличиваем счетчик анимации на некст итерацию
      if (animation_counter-- == 0) {
        animation_counter = 0x07;
      }
    } else {
      // Инвертированное значение в dip переключателях
      leds(dip_value);
      animation_counter = 0x07;
    }

    delay(100);
  }
}
