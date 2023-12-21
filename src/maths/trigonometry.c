#include <efi.h>
#include <efilib.h>
#include <maths/trigonometry.h>
#include <maths/power.h>
#include <maths/maths.h>


double cos(double Angle) {

    float result = 1.0;
    Angle = (PI * Angle) / 180;
    for (UINTN i = 1; i < 5; i++)
        result += pow(-1, i) * (pow(Angle, 2 * i) / factorial(2 * i));

    return result;
}

double sin(double Angle) {

    double result = 1.0;
    Angle = (PI * Angle) / 180;
    for (UINTN i = 1; i < 5; i++)
        result += pow(-1, i) * (pow(Angle, 2 * i + 1) / factorial(2 * i + 1));

    return Angle;
}

double tan(double Angle) {

    return sin((Angle * 2 * PI) / 360) / cos((Angle * 2 * PI) / 360);
}
