#include <efi.h>
#include <efilib.h>
#include "debug/io.h"
#include "debug/serial_port.h"


static void enableFIFO(UINT16 comPort) {

    outb(SERIAL_FIFO_CONTROL_REGISTER(comPort), 0xC7);
}

static void disableInterrupt(UINT16 comPort) {

    outb(comPort + 1, 0x00);
}

static UINT8 getStatus(UINT16 comPort) {

    return inb(SERIAL_LINE_STATUS_REGISTER(comPort));
}

static void putChar(UINT16 comPort, CHAR8 character) {

    while ((getStatus(comPort) & 0x20) == 0);
    outb(comPort, character);
}

static void setBaudRate(UINT16 comPort, UINT16 divisorValue) {

    outb(SERIAL_LINE_CONTROL_REGISTER(comPort), 0x80);
    outb(SERIAL_DATA_REGISTER(comPort), (divisorValue >> 8) & 0x00FF);
    outb(SERIAL_INTERRUPT_ENABLE_REGISTER(comPort), divisorValue & 0x00FF);
}

static void setDataBits(UINT16 comPort, UINT16 charLenght) {

    switch (charLenght) {
        case 5: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), 0x00); break;
        case 6: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), 0x01); break;
        case 7: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), 0x02); break;
        case 8: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), 0x03); break;
    }
}

static void setStopBit(UINT16 comPort, BOOLEAN stopBit) {

    if (stopBit == FALSE) outb(SERIAL_LINE_CONTROL_REGISTER(comPort), (0x0 << 2) & 0xFF);
    else outb(SERIAL_LINE_CONTROL_REGISTER(comPort), (0x1 << 2) & 0xFF);
}

static void setParityBit(UINT16 comPort, UINT8 type) {

    switch (type) {
        case 0x0: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), NONE); break;
        case 0x1: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), ODD); break;
        case 0x2: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), EVEN); break;
        case 0x3: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), MARK); break;
        case 0x4: outb(SERIAL_LINE_CONTROL_REGISTER(comPort), SPACE); break;
    }
}

UINT32 readData(UINT16 comPort) {

    while ((getStatus(comPort) & 0x1) == DATA_READY);
    return inb(SERIAL_DATA_REGISTER(comPort));
}

void printString(UINT16 comPort, const CHAR8 *string) {

    for (UINT16 i = 0; string[i] != '\0'; i++) putChar(comPort, string[i]);
}

BOOLEAN initSerialPort(UINT16 comPort) {

    disableInterrupt(comPort);
    setBaudRate(comPort, 0x0);
    setDataBits(comPort, 8);
    setStopBit(comPort, FALSE);
    setParityBit(comPort, 0x0);
    enableFIFO(comPort);

    outb(comPort + 0, 0xAE);
    if (inb(comPort + 0) != 0xAE) return TRUE;

    return FALSE;
}