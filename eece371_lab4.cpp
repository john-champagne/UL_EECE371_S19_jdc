#define PIECEWISE

#ifndef PIECEWISE
#include <math.h>
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


typedef uint8_t byte;


#ifdef PIECEWISE
/* piecewise linearization */
float sig(float i){
    if (i > 3)
        return 1;
    if (i < -3)
        return 0;
    return (i/6 + 0.5f);
}

float tanh(float i){
    if (i > 1.667)
        return 1;
    if (i < -1.667)
        return -1;
    return i*0.6;
}

#else
float sig(float i){
    return 1/(1+exp(-1*i));
}

float tanh(float i){
    return (exp(2*i) - 1)/(exp(2*i + 1));
}
#endif

float relu(float i) { return i >= 0 ? i : 0; }




float* perceptron_layer(float* inputs, byte input_size, float** weights, byte output_size, float* bias){
    /* allocate output matrix */
    float* output = (float*)malloc(sizeof(float)*output_size);
    
    /* matrix multiplication the dumb way */
    for (int i = 0; i < output_size; i++) {
        output[i] = bias[i];    // add the bias
        for (int j = 0; j < input_size; j++){
            output[i] += inputs[j]*weights[i][j]; // sum up the inputs * weights
        }
        output[i] = sig(output[i]);     // sigmoid
    }
    return output;
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

float** conv(float data[5][5], float filter[3][3]){
    float** output = (float**)malloc(sizeof(float*) * 3);
    for (int i = 0; i < 3; i++)
        output[i] = (float*)malloc(sizeof(float) * 3);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            float window[3][3];
            for (int k = 0; k < 3; k++)
                for (int l = 0; l < 3; l++)
                    window[k][l] = data[i + k][j + l];
            
            output[i][j] = conv_single(window,filter);
        }
    }
    return output;
}

int main() {
    float layer_1_weights[2][2];
    float layer_1_bias[2];

    float output_weights[1][2];
    float output_bias[1] = {rand()};
    
    for (int i = 0; i < 2; i++){
        layer_1_bias[i] = rand();
        output_weights[1][i] = rand();
        for (int j = 0; j < 2; j++)
            layer_1_weights[i][j] = rand();
    }

    float x[2] = {1,1};
    float* layer_1 = perceptron_layer((float*)x, 2, (float**)layer_1_weights, 2, layer_1_bias);
    float* out = perceptron_layer(layer_1, 2, (float**)output_weights, 1, output_bias);
    printf("%f", (*out));
}

