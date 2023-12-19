#include <efi.h>
#include <efilib.h>
#include <maths/power.h>


UINT64 pow(UINT64 Number, UINT64 power) {

    UINT64 number = 1;
    for (UINT64 i = 0; i < power; i++) number *= Number;
    return number;
}

UINT64 factorial(UINT64 Number) {

    if (Number == 0) return 1;
    return Number * factorial(Number-1);
}

float exp(UINT64 Number) {

    return (1 + (pow(Number, 2) / factorial(2)) + (pow(Number, 3) / factorial(3)) + (pow(Number, 4) / factorial(4)) + (pow(Number, 5) / factorial(5)) + (pow(Number, 6) / factorial(6)) + (pow(Number, 7) / factorial(7)));
}

float sqrt(UINT64 Number) {

    return (1 + (1/2 * Number) - (1/8 * pow(Number, 2)) + (1/16) * pow(Number, 3));
}

double sqrt(double Number) {

    return (1.0 + (1.0 / 2 * Number) - (1.0 / 8 * pow(Number, 2)) + (1.0 / 16) * pow(Number, 3));
}
