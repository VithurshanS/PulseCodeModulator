// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:



// implementation
int size;



int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
int floori(double num) {
    int result = (int)num; 
    if (num < 0 && num != result) {
        result -= 1;
    }

    return result;
}
double power(double base, int exp) {
    double result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

double nor(double x) {
    double pi = 3.14159265358979323846;
    while (x > pi) {
        x -= 2 * pi;
    }
    while (x < -pi) {
        x += 2 * pi;
    }
    return x;
}

double sine(double x) {
    x = nor(x);
    double value = x;

    double term;
    int sign = -1;
    for (int i = 3; i <= 13; i += 2) {
        term = power(x, i) / factorial(i);
        value += sign * term;
        sign *= -1; 
    }

    return value;
}







float analog_signal_generator(asignal signal, int t)
{
	float angle,answer;
	angle = (signal.omega * t) + signal.sigma;
	answer = signal.A*sine(angle);
	return answer;
}

void sampler(float *samples, int interval, asignal signal)
{
    
    int j =0;
    size = ((signal.duration)/interval)+1;
    for (int i = 0 ; i<=signal.duration;i = i+interval){
        samples[j] = analog_signal_generator(signal,i);
        j++;
    }

}


void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
    for(int i = 0;i<size;i++){
        float selval = samples[i];
        float ans;
        ans = ((selval-(-1)*A)/(A-(-1)*A))*levels;
        pcmpulses[i] = floori(ans);
        //printf("%.2f\n",floor(ans));
    }
	
}

void enco(int *ds,int n,int *ind,int bits){
	int x = n;
	int i = 0;
	int arr[bits];
    for(int y=0;y<bits;y++){
        arr[y]=0;
    }
	while(x>1){
		 arr[i] = x%2;
		 x = x/2;
		 i++;
	}
	arr[i] = x;
	for(int j = bits-1;j>=0;j--){
		ds[*ind] = arr[j];
		(*ind)++;
	}

}

void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	int ind = 0;
	for(int i = 0; i<size;i++){
		enco(dsignal,pcmpulses[i],&ind,encoderbits);
	}
	//TODO
}
