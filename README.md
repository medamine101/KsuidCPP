# KSUID C++

## KSUID Implementation in C++

Implementation complete and appears to be working, only tested on macOS 12.3.1 on an Intel CPU.

Credits to German Mendez Bravo (Kronuz) for the base_x.hh and uinteger_t.hh files. Original repo can be found [here](https://github.com/Kronuz/base-x).

This implementation is a C++ port of the Java implementation [ksuid](https://github.com/ksuid/ksuid). This verson is functionally equivalent, with some differences listed below:
- Operator overloading is used in this C++ implementation to support sorting rather than the Java version's equals() and compareTo() methods.
- The Java version's hashCode() method is not implemented in this C++ version.
- The Java version's toString() method is not implemented in this C++ version. Other printing methods are implemented.

Potential Issues with this implementation:
- If anything other than a 64-bit machine is used, then the toLogString() method may not work as the assumption that an int is 4 bytes is made.
- I do not know if endianness is an issue with relation to how information is moved from the int timestamp to 4 separate bytes in ksuidBytes vector.