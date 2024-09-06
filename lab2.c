// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);
void view(int *samples,int size);
int poweri(int base, int exp);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here

    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
    float A,omega,sigma;
    int duration,interval,encoderbits;
    printf("enter the input (Amplitude  angularspeed_inRadians  phase_shift  duration  time_interval  encoderbits):- ");
    scanf("%f %f %f %i %i %i",&A,&omega,&sigma,&duration,&interval,&encoderbits);
    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;
    inputsignal->duration = duration;
    //interval = 1;
    int bits = encoderbits;
    float *samples;
    int *pcmpulses;
    int *dsignal;
    //size = 6;
    int size1 = ((inputsignal->duration)/interval)+1;
    dsignal = malloc(size1*bits*sizeof(int));

   // printf("ffds%i\n",(*signal).duration);
    
    samples = malloc(size1 * sizeof(float));
    pcmpulses = malloc(size1*sizeof(int));
    sampler(samples,interval,*inputsignal);
    //viewf(samples,size1);
   // printf("hida %i\n",*(signal->duration));
    quantizer(samples,pcmpulses,poweri(2,encoderbits),(*inputsignal).A);
    //view(pcmpulses,size1);
    encoder(pcmpulses,dsignal,bits);
    view(dsignal,size1*bits);
    free(samples);
    free(pcmpulses);
    free(dsignal);

	
}

void view(int *samples,int size){
    for (int j = 0 ; j<size;j++){
        printf("%i",samples[j]);
    }
    printf("\n");
}
void viewf(float *samples,int size){
    for (int j = 0 ; j<size;j++){
        printf("%.3f, ",samples[j]);
    }
    printf("\n");
}

int poweri(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}