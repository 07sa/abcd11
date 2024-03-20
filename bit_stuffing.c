#include <stdio.h>
#include <string.h>

#define MAX_DATA_LENGTH 50
#define FLAG_LENGTH 8

char flag[FLAG_LENGTH] = {'0', '1', '1', '1', '1', '1', '1', '0'};

void receiver(char data[]) {
    char res[MAX_DATA_LENGTH];
    int j, k = 0;
    int count = 0;
    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == '0') {
            count = 0;
            for (j = i + 1; j < i + 7; j++) {
                if (data[j] == '1') {
                    count++;
                    if (count == 5) {
                        i = j;  // Skip the next five 1's
                    }
                } else {
                    break;
                }
            }
        }
        res[k++] = data[i];
    }
    res[k] = '\0';
    printf("Data after Flag bytes dropped by receiver: %s\n", res);
}

int main() {
    char data[MAX_DATA_LENGTH];
    char stuffed_data[MAX_DATA_LENGTH * 2]; // Max possible length after stuffing
    printf("Enter the data: ");
    scanf("%s", data);

    // Stuffing zeros after five consecutive ones
    int k = 0;
    int ones_count = 0;
    for (int i = 0; i < strlen(data); i++) {
        stuffed_data[k++] = data[i];
        if (data[i] == '1') {
            ones_count++;
            if (ones_count == 5) {
                stuffed_data[k++] = '0';
                ones_count = 0; // Reset count after stuffing zero
            }
        } else {
            ones_count = 0; // Reset count if not a one
        }
    }
    stuffed_data[k] = '\0';
    printf("Data after stuffing 0's: %s \n", stuffed_data);

    // Flagging
    char final_data[MAX_DATA_LENGTH + FLAG_LENGTH * 2];
    strcpy(final_data, flag); // Add start flag
    strcat(final_data, stuffed_data);
    strcat(final_data, flag); // Add end flag

    printf("Final Data to be sent: %s\n", final_data);

    // Receiver function to remove flag bytes
    receiver(final_data);

    return 0;
}
