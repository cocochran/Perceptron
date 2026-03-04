#include <stdio.h>

/*
    Perceptron computes y=sign(w*x+b) where
        - w is a float weight vector
        - b is a float bias
        - sign(z) = 1 if z>=0, otherwise -1

    The variable y signifies the activation (or non-activation) of the perceptron.
*/

float dot_product(float x[][2], float *w, int n);
int predict(float x[][2], float *w, int n);
void train(float x[][2], float *w, float *b, int *y, float *eta, int n);
void perceptron();


struct perceptron {
    float w[2];
    float b;
    float eta;
};

int main(){
    float x[4][2] = {
        {1.0, 1.0},
        {2.0, 2.0},
        {-1.0, -1.0},
        {-2.0, -1.0}
    };

    int y[4] = {1, 1, -1, -1};

    struct perceptron p;

    p.w[0] = 0.0;
    p.w[1] = 0.0;
    p.b = 0.0;
    p.eta = 0.1;

    train(x, p.w, &p.b, y, &p.eta, 50);
    printf("W[0]=%f, W[1]=%f, b=%f, eta=%f", p.w[0], p.w[1], p.b, p.eta);
    return 0;
}

/* Returns the dot product of a two floating-point vectors. */
float dot_product(float x[][2], float *w, int n){
    float sum = 0.0;
    for (int i = 0; i < n; i++){
        sum += (**(x + i)) * (*(w + i));
    }
    return sum;
}

int predict(float x[][2], float *w, int n){
    return dot_product(x, w, n) >= 0.0 ? 1 : -1;
}

void train(float x[][2], float *w, float *b, int *y, float *eta, int n){
    fopen("/output/traing-log.txt", "w");
    for (int k = 0; k < n; k++){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 2; j++){
		if (predict(x, w, n) == y[j]) return;
                w[j] = w[j] + *eta * y[i] * x[i][j];

		
            }
            *b = *b + *eta * y[i];
            printf("Epoch %d: w[0]=%f, w[1]=%f, b=%f, eta=%f\n", k, w[0], w[1], *b, *eta);

        }
    }
}


