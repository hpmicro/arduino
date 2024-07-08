/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "usbd_core.h"
#include "usbd_hid.h"
#include "USBMouse.h"


/*!< endpoint address */
#define HID_INT_EP          0x81
#define HID_INT_EP_SIZE     4
#define HID_INT_EP_INTERVAL 10

/*!< config descriptor size */
#define USB_HID_CONFIG_DESC_SIZ 34
/*!< report descriptor size */
#define HID_MOUSE_REPORT_DESC_SIZE 74

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
    0x02,                          /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,                             /* iInterface: Index of string descriptor */
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,                    /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE_HID, /* bDescriptorType: HID */
    0x11,                    /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,                       /* bCountryCode: Hardware target country */
    0x01,                       /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                       /* bDescriptorType */
    HID_MOUSE_REPORT_DESC_SIZE, /* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Mouse endpoint ********************/
    /* 27 */
    0x07,                         /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT, /* bDescriptorType: */
    HID_INT_EP,                   /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                         /* bmAttributes: Interrupt endpoint */
    HID_INT_EP_SIZE,              /* wMaxPacketSize: 4 Byte max */
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
    0x02,                          /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,                             /* iInterface: Index of string descriptor */
    /******************** Descriptor of Joystick Mouse HID ********************/
    /* 18 */
    0x09,                    /* bLength: HID Descriptor size */
    HID_DESCRIPTOR_TYPE_HID, /* bDescriptorType: HID */
    0x11,                    /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,                       /* bCountryCode: Hardware target country */
    0x01,                       /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,                       /* bDescriptorType */
    HID_MOUSE_REPORT_DESC_SIZE, /* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Mouse endpoint ********************/
    /* 27 */
    0x07,                         /* bLength: Endpoint Descriptor size */
    USB_DESCRIPTOR_TYPE_ENDPOINT, /* bDescriptorType: */
    HID_INT_EP,                   /* bEndpointAddress: Endpoint Address (IN) */
    0x03,                         /* bmAttributes: Interrupt endpoint */
    HID_INT_EP_SIZE,              /* wMaxPacketSize: 4 Byte max */
    0x00,
    HID_INT_EP_INTERVAL,          /* bInterval: Polling Interval */
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "HPMicro",                    /* Manufacturer */
    "HPMicro Mouse Demo",         /* Product */
    "2024062001",                 /* Serial Number */
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

/*!< hid mouse report descriptor */
static const uint8_t _hidReportDescriptor[HID_MOUSE_REPORT_DESC_SIZE] = {
    0x05, 0x01, /*     USAGE_PAGE (Generic Desktop) */
    0x09, 0x02, /*     USAGE (Mouse) */
    0xA1, 0x01, /*     COLLECTION (Application) */
    0x09, 0x01, /*     USAGE (Pointer) */

    0xA1, 0x00, /*     COLLECTION (Physical) */
    0x05, 0x09, /*     USAGE_PAGE (Button) */
    0x19, 0x01, /*     USAGE_MINIMUM (Button 1) */
    0x29, 0x03, /*     USAGE_MAXIMUM (Button 3) */

    0x15, 0x00, /*     LOGICAL_MINIMUM (0) */
    0x25, 0x01, /*     LOGICAL_MAXIMUM (1) */
    0x95, 0x03, /*     REPORT_COUNT (3) */
    0x75, 0x01, /*     REPORT_SIZE (1) */

    0x81, 0x02, /*     INPUT (Data,Var,Abs) */
    0x95, 0x01, /*     REPORT_COUNT (1) */
    0x75, 0x05, /*     REPORT_SIZE (5) */
    0x81, 0x01, /*     INPUT (Cnst,Var,Abs) */

    0x05, 0x01, /*     USAGE_PAGE (Generic Desktop) */
    0x09, 0x30, /*     USAGE (X) */
    0x09, 0x31, /*     USAGE (Y) */
    0x09, 0x38,

    0x15, 0x81, /*     LOGICAL_MINIMUM (-127) */
    0x25, 0x7F, /*     LOGICAL_MAXIMUM (127) */
    0x75, 0x08, /*     REPORT_SIZE (8) */
    0x95, 0x03, /*     REPORT_COUNT (2) */

    0x81, 0x06, /*     INPUT (Data,Var,Rel) */
    0xC0, 0x09,
    0x3c, 0x05,
    0xff, 0x09,

    0x01, 0x15,
    0x00, 0x25,
    0x01, 0x75,
    0x01, 0x95,

    0x02, 0xb1,
    0x22, 0x75,
    0x06, 0x95,
    0x01, 0xb1,

    0x01, 0xc0 /*   END_COLLECTION */
};

#define BUS_ID 0

/*!< mouse report */
ATTR_PLACE_AT_NONCACHEABLE_BSS mouse_data_t mouse_data;

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

//================================================================================
//================================================================================
//	Mouse

USBMouse_::USBMouse_(void) : _buttons(0)
{
}

void USBMouse_::begin(void) 
{
    usbd_desc_register(BUS_ID, &hid_descriptor);
    usbd_add_interface(BUS_ID, usbd_hid_init_intf(BUS_ID, &intf0, _hidReportDescriptor, HID_MOUSE_REPORT_DESC_SIZE));
    usbd_add_endpoint(BUS_ID, &hid_in_ep);

    usbd_initialize(BUS_ID, CONFIG_HPM_USBD_BASE, usbd_event_handler);
}

void USBMouse_::end(void) 
{
    usbd_deinitialize(BUS_ID);
}

void USBMouse_::click(uint8_t b)
{
    _buttons = b;
    move(0,0,0);
    _buttons = 0;
    move(0,0,0);
}

void USBMouse_::move(signed char x, signed char y, signed char wheel)
{
    mouse_data.buttons = _buttons;
    mouse_data.x = x;
    mouse_data.y = y;
    mouse_data.wheel = wheel;
    while (hid_busy) {
        ;
    }
    hid_busy = true;
    usbd_ep_start_write(BUS_ID, HID_INT_EP, (uint8_t *)&mouse_data, 4);
}

void USBMouse_::buttons(uint8_t b)
{
	if (b != _buttons)
	{
		_buttons = b;
		move(0,0,0);
	}
}

void USBMouse_::press(uint8_t b) 
{
	buttons(_buttons | b);
}

void USBMouse_::release(uint8_t b)
{
	buttons(_buttons & ~b);
}

bool USBMouse_::isPressed(uint8_t b)
{
	if ((b & _buttons) > 0) 
		return true;
	return false;
}

USBMouse_ USBMouse;
