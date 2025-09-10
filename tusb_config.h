#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

#define CFG_TUSB_MCU OPT_MCU_RP2040
#define CFG_TUSB_RHPORT0_MODE (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)

#define CFG_TUSB_OS OPT_OS_PICO

// Max number of endpoints
#define CFG_TUD_ENDPOINT0_SIZE 64

//--------------------------------------------------------------------
// DEVICE CONFIGURATION
//--------------------------------------------------------------------

#define CFG_TUD_HID 1   // Enable HID
#define CFG_TUD_CDC 0   // Disable Serial
#define CFG_TUD_MSC 0   // Disable USB Mass Storage
#define CFG_TUD_MIDI 0
#define CFG_TUD_VENDOR 0

// HID buffer size
#define CFG_TUD_HID_EP_BUFSIZE 64

#endif /* _TUSB_CONFIG_H_ */
