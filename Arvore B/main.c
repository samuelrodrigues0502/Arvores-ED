#include <stdio.h>
#include <stdlib.h>

typedef struct Registro {
    int chave;
} Registro;

typedef struct TipoPag *Apontador;

typedef struct TipoPag {
    int n;
    Registro r[4];
    Apontador p[4 + 1];

} TipoPag;

void Inicializa(Apontador *Dicionario);
void Pesquisa(Registro *x, Apontador Ap);
void Ins(Registro Reg, Apontador Ap, short *Cresceu, Registro *RefRetorno, Apontador *ApRetorno);
void InsereNaPag(Apontador Ap, Registro Reg, Apontador ApDir);
void Insere(Registro Reg, Apontador *Ap);
void ImprimeI(Apontador p, int nivel);
void Imprime(Apontador p);

int main(int argc, char** argv) {

    Apontador Pag;
    Registro Reg;

    Inicializa(&Pag);

    do{
        scanf("%d", &Reg.chave);
        Insere(Reg, &Pag);

    }while(Reg.chave != 0);

    Imprime(Pag);


    return (EXIT_SUCCESS);
}

void Inicializa(Apontador *Dicionario) {
    *Dicionario = NULL;
}

void Pesquisa(Registro *x, Apontador Ap) {
    long i = 1;

    if (Ap == NULL) {
        printf(" Não está na árvore");
        return;
    }
    while (i < Ap->n && x->chave > Ap->r[i - 1].chave) {
        i++;}

    if (x->chave == Ap->r[i - 1].chave) {
        *x = Ap->r[i - 1];
        return;
    }

    if (x->chave < Ap->r[i - 1].chave) {
        Pesquisa(x, Ap->p[i - 1]);
    } else {
        Pesquisa(x, Ap->p[i]);
    }
}

void Ins(Registro Reg, Apontador Ap, short *Cresceu, Registro *RegRetorno, Apontador *ApRetorno) {
    long i = 1;
    long j;
    Apontador ApTemp;

    if (Ap == NULL) {
        *Cresceu = 1;
        *RegRetorno = Reg;
        *ApRetorno = NULL;
        return;
    }
    while (i < Ap->n && Reg.chave > Ap->r[i - 1].chave) {
        i++;
    }
    if (Reg.chave == Ap->r[i - 1].chave) {
        printf(" Erro: Registro ja esta presente\n");
        return;
    }
    if (Reg.chave < Ap->r[i - 1].chave) {
        i--;
    }

    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);

    if (*Cresceu == 0) {
        return;
    }
    if (Ap->n < 4 + 1) {
        InsereNaPag(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        return;
    }


    /*Overflow: Pagina tem que ser dividida*/

    ApTemp = (Apontador) malloc(sizeof (TipoPag));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < 2 + 1) {
        InsereNaPag(ApTemp, Ap->r[4 - 1], Ap->p[4]);
        Ap->n--;
        InsereNaPag(Ap, *RegRetorno, *ApRetorno);
    } else InsereNaPag(ApTemp, *RegRetorno, *ApRetorno);
    for (j = 2 + 2; j <= 4; j++) {
        InsereNaPag(ApTemp, Ap->r[j - 1], Ap->p[j]);
    }
    Ap->n = 2;
    ApTemp->p[0] = Ap->p[2 + 1];
    *RegRetorno = Ap->r[2];
    *ApRetorno = ApTemp;

}

void InsereNaPag(Apontador Ap, Registro Reg, Apontador ApDir) {
    short NaoAchouPosicao = 0;
    int k;
    k = Ap->n;
    NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao == 1) {
        if (Reg.chave >= Ap->r[k - 1].chave) {
            NaoAchouPosicao = 0;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)NaoAchouPosicao = 0;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Insere(Registro Reg, Apontador *Ap) {
    short Cresceu = 0;
    Registro RegRetorno;
    TipoPag *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
    if (Cresceu == 1) {
        ApTemp = (TipoPag*) malloc(sizeof (TipoPag));
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

void ImprimeI(Apontador p, int nivel) {
    long i;
    if (p == NULL) return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->n; i++)
        printf("%d ", p->r[i].chave);
    putchar('\n');
    nivel++;
    for (i = 0; i <= p->n; i++)
        ImprimeI(p->p[i], nivel);
}

void Imprime(Apontador p) {
    int n = 0;
    ImprimeI(p, n);
}
