# Programming a Microchip

In embedded systems development, building and transferring binaries to the
microchips requires a specific awareness of the hardware, software, and tools
involved. Unlike developing for a desktop computer, the process is not a
simple compile-and-run, but a multi-step workflow involving cross-compilation
and specialized programming hardware.

## Building binaries

Almost in all cases, the development computer (host) has different architecture
from the microchip (target). So, we need a cross-compiler that can run in the
host computer and generate instructions for target computer.

**Examples**
- avr-gcc: GCC compiler that runs in Windows/Linux or Mac, and generates the
instructions for AVR target architecture.
- arm compiler: cross compiler that generates binaries for ARM architecture

To generate correct binary, the compiler must be configured with specific flags.
For example, select the target (-mcpu), floating-point unit if applicable (-mfpu),
and instruction set (-mthumb).

Linker scripts: The linker needs special script to know how to place the compiled
code and data into the microchip's specific memory layout (flash and RAM).

### Memory Layout
Microchips typically have distinct memory map that differs from a desktop system.

* Flash vs RAM: The code is stored in persistent flash memory but executes from
RAM, a dedicated instruction-cache, or directly from flash depending on the chip
and configuration.
* Vector table: Most embedded applications start at a specific memory address
where the processor finds the "vector table", a list of pointers to interrupt
service routines and the initial program entry point.

### Linking
* A linker script should be updated with target's memory layout, the order of
sections in which the target code to be arranged, required symbol definitions
(such as stack pointer, heap start etc).
* The linker shall link the input object files as per the configurations
specified in the linker script.
* The linker may output binary file in the .elf format. It needs to be converted
into .bin or .hex as per target's programming eco-system requirement.

- .bin: A raw, flat binary file containing only the machine code. It has no
metadata and is direct image of what will be written to memory.
- .elf: A more complex format containing executable code, data and debugging
information. The debuggers will use this format.
- .hex: An ASCII text file that represents the binary data along with addresses,
making it easier to parse and transfer.

## Programming Target (transferring binaries)
The binary file cannot be simply copied into the chip. Specialized hardware,
often called an in-circuit programmer or debugger, is required to communicate
with the microchip.

* programmer device: a device that connects to the computer on one end and to
the microchip on the other. Example: J-Link or ST-Link.
* evaluation board: the board with microcontoller connected and provides
interfaces (to program and debug) such as USB-A, micro USB to connect to the
computer.
* bootloader: some microcontroller, like those in Arduino, have a pre-written
"bootloader" program in their memory. We can use a serial connection (like USB)
to upload new code through this bootloader, eliminating the need for a
separate programmer in some cases.
* programming software: Software on the computer, often part of the IDE
(MPLAB Studio, Arduino etc), controls the programmer device to send the
compiled code to the microcontroller.

### Hardware Interfaces
The programmer connects to the microchip using specific debug interfaces.
* **JTAG**: A widely adopted standard interface for testing, programming,
and debugging integrated circuits, including microcontrollers.
* **SWD (Serial Wire Debug):** A two-wire interface developed by ARM,
offering a simpler and more compact alternative to JTAG, common on modern
ARM Cortex-M microcontrollers.
* **SWV (Serial Wire Viewer):**
* **UPDI (Unified Program and Debug Interface):**
* DebugWIRE: A two-wire debugging interface used by some AVR microcontrollers,
allowing on-chip debugging without dedicated JTAG pins.
* **ISP (In-System Programming):** A method for programming microcontrollers
directly on the target board, often using SPI or I2C protocols, without the
need for a separate programmer.

### Software Interfaces
* **IDE:** Software suites like IAR Embedded workbench, Keil MDK, STM32CubeIDE,
and MPLAB X IDE integrate code editors, compilers, and debuggers, providing a
unified environment for development. These IDEs typically connect to hardware
debuggers through specific drivers or plugins.
* **GDB(GNU Debugger):** A powerful command-line debugger widely used in
embedded development. It can connect to remote targets (like microcontrollers)
via a GDB server running on the host computer, which in turn communicate with
the hardware debugger.
* **Vendor Specific Tools:** The microcontroller manufacturers provide their
own programming and debugging utilities and GUIs, such as Microchip's MPLAB
IPE or STMicroelectronics' STM32 ST-LINK utility.
* **Semi hosting:** An ARM specific feature that allows the target microcontroller
to use host computer's I/O facilities (like printing to console) through the
debugger connection, simplifying debugging output.
* **Segger Real-Time Terminal (RTT):** A technology from Segger that enables
high-speed, bi-directional communication between the host and target, offering
a more efficient alternative to semihosting for debugging output.
