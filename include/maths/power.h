/* Ce fichier contient toutes les fonctions permettant de faire appel aux fonctions exponentiel et puissance.
*/

#ifndef _POWER_
#define _POWER_

#include <efi.h>
#include <efilib.h>


UINT64 pow(UINT64 Number, UINT64 power);
UINT64 factorial(UINT64 Number);
float exp(UINT64 Number);
float sqrt(UINT64 Number);

#endif
