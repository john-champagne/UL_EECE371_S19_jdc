#define PIECEWISE

#ifndef PIECEWISE
#include <math.h>
#endif

typedef byte uint8_t;


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

float relu(float i) { return x >= 0 ? x : 0; }




float* perceptron_layer(float* inputs, byte input_size, float** weights, byte output_size, float* bias){
    /* allocate output matrix */
    float* output = malloc(sizeof(float)*output_size);
    
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

float conv_single(float data[5][5], float filter[3][3], byte X, byte Y){
    for (int i = 0; i < 3; i++)
}

float** conv(float data[5][5], float filter[3][3]){
    float output[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            output[i][j] = conv_single(data,filter,i,j);
        }
    }
}

void setup() {
    float layer_1_weights[2][2];
    float layer_1_bias[2];

    float output_weights[1][2];
    float output_bias[1];
}

void loop() {

}
