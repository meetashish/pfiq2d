#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/// @brief Generate Uniformly distributed random number with in [a,b]
/// @param[in] a lower limit
/// @param[in] b upper limit
/// @return Uniformly distributed random number with in [a,b]
float UnifRand(float a, float b);

/// @brief Packs two float i and q into a double
///         -----------------------------------
///  IQ ==> |     float i    |    float q     |
///         -----------------------------------
///         0              31,32              63
/// @param[in] i inphase sample
/// @param[in] q quadrature sample
/// @return packed i and q in double
double packiq(float i, float q);

/// @brief Separates i and q from iq double
/// @param[in] piq pointer to double iq
/// @param[out] pi pointer to inpahse sample
/// @param[out] pi pointer to quadrature sample
void unpackiq(double *piq, float *pi, float *pq);

int main() {
    
    // Generate random inphase sample and display it
    float i = UnifRand(0,5);
    printf("Inphase sample = %f\n", i);
    
    // Generate random quadrature sample and display it
    float q = UnifRand(-10,5); 
    printf("Quadrature sample = %f\n", q);

    // Pack i and q sample and display it
    double iq = packiq(i, q);
    printf("Packed IQ sample = %f\n",iq);

    // Check now by separating i and q from iq
    float ni, nq;
    // Unpack i and q sample from iq and display it
    unpackiq(&iq, &ni, &nq);
    printf("Unpacked inphase sample = %f\n", ni);
    printf("Unpacked quadrature sample = %f\n", nq);

    return 0;
}

float UnifRand(float a, float b) {
    return a + rand() / (RAND_MAX / (b - a + 1) + 1);
}

double packiq(float i, float q) {
    // Type cast i to int32_t
    int32_t *pI = (int32_t*)&i;
    // Type cast pI to int64_t
    int64_t I = (int64_t)*pI;
    // Type cast q to int32_t
    int32_t *pQ = (int32_t*)&q;
    // Type cast pQ to int64_t
    int64_t Q = (int64_t)*pQ;

    // pack I and Q
    int64_t IQ = (Q << 32) | (I & 0xFFFFFFFF);
    // Type cast IQ to double
    double *piq = (double*)&IQ;
    double iq = *piq;
    return iq;
}

void unpackiq(double *piq, float *pi, float *pq) {
    // Type cast *piq into float pointer
    float *ptriq = (float *)piq;
    // First 32-bit (0-31) belongs to inphase
    *pi = ptriq[0];
    // Second 32-bit (32-63) belongs to quadrature
    *pq = ptriq[1];
}