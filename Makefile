COMPILER = gcc
OPT = -Wreturn-type -Wimplicit-function-declaration -pedantic

perceptron: perceptron
	$(COMPILER) $(OPT) perceptron.c -o perceptron

perceptron.zip: Makefile perceptron.c
	zip perceptron.zip Makefile perceptron.c

clean:
	rm -rf *.o perceptron perceptron.zip training-log.txt