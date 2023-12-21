#include <efi.h>
#include <efilib.h>
#include <maths/maths.h>


double pow(double Number, UINT32 power) {

    if (power == 0) return 1;
    else return pow(Number, power - 1);
}

UINT64 factorial(UINT64 Number) {

    if (Number == 0) return 1;
    return Number * factorial(Number-1);
}

double exp(double Number) {

    double result = 1;
    for (UINTN i = 1; i < 21; i++)
        result += pow(Number, i) / factorial(i);

    return result;
}

double sqrt(double Number) {

    double result = 1;
    for (UINTN i = 1; i < 21; i++)
        result += pow(-1, i-1) * ((2*i-3) / (pow(2, i) * factorial(i))) * pow(Number, i);

    return result;
}
