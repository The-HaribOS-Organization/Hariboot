#include <efi.h>
#include <efilib.h>
#include <maths/trigonometry.h>
#include <maths/power.h>


float cos(float Angle) {

    return (1 - (pow(Angle, 2) / factorial(2)) + (pow(Angle, 4) / factorial(4)) - (pow(Angle, 6) / factorial(6)) + (pow(Angle, 8) / factorial(8)));
}

float sin(float Angle) {

    return (Angle - (pow(Angle, 3) / factorial(3)) + (pow(Angle, 5) / factorial(5)) - (pow(Angle, 7) / factorial(7)) + (pow(Angle, 9) / factorial(9)));
}

float tan(float Angle) {

    return (Angle + (pow(Angle, 3) / 3) + (pow((2 * Angle), 5)));
}

float acos(float Angle) { return Angle; }

float asin(float Angle) { return Angle; }

float atan(float Angle) { return Angle; }
