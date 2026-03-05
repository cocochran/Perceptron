#include <stdio.h>
#include <stdlib.h>

struct perceptron {
    float *w;
    float b;
    float eta;
};

float dot_product(float x[], float *w, int n);
int predict(float x[], struct perceptron *p, int n);
void train(float x[][2], int *y, struct perceptron *p, int n, int samples, int dimensions);
void print_epoch(int epoch, int errors, int dimensions, FILE *log, struct perceptron *p);
void print_perceptron(int dimensions, FILE *log, struct perceptron *p);


int main(){
    int dimensions = 2;
    float x[4][2] = {
        {1.0, 1.0},
        {2.0, 1.0},
        {-1.0, -1.0},
        {-2.0, -1.0}
    };

    int y[4] = {1, 1, -1, -1};

    //tried this with other sample sizes, so had to do it dynamically 
    struct perceptron p = {calloc(dimensions, sizeof(float)), 0.0, 0.1};

    train(x, y, &p, 50, 4, 2);
    free(p.w);
    return 0;
}

/* Returns the dot product of a two floating-point vectors. */
float dot_product(float x[], float *w, int dimensions){
    float sum = 0.0;
    for (int i = 0; i < dimensions; i++){
        sum += (*(x + i)) * (*(w + i));
    }
    return sum;
}

/* Predicts the value 1 or -1 by using the dot product and adding the perceptron bias.*/
int predict(float x[], struct perceptron *p, int n){
    return dot_product(x, p->w, n) + p->b >= 0.0 ? 1 : -1;
}

/* 
Trains a perceptron using n epochs, utilizing the arrays x and y as sample data.
*/
void train(float x[][2], int *y, struct perceptron *p, int n, int samples, int dimensions) {
    FILE *log = fopen("training-log.txt", "w");

    for (int k = 0; k < n; k++) {
        int all_correct = 1;
        int errors = 0;
        for (int i = 0; i < samples; i++) {
            if (predict(x[i], p, dimensions) != y[i]) {
                all_correct = 0;
                errors++;
                for (int j = 0; j < dimensions; j++)
                    p->w[j] = p->w[j] + p->eta * y[i] * x[i][j];
                p->b = p->b + p->eta * y[i];
            }

        }   
        print_epoch(k + 1, errors, dimensions, log, p);
        if (all_correct == 1) break;
    }
    print_perceptron(dimensions, log, p);
    fclose(log);
}

/* Helper function to print out the data of an epoch. */
void print_epoch(int epoch, int errors, int dimensions, FILE *log, struct perceptron *p){
    printf("Epoch %d: errors = %d, w = [", epoch, errors);
    fprintf(log, "Epoch %d: errors = %d, w = [", epoch, errors);

    for (int i = 0; i < dimensions - 1; i++){
        printf("%.2f, ", p->w[i]);
        fprintf(log, "%.2f, ", p->w[i]);

    }    
    printf("%.2f], ", p->w[dimensions-1]);
    printf("b = %.2f\n", p->b);
    fprintf(log, "%.2f], ", p->w[dimensions-1]);
    fprintf(log, "b = %.2f\n", p->b);
}

/* Helper function to print out the final data of a trained perceptron. */
void print_perceptron(int dimensions, FILE *log, struct perceptron *p){
    printf("Final: w = [");
    fprintf(log, "Final: w =[");

    for (int i = 0; i < dimensions-1; i++){
        printf("%.2f, ", p->w[i]);
        fprintf(log, "%.2f, ", p->w[i]);

    }    
    printf("%.2f], ", p->w[dimensions-1]);
    printf("b = %.2f\n", p->b);
    fprintf(log, "%.2f], ", p->w[dimensions-1]);
    fprintf(log, "b = %.2f\n", p->b);
}



