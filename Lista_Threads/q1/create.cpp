#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *f;
    char buff[50];
    for(int i=0;i<10;i++){
        sprintf(buff,"%d.in",i);
        f=fopen(buff,"w");
        if(f!=NULL){
            for(int j=0;j<6;j++){
                sprintf(buff,"%d\n",j);
                fwrite(buff,1,2,f);
            }
            fclose(f);
        }
    }
    
}