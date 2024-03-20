#include <stdio.h>
#include <string.h>
#define S 20

int data2[S];

void sender(){
    int data1[S];
    int data;
    int data_len=0, i=0;
    int last_digit;
    printf("Enter Data:");
    scanf("%d",&data);

    while(data!=0){
        last_digit=data%10;
        data=data/10;
        data1[i++]=last_digit;
        data_len++;
    }
    data2[0]=data_len+1;
    int k=1;
    for(int i=data_len-1; i>=0; i--){
        data2[k++]=data1[i];
    }
   
 printf("Enter sender's data:");
    for(int i=0; i<data_len+1; i++){
        printf("%d",data2[i]);
    }
    printf("\n");
}

void receiver(int data[]){
    char rev_data[S];
    int data_sz = data[0];
    int j=0;
    for (int i = 1; i < data_sz; i++)
    {
        rev_data[j++]=data[i];
    }
    printf("Original received data: ");
    for(int i=0; i<data_sz-1; i++){
        printf("%d",rev_data[i]);
    }
    printf("\n");
}
int main(){
    sender();
    receiver(data2);
}