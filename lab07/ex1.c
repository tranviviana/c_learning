#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "ex1.h"

long long int sum(int vals[NUM_ELEMS]) {
    clock_t start = clock();

    long long int sum = 0;
    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for(unsigned int i = 0; i < NUM_ELEMS; i++) {
            if(vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

long long int sum_unrolled(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    long long int sum = 0;

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
            if(vals[i] >= 128) sum += vals[i];
            if(vals[i + 1] >= 128) sum += vals[i + 1];
            if(vals[i + 2] >= 128) sum += vals[i + 2];
            if(vals[i + 3] >= 128) sum += vals[i + 3];
        }

        // TAIL CASE, for when NUM_ELEMS isn't a multiple of 4
        // NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
        // Order is important, since (NUM_ELEMS / 4) effectively rounds down first
        for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

long long int sum_simd(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    __m128i _127 = _mm_set1_epi32(127); // This is a vector with 127s in it... Why might you need this?
    long long int result = 0; // This is where you should put your final result!
    /* DO NOT MODIFY ANYTHING ABOVE THIS LINE (in this function) */

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        /* YOUR CODE GOES HERE */
        __m128i sum_vec = _mm_setzero_si128();
        for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
            __m128i tmp = _mm_loadu_si128((__m128i *) (vals + i));
            __m128i cmp = _mm_cmpgt_epi32(tmp,_127);
            __m128i adding = _mm_and_si128(cmp, tmp);
            sum_vec = _mm_add_epi32(adding, sum_vec);
            
        }
        int tmp_arr[4];
        _mm_storeu_si128((__m128i *) tmp_arr, sum_vec);
        result += tmp_arr[0] + tmp_arr[1] + tmp_arr[2] + tmp_arr[3];

        /* Hint: you'll need a tail case. */
        for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                result += vals[i];
            }
        }
    }

    /* DO NOT MODIFY ANYTHING BELOW THIS LINE (in this function) */
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}

long long int sum_simd_unrolled(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    __m128i _127 = _mm_set1_epi32(127);
    long long int result = 0;
    /* DO NOT MODIFY ANYTHING ABOVE THIS LINE (in this function) */

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        /* YOUR CODE GOES HERE */
        /* Copy your sum_simd() implementation here, and unroll it */
        __m128i sum_vec = _mm_setzero_si128();
        for(unsigned int i = 0; i < NUM_ELEMS / 16 * 16; i += 16) {
            __m128i tmp = _mm_loadu_si128((__m128i *) (vals + i));
            __m128i cmp = _mm_cmpgt_epi32(tmp,_127);
            __m128i adding = _mm_and_si128(cmp, tmp);
            sum_vec = _mm_add_epi32(adding, sum_vec);


            __m128i tmp2 = _mm_loadu_si128((__m128i *) (vals + 4 + i));
            __m128i cmp2 = _mm_cmpgt_epi32(tmp2,_127);
            __m128i adding2 = _mm_and_si128(cmp2, tmp2);
            sum_vec = _mm_add_epi32(adding2, sum_vec);


            __m128i tmp3 = _mm_loadu_si128((__m128i *) (vals + 8 + i));
            __m128i cmp3 = _mm_cmpgt_epi32(tmp3,_127);
            __m128i adding3 = _mm_and_si128(cmp3, tmp3);
            sum_vec = _mm_add_epi32(adding3, sum_vec);


            __m128i tmp4 = _mm_loadu_si128((__m128i *) (vals + 12 + i));
            __m128i cmp4 = _mm_cmpgt_epi32(tmp4,_127);
            __m128i adding4 = _mm_and_si128(cmp4, tmp4);
            sum_vec = _mm_add_epi32(adding4, sum_vec);
        
        }
        int tmp_arr[4];
        _mm_storeu_si128((__m128i *) tmp_arr, sum_vec);
        result += tmp_arr[0] + tmp_arr[1] + tmp_arr[2] + tmp_arr[3];
        for(unsigned int i = NUM_ELEMS / 16 * 16; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                result += vals[i];
            }
        }
        if (NUM_ELEMS < 16) {
        result = 0;
        for(unsigned int i = 0; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                result += vals[i];
            }
        }
        }

        /* Hint: you'll need 1 or maybe 2 tail cases here. */
    }

    /* DO NOT MODIFY ANYTHING BELOW THIS LINE (in this function) */
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}
