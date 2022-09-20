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
        Acesso_ao_Banco = PTHREAD_MUTEX_INITIALIZER;
        mutex_leitura = PTHREAD_MUTEX_INITIALIZER;
        mutex_escrita = PTHREAD_MUTEX_INITIALIZER;
        terminando_escrita = PTHREAD_COND_INITIALIZER;
        terminando_leitura = PTHREAD_COND_INITIALIZER;
        interrupcao_escrita=0;
        threads_lendo=0;
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
    void INT_escrita(void){
        pthread_mutex_lock(&mutex_escrita);
        //indica que há uma thread com intenção de realizar escrita
            interrupcao_escrita++;
            printf("escritora quer escrever\n");
        pthread_mutex_unlock(&mutex_escrita);
    }
    void esperar_leitoras_correntes(void){
        pthread_mutex_lock(&mutex_leitura);
            while(threads_lendo){//espera as threads que já estão lendo terminarem o processo
                printf("escritora esperando threads lendo(%d)\n",threads_lendo);
                pthread_cond_wait(&terminando_leitura,&mutex_leitura);
            }
        pthread_mutex_unlock(&mutex_leitura);
    }
    void escreva(int p){
        pthread_mutex_lock(&Acesso_ao_Banco);
            SGBD[p]= numero();
            printf("escrevendo SGBD[%d] <= %d\n",p,SGBD[p]);
        pthread_mutex_unlock(&Acesso_ao_Banco);
    }
    void END_escrita(void){
        pthread_mutex_lock(&mutex_escrita);
            interrupcao_escrita--;//indica que há uma thread com intenção de realizar escrita
            pthread_cond_broadcast(&terminando_escrita);
        pthread_mutex_unlock(&mutex_escrita);
    }
    void esperar_escritas_correntes(void){
        pthread_mutex_lock(&mutex_escrita);
            //Impede que novas threads leitoras realizem a leitura enquanto 
            //uma thread escritora demonstrou intenção de leitura
            while(interrupcao_escrita){
                printf("leitora esperando\n");
                pthread_cond_wait(&terminando_escrita,&mutex_escrita);
            }
        pthread_mutex_unlock(&mutex_escrita);
    }
    void END_leitura(void){
        pthread_mutex_lock(&mutex_leitura);
            threads_lendo--;
            if(threads_lendo==0)pthread_cond_broadcast(&terminando_leitura);
            printf("saindo da leitura\n");
        pthread_mutex_unlock(&mutex_leitura);
    }
    void leia(int p){
        printf("lendo Banco[%d] => %d\n",p,SGBD[p]);
    }
    void INIT_leitura(void){
        pthread_mutex_lock(&mutex_leitura);
            threads_lendo++;
        pthread_mutex_unlock(&mutex_leitura);
    }
    void escrever(void){
        while(true){
            INT_escrita();                  // interrupção_de_escrita++
            esperar_leitoras_correntes();   //se threads_lendo > 0 esperar aqui
                escreva(pos());             //escrita
            END_escrita();                  //interrupção_de_escrita--

            print_banco();
            sleep(1);
        }
    }
    void ler(void){
        while(true){
            esperar_escritas_correntes();   //se interrupção_de_leitura > 0 espera aqui
            INIT_leitura();                 //threads_lendo++
                leia(pos());                //realiza leitura
            END_leitura();                  //threads_lendo--

            print_banco();
            sleep(1);
        }
    }
    private:
    pthread_mutex_t Acesso_ao_Banco;
    pthread_mutex_t mutex_leitura;
    pthread_mutex_t mutex_escrita;
    pthread_cond_t terminando_escrita;
    pthread_cond_t terminando_leitura;
    int threads_lendo;
    int interrupcao_escrita;
    int *SGBD;
    int tam;
};
void* le(void* mem){
    Memoria *M = (Memoria*)mem;
    M->ler();//realiza a função ler
    pthread_exit(NULL);
}
void* escreve(void* mem){
    Memoria *M = (Memoria*)mem;
    M->escrever();//realiza a função escrever
    pthread_exit(NULL);
}
int main(){
    int N,M,i;
    Memoria Mem(1);//passa como parâmetro o tamanho do banco de dados
    scanf("%d %d",&N,&M);//N(numero de leitoras) e M(numeros de escritoras)
    pthread_t leitoras[N],escritoras[M];
//passa o mesmo objeto "&Mem" para as threads para que elas possam ter acesso ao mesmo ambiente
    for(i=0;i<N;i++) if(pthread_create(&(leitoras[i]),NULL,le,(void*)&Mem))perror("Failed to create thread");
    for(i=0;i<M;i++) if(pthread_create(&(escritoras[i]),NULL,escreve,(void*)&Mem))perror("Failed to create thread");
    for(i=0;i<N;i++) pthread_join(leitoras[i],NULL);
    for(i=0;i<M;i++) pthread_join(escritoras[i],NULL);
}