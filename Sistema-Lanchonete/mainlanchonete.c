/*
 * Arquivo principal do sistema de lanchonete
 * Responsável por inicializar dados e controlar o fluxo do programa
 */

#include <stdio.h>
#include "lanchonete.h"


int main(){

    int SenhaGerente = 1234;
    int *ptrSenhaGerente = &SenhaGerente;

    float TotalPedido = 0; // Variável para o valor total em R$ do pedido do usuario.
    float *ptrTotalPedido = &TotalPedido; // Ponteiro para a variável TotalPedido.
    
    struct produto *Lista = NULL;
    
    int OpcaoMenu; // Variável para manter o do while do menu inicial

    ExibirBoasVindas(); // Função para exibir texto de boas vindas

    // Lista de produtos defaut. Permite testar o programa sem ter que criar novos produtos.
    InserirFinalCardapio(&Lista,10,15,"Hamburguer");
    InserirFinalCardapio(&Lista,11,30,"Pizza");
    InserirFinalCardapio(&Lista,12,5,"Refri");
    InserirFinalCardapio(&Lista,14,7,"Batata Frita");

    do{

        OpcaoMenu = ExibirMenuInicial(ptrSenhaGerente,&Lista, ptrTotalPedido); // Variável OpcaoMenu recebe o valor da função ExibirMenuInicial
    
    }while(OpcaoMenu != 0); // Verifica se o valor da função ExibirMenuInicial é diferente de 0
    
    
    LiberarCardapio(&Lista); 
    return 0; // Encerra o programa.
    
    
}