#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SAMPLE_RATE 44100
#define DURATION 1.0                    // seconds
#define BASE_FREQ 220.0                 // A3
#define N_HARMONICS 4                  // Number of sine partials
#define PI 3.14159265358979323846

int main() {
    int num_samples = (int)(SAMPLE_RATE * DURATION);
    double *output = malloc(num_samples * sizeof(double));
    if (!output) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Generate the additive synthesis signal
    for (int i = 0; i < num_samples; ++i) {
        double t = (double)i / SAMPLE_RATE;
        double sum = 0.0;

        for (int h = 1; h <= N_HARMONICS; ++h) {
            sum += sin(2.0 * PI * BASE_FREQ * h * t) / h;  // roll-off
        }

        output[i] = sum;
    }

    // Prevent optimization: use checksum
    double checksum = 0.0;
    for (int i = 0; i < num_samples; ++i) {
        checksum += output[i];
    }

    printf("Generated %d samples. Checksum: %lf\n", num_samples, checksum);
    free(output);
    return 0;
}
