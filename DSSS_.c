
#include <stdio.h>
#include <string.h>
#define S 110

char *org_signl(char data[], char data1[]);
char *XNOR(char data1[], char result[]);
char *org_dataa(char org_result[], char org_data[]);

void main(){
    char data[10];
    char data1[S];
    char result[S];
    char org_result[S];
    char org_data[10];
    printf("Enter Data to be sent: ");
    scanf("%s",data);
    org_signl(data,data1);
    printf("%s\n",data1);
    XNOR(data1,result);
    printf("Result: %s\n",result);
    XNOR(result,org_result);
    printf("Org_result: %s\n",org_result);
    org_dataa(org_result,org_data);
    printf("Org_Data: %s\n",org_data);

}

char *org_signl(char data[], char data1[]){
    int k=0;
    for(int i=0; i<strlen(data); i++){
        if(data[i]=='1'){
            for(int j=0; j<11; j++){
                data1[k++] = '1';
            }
        }else{
            for(int j=0; j<11; j++){
                data1[k++] = '0';
            }
        }
    }
    data1[strlen(data)*11]='\0';
    return data1;
}

char *XNOR(char data1[], char result[]){
    char pattern[] = {'1','0','1','1','0','1','1','1','0','0','0'};
    int l = strlen(data1)/11;
    int k=0;
    while(l>0){
        for(int i=0; i<11; i++){
            if(data1[k]==pattern[i]){
                result[k++]='1';
            }else{
                result[k++]='0';
            }
        }
        l--;
    }
    result[strlen(result)]='\0';
    return result;
}

char *org_dataa(char org_result[], char org_data[]){
    int flag=-1, k=0, j=0;
    int l = strlen(org_result)/11;
    int m=l;
    while(l>0){
        for(int i=0; i<11; i++){
            if(org_result[k]=='1'){
                flag=1;
            }else if(org_result[k]=='0'){
                flag=0;
            }else{
                flag=-1;
            }
            k++;
        }
        // printf("%d\n",flag);
        if(flag==1){
            org_data[j++]='1';
        }else if(flag==0){
            org_data[j++]='0';
        }else{
            printf("Something Wrong\n");
        }
        l--;
    }
    org_data[m]='\0';
    return org_data;
}