#include <stdio.h>
#include <math.h>

// Function to calculate the maximum number of packets to be transmitted
int calculateMaxPackets(float Tp, float Tt) {
    float a = Tp / Tt;
    return (int)(1 + 2 * a);
}

// Function to calculate the number of bits in the sequence number
int calculateNumBits(int maxPackets) {
    return (int)ceil(log2(maxPackets));
}

// Function to calculate the sender's window size
int calculateSenderWindow(int numBits) {
    return pow(2, numBits);
}

// Function to calculate the maximum throughput
double calculateMaxThroughput(int senderWindow, int maxPackets) {
    return ((double)senderWindow / maxPackets) * 100;
}

// Function to simulate packet transmission and acknowledgment
void simulateTransmission(int maxPackets, int senderWindow, int roundTripTime) {
    int transmitted = 0, outstanding = 0, acknowledged = 0;
    int time = 0;

    outstanding = maxPackets - senderWindow;

    // Simulate transmission until the sender window is filled
    while (transmitted < senderWindow) {
        printf("At Time %d: ", time);
        printf("Transmitted: %d  ", transmitted);
        printf("Outstanding: %d  ", outstanding);
        printf("Acknowledged: %d  \n", acknowledged);

        if (time == senderWindow) {
            time = roundTripTime;
            break;
        }

        transmitted++;
        time++;
    }

    int out = outstanding;
    int ti = time;

    // Simulate the remaining transmissions until all packets are acknowledged
    while (transmitted < maxPackets) {
        time++;
        transmitted++;
        acknowledged++;
        outstanding--;

        printf("At Time %d: ", time);
        printf("Transmitted: %d  ", transmitted);
        printf("Outstanding: %d  ", outstanding);
        printf("Acknowledged: %d  \n", acknowledged);

        if (time == ti + out) {
            break;
        }
    }

    // Simulate acknowledgments for remaining outstanding packets
    while (outstanding > 0) {
        time++;
        acknowledged++;
        printf("At Time %d: ", time);
        printf("Transmitted: %d  ", transmitted);
        printf("Outstanding: %d  ", outstanding);
        printf("Acknowledged: %d  \n", acknowledged);
        outstanding--;
    }

    // Simulate final acknowledgments after the last packet is sent
    while (acknowledged < maxPackets) {
        time++;
        acknowledged++;
        printf("At Time %d: ", time);
        printf("Transmitted: %d  ", transmitted);
        printf("Outstanding: %d  ", outstanding);
        printf("Acknowledged: %d  \n", acknowledged);
    }
}

int main() {
    float Tt, Tp; // Transmission time and Propagation Protocol

    // Input Tp and Tt from user
    printf("Enter Transmission time (Tt): ");
    scanf("%f", &Tt);

    printf("Enter Propagation time (Tp): ");
    scanf("%f", &Tp);

    int maxPackets = calculateMaxPackets(Tp, Tt);
    printf("Maximum number of packets to be transmitted: %d\n", maxPackets);

    int numBits = calculateNumBits(maxPackets);
    printf("Number of bits in sequence number: %d\n", numBits);

    int senderWindow = calculateSenderWindow(numBits);
    printf("Sender's Window size: %d\n", senderWindow);

    double maxThroughput = calculateMaxThroughput(senderWindow, maxPackets);
    printf("Maximum Throughput: %.2f%%\n", maxThroughput);

    int roundTripTime = (int)(Tt + Tp + Tp);

    simulateTransmission(maxPackets, senderWindow, roundTripTime);

    return 0;
}
