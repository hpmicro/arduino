/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "usbd_core.h"
#include "usbd_hid.h"
#include "Arduino.h"
#include "USBKeyboard.h"

//================================================================================
//================================================================================
//  Keyboard

#define HID_INT_EP          0x81
#define HID_INT_EP_SIZE     8
#define HID_INT_EP_INTERVAL 10

#define USB_HID_CONFIG_DESC_SIZ       34
#define HID_KEYBOARD_REPORT_DESC_SIZE 63

static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0002, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_HID_CONFIG_DESC_SIZ, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),

    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,                          /* bLength: Interface Descriptor size */
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType: Interface descriptor type */
    0x00,                          /* bInterfaceNumber: Number of Interface */
    0x00,                          /* bAlternateSetting: Alternate setting */
    0x01,                          /* bNumEndpoints */
    0x03,                          /* bInterfaceClass: HID */
    0x01,                          /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x01,                          /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,                             /* iInterface: Index of string descriptor */
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,                    /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE_HID, /* bDescriptorType: HID */
    0x11,                    /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,                          /* bCountryCode: Hardware target country */
    0x01,                          /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                          /* bDescriptorType */
    HID_KEYBOARD_REPORT_DESC_SIZE, /* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Mouse endpoint ********************/
    /* 27 */
    0x07,                         /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT, /* bDescriptorType: */
    HID_INT_EP,                   /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                         /* bmAttributes: Interrupt endpoint */
    HID_INT_EP_SIZE,              /* wMaxPacketSize */
    0x00,
    HID_INT_EP_INTERVAL,          /* bInterval: Polling Interval */
};

static const uint8_t device_quality_descriptor[] = {
    USB_DEVICE_QUALIFIER_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, 0x01),
};

static const uint8_t other_speed_config_descriptor[] = {
    USB_OTHER_SPEED_CONFIG_DESCRIPTOR_INIT(USB_HID_CONFIG_DESC_SIZ, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),

    /************** Descriptor of Joystick Mouse interface ****************/
    /* 09 */
    0x09,                          /* bLength: Interface Descriptor size */
    USB_DESCRIPTOR_TYPE_INTERFACE, /* bDescriptorType: Interface descriptor type */
    0x00,                          /* bInterfaceNumber: Number of Interface */
    0x00,                          /* bAlternateSetting: Alternate setting */
    0x01,                          /* bNumEndpoints */
    0x03,                          /* bInterfaceClass: HID */
    0x01,                          /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x01,                          /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,                             /* iInterface: Index of string descriptor */
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,                    /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE_HID, /* bDescriptorType: HID */
    0x11,                    /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,                          /* bCountryCode: Hardware target country */
    0x01,                          /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                          /* bDescriptorType */
    HID_KEYBOARD_REPORT_DESC_SIZE, /* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Mouse endpoint ********************/
    /* 27 */
    0x07,                         /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT, /* bDescriptorType: */
    HID_INT_EP,                   /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                         /* bmAttributes: Interrupt endpoint */
    HID_INT_EP_SIZE,              /* wMaxPacketSize */
    0x00,
    HID_INT_EP_INTERVAL,          /* bInterval: Polling Interval */
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "HPMicro",                    /* Manufacturer */
    "HPMicro HID DEMO",           /* Product */
    "2024051702",                 /* Serial Number */
};

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    (void)speed;

    return device_descriptor;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    (void)speed;

    return config_descriptor;
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    (void)speed;

    return device_quality_descriptor;
}

static const uint8_t *other_speed_config_descriptor_callback(uint8_t speed)
{
    (void)speed;

    return other_speed_config_descriptor;
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    (void)speed;

    if (index >= (sizeof(string_descriptors) / sizeof(char *))) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor hid_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .other_speed_descriptor_callback = other_speed_config_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback,
};

static const uint8_t hid_keyboard_report_desc[HID_KEYBOARD_REPORT_DESC_SIZE] = {
    0x05, 0x01, /* USAGE_PAGE (Generic Desktop) */
    0x09, 0x06, /* USAGE (Keyboard) */
    0xa1, 0x01, /* COLLECTION (Application) */
    0x05, 0x07, /* USAGE_PAGE (Keyboard) */
    0x19, 0xe0, /* USAGE_MINIMUM (Keyboard LeftControl) */
    0x29, 0xe7, /* USAGE_MAXIMUM (Keyboard Right GUI) */
    0x15, 0x00, /* LOGICAL_MINIMUM (0) */
    0x25, 0x01, /* LOGICAL_MAXIMUM (1) */
    0x75, 0x01, /* REPORT_SIZE (1) */
    0x95, 0x08, /* REPORT_COUNT (8) */
    0x81, 0x02, /* INPUT (Data,Var,Abs) */
    0x95, 0x01, /* REPORT_COUNT (1) */
    0x75, 0x08, /* REPORT_SIZE (8) */
    0x81, 0x03, /* INPUT (Cnst,Var,Abs) */
    0x95, 0x05, /* REPORT_COUNT (5) */
    0x75, 0x01, /* REPORT_SIZE (1) */
    0x05, 0x08, /* USAGE_PAGE (LEDs) */
    0x19, 0x01, /* USAGE_MINIMUM (Num Lock) */
    0x29, 0x05, /* USAGE_MAXIMUM (Kana) */
    0x91, 0x02, /* OUTPUT (Data,Var,Abs) */
    0x95, 0x01, /* REPORT_COUNT (1) */
    0x75, 0x03, /* REPORT_SIZE (3) */
    0x91, 0x03, /* OUTPUT (Cnst,Var,Abs) */
    0x95, 0x06, /* REPORT_COUNT (6) */
    0x75, 0x08, /* REPORT_SIZE (8) */
    0x15, 0x00, /* LOGICAL_MINIMUM (0) */
    0x25, 0xFF, /* LOGICAL_MAXIMUM (255) */
    0x05, 0x07, /* USAGE_PAGE (Keyboard) */
    0x19, 0x00, /* USAGE_MINIMUM (Reserved (no event indicated)) */
    0x29, 0x65, /* USAGE_MAXIMUM (Keyboard Application) */
    0x81, 0x00, /* INPUT (Data,Ary,Abs) */
    0xc0        /* END_COLLECTION */
};

static const uint8_t KeyboardLayout_en_US[128] =
{
    0x00,          // NUL
    0x00,          // SOH
    0x00,          // STX
    0x00,          // ETX
    0x00,          // EOT
    0x00,          // ENQ
    0x00,          // ACK
    0x00,          // BEL
    0x2a,          // BS  Backspace
    0x2b,          // TAB Tab
    0x28,          // LF  Enter
    0x00,          // VT
    0x00,          // FF
    0x00,          // CR
    0x00,          // SO
    0x00,          // SI
    0x00,          // DEL
    0x00,          // DC1
    0x00,          // DC2
    0x00,          // DC3
    0x00,          // DC4
    0x00,          // NAK
    0x00,          // SYN
    0x00,          // ETB
    0x00,          // CAN
    0x00,          // EM
    0x00,          // SUB
    0x00,          // ESC
    0x00,          // FS
    0x00,          // GS
    0x00,          // RS
    0x00,          // US

    0x2c,          // ' '
    0x1e|SHIFT,    // !
    0x34|SHIFT,    // "
    0x20|SHIFT,    // #
    0x21|SHIFT,    // $
    0x22|SHIFT,    // %
    0x24|SHIFT,    // &
    0x34,          // '
    0x26|SHIFT,    // (
    0x27|SHIFT,    // )
    0x25|SHIFT,    // *
    0x2e|SHIFT,    // +
    0x36,          // ,
    0x2d,          // -
    0x37,          // .
    0x38,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x33|SHIFT,    // :
    0x33,          // ;
    0x36|SHIFT,    // <
    0x2e,          // =
    0x37|SHIFT,    // >
    0x38|SHIFT,    // ?
    0x1f|SHIFT,    // @
    0x04|SHIFT,    // A
    0x05|SHIFT,    // B
    0x06|SHIFT,    // C
    0x07|SHIFT,    // D
    0x08|SHIFT,    // E
    0x09|SHIFT,    // F
    0x0a|SHIFT,    // G
    0x0b|SHIFT,    // H
    0x0c|SHIFT,    // I
    0x0d|SHIFT,    // J
    0x0e|SHIFT,    // K
    0x0f|SHIFT,    // L
    0x10|SHIFT,    // M
    0x11|SHIFT,    // N
    0x12|SHIFT,    // O
    0x13|SHIFT,    // P
    0x14|SHIFT,    // Q
    0x15|SHIFT,    // R
    0x16|SHIFT,    // S
    0x17|SHIFT,    // T
    0x18|SHIFT,    // U
    0x19|SHIFT,    // V
    0x1a|SHIFT,    // W
    0x1b|SHIFT,    // X
    0x1c|SHIFT,    // Y
    0x1d|SHIFT,    // Z
    0x2f,          // [
    0x31,          // bslash
    0x30,          // ]
    0x23|SHIFT,    // ^
    0x2d|SHIFT,    // _
    0x35,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c,          // y
    0x1d,          // z
    0x2f|SHIFT,    // {
    0x31|SHIFT,    // |
    0x30|SHIFT,    // }
    0x35|SHIFT,    // ~
    0x00           // DEL
};

#define BUS_ID 0

ATTR_PLACE_AT_NONCACHEABLE_BSS KeyReport_t _keyReport;

/*!< hid state ! Data can be sent only when state is idle  */
static volatile bool hid_busy = true;

static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    (void)busid;

    switch (event) {
    case USBD_EVENT_RESET:
        break;
    case USBD_EVENT_CONNECTED:
        break;
    case USBD_EVENT_DISCONNECTED:
        hid_busy = true;
        break;
    case USBD_EVENT_RESUME:
        break;
    case USBD_EVENT_SUSPEND:
        break;
    case USBD_EVENT_CONFIGURED:
        hid_busy = false;
        break;
    case USBD_EVENT_SET_REMOTE_WAKEUP:
        break;
    case USBD_EVENT_CLR_REMOTE_WAKEUP:
        break;

    default:
        break;
    }
}

/* function ------------------------------------------------------------------*/
static void usbd_hid_int_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    (void)busid;
    (void)ep;
    (void)nbytes;

    hid_busy = false;
}

/*!< endpoint call back */
static struct usbd_endpoint hid_in_ep = {
    .ep_addr = HID_INT_EP,
    .ep_cb = usbd_hid_int_callback,
};

static struct usbd_interface intf0;

USBKeyboard_::USBKeyboard_(void)
{
    _asciimap = KeyboardLayout_en_US;
}

void USBKeyboard_::begin(void)
{
    usbd_desc_register(BUS_ID, &hid_descriptor);
    usbd_add_interface(BUS_ID, usbd_hid_init_intf(BUS_ID, &intf0, hid_keyboard_report_desc, HID_KEYBOARD_REPORT_DESC_SIZE));
    usbd_add_endpoint(BUS_ID, &hid_in_ep);

    usbd_initialize(BUS_ID, CONFIG_HPM_USBD_BASE, usbd_event_handler);
}

void USBKeyboard_::end(void)
{
    usbd_deinitialize(BUS_ID);
}

void USBKeyboard_::sendReport(KeyReport_t* keys)
{
    while (hid_busy) {
        ;
    }
    hid_busy = true;
    usbd_ep_start_write(BUS_ID, HID_INT_EP, (uint8_t *)keys, sizeof(KeyReport_t));
}

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way
// USB HID works, the host acts like the key remains pressed until we
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t USBKeyboard_::press(uint8_t k)
{
    uint8_t i;
    if (k >= 136) {     // it's a non-printing key (not a modifier)
        k = k - 136;
    } else if (k >= 128) {  // it's a modifier key
        _keyReport.modifiers |= (1<<(k-128));
        k = 0;
    } else {    // it's a printing key
        k = pgm_read_byte(_asciimap + k);
        if (!k) {
            setWriteError();
            return 0;
        }
        if ((k & ALT_GR) == ALT_GR) {
            _keyReport.modifiers |= 0x40;   // AltGr = right Alt
            k &= 0x3F;
        } else if ((k & SHIFT) == SHIFT) {
            _keyReport.modifiers |= 0x02;   // the left shift modifier
            k &= 0x7F;
        }
        if (k == ISO_REPLACEMENT) {
            k = ISO_KEY;
        }
    }

    // Add k to the key report only if it's not already present
    // and if there is an empty slot.
    if (_keyReport.keys[0] != k && _keyReport.keys[1] != k &&
        _keyReport.keys[2] != k && _keyReport.keys[3] != k &&
        _keyReport.keys[4] != k && _keyReport.keys[5] != k) {

        for (i=0; i<6; i++) {
            if (_keyReport.keys[i] == 0x00) {
                _keyReport.keys[i] = k;
                break;
            }
        }
        if (i == 6) {
            setWriteError();
            return 0;
        }
    }
    sendReport(&_keyReport);
    return 1;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t USBKeyboard_::release(uint8_t k)
{
    uint8_t i;
    if (k >= 136) {    // it's a non-printing key (not a modifier)
        k = k - 136;
    } else if (k >= 128) {    // it's a modifier key
        _keyReport.modifiers &= ~(1<<(k-128));
        k = 0;
    } else {    // it's a printing key
        k = pgm_read_byte(_asciimap + k);
        if (!k) {
            return 0;
        }
        if ((k & ALT_GR) == ALT_GR) {
            _keyReport.modifiers &= ~(0x40);   // AltGr = right Alt
            k &= 0x3F;
        } else if ((k & SHIFT) == SHIFT) {
            _keyReport.modifiers &= ~(0x02);    // the left shift modifier
            k &= 0x7F;
        }
        if (k == ISO_REPLACEMENT) {
            k = ISO_KEY;
        }
    }

    // Test the key report to see if k is present.  Clear it if it exists.
    // Check all positions in case the key is present more than once (which it shouldn't be)
    for (i=0; i<6; i++) {
        if (0 != k && _keyReport.keys[i] == k) {
            _keyReport.keys[i] = 0x00;
        }
    }

    sendReport(&_keyReport);
    return 1;
}

void USBKeyboard_::releaseAll(void)
{
    _keyReport.keys[0] = 0;
    _keyReport.keys[1] = 0;
    _keyReport.keys[2] = 0;
    _keyReport.keys[3] = 0;
    _keyReport.keys[4] = 0;
    _keyReport.keys[5] = 0;
    _keyReport.modifiers = 0;
    sendReport(&_keyReport);
}

size_t USBKeyboard_::write(uint8_t c)
{
    uint8_t p = press(c);   // Keydown
    delay(5);
    release(c);     // Keyup
    delay(5);
    return p;       // just return the result of press() since release() almost always returns 1
}

size_t USBKeyboard_::write(const uint8_t *buffer, size_t size) {
    size_t n = 0;
    while (size--) {
        if (*buffer != '\r') {
            if (write(*buffer)) {
                n++;
            } else {
                break;
            }
        }
        buffer++;
    }
    return n;
}

USBKeyboard_ USBKeyboard;
