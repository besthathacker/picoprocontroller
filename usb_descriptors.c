#include "tusb.h"

// USB Device Descriptor for Switch Pro Controller
tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

    .idVendor           = 0x057E,
    .idProduct          = 0x2009,
    .bcdDevice          = 0x0100,

    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,

    .bNumConfigurations = 0x01
};

uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

// HID Report Descriptor
uint8_t const desc_hid_report[] =
{
    TUD_HID_REPORT_DESC_GAMEPAD()
};

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) {
    (void)instance;
    return desc_hid_report;
}

// Strings
char const* string_desc_arr[] = {
    (const char[]) {0x09, 0x04},
    "Nintendo Co., Ltd.",
    "Pro Controller",
    "00000001",
};

static uint16_t _desc_str[32];
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void) langid;
    uint8_t chr_count;

    if (index == 0) {
        _desc_str[1] = (0x0409);
        _desc_str[0] = (TUSB_DESC_STRING << 8) | (2 + 2);
        return _desc_str;
    }

    const char* str = string_desc_arr[index];
    chr_count = strlen(str);
    if (chr_count > 31) chr_count = 31;

    for (uint8_t i = 0; i < chr_count; i++) {
        _desc_str[1+i] = str[i];
    }
    _desc_str[0] = (TUSB_DESC_STRING << 8) | (2*chr_count + 2);
    return _desc_str;
}
