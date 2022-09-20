#include<iostream>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0
using namespace std;
class Contagem{
    public:
    Contagem(int qtd_arq,int qtd_cand){
        qtd_candidados = qtd_cand;
        qtd_arquivos = qtd_arq;
        mutex_array = (pthread_mutex_t*)malloc((qtd_cand+1)*sizeof(pthread_mutex_t));
        mutex_arquivo = (pthread_mutex_t*)malloc((qtd_arq)*sizeof(pthread_mutex_t));
        votos = (int*)malloc((qtd_cand+1)*sizeof(int));
        lido = (bool*)calloc((qtd_arq),sizeof(bool));
        for(int i=0;i<qtd_cand+1;i++)mutex_array[i] = PTHREAD_MUTEX_INITIALIZER;
        for(int i=0;i<qtd_arq;i++)mutex_arquivo[i] = PTHREAD_MUTEX_INITIALIZER;
    }
    ~Contagem(){
        int i;
        for(i=0;i<qtd_candidados+1;i++)pthread_mutex_destroy(&(mutex_array[i])); 
        for(i=0;i<qtd_arquivos;i++)pthread_mutex_destroy(&(mutex_arquivo[i])); 
        free(mutex_array);
        free(mutex_arquivo);
        free(votos);
    }
    void contar(void){
        for(int i=0;i<qtd_arquivos;i++){
            //mutex para acessar a variável lido[i]
            if(!pthread_mutex_trylock(&(mutex_arquivo[i]))){
                //se o arquivo não foi lido
                if(!lido[i]){
                    //ler o arquivo
                    ler_arquivo(i);
                    //mudar variavel lido para true. Isso impede que outro contador
                    //acesse o arquico novamente depois de lido e o mutex ter sido destravado 
                    //pelo contador que leu
                    lido[i]=TRUE;
                }
                //saindo da zona de conflito
                pthread_mutex_unlock(&(mutex_arquivo[i]));
            }
        }
    }
    void ler_arquivo(int a){
        char string[10];
        char buff[50];
        int num;
        int n,i;
        sprintf(string,"%d.in",a);
        FILE *arq=fopen(string,"r");
        if(arq!=NULL){
            rewind(arq);
            while(!feof(arq)){
                i=-1;
                //leitura do numero em determinada linha
                do{
                    i++;
                    fread(&(buff[i]),1,1,arq);
                }while(buff[i]!='\n' && !feof(arq));
                //converter char em int
                if(!feof(arq)){
                    num=0;
                    for(int j=0;j<i;j++){//-48
                        n=buff[j]-48;
                        n*=pow((float)10,(float)(i-j-1));
                        num+=n;
                    }
                    //acesso ao array de votos atômico
                    pthread_mutex_lock(&(mutex_array[num]));
                        votos[num]++;
                    pthread_mutex_unlock(&(mutex_array[num]));
                }
            }
        }
        //print_array_votos();
        //sleep(1);
        fclose(arq);
    }
    void print_array_votos(void){
        printf("[NULOS] %d\n",votos[0]);
        for(int i=1;i<qtd_candidados+1;i++){
            printf("[candidato %d] %d\n",i,votos[i]);
        }
    }
    private:
    int *votos;
    bool *lido;
    int qtd_candidados;
    int qtd_arquivos;
    pthread_mutex_t *mutex_arquivo; 
    pthread_mutex_t *mutex_array;
};

void* routine(void *mesa){
    Contagem *m = (Contagem*)mesa;
    m->contar();
    pthread_exit(NULL);
}
int main(){
    int N/*arquivos*/,T/*threads*/, C/*candidatos*/;
    cin >> N >> T >> C;
    pthread_t contador[T];
    Contagem mesa(N,C);
    for(int i=0;i<T;i++)pthread_create(&(contador[i]),NULL,routine,&mesa);
    for(int i=0;i<T;i++)pthread_join(contador[i],NULL);
    mesa.print_array_votos();
    return 0;
}