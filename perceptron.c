#include <stdio.h>

/*
    Perceptron computes y=sign(w*x+b) where
        - w is a float weight vector
        - b is a float bias
        - sign(z) = 1 if z>=0, otherwise -1

    The variable y signifies the activation (or non-activation) of the perceptron.
*/

float dot_product(float *x, float *w, int n);
int predict(float *x, float *w, int n);
int train(float *x, float *w, float *b, int y, float eta);
void perceptron();



int main(){

    return 0;
}

/* Returns the dot product of a two floating-point vectors. */
float dot_product(float *x, float *w, int n){
    float sum = 0.0;
    for (int i = 0; i < n; i++){
        sum += (*(x + i)) * (*(w + i));
    }
    return sum;
}

int predict(float *x, float *w, int n){
    return dot_product(x, w, n) >= 0.0 ? 1 : -1;
}

int train(float *x, float *w, float *b, int y, float eta){
    
}

void perceptron(){
    float w[2] = {0.0, 0.0};
    float b = 0.0;
    float eta = 0.1; // learning rate
}

