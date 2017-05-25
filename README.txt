Batlab V1.0 Measurement Processor Firmware

This firmware was developed using the MPLABX IDE and the free version of the XC8 compiler. The target device is a PIC18F24k40 microcontroller.

Description:

The Measurement Processor is the main processor in the Batlab system. It handles the collection of all voltage, current, and temperature measurements, and also controls the cell relays, a MESSAGE LED, and the current drivers for the 4 cell channels. It features a communications interface over UART featuring a slim register-transation-based communications protocol, data from which is routed to the Communications Processor and sent to a PC connected over USB.

More information, along with a complete programming user's guide, can be found at http://www.lexcelon.com


