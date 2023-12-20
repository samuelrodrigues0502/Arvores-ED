#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo *Apontador;

typedef struct TipoNo {
    int info;
    Apontador esq, dir;
    int bal; //-1, 0, +1 - Variável que auxilia no balanceamento da AVL.

} TipoNo;

void InsereAVL(int x, Apontador *p, int *pH);
void RetiraAVL(int x, Apontador *p, int *h);
void DelMin(Apontador *q, Apontador *r, int *h);
void balanceieR(Apontador *p, int *h);
void balanceieL(Apontador *p, int *h);
void Inicializa(Apontador *Arvore);
void inOrdem(Apontador p);
void Busca(int x, Apontador p);
void imprimirNivel(Apontador p, int nivel);//Impressão em nível

int main()
{
    int op;
    int h = 0, *pH = &h;
    Apontador Arvore2;//Criação das árvores.
    int x;
    Inicializa(&Arvore2);//Inicialização das duas árvores.

    while(op != 5){
        printf(" Arvore AVL\n");
        printf("\n 1 - Inserir numero na arvore");
        printf("\n 2 - Retirar numero da arvore");
        printf("\n 3 - Busca de um numero na arvore");
        printf("\n 4 - Imprimir arvore em nível");
        printf("\n 5 - Sair");
        printf("\n Digite a opção desejada: ");
        scanf("%d", &op);
        printf("\n");

        if(op>=1 && op<=4)
        {
            switch(op)
            {
            //Inserção de números até quando o usuário digitar 0;
            case 1:
                printf("\n Digite o numero desejado ou 0 para o fim do preenchimento.\n");
                scanf("%d", &x);

                h = 0;//zerando auxiliar para não haver conflito.
                while(x > 0)
                {
                    InsereAVL(x, &Arvore2, pH);
                    scanf("%d", &x);
                }
                break;

            case 2:
                printf("\n Digite o numero que deseja retirar: ");
                scanf("%d", &x);

                h = 0;//zerando auxiliar para não haver conflito.
                RetiraAVL(x, &Arvore2, pH);

                break;

            case 3:
                printf("\n Digite o numero que deseja buscar: ");
                scanf("%d", &x);

                Busca(x, Arvore2);
                break;

            case 4:
                imprimirNivel(Arvore2, 1);
                printf("\n\n");
                break;

            }
        }
    }
    return 0;
}

void Inicializa(Apontador *Arvore){//Função que inicializa a árvore

    *Arvore = NULL;
}

void inOrdem(Apontador p){//Função que realiza a impressão dos números de uma árvore em ordem.

    if (p != NULL) {
        inOrdem(p->esq);
        printf(" %d\n", p->info);
        inOrdem(p->dir);
    }
}

void Busca(int x, Apontador p){//Função que realiza a busca por um numero na árvore.

    int aux = 0;
    int cont = 0; //Contador que acumula o nível do número na árvore

    //Busca não recursiva
    while (p != NULL) { //While responsável por buscar o número enquanto a arvore não for nula e encontra seu nível.
        if (x < p->info) {
            p = p->esq; //Anda pra esquerda
            cont++;
        } else if (x > p->info) {
            p = p->dir; //Anda pra direita
            cont++;
        } else { //Se o número não for maior nem menor, ele foi encontrado.
            aux = 1;
            break;
        }
    }
    if (aux == 1) {
        printf("\n O numero %d foi encontrado no nivel %d\n\n", x, cont);
    } else {
        printf("\n O numero %d nao foi encontrado em nenhum nível\n\n", x);
    }

}

void imprimirNivel(Apontador p, int nivel){ //Função recursiva que realiza impressão da árvore em nível.
                                            //Recebe como parâmetro o apontador da árvore e o índice 1 como nível.
    int i;

    if(p != NULL){
        imprimirNivel(p->dir, nivel+1);
        printf("\n\n");

        for(i=0; i<nivel; i++)//Laço que auxilia no tabelamento no momento da impressão dos números.
            printf("\t");

        printf("%d", p->info);
        imprimirNivel(p->esq, nivel+1);
    }

}

void InsereAVL(int x, Apontador *p, int *h){    //Função recursiva de inserção na árvore dinâmica.
                                                //Recebe como parâmetro o número, o apontador da árvore
    Apontador pB, pC;                           //e um ponteiro que auxilia nas rotações da AVL para garantir o balanceamento

    if(*p == NULL){ //Inserção
        *p = malloc(sizeof(TipoNo));
        *h = 1;
        (*p)->info = x;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
        (*p)->bal = 0;
    }else{
        if(x < (*p)->info){
        InsereAVL(x, &(*p)->esq, h);
            if(*h == 1){    //Se h = 1, subárvore cresceu à esquerda
                switch((*p)->bal){//Verificação da variável de balanceamento.
                case -1://Se p->bal = -1 o desbalanceamento foi equilibrado.
                    (*p)->bal = 0;
                    *h = 0;     //zerando váriavel que indica crescimento da arvore.
                break;
                case 0://Se p->bal = 0 a altura da árvore é maior à esquerda.
                    (*p)->bal = (*p)->bal + 1;
                break;
                case 1://Se p->bal = 1 é necessário o balanceamento.
                    pB = (*p)->esq;
                        if(pB->bal == 1){ //Rotação LL(rotação a direita)
                            (*p)->esq = pB->dir;
                            pB->dir = (*p);
                            (*p)->bal = 0;
                            (*p) = pB;
                        }else{          //Rotação LR(rotação a esquerda-direita)
                            pC = pB->dir;
                            pB->dir = pC->esq;
                            pC->esq = pB;
                            (*p)->esq = pC->dir;
                            pC->dir = (*p);
                            if(pC->bal == 1){
                                (*p)->bal = -1;
                            }else{
                                (*p)->bal = 0;
                            }
                            if(pC->bal == -1){
                                pB->bal = 1;
                            }else{
                                pB->bal = 0;
                            }
                            (*p) = pC;
                        }
                        (*p)->bal = 0;
                        *h = 0;
                break;
                }
            }
        }else{
            if(x > (*p)->info){
            InsereAVL(x,&(*p)->dir, h);
                if(*h == 1){    //Se h = 1, subárvore cresceu à direita
                    switch((*p)->bal){//Verificação da variável de balanceamento.
                    case 1://Se p->bal = 1 o desbalanceamento foi equilibrado.
                        (*p)->bal = 0;
                        *h = 0;
                    break;
                    case 0://Se p->bal = 0 a altura da árvore é maior à direita.
                        (*p)->bal = (*p)->bal - 1;
                    break;
                    case -1://Se p->bal = -1 é necessário o balanceamento.
                        pB = (*p)->dir;
                            if(pB->bal == -1){  //Rotação RR(rotação a esquerda)
                                (*p)->dir = pB->esq;
                                pB->esq = (*p);
                                (*p)->bal = 0;
                                (*p) = pB;
                            }else{              //Rotação RL(rotação a direita-esquerda)
                                pC = pB->esq;
                                pB->esq = pC->dir;
                                pC->dir = pB;
                                (*p)->dir = pC->esq;
                                pC->esq = (*p);
                                if(pC->bal == -1){
                                    (*p)->bal = 1;
                                }else{
                                    (*p)->bal = 0;
                                }
                                if(pC->bal == 1){
                                    pB->bal = -1;
                                }else{
                                    pB->bal = 0;
                                }
                                (*p) = pC;
                            }
                            (*p)->bal = 0;
                            *h = 0;
                    break;
                    }
                }
            }
        }
    }
}

void RetiraAVL(int x, Apontador *p, int *h){        //Função recursiva de remoção na árvore dinâmica.
                                                    //Recebe como parâmetro o número, o apontador da árvore
    Apontador *q;                                   //e um ponteiro que auxilia nas rotações da AVL para garantir o balanceamento

    if(*p == NULL){
        printf(" Erro : Registro fora da arvore\n");
        return;
    }
    if(x < (*p)->info){
        RetiraAVL(x, &(*p)->esq, h);
        if(*h == 1){//Se h = 1 é necessário o rebalanceamento após a remoção.
            balanceieL(&(*p), h);//Balanceamento à esquerda
        }
    }else{
        if(x > (*p)->info){
        RetiraAVL(x, &(*p)->dir, h);
            if(*h == 1){//Se h = 1 é necessário o rebalanceamento após a remoção.
                balanceieR(&(*p), h);//Balanceamento à direita
            }
        }else{
            q = p;
            if((*q)->dir == NULL){
                *p = (*q)->esq;
                *h = 1;
            }else{
                if((*q)->esq == NULL){
                    *p = (*q)->dir;
                    *h = 1;
                }else{
                    DelMin(&(*q), &(*q)->dir, h);//Função que só é chamada qdo o nó
                    if(*h == 1){                 //em questão possui duas subárvores.
                        balanceieR(&(*p), h);
                    }
                }
            }
        }
    }
}

void DelMin(Apontador *q, Apontador *r, int *h){//O método DelMin procura, na subárvore direita, pelo
                                                //menor valor e só é chamando quando o nó com chave x
                                                //possui as duas subárvores
    if((*r)->esq != NULL){
        DelMin(&(*q), &(*r)->esq, h);
        if(*h == 1){
            balanceieL(&(*r),h);
        }
    }
    else{
        (*q)->info = (*r)->info;
        q = r;
        *r = (*r)->dir;
        *h = 1;
    }
}

void balanceieL(Apontador *p, int *h){//Função que balanceia a árvore à esquerda
                                      //após a remoção de um nó.
    Apontador pB, pC;
    int balB, balC;

    switch((*p)->bal){//Verificação da variável de balanceamento.

        case 1://Se p->bal = 1 o desbalanceamento foi equilibrado.
            (*p)->bal = 0;
            break;
        case 0://Se p->bal = 0 a altura da árvore é maior à direita.
            (*p)->bal = - 1;
            *h = 0;
            break;
        case -1://Se p->bal = -1 é necessário o balanceamento.
            pB = (*p)->dir;
            balB = pB->bal;
            if(balB <= 0)   //Rotação RR(rotação a esquerda)
            {
                (*p)->dir = pB->esq;
                pB->esq = (*p);
                if(balB == 0){
                    (*p)->bal = -1;
                    pB->bal = 1;
                    *h = 0;
                }else{
                    (*p)->bal = 0;
                    pB->bal = 0;
                }
                (*p) = pB;
            }else{                //Rotação RL(rotação a direita-esquerda)
                pC = pB->esq;
                balC = pC->bal;
                pB->esq = pC->dir;
                pC->dir = pB;
                (*p)->dir = pC->esq;
                pC->esq = (*p);
                if(balC == -1){
                    (*p)->bal = 1;
                }
                else{
                    (*p)->bal = 0;
                }
                if(balC == 1){
                    pB->bal = -1;
                }
                else{
                    pB->bal = 0;
                }
                (*p) = pC;
                pC->bal = 0;
            }
            break;
        }
}

void balanceieR(Apontador *p, int *h){//Função que balanceia a árvore à direita
                                      //após a remoção de um nó.
    Apontador pB, pC;
    int balB, balC;

    switch((*p)->bal){

        case -1://Se p->bal = -1 o desbalanceamento foi equilibrado.
            (*p)->bal = 0;
            break;
        case 0://Se p->bal = 0 a altura da árvore é maior à esquerda.
            (*p)->bal = 1;
            *h = 0;
            break;
        case 1://Se p->bal = 1 é necessário o balanceamento.
            pB = (*p)->esq;
            balB = pB->bal;
            if(balB >= 0)   //Rotação RR(rotação a esquerda)
            {
                (*p)->esq = pB->dir;
                pB->dir = (*p);
                if(balB == 0){
                    (*p)->bal = 1;
                    pB->bal = -1;
                    *h = 0;
                }else{
                    (*p)->bal = 0;
                    pB->bal = 0;
                }
                (*p) = pB;
            }else{                //Rotação RL(rotação a direita-esquerda)
                pC = pB->dir;
                balC = pC->bal;
                pB->dir = pC->esq;
                pC->esq = pB;
                (*p)->esq = pC->dir;
                pC->dir = (*p);
                if(balC == 1){
                    (*p)->bal = -1;
                }
                else{
                    (*p)->bal = 0;
                }
                if(balC == -1){
                    pB->bal = 1;
                }
                else{
                    pB->bal = 0;
                }
                (*p) = pC;
                pC->bal = 0;
            }
            break;
        }
}
