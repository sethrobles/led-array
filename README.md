# LED Array (32×32 STM32-Driven Matrix)

This repository contains the **hardware design and firmware** for a custom **32×32 LED matrix PCB** designed in **KiCad** and driven by an **STM32 microcontroller**.

The project was built both as a learning exercise in multi-layer PCB design and as a functional, firmware-controlled LED display.

🔗 **Project blog / design log:**
https://sethrobles.github.io/blogs/led-array/

---

## Project Overview

The LED array is implemented as a multiplexed matrix driven by shift registers and MOSFETs, with all timing and animation handled in firmware.

### Hardware Features

- **32×32 LED matrix** (1,032 LEDs total)
- **16× 74HC595 shift registers** for serial-to-parallel expansion
- **8× N-channel MOSFETs** for row/column current switching
- **STM32 microcontroller** for scanning, timing, and animation logic
- **On-board buck converter** for efficient 3.3 V regulation
- **4-layer PCB** designed and routed in KiCad
- **Hierarchical schematics** to support scalable layout and reuse




## Schematic Structure

The board uses an **on-board switching buck converter (TPS54331DR)** to step a ~5 V input down to 3.3V for the STM32 and logic circuitry.


The design uses a hierarchical schematic organization to keep both the schematic and PCB layout manageable:

- **LED Row**: 8 LEDs tied to a single shift-register output
- **LED Module**: One shift register driving 64 LEDs
- **LED Group**: Four LED modules grouped for layout and logic convenience

In total:
- **16 shift registers**
- **1,032 LEDs**


---

## Firmware

Firmware is written using **STM32CubeIDE** and is responsible for:

- High-speed LED scanning
- Register shifting and latch control
- Multiplex timing
- Multiple animation modes (spirals, perimeter effects, hearts, text, etc.)
- Minimizing ghosting and partial illumination

Programming and debugging are currently done using **ST-Link**. A future revision may include a USB bootloader to eliminate the need for programming headers.

Firmware lives alongside the hardware files but is kept logically separate. It is divided into 3 .c files: main, led_array, and frames. Main is actually uploaded to the board, led_array includes the basic logic for programming a frame, and frames contains specific frames for the board that build the animations.

---

## Repository Structure

- `Firmware/` – STM32 firmware source (CubeIDE project)
- KiCad project files – schematics, PCB layout, and libraries
- Backup and fabrication-related artifacts (not required for normal use)

---

## Status

The board has been fabricated, assembled, powered, and tested:

- Buck converter output verified (~20 mV ripple observed)
- STM32 successfully flashed and running on hardware
- LED scanning and animations functional

---

## Motivation & Inspiration

This project was inspired by:
- Phil’s Lab STM32 PCB design tutorials
- Guidance and feedback from friends with PCB design experience

The full design process, decisions, mistakes, and lessons learned are documented on the project blog.

📖 **Read the full build log:**
https://sethrobles.github.io/blogs/led-array/


*Summary Written with ChatGPT, read before publishing
