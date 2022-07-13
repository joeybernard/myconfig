#include <stdio.h>

int main(int argc, char **argv) {
    float a = 0.1;
    float x = 0.0;
    for (int i = 0; i<30; i++) {
	x = x+ a;
    }
    printf("%f", x);
}
