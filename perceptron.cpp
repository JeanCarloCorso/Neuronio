#include<stdio.h>
#include<stdlib.h>

#define entradas 4
#define taxa_apre 1
#define qtd_dados 16

float w[10];

float dados[16][5] = 
    {
        {0,0,0,0,0},
        {0,0,0,1,1},
        {0,0,1,0,1},
        {0,0,1,1,1},
        {0,1,0,0,0},
        {0,1,0,1,1},
        {0,1,1,0,1},
        {0,1,1,1,1},
        {1,0,0,0,0},
        {1,0,0,1,1},
        {1,0,1,0,1},
        {1,0,1,1,1},
        {1,1,0,0,0},
        {1,1,0,1,1},
        {1,1,1,0,1},
        {1,1,1,1,1}
    };

void inicializapesos(){
    for(int i = 0; i < entradas; i++){
        w[i] = 0;
    }
}

int ativacao(float soma){
    if(soma >= 1){
        return 1;
    }else{
        return 0;
    }
}

float soma(float x, float w){
    return x * w;
}

float aprende(float x, float w, float erro){
    return w + (x * erro * taxa_apre);
}

int main(){
    int j = 0;

    printf("\n\n-------------DADOS-DE-TREINAMENTO-------------\n\n");

    for(int i = 0; i<entradas; i++){
        printf("  x%d   |",i);
    }
    printf(" saida |\n");
    for(int i = 0; i < (entradas + 1); i++){
        printf("-------|",i);
    }
    for(int i = 0; i<qtd_dados; i++){
       printf("\n");
       for(j = 0; j < (entradas + 1); j++){
           printf("  %2.1f  |", dados[i][j]);
       }
    }
    printf("\n\n");
    inicializapesos();
    float erro = 0;
    float somatoria = 0;
    float saida = 0;
    int qtd_erros = 0;
    int passos = 0;
    do{
        qtd_erros = 0;
        saida = 0;
        erro = 0;
        passos += 1;
        printf("==========Teste[%d]==========\n                           =\n", passos);
        //percorre os dados de entrada do neuronio
        for(int i = 0; i < qtd_dados; i++){
            //somatória das entradas * pesos (x * w)
            somatoria = 0;
            for(j = 0; j < entradas; j++){
                printf("  x[%d]: %2.1f --- w[%d]: %2.1f  =\n", j, dados[i][j], j, w[j]);
                somatoria += soma(dados[i][j], w[j]);
            }

            printf("                           =\n");
            //ativação do neuronio
            saida = ativacao(somatoria);

            //calculo do erro
            erro = dados[i][j] - saida;

            printf("  Somatoria: %2.1f           =\n  Saida:          %2.1f      =\n  Saida esperada: %2.1f      =\n  Erro:           %2.1f      =\n  -----------------------  =\n                           =\n",
             somatoria, saida, dados[i][j], erro);

            //verifica se houve erro
            if(erro != 0){
                qtd_erros += 1;
                for(j = 0; j < entradas; j++){
                    w[j] = aprende(dados[i][j], w[j], erro);
                }
            }
        }
       
    }while(qtd_erros != 0);

     printf("    |---------------|      =\n    |  qtd erros: %d |      =\n", passos, qtd_erros);
        for(j = 0; j < entradas; j++){
            printf("    |  w[%d]: %2.1f    |      =\n", j, w[j]);
        }
        printf("    |---------------|      =\n                           =\n");


    return 0;
}