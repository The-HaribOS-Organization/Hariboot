
#ifndef _SERIAL_PORT_
#define _SERIAL_PORT_

#include <efi.h>
#include <efilib.h>

// Serial com port of the serial port.
#define SERIAL_COM1 0x3F8
#define SERIAL_COM2 0x2F8
#define SERIAL_COM3 0x3E8
#define SERIAL_COM4 0x2E8
#define SERIAL_COM5 0x5F8
#define SERIAL_COM6 0x4F8
#define SERIAL_COM7 0x5E8
#define SERIAL_COM8 0x4E8

// All the registers of the serial port.
#define SERIAL_DATA_REGISTER(x) (x)
#define SERIAL_INTERRUPT_ENABLE_REGISTER(x) (x+1)
#define SERIAL_FIFO_CONTROL_REGISTER(x) (x+2)
#define SERIAL_LINE_CONTROL_REGISTER(x) (x+3)
#define SERIAL_MODEM_CONTROL_REGISTER(x) (x+4)
#define SERIAL_LINE_STATUS_REGISTER(x) (x+5)
#define SERIAL_MODEM_STATUS_REGISTER(x) (x+6)
#define SERIAL_SCRATCH_REGISTER(x) (x+7)

// Parity for line protocol
#define NONE (0x0 << 3) & 0xFF
#define ODD (0x1 << 3) & 0xFF
#define EVEN ((0x1 << 4) | (0x1 << 3))
#define MARK ((0x1 << 5) | (0x1 << 3))
#define SPACE ((0x1 << 5) | (0x1 << 4) | (0x1 << 3))

// Macro for line status register
#define DATA_READY 0x0
#define OVERRUN_ERROR 0x1
#define PARITY_ERROR 0x2
#define FRAMING_ERROR 0x3
#define BREAK_INDICATOR 0x4
#define TRANSMITTER_HOLDING_REGISTER_EMPTY 0x5
#define TRANSMITTER_EMPTY 0x6
#define IMPENDING_ERROR 0x7

UINT32 readData(UINT16 comPort);
void printString(UINT16 comPort, const CHAR8 *string);
BOOLEAN initSerialPort(UINT16 comPort);

#endif
