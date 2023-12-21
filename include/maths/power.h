/* Ce fichier contient toutes les fonctions permettant de faire appel aux fonctions exponentiel et puissance.
*/

#ifndef _POWER_
#define _POWER_

#include <efi.h>
#include <efilib.h>


UINT64 factorial(UINT64 Number);
double pow(double Number, UINT32 power);
double exp(double Number);
double sqrt(double Number);

#endif
