See https://github.com/rusefi/rusefi/wiki/Custom-Firmware

A universal firmware for boards based on https://github.com/andreika-git/hellen-one/tree/master/modules/mega-mcu144

See also https://github.com/rusefi/fw-community-hellen-100

## Local firmware build

Install the rusEFI build prerequisites, including Arm GNU Toolchain 14.2.Rel1,
Java, and the FAT filesystem image tools, then initialize the submodules:

```bash
bash bin/_init.sh
./compile_firmware.sh
```

The script works from any directory and accepts make arguments, for example
`./compile_firmware.sh clean` or `./compile_firmware.sh -j4`.
The build automatically regenerates configuration headers and the matching
TunerStudio INI under `generated/`; manual metadata generation is unnecessary.

Firmware outputs are in `ext/rusefi/firmware/build/` (`rusefi.bin`,
`rusefi.hex`, `rusefi.elf`, and the CRC-protected `rusefi.srec`). Generate
the binary and CRC-protected DFU in `ext/rusefi/firmware/deliver/` with
`./compile_firmware.sh dfu`.

Build the Linux simulator with `./_compile_simulator.sh`.

Run rusEFI's floating-point timestamp conversion check after building:

```bash
(cd ext/rusefi/firmware && bash check_illegal_conversion.sh)
```
