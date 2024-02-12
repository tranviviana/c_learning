#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// Use a union to allow bit level access for ease of conversion
typedef union {
	float f;
	uint32_t i;
} flint;
typedef union {
    double d;
    uint64_t i;
} dlint;

int main() {
	/*flint x;
	x.f = 2.0; // The single-precision floating point number 2.0 is represented by 0x4000 0000 in hexadecimal
  
	
	printf("value in x is: %f as a float, and 0x%x = %d as a uint32_t.\n", x.f, x.i, x.i);*/
    dlint twos;
    twos.d = pow(2, 64.0);
    dlint max;
    max.d = pow(2, 64.0);
    dlint min;
    min.d = 0.0;
    dlint mid;
    mid.d = max.d / 2;
    dlint next;
    next.i = mid.i + 1;
    while (0 <= mid.i && mid.i < twos.i) {
    if (mid.i >= (uint64_t) mid.d && next.i < (uint64_t) (next.d))      { 
        printf("value in x is: %f as a double, and 0x%lx = %lu as a uint64_t.\n", mid.d ,mid.i, mid.i);
        printf("done");
        break;
    }
    else if (mid.i < (uint64_t) mid.d) {
    max.d = mid.d;
    mid.d = (max.d + min.d)/2;
    next.i = mid.i + 1;
    }
    else {
        min.d = mid.d;
        mid.d = (mid.d + max.d) / 2;
        next.i = mid.i + 1;
    }
    printf("value in x is: %f as a double, and 0x%lx = %lu as a uint64_t.\n", mid.d ,mid.i, mid.i);
 
    }

}


