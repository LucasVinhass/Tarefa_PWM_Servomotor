#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SERVO_PIN 22
#define LED_RED_PIN 13 // Pino para o LED vermelho
#define PWM_WRAP 24999  // 20ms (50Hz) para servos
#define PWM_CLK_DIV 100  // Divisor de clock para obter o período correto

// Função para converter microssegundos em nível PWM
uint32_t us_to_level(uint32_t us) {
    return (uint32_t)(us * 1.25f); // 1µs ≈ 1.25 unidades
}

// Função para inicializar o PWM e GPIOs do LED RGB
void inicia() {
    // Configura o PWM para o servo
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, PWM_CLK_DIV); // Divisor de clock
    pwm_config_set_wrap(&config, PWM_WRAP);      // Wrap
    pwm_init(slice_num, &config, true);

    // Configura os pinos do LED RGB como saída
    // Configura o PWM para o LED RGB
    gpio_set_function(LED_RED_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(LED_RED_PIN);
    pwm_config pwm_led_config = pwm_get_default_config();
    pwm_config_set_clkdiv(&pwm_led_config, PWM_CLK_DIV); // Divisor de clock
    pwm_config_set_wrap(&pwm_led_config, PWM_WRAP);      // Wrap
    pwm_init(slice_num, &pwm_led_config, true);

}

// Função para controlar o brilho do LED
void set_led_brightness(uint16_t brightness) {
    uint slice_num = pwm_gpio_to_slice_num(LED_RED_PIN);
    uint channel = pwm_gpio_to_channel(LED_RED_PIN);
    pwm_set_chan_level(slice_num, channel, brightness);
}

// Função para ajustar o LED conforme o ângulo do servo
void set_led_for_angle(uint angle) {
    if (angle == 0) {
        set_led_brightness(PWM_WRAP / 4);  // vermelho (baixa intensidade)
    } else if (angle == 90) {
        set_led_brightness(PWM_WRAP / 2);  // Vermelho (média intensidade)
    } else if (angle == 180) {
        set_led_brightness(PWM_WRAP);      // Vermelho (alta intensidade)
    }
}


int main() {
  stdio_init_all(); // Inicializa a comunicação serial para debug
  uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);


  // Inicializa o PWM e GPIOs do LED RGB
  inicia();

  // Move o servo para 2400µs (2.4ms) - 180 graus
  pwm_set_gpio_level(SERVO_PIN, us_to_level(2400));
  set_led_for_angle(180); // LED vermelho 
  sleep_ms(5000);

  // Move o servo para 1470µs (1.47ms) - 90 graus
  pwm_set_gpio_level(SERVO_PIN, us_to_level(1470));
  set_led_for_angle(90); // LED vermelho 
  sleep_ms(5000);

  // Move o servo para 500µs (0.5ms) - 0 graus
  pwm_set_gpio_level(SERVO_PIN, us_to_level(500));
  set_led_for_angle(0); // LED vermelho
  sleep_ms(5000);
  
  int i = 0;
  while (1) {
    // Movimento suave do ângulo 0° (500us) até 180° (2400us)
    for (i = us_to_level(500); i <= us_to_level(2400); i += 5) {
        pwm_set_gpio_level(SERVO_PIN, i);
        set_led_brightness(PWM_WRAP/2); // LED variando
        sleep_ms(5); 
    }

    sleep_ms(100); 

    // Movimento suave de volta de 180° para 0°
    for (i = us_to_level(2400); i >= us_to_level(500); i -= 5) { 
        pwm_set_gpio_level(SERVO_PIN, i);
        set_led_brightness(PWM_WRAP/2);
        set_led_brightness(PWM_WRAP/4); // LED variando
        sleep_ms(5);
    }

    sleep_ms(100); 
}

}
