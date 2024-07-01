# Linux driver for Virgoo Turbocharger

Due to an invalid USB HID report descriptor, the Turbocharger Sound Voltex controller from Virgoo doesn't work under Linux.
This can be seen in the kernel log as the following lines when the controller is plugged in:
```
hid-generic 0003:C252:1F01.000B: item 0 1 0 8 parsing failed
hid-generic 0003:C252:1F01.000B: probe with driver hid-generic failed with error -22
```

This repository contains a kernel module that fixes the report descriptor, allowing the controller to be detected as an input device.

## Building

> [!IMPORTANT]
> You need to build the module every time you update your kernel

You need basic build tools and the kernel headers to build the module.

For Arch Linux, you need to install `base-devel` and `linux-headers` packages.

For Ubuntu, you need to install `build-essential` and the correct kernel headers, e.g. by running `sudo apt install linux-headers-$(uname -r)`.

Run `make` in the repo root and it should produce a `hid-turbocharger.ko` file.

## Installing / Loading

> [!IMPORTANT]
> You need to load the module after every boot

To load the built module into the kernel, you can run `sudo insmod hid-turbocharger.ko`.

You can check that the module was loaded correctly by checking if the `lsmod` listing includes the module: `lsmod | grep turbocharger`.

When the module is loaded and the controller is plugged in, the kernel should log something like:
```
turbocharger 0003:C252:1F01.000B: patching Turbocharger report descriptor
input: Rainbow Controller Rainbow Controller as /devices/pci0000:00/0000:00:01.2/0000:02:00.0/0000:03:08.0/0000:06:00.3/usb3/3-4/3-4:1.0/0003:C252:1F01.000B/input/input36
```