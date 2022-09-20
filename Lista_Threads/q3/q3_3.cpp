#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
class Memoria{
    public:
    Memoria(int n){
        tam = n;
        SGBD = (int*)malloc(n*sizeof(int));
        interrupcao_escrita = (int*)calloc(n,sizeof(int));
        Acesso_ao_Banco = (pthread_mutex_t*)malloc(n*sizeof(pthread_mutex_t));
        mutex_leitura = (pthread_mutex_t*)malloc(n*sizeof(pthread_mutex_t));
        mutex_escrita = (pthread_mutex_t*)malloc(n*sizeof(pthread_mutex_t));
        terminando_escrita = (pthread_cond_t*)malloc(n*sizeof(pthread_cond_t));
        terminando_leitura = (pthread_cond_t*)malloc(n*sizeof(pthread_cond_t));
        for(int i=0;i<n;i++){
            terminando_escrita[i] = PTHREAD_COND_INITIALIZER;
            terminando_leitura[i] = PTHREAD_COND_INITIALIZER;
            Acesso_ao_Banco[i] = PTHREAD_MUTEX_INITIALIZER;
            mutex_leitura[i] = PTHREAD_MUTEX_INITIALIZER;
            mutex_escrita[i] = PTHREAD_MUTEX_INITIALIZER;
        }
        threads_lendo = (int*)calloc(n,sizeof(int));
    }
    ~Memoria(){
        free(SGBD);
    }
    int pos(void){
        return abs(rand()%tam);
    }
    int numero(void){
        return rand()%101;
    }
    void print_banco(void){
        for(int i=0;i<tam;i++)printf("%d ",SGBD[i]);
        printf("\n");
    }
    void* escrever(void){
        int p;
        while(true){
            p=pos();
            pthread_mutex_lock(&mutex_escrita[p]);
                interrupcao_escrita[p]++; //indica que há uma thread com intenção de realizar escrita na posição 'p'
            pthread_mutex_unlock(&mutex_escrita[p]);

            pthread_mutex_lock(&mutex_leitura[p]);
                while(threads_lendo[p]){//espera as threads que já estão lendo em 'p' terminarem a leitura
                    printf("escritora esperando threads lendo(%d)\n",threads_lendo[p]);
                    pthread_cond_wait(&terminando_leitura[p],&mutex_leitura[p]);
                }
            pthread_mutex_unlock(&mutex_leitura[p]);
            
            pthread_mutex_lock(&Acesso_ao_Banco[p]);//se duas treds escritoras chegarem aqui, cada uma terá acesso exclusivo ao banco
                SGBD[p]= numero();
                printf("escrevendo SGBD[%d] <= %d\n",p,SGBD[p]);
                print_banco();
                sleep(1);
            pthread_mutex_unlock(&Acesso_ao_Banco[p]);

            pthread_mutex_lock(&mutex_escrita[p]);
                interrupcao_escrita[p]--;
                pthread_cond_broadcast(&terminando_escrita[p]);//Avisa às treads leitoras que mais uma escrita está sendo terminada na posição 'p'
            pthread_mutex_unlock(&mutex_escrita[p]);
        }
    }
    int ler(void){
        int p;
        while(true){
            p=pos();
            pthread_mutex_lock(&mutex_escrita[p]);
                while(interrupcao_escrita[p]){//Impede que novas threads leitoras realizem a leitura enquanto uma thread escritora demonstrou intenção de escrita em 'p'
                    printf("leitora esperando\n");
                    pthread_cond_wait(&terminando_escrita[p],&mutex_escrita[p]);
                }
            pthread_mutex_unlock(&mutex_escrita[p]);
            
            pthread_mutex_lock(&mutex_leitura[p]);
                threads_lendo[p]++;
            pthread_mutex_unlock(&mutex_leitura[p]);

                printf("lendo Banco[%d] => %d\n",p,SGBD[p]);
                print_banco();
                sleep(1);

            pthread_mutex_lock(&mutex_leitura[p]);
                threads_lendo[p]--;
                printf("saindo da leitura\n");
                pthread_cond_broadcast(&terminando_leitura[p]);//Avisa às treds escritoras que mais uma leitura está sendo terminada 'p'
            pthread_mutex_unlock(&mutex_leitura[p]);
            
        }
    }
    private:
    pthread_mutex_t *Acesso_ao_Banco;
    pthread_mutex_t *mutex_leitura;
    pthread_mutex_t *mutex_escrita;
    pthread_cond_t *terminando_escrita;
    pthread_cond_t *terminando_leitura;
    int *threads_lendo;
    int *SGBD;
    int *interrupcao_escrita;
    int tam;
};
void* le(void* mem){
    Memoria *M =(Memoria*)mem;
    M->ler();
}
void* escreve(void* mem){
    Memoria *M =(Memoria*)mem;
    M->escrever();
}
int main(){
    int N,M,i;
    Memoria Mem(1);
    scanf("%d %d",&N,&M);
    pthread_t leitoras[N],escritoras[M];
    for(i=0;i<N;i++) pthread_create(&(leitoras[i]),NULL,le,(void*)&Mem);
    for(i=0;i<M;i++) pthread_create(&(escritoras[i]),NULL,escreve,(void*)&Mem);
    for(i=0;i<N;i++) pthread_join(leitoras[i],NULL);
    for(i=0;i<M;i++) pthread_join(escritoras[i],NULL);
}