#define PIECEWISE
#ifndef PIECEWISE
#include <math.h>
#endif
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef uint8_t byte;
byte image[2048][2048];
byte downsampled_image[128][128];
float sig(float i){
    return 1/(1+exp(-1*i));
}
float tanh(float i){
    return (exp(2*i) - 1)/(exp(2*i + 1));
}
float relu(float i) { return i >= 0 ? i : 0; }
// Dummy function to test if code compiles 
byte pgm_read_byte_near(short addr) {
    return 0;
}
float conv_single(float data[3][3], float filter[3][3]){
    float sum = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                sum += data[i][k] * filter[k][j];       
            }
        }
    }
    return sum;
}
// Performs convolution on a 32x32 image with a 3x3 filter.
// Returns a 30x30 image.
float** conv(float data[32][32], float filter[3][3]){
    // Allocate output array.
    float** output = (float**)malloc(sizeof(float*) * 30);
    for (int i = 0; i < 30; i++)
        output[i] = (float*)malloc(sizeof(float) * 30);
    
    for (int i = 1; i < 30; i++){
        for (int j = 1; j < 30; j++){
            float window[3][3];
            for (int k = -1; k <= 1 ; k++)
                for (int l = -1; l <= 1; l++)
                    window[k][l] = data[i + k][j + l];
            output[i][j] = conv_single(window,filter);
        }
    }
    return output;
}
int main() {
    // Downsample the image.
    for (int i = 0; i < 128; i++)
        for (int j = 0; j < 128; j++)
            downsampled_image[i][j] = image[i*16][j*16];
}
