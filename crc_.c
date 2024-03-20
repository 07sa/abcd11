

#include <stdio.h>
#include <string.h>
#define N 15

char dividend[N];

int queue[N];
int front,rear;

void enqueue(int x);
void display();
void dequeue();

char* XOR(char data[], char crc_key[]);
char* send(char data[], char crc_key[]);
char* error(char data[]);
void receive(char data[], char crc_key[]);

int main() {
    char data[N];
    char original_data[N];
    char crc_key[10];
    int choice;

    do{
        printf("Enter data: ");
        scanf("%s", data);
        printf("Enter CRC Key: ");
        scanf("%s", crc_key);
        getchar();

        for (int k = 0; k < strlen(data); k++) {
            original_data[k] = data[k];
        }
        original_data[strlen(data)]='\0';

        send(data,crc_key);
        printf("1.Enter [a] to pass data without error.\n2.Enter [b] to pass data with error.\n");
        char ch;
        scanf(" %c",&ch);

        switch(ch){
            case 'a': receive(data,crc_key);
                break;
            case 'b': error(data); receive(data,crc_key);
                break;
            default:printf("Wrong Input.");
        }
        printf("\nDo you want to continue:[yes(1)/no(0)]");
        scanf("%d",&choice);
    }while(choice);
    return 0;
}

char* XOR(char data[], char crc_key[]){
    // XOR division
    int crc_size = strlen(crc_key);
    char *ptr;
    ptr = &data[crc_size - 1];
    for (int b = 0; b < crc_size; b++) {
        dividend[b] = data[b];
    }
    dividend[crc_size] = '\0';

    while (1) {
        for (int l = 0; l < crc_size; l++) {
            if (dividend[l] == crc_key[l]) {
                enqueue(0);
            } else {
                enqueue(1);
            }
        }

        printf("Queue after XOR division: ");
        display();
        printf("\n");

        int count=0;
        int qidx=front;

        while(queue[qidx++]==0){
            count++;
            if(qidx==crc_size){
                break;
            }
        }

        if (count!=0) {

            for (int s = 0; s < crc_size - count; s++) {
                dividend[s] = (char)(queue[count+s] + '0');
            }
            for(int i=0;i<count;i++){
                dequeue();
                ptr++;
                dividend[crc_size + i- count] = *ptr;
            }

            dividend[crc_size] = '\0';

            printf("Dividend after shifting: %s\n", dividend);

            for (int p = 0; p < crc_size - count; p++) {
                dequeue();
            }
        } else {
            for (int t = 0; t < crc_size; t++) {
                dividend[t] = (char)(queue[t] + '0');
            }
            dividend[crc_size] = '\0';

            printf("Dividend without shifting: %s\n", dividend);

            for (int p = 0; p < crc_size; p++) {
                dequeue();
            }
        }

        if (*ptr == '\0') {
            break;
        }
        if(strlen(dividend)<crc_size){
            return dividend;
        }
    }
    return dividend;
}

char* send(char data[], char crc_key[]){

    front=rear=-1;

    // Appending 0's to data
    int crc_size = strlen(crc_key);
    int data_size = strlen(data);

    for (int i = 0; i < crc_size - 1; i++) {
        data[data_size + i] = '0';
    }
    data[data_size+crc_size-1] = '\0';
    printf("Data after appending 0's: %s\n", data);
    XOR(data,crc_key);
    printf("%s\n",data);
    printf("Dividend: %s",dividend);
    int dividend_l = strlen(dividend);
    for(int x=strlen(data)-1; x>strlen(data)-crc_size;x--){
        if(dividend_l<=0){
            data[x] = '0';

        }else{
            data[x] = dividend[dividend_l-1];
            dividend_l--;
        }
    }
    printf("\nFinal data:");
    for(int d=0; d<strlen(data); d++){
        printf("%c",data[d]);
    }
    printf("\n");

    return data;
}

char* error(char data[]){
    printf("Enter position for switching a bit:");
    int pos;
    scanf("%d",&pos);
    if(data[pos-1]=='0'){
        data[pos-1]='1';
    }else{
        data[pos-1]='0';
    }
    return data;
}

void receive(char data[], char crc_key[]){
    XOR(data,crc_key);
    printf("%s\n",dividend);
    // if(strlen(dividend)==0){
    //     printf("Accepted.");
    // }
    int flag=1; //data accept.
    for (int i = 0; i < strlen(dividend); i++)
    {
        if(dividend[i]=='1'){
            flag=0;//data rejected.
        }
    }
    if (flag==1 || strlen(dividend)==0){

        printf("DATA Accepted");
    }
    else
    {
        printf("DATA Rejected.");
    }
}

void enqueue(int x) {
    if (rear == N - 1) {
        printf("Overflow\n");
    } else if (front == -1 && rear == -1) {
        front = rear = 0;
        queue[rear] = x;
    } else {
        rear++;
        queue[rear] = x;
    }
}

void display() {
    if (front == -1 && rear == -1) {
        printf("Empty Queue.");
    } else {
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
    }
}

void dequeue() {
    if (front == -1 && rear == -1) {
        printf("Empty Queue.");
    } else if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }
}