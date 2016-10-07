#include <iostream>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <queue>
#include <set>

/*Constantes utilizadas*/
#define esquerda 0
#define direita 1
#define cima 2
#define baixo 3
#define nenhuma 4

using namespace std;


/*Classe que encapsula a configuração das peças no tabuleiro*/
/*****************************************************************************/
class State{
    int peca[3][3];
    int vazio;
    public:
    State( vector <int> v);
    State( State * s);
    void show();
    int get_peca(int i,int j) { return this->peca[i][j]; }
    bool igual(State*s);
    void swap_vazio(int a,int b,int c,int d);
    State* move(int dir);
    
    
    
};
/*****************************************************************************/
/*construtor que recebe como parametro uma lista de numeros*/
State::State( vector <int> v ){
    int l,c,i;
    for(i=0; i<9 ; i++ ){
        l = i/3;
        c = i%3;
        this->peca[l][c] = v[i];
        if(v[i]==9) this->vazio=i;
    }
}

State::State( State * s){
    int i,j;
    for(i=0;i<3;i++)
     for(j=0;j<3;j++)
       this->peca[i][j] = s->get_peca(i,j); 
}

/*método que mostra a configuração das peças no tabuleiro*/
void State::show(){
    int i,j;
    for(i=0;i<3;i++){
     for(j=0;j<3;j++){
       if( peca[i][j]!=9)
       cout << this->peca[i][j];
       else 
       cout << " ";
     }
     cout<<endl;
    }
}

/*
método que retorna true, se um estado é igual ao estado passado por
parâmetro.
*/
bool State::igual(State* s){
    int i,j;
    for(i=0;i<3;i++)
     for(j=0;j<3;j++)
       if( this->peca[i][j] != s->get_peca(i,j) ) 
         return false;
    return true;  
}

/*
método que troca o vazio da posicao (a,b) para a posição (c,d) e atualiza a 
variável vazio
*/
void State::swap_vazio(int a,int b,int c,int d){
    char temp;
    temp = this->peca[a][b];
    this->peca[a][b] = this->peca[c][d];
    this->peca[c][d] = temp; 
    this->vazio = 3*c + d;
}

/*método que retorna um estado de acordo com o movimento realizado.*/
State* State::move(int dir){
  
  int i,j;
  i = this->vazio/3;
  j = this->vazio%3;
  
  State* s = new State( this );
  
  switch(dir){
  case esquerda:
    if(j!=0) s->swap_vazio(i,j,i,j-1); break;
  case direita:
    if(j!=2) s->swap_vazio(i,j,i,j+1); break;
  case cima:
    if(i!=0) s->swap_vazio(i,j,i-1,j); break;
  case baixo:
    if(i!=2) s->swap_vazio(i,j,i+1,j); break;
  }
  return s;
}
/*****************************************************************************/



/*classe que encapsula as informações necessárias para um nó da árvore de 
busca*/
/*****************************************************************************/
class No{
      State* s;//Estado que representa no espaço de busca
      No*  pai;//Nó ancestral na árvore de busca
      int custo;//custo do caminho desde do estado inicial      
      int acao;//acao que foi aplicada ao pai para gerar este nó
      public:
      No(State* s, No* pai , int custo , int acao);
      State* get_state(){return this->s;};
      int get_custo(){ return this->custo;}
      int get_acao() { return this->acao;}
      void show();
      void print_path();
      No* move(int dir);
      bool igual(No* s);
};

No::No(State* s, No* pai , int custo , int acao){
    this->s = s;
    this->pai = pai;
    this->custo = custo;
    this->acao = acao;
}

void No::show(){
    this->s->show();
    cout << "Custo:" <<this->custo << endl;
    cout << "Acao: " <<this->acao << endl;
}

void No::print_path(){
    if(this->pai!=NULL){
        this->pai->print_path();
        switch(this->acao){
        case esquerda: cout << "esquerda" << endl; break;
        case direita: cout << "direita" << endl; break;
        case baixo : cout << "para baixo" << endl; break;
        case cima : cout << "para cima" << endl; break;
        
        }
    }else{
        cout << "Inicio da Solucao:" << endl;
        this->show();
    }
}

No* No::move(int dir){
    No * temp = new No( this->s->move(dir), this , this->get_custo() + 1 , dir );
    return temp;
}

bool No::igual(No* nodo){
    return this->s->igual(nodo->get_state());
}

class Fronteira{
    public:
    void coloca(No *s){};
    No* retira(){};
    bool vazia(){};
};


class FronteiraFila: public Fronteira{
    queue <No*> fila;
    public:
    void coloca(No *s);
    No* retira();
    bool vazia(); 
};

void FronteiraFila::coloca(No* s){
    fila.push(s);
}

No* FronteiraFila::retira(){
    No* temp = fila.front();
    fila.pop();
    return temp;
}

bool FronteiraFila::vazia(){
    return fila.size()==0;
}



class Busca{
    State * inicial;
    
    No * raiz;
    
    public:
        Busca(State* inicio, State * fim){ 
            this->inicial = inicio; 
            this->final = fim;
            this->raiz = new No(inicial, NULL , 0 , nenhuma); 
        }
        vector <No*> sucessores(No* nodo);
        No* get_raiz(){ return this->raiz;};
        State* get_final(){ return this->final; }
        State * final;
};




class BuscaLargura: public Busca{
    FronteiraFila fronteira;
    int num_explorados;
    int num_nodes;
    public:
        BuscaLargura(State *inicio, State *fim);
        bool bl(int m);
};


BuscaLargura::BuscaLargura(State *inicio, State *fim):Busca(inicio,fim){
    this->fronteira = FronteiraFila();
    this->num_explorados = 0;
    this->num_nodes = 0;
}


bool BuscaLargura::bl(int m){
    No* temp;
    int i;
    
    this->fronteira.coloca(this->get_raiz());
    
    this->num_nodes++;
    
    while(!this->fronteira.vazia() ){
        
        
        temp = fronteira.retira();
        this->num_explorados++;
        
        
        
        if( temp->get_state()->igual( this->get_final() )){
            cout << "Custo da solucao: " << temp->get_custo() << endl; 
            temp->print_path();
            cout << "Total de Nos: " << this->num_nodes << endl;
            cout << "Total de Nos Explorados" << this->num_explorados << endl;
            return true;
        }
        
        if( temp->get_custo() < m ){
            vector <No*> lista = this->sucessores(temp);
            for(i=0;i<lista.size(); i++){
               this->fronteira.coloca(lista[i]);
               this->num_nodes++;
            }
        }
        
    }
    
    return false;
    
}



vector <No*> Busca::sucessores( No* nodo){
    int dir;
    vector <No*> succ;
    No* temp;
    for( dir = esquerda; dir <= baixo ; dir++ ){
        temp = nodo->move(dir);
        if( !temp->igual(nodo) )
            succ.push_back(temp);
    }
    return succ;     
}




int main(){
    int i,j,temp;
    vector <int> v;
    
    for(i=0;i<9;i++){
        cin >> temp;
        v.push_back(temp);
    }  
    
    State * inicio = new State(v);
    
    v.clear();
    
    for(i=0;i<9;i++){
        cin >> temp;
        v.push_back(temp);
    }  
    
    State * final = new State(v);
    
    
    BuscaLargura b1 = BuscaLargura(inicio,final);
    cout << "Busca Largura" << endl;
    b1.bl(20);
    cout << "*********************************************" << endl << endl;
    
    

    

    system("PAUSE");
}
