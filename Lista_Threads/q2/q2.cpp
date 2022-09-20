#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define TRUE 1
int Interceccoes[5];
int T_na_Intercec[10];
pthread_mutex_t mutex[5];
pthread_cond_t cond[5];
void *percursso(void * n){
    //um trem passa por todas as intercecções
    int *trem_id = (int*)n;
    int i;
    while(TRUE){
        for(i=0;i<5;i++){
            //bloqueia o mutex para ter acesso à intercecção
            pthread_mutex_lock(&mutex[i]);
                //se dois trens já estão na intercecção, eles ficam presos nessa espera
                // esperando algum trem indicar que saiu da interceção através de um cond_signal
                while(Interceccoes[i]>=2){
                    printf("trem[%d] ESPERANDO na intercecção[%d]...\n",*trem_id,i);
                    pthread_cond_wait(&(cond[i]),&(mutex[i]));
                }
                //Indica que está na intercecção i , incrementando 
                Interceccoes[i]++;
                if(Interceccoes[i]==1)T_na_Intercec[i*2]=*trem_id;
                else if(Interceccoes[i]==2)T_na_Intercec[i*2+1]=*trem_id;
                //mutex é liberado
            pthread_mutex_unlock(&mutex[i]);
            //trem passa 0,5 segundo na intercecção 
            //printf("trem[%d] PASSANDO na intercecção[%d]...\n",*trem_id,i);
            sleep(1);
            //bloqueia o mutex para ter acesso à intercecção
            pthread_mutex_lock(&mutex[i]);
                //trem sai da intercecção depois de passar 0,5 segundo
                Interceccoes[i]--;
                if(*trem_id ==T_na_Intercec[i*2])T_na_Intercec[i*2]=-1;
                else if(*trem_id ==T_na_Intercec[i*2+1])T_na_Intercec[i*2+1]=-1;
                //trem avisa que saiu da intercecção à outros trens que estão esperando para entrar
                pthread_cond_signal(&(cond[i]));
                //printf("trem[%d] SAINDO da intercecção[%d]...\n",*trem_id,i);
                //mutex é liberado 
            pthread_mutex_unlock(&mutex[i]);
        }
    }
    pthread_exit(NULL);
}
int main(){
    int i;
    pthread_t trem[10];
    int trem_id[10];
    for(i=0;i<10;i++){trem_id[i]=i;T_na_Intercec[i]=-1;}
    for(i=0;i<5;i++){
        mutex[i] = PTHREAD_MUTEX_INITIALIZER;
        cond[i] = PTHREAD_COND_INITIALIZER;
    }
    for(i=0;i<10;i++)pthread_create(&(trem[i]),NULL,percursso,&(trem_id[i]));
    while(TRUE){
        //system("clear");
        for(i=0;i<5;i++){
            printf("Na Intercecção %d: %d %d \n",i,T_na_Intercec[i*2],T_na_Intercec[i*2+1]);
        }
        sleep(1); 
        printf("\n");
    }
    for(i=0;i<10;i++)pthread_join(trem[i],NULL);
    for(i=0;i<5;i++){
        pthread_mutex_destroy(&(mutex[i]));
        pthread_cond_destroy(&(cond[i]));
    }
    return 0;
}