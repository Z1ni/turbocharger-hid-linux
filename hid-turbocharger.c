// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  USB HID driver for Virgoo / Rainbow Turbocharger controller, which has an
 *  invalid report descriptor.
 *
 *  Copyright (c) 2024 Mark Mäkinen <marktmakinen@gmail.com>
 */

#include <linux/hid.h>
#include <linux/module.h>

MODULE_AUTHOR("Mark Mäkinen <marktmakinen@gmail.com>");
MODULE_DESCRIPTION("HID driver for Virgoo / Rainbow Turbocharger controller");

/*
 * Virgoo (reported as Rainbow) Turbocharger controller specifies an incorrect
 * value for Logical Minimum for the Slider and Dial for the Game Pad.
 * The value should be -127, but the value size is 2 bytes instead of one,
 * causing the value to be interpreted as 129. This is fixed by setting the
 * following byte to 0xFF instead of 0x00.
 */
static const __u8 *turbocharger_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int *rsize)
{
	if (*rsize == 138 && rdesc[36] == 0x16 && rdesc[37] == 0x81
		&& rdesc[38] == 0) {
		hid_info(hdev, "patching Turbocharger report descriptor\n");
		rdesc[38] = 0xFF;
	}
	return rdesc;
}

static const struct hid_device_id turbocharger_devices[] = {
	{ HID_USB_DEVICE(0xC252, 0x1F01) },
	{ }
};
MODULE_DEVICE_TABLE(hid, turbocharger_devices);

static struct hid_driver turbocharger_driver = {
	.name = "turbocharger",
	.id_table = turbocharger_devices,
	.report_fixup = turbocharger_report_fixup
};

module_hid_driver(turbocharger_driver);

MODULE_LICENSE("GPL");
