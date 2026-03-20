#include <stdio.h>

//uint8_t upper_bound = 100;
//uint8_t lower_bound = -100;

double noise_constant(){
        double value = (double)(rand() % 201 - 100) / 3000.0f;
        /*double value = (double)(rand() % (upper_bound - lower_bound + 1)
                    + lower_bound) / 500.0f;*/

        //printf("%f\n",value);
        return value;
    }

double noise_constant_only_positive(){
        double value = (double)(rand() % 101) / 3000.0f;
        /*double value = (double)(rand() % (upper_bound+ 1)) / 500.0f;*/

        //printf("%f\n",value);
        return value;
}
