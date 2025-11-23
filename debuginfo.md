DWARF (`Debugging With Attributed Record Formats`) is a widely used, standardized debugging data format.
It provides a comprehensive and standardized way for compilers to encode debugging information within
executable and object files, enabling debuggers to effectively analyze and control program execution.

## Key aspects of DWARF:
### Standardization:
DWARF is an open standard, ensuring interoperability between different compilers, debuggers, and
operating systems. The standard is maintained and evolved by the DWARF Debugging Information Format Committee.

### Rich Information:
It stores a wealth of debugging information, including:
* **Source file and line number mapping:** Allows debuggers to link machine code instructions back to the
 original source code.
* **Variable information:** Details about variable names, types, scopes, and memory locations.
* **Function and subroutine information:** Includes function names, parameters, return types, and call stack details.
* **Type information:** Descriptions of complex data types like structures, unions, and classes.
* **Optimized code support:** Provides mechanisms to handle information for code that has been optimized by the compiler.

### Independence from Object File Format:
While often used with Executable and Linkable Format (ELF), DWARF is designed to be independent
of the specific object file format.

**Evolution:** The DWARF standard has undergone several revisions, with DWARF 5 being the current
stable version and DWARF 6 under development. Each revision introduces enhancements and support
for new language features and debugging requirements.

## How DWARF works:
When a program is compiled with debugging information enabled (e.g., using the -g flag with GCC),
the compiler generates DWARF data and embeds it into the object files and ultimately the executable.
This data is typically organized into various sections within the object file, such as `.debug_info`,
`.debug_line`, `.debug_abbrev`, etc. Debuggers then parse this DWARF information to provide features
like setting breakpoints, inspecting variables, and stepping through code at the source level.
