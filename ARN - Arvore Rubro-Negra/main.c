#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo *Apontador;

typedef struct TipoNo {
    int info;
    Apontador esq, dir;
    int bal; //-1, 0, +1 - Vari�vel que auxilia no balanceamento da AVL.

} TipoNo;

void InsereAVL(int x, Apontador *p, int *pH);
void RetiraAVL(int x, Apontador *p, int *h);
void DelMin(Apontador *q, Apontador *r, int *h);
void balanceieR(Apontador *p, int *h);
void balanceieL(Apontador *p, int *h);
void Inicializa(Apontador *Arvore);
void inOrdem(Apontador p);
void Busca(int x, Apontador p);
void imprimirNivel(Apontador p, int nivel);//Impress�o em n�vel

int main()
{
    int op;
    int h = 0, *pH = &h;
    Apontador Arvore2;//Cria��o das �rvores.
    int x;
    Inicializa(&Arvore2);//Inicializa��o das duas �rvores.

    while(op != 5){
        printf(" Arvore AVL\n");
        printf("\n 1 - Inserir numero na arvore");
        printf("\n 2 - Retirar numero da arvore");
        printf("\n 3 - Busca de um numero na arvore");
        printf("\n 4 - Imprimir arvore em n�vel");
        printf("\n 5 - Sair");
        printf("\n Digite a op��o desejada: ");
        scanf("%d", &op);
        printf("\n");

        if(op>=1 && op<=4)
        {
            switch(op)
            {
            //Inser��o de n�meros at� quando o usu�rio digitar 0;
            case 1:
                printf("\n Digite o numero desejado ou 0 para o fim do preenchimento.\n");
                scanf("%d", &x);

                h = 0;//zerando auxiliar para n�o haver conflito.
                while(x > 0)
                {
                    InsereAVL(x, &Arvore2, pH);
                    scanf("%d", &x);
                }
                break;

            case 2:
                printf("\n Digite o numero que deseja retirar: ");
                scanf("%d", &x);

                h = 0;//zerando auxiliar para n�o haver conflito.
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

void Inicializa(Apontador *Arvore){//Fun��o que inicializa a �rvore

    *Arvore = NULL;
}

void inOrdem(Apontador p){//Fun��o que realiza a impress�o dos n�meros de uma �rvore em ordem.

    if (p != NULL) {
        inOrdem(p->esq);
        printf(" %d\n", p->info);
        inOrdem(p->dir);
    }
}

void Busca(int x, Apontador p){//Fun��o que realiza a busca por um numero na �rvore.

    int aux = 0;
    int cont = 0; //Contador que acumula o n�vel do n�mero na �rvore

    //Busca n�o recursiva
    while (p != NULL) { //While respons�vel por buscar o n�mero enquanto a arvore n�o for nula e encontra seu n�vel.
        if (x < p->info) {
            p = p->esq; //Anda pra esquerda
            cont++;
        } else if (x > p->info) {
            p = p->dir; //Anda pra direita
            cont++;
        } else { //Se o n�mero n�o for maior nem menor, ele foi encontrado.
            aux = 1;
            break;
        }
    }
    if (aux == 1) {
        printf("\n O numero %d foi encontrado no nivel %d\n\n", x, cont);
    } else {
        printf("\n O numero %d nao foi encontrado em nenhum n�vel\n\n", x);
    }

}

void imprimirNivel(Apontador p, int nivel){ //Fun��o recursiva que realiza impress�o da �rvore em n�vel.
                                            //Recebe como par�metro o apontador da �rvore e o �ndice 1 como n�vel.
    int i;

    if(p != NULL){
        imprimirNivel(p->dir, nivel+1);
        printf("\n\n");

        for(i=0; i<nivel; i++)//La�o que auxilia no tabelamento no momento da impress�o dos n�meros.
            printf("\t");

        printf("%d", p->info);
        imprimirNivel(p->esq, nivel+1);
    }

}

void InsereAVL(int x, Apontador *p, int *h){    //Fun��o recursiva de inser��o na �rvore din�mica.
                                                //Recebe como par�metro o n�mero, o apontador da �rvore
    Apontador pB, pC;                           //e um ponteiro que auxilia nas rota��es da AVL para garantir o balanceamento

    if(*p == NULL){ //Inser��o
        *p = malloc(sizeof(TipoNo));
        *h = 1;
        (*p)->info = x;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
        (*p)->bal = 0;
    }else{
        if(x < (*p)->info){
        InsereAVL(x, &(*p)->esq, h);
            if(*h == 1){    //Se h = 1, sub�rvore cresceu � esquerda
                switch((*p)->bal){//Verifica��o da vari�vel de balanceamento.
                case -1://Se p->bal = -1 o desbalanceamento foi equilibrado.
                    (*p)->bal = 0;
                    *h = 0;     //zerando v�riavel que indica crescimento da arvore.
                break;
                case 0://Se p->bal = 0 a altura da �rvore � maior � esquerda.
                    (*p)->bal = (*p)->bal + 1;
                break;
                case 1://Se p->bal = 1 � necess�rio o balanceamento.
                    pB = (*p)->esq;
                        if(pB->bal == 1){ //Rota��o LL(rota��o a direita)
                            (*p)->esq = pB->dir;
                            pB->dir = (*p);
                            (*p)->bal = 0;
                            (*p) = pB;
                        }else{          //Rota��o LR(rota��o a esquerda-direita)
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
                if(*h == 1){    //Se h = 1, sub�rvore cresceu � direita
                    switch((*p)->bal){//Verifica��o da vari�vel de balanceamento.
                    case 1://Se p->bal = 1 o desbalanceamento foi equilibrado.
                        (*p)->bal = 0;
                        *h = 0;
                    break;
                    case 0://Se p->bal = 0 a altura da �rvore � maior � direita.
                        (*p)->bal = (*p)->bal - 1;
                    break;
                    case -1://Se p->bal = -1 � necess�rio o balanceamento.
                        pB = (*p)->dir;
                            if(pB->bal == -1){  //Rota��o RR(rota��o a esquerda)
                                (*p)->dir = pB->esq;
                                pB->esq = (*p);
                                (*p)->bal = 0;
                                (*p) = pB;
                            }else{              //Rota��o RL(rota��o a direita-esquerda)
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

void RetiraAVL(int x, Apontador *p, int *h){        //Fun��o recursiva de remo��o na �rvore din�mica.
                                                    //Recebe como par�metro o n�mero, o apontador da �rvore
    Apontador *q;                                   //e um ponteiro que auxilia nas rota��es da AVL para garantir o balanceamento

    if(*p == NULL){
        printf(" Erro : Registro fora da arvore\n");
        return;
    }
    if(x < (*p)->info){
        RetiraAVL(x, &(*p)->esq, h);
        if(*h == 1){//Se h = 1 � necess�rio o rebalanceamento ap�s a remo��o.
            balanceieL(&(*p), h);//Balanceamento � esquerda
        }
    }else{
        if(x > (*p)->info){
        RetiraAVL(x, &(*p)->dir, h);
            if(*h == 1){//Se h = 1 � necess�rio o rebalanceamento ap�s a remo��o.
                balanceieR(&(*p), h);//Balanceamento � direita
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
                    DelMin(&(*q), &(*q)->dir, h);//Fun��o que s� � chamada qdo o n�
                    if(*h == 1){                 //em quest�o possui duas sub�rvores.
                        balanceieR(&(*p), h);
                    }
                }
            }
        }
    }
}

void DelMin(Apontador *q, Apontador *r, int *h){//O m�todo DelMin procura, na sub�rvore direita, pelo
                                                //menor valor e s� � chamando quando o n� com chave x
                                                //possui as duas sub�rvores
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

void balanceieL(Apontador *p, int *h){//Fun��o que balanceia a �rvore � esquerda
                                      //ap�s a remo��o de um n�.
    Apontador pB, pC;
    int balB, balC;

    switch((*p)->bal){//Verifica��o da vari�vel de balanceamento.

        case 1://Se p->bal = 1 o desbalanceamento foi equilibrado.
            (*p)->bal = 0;
            break;
        case 0://Se p->bal = 0 a altura da �rvore � maior � direita.
            (*p)->bal = - 1;
            *h = 0;
            break;
        case -1://Se p->bal = -1 � necess�rio o balanceamento.
            pB = (*p)->dir;
            balB = pB->bal;
            if(balB <= 0)   //Rota��o RR(rota��o a esquerda)
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
            }else{                //Rota��o RL(rota��o a direita-esquerda)
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

void balanceieR(Apontador *p, int *h){//Fun��o que balanceia a �rvore � direita
                                      //ap�s a remo��o de um n�.
    Apontador pB, pC;
    int balB, balC;

    switch((*p)->bal){

        case -1://Se p->bal = -1 o desbalanceamento foi equilibrado.
            (*p)->bal = 0;
            break;
        case 0://Se p->bal = 0 a altura da �rvore � maior � esquerda.
            (*p)->bal = 1;
            *h = 0;
            break;
        case 1://Se p->bal = 1 � necess�rio o balanceamento.
            pB = (*p)->esq;
            balB = pB->bal;
            if(balB >= 0)   //Rota��o RR(rota��o a esquerda)
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
            }else{                //Rota��o RL(rota��o a direita-esquerda)
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
