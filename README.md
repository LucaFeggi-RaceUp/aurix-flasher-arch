# aurix-flasher-arch

Arch Linux-ready fork of `volumit/aurix_flasher_linux` for flashing AURIX TC3xx targets through Infineon TAS/DAS.

This fork keeps the Linux command-line flasher buildable and usable on current Arch systems. It includes the local fixes needed by the RaceUp TC375 Lite Kit workflow:

- add the missing C++ fixed-width integer include for newer GCC/libstdc++ headers;
- fix `new[]`/`delete[]` mismatches in TAS packet buffers;
- initialize timeout variables used by the flash download path;
- reduce TAS read/write chunks from 32 KiB to 16 KiB for the TC375 setup.

## Build

Install the usual Arch build tools first:

```bash
sudo pacman -S --needed base-devel git
```

Then build the Linux flasher:

```bash
git clone git@github.com:LucaFeggi-RaceUp/aurix-flasher-arch.git
cd aurix-flasher-arch/linux
make -f Makefile_linux
```

The runtime helper file must stay next to the binary:

```bash
test -x ./aurix_flasher && echo "aurix_flasher OK"
test -f ./flash_TC3xx.hex && echo "flash_TC3xx.hex OK"
```

## TAS/DAS

The flasher connects to TAS on `localhost:24817`; it does not talk to the debug adapter by itself. Make sure Infineon TAS/DAS for Linux is installed and exactly one TAS server is running.

For the RaceUp Arch setup, DAS/TAS `8.3.0` is the Linux package currently used:

```text
DAS_8.3.0_linux_x64.deb
```

Do not assume the newest Infineon TAS/DAS package is available for Linux. Some newer TAS/DAS artifacts are Windows-only.

## Typical TC375 Standard Flash

From the `ControlUnitLogicOperator` repository root, prefer the helper script:

```bash
tools/flash_aurix_standard.sh
```

For a no-flash target check:

```bash
tools/flash_aurix_standard.sh --check
```

Continue only if the target list identifies the MCU, for example `TC37x`. Do not flash if it says `no device`.
