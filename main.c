#include "pico/stdlib.h"
#include "tusb.h"

#define BTN_Y     2
#define BTN_B     3
#define BTN_A     4
#define BTN_X     5
#define BTN_L     6
#define BTN_R     7
#define BTN_ZL    8
#define BTN_ZR    9
#define BTN_MINUS 10
#define BTN_PLUS  11
#define BTN_HOME  12
#define BTN_CAP   13

#define DPAD1_UP     14
#define DPAD1_DOWN   15
#define DPAD1_LEFT   16
#define DPAD1_RIGHT  17

#define DPAD2_UP     18
#define DPAD2_DOWN   19
#define DPAD2_LEFT   20
#define DPAD2_RIGHT  21

#define READ_BTN(pin) (!gpio_get(pin))

typedef struct {
    uint16_t buttons;
    uint8_t  hat;
    uint8_t  lx, ly;
    uint8_t  rx, ry;
} __attribute__((packed)) switch_report_t;

void setup_pins() {
    int pins[] = { BTN_Y, BTN_B, BTN_A, BTN_X, BTN_L, BTN_R,
                   BTN_ZL, BTN_ZR, BTN_MINUS, BTN_PLUS, BTN_HOME, BTN_CAP,
                   DPAD1_UP, DPAD1_DOWN, DPAD1_LEFT, DPAD1_RIGHT,
                   DPAD2_UP, DPAD2_DOWN, DPAD2_LEFT, DPAD2_RIGHT };
    for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
        gpio_init(pins[i]);
        gpio_pull_up(pins[i]);
        gpio_set_dir(pins[i], GPIO_IN);
    }
}

uint8_t dpad_hat_value() {
    if (READ_BTN(DPAD1_UP) && READ_BTN(DPAD1_LEFT)) return GAMEPAD_HAT_UP_LEFT;
    if (READ_BTN(DPAD1_UP) && READ_BTN(DPAD1_RIGHT)) return GAMEPAD_HAT_UP_RIGHT;
    if (READ_BTN(DPAD1_DOWN) && READ_BTN(DPAD1_LEFT)) return GAMEPAD_HAT_DOWN_LEFT;
    if (READ_BTN(DPAD1_DOWN) && READ_BTN(DPAD1_RIGHT)) return GAMEPAD_HAT_DOWN_RIGHT;
    if (READ_BTN(DPAD1_UP)) return GAMEPAD_HAT_UP;
    if (READ_BTN(DPAD1_DOWN)) return GAMEPAD_HAT_DOWN;
    if (READ_BTN(DPAD1_LEFT)) return GAMEPAD_HAT_LEFT;
    if (READ_BTN(DPAD1_RIGHT)) return GAMEPAD_HAT_RIGHT;
    return GAMEPAD_HAT_CENTERED;
}

void hid_task(void) {
    if (!tud_hid_ready()) return;
    switch_report_t rpt = {0};
    rpt.hat = dpad_hat_value();
    rpt.lx = 0x80; rpt.ly = 0x80;
    rpt.rx = 0x80; rpt.ry = 0x80;

    if (READ_BTN(DPAD1_UP))    rpt.ly = 0x00;
    if (READ_BTN(DPAD1_DOWN))  rpt.ly = 0xFF;
    if (READ_BTN(DPAD1_LEFT))  rpt.lx = 0x00;
    if (READ_BTN(DPAD1_RIGHT)) rpt.lx = 0xFF;

    if (READ_BTN(DPAD2_UP))    rpt.ry = 0x00;
    if (READ_BTN(DPAD2_DOWN))  rpt.ry = 0xFF;
    if (READ_BTN(DPAD2_LEFT))  rpt.rx = 0x00;
    if (READ_BTN(DPAD2_RIGHT)) rpt.rx = 0xFF;

    if (READ_BTN(BTN_Y))     rpt.buttons |= 1 << 0;
    if (READ_BTN(BTN_B))     rpt.buttons |= 1 << 1;
    if (READ_BTN(BTN_A))     rpt.buttons |= 1 << 2;
    if (READ_BTN(BTN_X))     rpt.buttons |= 1 << 3;
    if (READ_BTN(BTN_L))     rpt.buttons |= 1 << 4;
    if (READ_BTN(BTN_R))     rpt.buttons |= 1 << 5;
    if (READ_BTN(BTN_ZL))    rpt.buttons |= 1 << 6;
    if (READ_BTN(BTN_ZR))    rpt.buttons |= 1 << 7;
    if (READ_BTN(BTN_MINUS)) rpt.buttons |= 1 << 8;
    if (READ_BTN(BTN_PLUS))  rpt.buttons |= 1 << 9;
    if (READ_BTN(BTN_HOME))  rpt.buttons |= 1 << 12;
    if (READ_BTN(BTN_CAP))   rpt.buttons |= 1 << 13;

    tud_hid_report(0, &rpt, sizeof(rpt));
}

int main() {
    stdio_init_all();
    tusb_init();
    setup_pins();
    while (1) {
        tud_task();
        hid_task();
        sleep_ms(5);
    }
}
