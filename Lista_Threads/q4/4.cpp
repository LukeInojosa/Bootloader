//animcao do algoritmo para varias threads: https://www.youtube.com/watch?v=6ODPqo1dVrs

#include <iostream>
#include <vector>
#include <list>
#include <pthread.h>

#define INFINITY 1000

using namespace std;

//Disjoint sets (union find)
class Floresta{
    public:
        int n_arvores;
        vector<int> pai;
        vector<int> rank;
        vector<list<int>> arvore;

        Floresta floresta(int n_nodes){
            Floresta f;
            f.n_arvores = n_nodes;
            f.pai.resize(n_nodes);
            f.rank.resize(n_nodes);
            f.arvore.resize(n_nodes);
            for(int i =0; i < n_nodes; i++){
                f.pai[i] = i;
                f.rank[i]= 0;
                f.arvore[i].push_back(i);
            }
            return f;
        }

        int Find(int node){
            if (pai[node] == node){
                
                return pai[node];
            }
            
            int raiz = Find(pai[node]);
            pai[node] = raiz;
            return raiz;
        }

        void Union(int node1, int node2){
            int raiz1 = Find(node1);
            int raiz2 = Find(node2);
            
            if (rank[raiz1] > rank[raiz2])
                swap(raiz1,raiz2);
            
            if (rank[raiz1] == rank[raiz2])
                rank[raiz2]++;

            arvore[raiz2].splice(arvore[raiz2].end(), arvore[raiz1]);
        
            pai[raiz1] = pai[raiz2];
            this->n_arvores -= 1;
        }     
};

struct aresta{
    int node1;
    int node2;
    int peso;
    aresta(int p){
        peso = p;
    }
    aresta(int n1, int n2, int p){
        node1 = n1;
        node2 = n2;
        peso = p;
    }
};

typedef struct {  
    int node;
    Floresta f;
    vector<vector<pair<int,int>>> grafo;
} Params;

//Variáveis globais
pthread_mutex_t mutex;
vector<aresta> best_edges;

aresta find_best_edge(vector<vector<pair<int,int>>>grafo, Floresta &f, list<int>&arvore){
    struct aresta best_edge(INFINITY);
    
    // para cada node na arvore
    for(auto node : arvore){
    //olha todas arestas ligadas a este node
        for (auto a : grafo[node]){
            int vizinho           = a.first;
            int peso_node_vizinho = a.second;
            
            //apenas arestas que ligam a arvore a outra
            if (f.Find(vizinho) == f.Find(node)) continue;

            if(best_edge.peso > peso_node_vizinho){
                best_edge = aresta(node,vizinho,peso_node_vizinho);
            };
            
        }
    }
    return best_edge;
}

void *thread_function(void * params) {
    Params p = *(Params*) params;
    if(p.f.pai[p.node] == p.node){
        int raiz = p.node;
        aresta best_edge = find_best_edge(p.grafo, p.f, p.f.arvore[raiz]);
        pthread_mutex_lock(&mutex);
        best_edges.push_back(best_edge);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

Params create_params(int node, Floresta f, vector<vector<pair<int,int>>> grafo) {
    Params p;
    p.node = node;
    p.f = f;
    p.grafo = grafo;
    return p;
}

vector<aresta> find_best_edges(vector<vector<pair<int,int>>>grafo, Floresta &f, vector<aresta> &mst){
    int n_nodes = grafo.size();
    pthread_t thread[n_nodes];
    Params params[n_nodes];
    vector<aresta> teste;

    best_edges.clear(); //Reiniciando o array antes de utiliza-lo novamente

    for (int node = 0; node < n_nodes; node++){

        params[node] = create_params(node, f, grafo);
        pthread_create(&thread[node], NULL, thread_function, &params[node]); //Criando uma thread para cada nó.

    }
    for (int i=0; i<n_nodes; i++) {
        pthread_join(thread[i], NULL);
    }
    return best_edges;
}

vector <aresta> boruvka(vector<vector<pair<int,int>>>grafo){
    vector <aresta> mst;
     
    int n_nodes = grafo.size();

    Floresta f;
    f = f.floresta(n_nodes);

    while (f.n_arvores >  1){
        best_edges = find_best_edges(grafo,f,mst); //Vai procurar as melhores arestas de forma paralela!
        for(auto best_edge : best_edges){
            
            int n1 = best_edge.node1;
            int n2 = best_edge.node2;
            
            if(f.Find(n1) != f.Find(n2)){
                mst.push_back(best_edge);
                f.Union(n1,n2);
            }
        }
    }
    return mst;
}

int main() {
        /* Let us create the following graph
       2   3
   (0)--(1)--(2) 
    |      /  |       
   6|   8/    |7       
    |  /      |       
   (3)-------(4)
        9     */
    int V = 5;

    vector<vector<pair<int,int>>> graph = {
        {make_pair(1,2), make_pair(3,6)},                   //0
        {make_pair(0,2), make_pair(2,3)},                   //1
        {make_pair(1,3), make_pair(3,8), make_pair(4,7)},   //2
        {make_pair(0,6), make_pair(2,8), make_pair(4,9)},   //3
        {make_pair(3,9), make_pair(2,7)}                    //4
    };

    vector<aresta> mst = boruvka(graph);
    for (auto a: mst){
        cout<< a.node1<<" - "<<a.node2<< " " << a.peso<< endl;
        
    }
    return 0;
}