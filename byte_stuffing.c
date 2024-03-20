// flag bytes with byte stuffing Framing Method
#include <stdio.h>
#include <string.h>
#define S 100

char flag[]={'0','1','1','1','1','1','1','0'};
char esc[]={'0','0','0','1','1','0','1','1'};

void reciever(char data[]){
    char res[S];
    int count=0, count1=0, j=0, k=0, l=0, p=0;
    while(1){
        int isFlag=0, isEsc=0;
        for(int i=0; i<8; i++){
            if(data[j+i]==flag[i]){
                isFlag=1;
            }else{
                isFlag=0;
                break;
            }
        }
        for(int m=0; m<8; m++){
            if(data[j+m]==esc[m]){
                isEsc=1;
            }else{
                isEsc=0;
                break;
            }
        }
        if(isFlag==1 && count1==0){
            count++;
            l++;
        }else if(isEsc==1 && count1==0){
      
      count1++;
            l++;
        }else{
            for(int i=0; i<8; i++){
                res[p++]=data[j+i];
            }
            count1=0;
        }
        j+=8;
        if(count==2){
            break;
        }
    }
    res[strlen(data)-l*8]='\0';
    printf("Original Data is %s",res);
}

int main(){
    char data[S];
    char data1[S];
    char data2[S];

    printf("Enter Data:");
    scanf("%s",data);
    data[strlen(data)] = '\0';

    //covert bits to bytes by appending leading zero's
    int c_bytes;
    if(strlen(data)%8 == 0){
        c_bytes = strlen(data)/8;
        for(int i=0; i<c_bytes*8; i++){
            data1[i]=data[i];
        }
        data1[c_bytes*8]='\0';
    }else{
        c_bytes = (strlen(data)/8)+1;
        for(int i=0; i<(c_bytes*8)-strlen(data); i++){
           
 data1[i] = '0';
        }
        int j=0;
        for(int i=(c_bytes*8)-strlen(data); i<c_bytes*8; i++){
            data1[i] = data[j++]; 
        }
        data1[c_bytes*8]='\0';
    }
    printf("Data is of %d bytes.\n",c_bytes);
    printf("Data Converted in Bytes format: %s\n",data1);

    //append esc if data bits are equal to flag or esc key
    int j=0, k=0, count1=0; 
    int count = c_bytes;
    while(1){
        int isFlag=1, isEsc=1;
        for(int i=0; i<8; i++){
            if(data1[j+i]!=flag[i]){
                isFlag=0;
                break;
            }
        }
        
        for(int m=0; m<8; m++){
            if(data1[j+m]!=esc[m]){
                isEsc=0;
                break;
            }
        }
        if(isFlag==1 || isEsc==1){
            count1++;
            for(int i=0; i<8; i++){
                data2[k++] = esc[i];
            }
        }
        for(int l=0; l<8; l++){
            data2[k++]=data1[j++];
    
    }
        count--;
        if(count==0){
            break;
        }
        }
        data2[strlen(data1)+count1*8]='\0';
        printf("Data after inserting Esc key if data having flag or Esc byte: %s\n",data2);

        //create final data by appending flag at both ends
        for(int i=0; i<8; i++){
            data1[i] = flag[i];
        }
        for(int i=0; i<strlen(data2); i++){
            data1[8+i] = data2[i];
        }
         for(int i=0; i<8; i++){
            data1[8+strlen(data2)+i] = flag[i];
        }
        data1[16+strlen(data2)]='\0';
        printf("Final data to be sent: %s\n",data1);

        reciever(data1);
        return 0;
    }
