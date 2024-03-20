#include <stdio.h>
#include <stdlib.h>

int numofPacket;
float tp;
float tt;
float time = 0;
int i, j, k;

void sender();
void receiver();

void sender(){
    printf("\nEnter number of packets :");
    scanf("%d", &numofPacket);
    
    int packet[numofPacket];

    printf("\nEnter packets : ");
    for(i = 0; i < numofPacket; i++){
        scanf("\n%d", &packet[i]);
    }

    printf("\nEnter transmission time in ms : ");
    scanf("%f", &tt);

    printf("\nEnter propagation time in ms : ");
    scanf("%f", &tp);

    printf("\nTheoretically time taken to transmit %d number of packets should be %f", numofPacket, numofPacket*2*(tt+tp));
    printf("\n");
    
    for(i = 0; i < numofPacket; i++){
        time += tt;
        printf("\nTime taken to transmit '%d' at %f is ", packet[i], time);
        receiver();
    }
    printf("\n");
    printf("\nTotal time taken is %f", time);
    printf("\n");
}

void receiver(){
    time += tp;
    printf("\nPacket received at %f", time);
    time += tt;
    printf("\nAcknowledgement sent at %f", time);
    time += tp;
    printf("\n");
}

int main(){
    sender();
    return 0;
}