#include <iostream>
#include <list>
using namespace std;
int totalNodos=0;

class Vertice
{
public:
    Vertice();
    Vertice(Vertice *copiaPai);
    Vertice *pai = NULL;
    int tabuleiro[3][3];
    int jogador = -1;
    int miniMax = 999;
    Vertice* operator++();
    Vertice *filho0,*filho1,*filho2,*filho3,*filho4,*filho5,*filho6,*filho7,*filho8;
    list<Vertice*>filho = {filho0,filho1,filho2,filho3,filho4,filho5,filho6,filho7,filho8};
    //filho0,filho1,filho2,filho3,filho4,filho5,filho6,filho7,filho8
};

Vertice* Vertice::operator++(){
    return this;
}

Vertice::Vertice()
{
    int i,j;
    for (i=0; i<3; ++i){
        for(j=0; j<3; ++j){
            this->tabuleiro[i][j] = 0;
        }
    }
}

Vertice::Vertice(Vertice *copiaPai)
{
    int i,j;
    this->pai = copiaPai;
    for (i=0; i<3; ++i){
        for(j=0; j<3; ++j){
            this->tabuleiro[i][j] = copiaPai->tabuleiro[i][j];
        }
    }
    if (copiaPai->jogador == 1)
        this->jogador = -1;
    else 
        this->jogador = 1;
}

int verificaVitoria(Vertice *v){
    int i=0,j=0;
    for (i=0;i<3;++i)
    {
        if (v->tabuleiro[0][i] == 1 && v->tabuleiro[1][i] == 1 && v->tabuleiro[2][i] == 1)
            return 1;
        else if (v->tabuleiro[0][i] == -1 && v->tabuleiro[1][i] == -1 && v->tabuleiro[2][i] == -1)
            return -1;
    }
    for (j=0;j<3;++j)
    {
        if (v->tabuleiro[j][0] == 1 && v->tabuleiro[j][1] == 1 && v->tabuleiro[j][2] == 1)
            return 1;
        else if (v->tabuleiro[j][0] == -1 && v->tabuleiro[j][1] == -1 && v->tabuleiro[j][2] == -1)
            return -1;
    }
    if (v->tabuleiro[0][0] == 1 && v->tabuleiro[1][1] == 1 && v->tabuleiro[2][2] == 1)
        return 1;
    if (v->tabuleiro[0][0] == -1 && v->tabuleiro[1][1] == -1 && v->tabuleiro[2][2] == -1)
        return -1;
    if (v->tabuleiro[0][2] == 1 && v->tabuleiro[1][1] == 1 && v->tabuleiro[2][0] == 1)
        return 1;
    if (v->tabuleiro[0][2] == -1 && v->tabuleiro[1][1] == -1 && v->tabuleiro[2][0] == -1)
        return -1;
    else return 0;
}

void printaTabuleiro(Vertice *v){
    int i=0,j=0;

    for (i=0;i<3;++i)
    {
        for (j=0;j<3;++j)
        {
            cout << v->tabuleiro[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
}

int fazJogada(Vertice *v, int filho) {
    int i,j,k=0;
    //if (filho != 0) {
        for (i=0; i<3; ++i)
        {
            for(j=0; j<3; ++j)
            {
                if (v->tabuleiro[i][j] == 0){
                    --filho;
                }
                if (filho >= 0){
                    ++k;
                }
            }
        }
    //}
    
    for (i=0; i<3; ++i)
    {
        for(j=0; j<3; ++j)
        {
            //cout << "K: " << k << endl;
            if (k <= 0 ) {
                v->tabuleiro[i][j] = v->jogador;
                //cout << "i = " << i << ", j = " << j << endl;
                //printaTabuleiro(v);
                return 0;
            }
            --k;
        }
    }
    return 1;
}

int escolhePiorFilho(Vertice *v, int nFilho){
    int i, resposta = 0;
    auto atual = v->filho.begin();
    for (i=0; i<nFilho; ++i){
        if ( (*atual)->miniMax > resposta ) {
            resposta = (*atual)->miniMax;
        }
        atual++;
    }
    return resposta;
}

int escolheMelhorFilho(Vertice *v, int nFilho){
    int i, resposta = 999;
    auto atual = v->filho.begin();
    for (i=0; i<nFilho; ++i){
        if ( (*atual)->miniMax < resposta ) {
            resposta = (*atual)->miniMax;
        }
        atual++;
    }
    return resposta;
}

int criaTabuleiro(Vertice *v, int nFilho){
    if (nFilho == 0) 
    {
        v->miniMax = 0;
        return 0;
    }
    auto atual = v->filho.begin();
    int i=0;
    for (; i<nFilho; ++atual, ++i)
    {
        totalNodos++;
        *atual = new Vertice(v);
        fazJogada(*atual,i);
        //cout << "Return Vitoria: " << verificaVitoria(*atual) << endl;
        //printaTabuleiro(*atual);
        if (verificaVitoria(*atual) == 0)
        {
            if ((*atual)->jogador == 1) 
            {
                //(*atual)->miniMax = escolhePiorFilho(*atual, nFilho);
            }

            else if ((*atual)->jogador == -1) 
            {
                //(*atual)->miniMax = escolheMelhorFilho(*atual, nFilho);
            }
            criaTabuleiro(*atual, nFilho-1);
        }
        if(verificaVitoria(*atual) != 0) 
        {
            (*atual)->miniMax = verificaVitoria(*atual);
        }
        /*else
            return 0;*/
    }
    return v->miniMax;
}

int main () {
    Vertice *v = new Vertice();
    int miniMax;
    miniMax = criaTabuleiro(v,9);
    cout << "Numero de Nodos: " << totalNodos << "\nMiniMax: " << miniMax;
    return 0;
}