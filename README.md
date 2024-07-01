# Linux driver for Virgoo Turbocharger

Due to an invalid USB HID report descriptor, the Turbocharger Sound Voltex controller from Virgoo doesn't work under Linux.
This can be seen in the kernel log as the following lines when the controller is plugged in:
```
hid-generic 0003:C252:1F01.000B: item 0 1 0 8 parsing failed
hid-generic 0003:C252:1F01.000B: probe with driver hid-generic failed with error -22
```

This repository contains a kernel module that fixes the report descriptor, allowing the controller to be detected as an input device.

When the module is loaded and the controller is plugged in, the kernel should log something like:
```
turbocharger 0003:C252:1F01.000B: patching Turbocharger report descriptor
input: Rainbow Controller Rainbow Controller as /devices/pci0000:00/0000:00:01.2/0000:02:00.0/0000:03:08.0/0000:06:00.3/usb3/3-4/3-4:1.0/0003:C252:1F01.000B/input/input36
```

## Installing

### Prerequisites

Basic build tools (C compiler and make) and kernel headers:
- Arch Linux: Install `base-devel` and `linux-headers` packages.
- Ubuntu/Debian: Install `build-essential` and `linux-headers-generic` packages.

### DKMS (recommended)

You can use [DKMS](https://en.wikipedia.org/wiki/Dynamic_Kernel_Module_Support) to install the module and it will then automatically load the module on boot and rebuild it when you update your kernel.

Steps:
1. Install DKMS and the Linux headers (see above for info about the headers)
    - Arch/Debian/Ubuntu etc.: Install `dkms` package
2. Download the latest release of this repo from [here](https://github.com/Z1ni/turbocharger-hid-linux/releases/latest) (the `hid-turbocharger-{version}-dkms.tar.gz` file from assets)
3. Extract the archive to `/usr/src/`
4. Run `sudo dkms install -m hid-turbocharger -v {version}` where `{version}` is e.g. 1.0.0.

After the above steps you shouldn't need to do anything when booting or upgrading your kernel.

You can check that the module is active by running `dkms status`.

### Manual install

#### Building

> [!IMPORTANT]
> You need to build the module every time you update your kernel

See [prerequisites](#prerequisites) above.

Run `make` in the repo root and it should produce a `hid-turbocharger.ko` file.

#### Installing / Loading

> [!IMPORTANT]
> You need to load the module after every boot

To load the built module into the kernel, you can run `sudo insmod hid-turbocharger.ko`.

You can check that the module was loaded correctly by checking if the `lsmod` listing includes the module: `lsmod | grep turbocharger`.