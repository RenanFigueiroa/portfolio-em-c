/*
 * Arquivo: lanchonete.c
 * Projeto: Sistema de Lanchonete
 * Descrição:
 *  Implementa as funcionalidades do sistema, incluindo:
 *  - Gerenciamento de produtos usando lista simplesmente encadeada
 *  - Fluxo de menus
 *  - Sistema de pedidos e pagamento
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lanchonete.h"


// Exibir mensagem de boas vindas
void ExibirBoasVindas(){
    printf("\n======================\n");
    printf("BEM-VINDO Á LANCHONETE");
    printf("\n======================\n");
    sleep(1);
}

// Exibe as opções do gerente e controla o fluxo das funcionalidades administrativas
// Recebe a lista de produtos e a senha do gerente para repasse às funções de controle

void MenuGerente(struct produto **Li, int *senhagerente){

    sleep(1);
    printf("Perfil: gerente\n");
    VerificarAcessoGerente(senhagerente);

    int opcao;

    do{

    printf("\n\n---MENU GERENTE---\n\n");
    printf("Digite o código da função escolhida:\n");
    printf("1.Criar novo produto\n");
    printf("2.Excluir produto\n");
    printf("0.Menu inicial!\n");
    scanf("%d",&opcao);

    switch (opcao)
    {
    case 1:
        CriarNovoProduto(Li);
        break;
    case 2:
        ExcluirProduto(Li);
        break;
    default:
        printf("Não existe função com esse número!!!\n");
        sleep(2);
        break;
    }



    }while(opcao != 0);

}

// Remove um produto da lista com base no código informado
// Recebe um ponteiro para a lista para permitir a alteração da estrutura

void ExcluirProduto(struct produto **Li){

    int opcao;

    do{

        int codigoProdutoExcluido;
        printf("\n\n---EXCLUIR PRODUTO---\n\n");
        printf("Digite o código do produto a ser excluido\n");
        scanf("%d",&codigoProdutoExcluido);

        struct produto *Atual =*Li;
        struct produto *Anterior = NULL;

        while(Atual != NULL){

                if(Atual ->codigo == codigoProdutoExcluido){

                    sleep(1);
                    printf("\nProduto encontrado:\n");
                    printf("  Nome: %s\n", Atual->nome);
                    printf("  Código: %d\n", Atual->codigo);
                    printf("  Preço: R$ %.2f\n\n", Atual->preco);
            
           
                    char confirmacao;
                    printf("Confirma exclusão? (s/n): ");
                    scanf(" %c", &confirmacao);
            
                    if(confirmacao != 's' && confirmacao != 'S'){
                        printf("Operação cancelada.\n");
                        sleep(1);
                        return;
                    }


                    if(Anterior == NULL){
                        *Li = Atual->proximo;


                    }else{
                        Anterior->proximo = Atual ->proximo;
                    
                    }

                    free(Atual);
                    printf("Produto Excluido com sucesso!\n");
                    return;
            }

        Anterior= Atual;
        Atual = Atual ->proximo;
    }

    printf("Não existe produto com esse código\n");
    sleep(1);

    printf("Digite 0 para voltar ao menu:\n");
    printf("Digite 1 para tentar novamente\n");
    scanf("%d",&opcao);


    }while(opcao !=0);
    
}

// Controla o acesso às funções administrativas por meio de verificação de senha
// Limita tentativas inválidas e aplica bloqueio temporário


void VerificarAcessoGerente(int *senhagerente){
    int senha=0;
    int numeroErros =0;

    do{

        if(numeroErros ==3){

            printf("\n!!!LIMITE DE 3 TENTATIVAS EXCEDIDA!!!\n");
            printf("A tela será bloqueada por 15 segundos\n");
            sleep(15);
            return;

        }

        sleep(1);
        printf("Digite a senha do gerente\n");
        printf("Senha:");
        scanf("%d",&senha);

        if(senha != *senhagerente){
            printf("\n!!!SENHA INCORRETA!!!\n\n");
            sleep(1);
            numeroErros ++;
        } else{
            sleep(1);
            printf("Acesso concluido\n");
            sleep(1);
            printf("Status de perfil: Ativo\n");
            sleep(1);
    
        }

    }while(senha!= *senhagerente) ;
    
}

// Cria um novo produto a partir das informações fornecidas pelo usuário
// Recebe um ponteiro para a lista para permitir a inserção do novo nó

void CriarNovoProduto(struct produto **Li){
    int codigo;
    float preco;
    char nome[20];


    InserirNomeNovoProduto(nome);

    preco = InserirPrecoNovoProduto();

    codigo =InserirCodigoNovoProduto(Li);

    InserirFinalCardapio(Li,codigo,preco,nome);

    printf("Produto cadastrado com sucesso!\n");
    sleep(1);
    printf("Dados do produto\n");
    printf("Nome: %s\n", nome);
    printf("Preço: %.2f\n",preco);
    printf("Código: %d\n",codigo);

    sleep(4);

}

// Solicita e valida o preço do novo produto
// Garante que o valor informado seja positivo

float InserirPrecoNovoProduto(){

    float preco;

    do{
        printf("Digite o preço do produto:\n");
        scanf("%f",&preco);

        if(preco <=0){
            printf("Preço inválido\n");
        }
    }while(preco <=0);

    return preco;

}

// Lê o nome do novo produto com limite de caracteres
// Recebe um vetor de caracteres para armazenar o nome

void InserirNomeNovoProduto(char nome[]){
    printf("Nome do produto (até 19 caracteres): \n");
    scanf(" %19[^\n]", nome);
}

// Solicita e valida o código de um novo produto
// Garante que o código seja positivo e não exista na lista

int InserirCodigoNovoProduto(struct produto **Li){

    int codigo;
    int codigoExiste;
    
    do {
        codigoExiste = 0;  
            
        do{
            printf("Digite o código do produto \n");
            scanf("%d", &codigo);

            if(codigo <=0){
                printf("Código inválido\n");
            }
        }while(codigo <=0);
        
        
        struct produto *Auxiliar = *Li;
        
        while(Auxiliar != NULL) {
            if(Auxiliar->codigo == codigo) {
                printf(" Código %d já existe! Escolha outro.\n", codigo);
                codigoExiste = 1;
                break;  
            }
            Auxiliar = Auxiliar->proximo;
        }
        
    } while( codigoExiste ==1);
    
    return codigo;
}

// Libera toda a memória alocada para a lista de produtos
// Recebe um ponteiro para a lista para redefinir o início após a liberação

void LiberarCardapio(struct produto **Li){
    struct produto *Atual = *Li;
    struct produto *Proximo;
    
    printf("\nLiberando memória...\n");
    
    while(Atual != NULL){
        Proximo = Atual->proximo;  
        
        printf("  Liberando: %s (Código %d)\n", Atual->nome, Atual->codigo);
        
        free(Atual);  
        Atual = Proximo;  
    }
    
    *Li = NULL;  
    printf("✓ Todos os produtos foram liberados da memória!\n");
}

// Insere o novo nó ao final da lista com os dados do novo produto
// Recebe ponteiro para lista para permitir a alteração da estrutura
// Recebe código, preço e nome para preencher os dados do novo nó

void InserirFinalCardapio(struct produto **Li,int CodigoProduto, float PrecoProduto, char NomeProduto[]){

    struct produto *novoProduto = (struct produto*) malloc(sizeof( produto));
    struct produto *Auxiliar = *Li;

    if (novoProduto == NULL){
        printf("Erro na alocação de memória");
        return;
    }
    
    novoProduto->codigo = CodigoProduto;
    novoProduto->preco =  PrecoProduto;
    strncpy(novoProduto->nome, NomeProduto, 19); 
    novoProduto->nome[19] = '\0';  
    novoProduto->proximo = NULL;

    if(*Li ==NULL){
        *Li=novoProduto;
        return;
    }

    while(Auxiliar ->proximo!= NULL){
        Auxiliar = Auxiliar->proximo;
    }

    Auxiliar->proximo = novoProduto;

}

// Exibe o menu principal e controla o fluxo geral do sistema
// Recebe a lista de produtos, a senha do gerente e o valor total do pedido

int ExibirMenuInicial(int *senhagerente,  struct produto **Li,float *ValorTotal){
    int OpcaoMenu=0;
    printf("\n\n//-----MENU-----//\n\n");
    printf("TOTAL DO PEDIDO: R$ %.2f\n", *ValorTotal);
    printf("Digite o código da função escolhida:\n");
    printf("1.Fazer pedido!\n");
    printf("2.Finalizar o pedido!\n");
    printf("3.Perfil do gerente!\n");
    printf("0.Sair do sistema!\n");
    scanf("%d",&OpcaoMenu);

     switch(OpcaoMenu){
        case 1:
            ExibirCardapio(Li, ValorTotal);
            break;
        case 2:
            ExibirMenuFinal(ValorTotal);
            break;
        case 3:
            MenuGerente(Li, senhagerente);
            break;
        case 0:
            if(*ValorTotal == 0){
                printf("Saindo do sistema...\n\n");
                sleep(1.2);
                printf("Volte sempre!\n");
            } else{
                printf("!!!Só é possível sair do sistema após finalizar o pagamento!!\n");
                sleep(2);
                ExibirMenuFinal(ValorTotal);
                return 1;
            }
            break;
        default:
            printf("\n!!!OPÇÃO INVÁLIDA!!!\n");
            sleep(2);
            break;
    }

    return OpcaoMenu;
}

// Percorre a lista de produtos e exibe o cardápio
// Controla o fluxo de pedidos e atualiza o valor total da conta

void ExibirCardapio(struct produto **Li, float *ValorTotal){

    int OpcaoMenu;

    do{

        printf("\n===== CARDÁPIO =====\n\n");
        printf("|Índice|    Especificação   |Código|   Preço  |\n");
        printf("|:-----|:-------------------|:-----|:---------|\n");

        struct produto *Auxiliar = *Li;

            int i =1;

            while(Auxiliar != NULL){

            printf("| %-4d | %-18s | %-4d | R$ %.2f |\n",
                i,Auxiliar->nome,Auxiliar->codigo,Auxiliar->preco);

            Auxiliar = Auxiliar->proximo;
            i++;

        }

        printf("|---------------------------------------------|\n");
        printf("|Digite 0(ZERO) para sair                     |\n\n");

        OpcaoMenu = FazerPedido(Li, ValorTotal);

    }while(OpcaoMenu != 0);

}

// Processa a escolha do produto e a quantidade informada pelo usuário
// Atualiza o valor total do pedido com base no item selecionado

int FazerPedido(struct produto **Li, float *ValorTotal){

    struct produto *Auxiliar = *Li;
    int QuantidadeDeItens;
    int CodigoDoProduto;

        if(Auxiliar == NULL){
        printf("Cardápio vazio!\n");
        return 0;
        }

    
        printf("Digite o código do produto ou Zero para sair:\n");
        scanf("%d",&CodigoDoProduto);

            if (CodigoDoProduto == 0){
                printf("Voltando para o Menu...\n");
                sleep(1);
                return CodigoDoProduto;
             }

        while (Auxiliar->codigo != CodigoDoProduto){
            
            Auxiliar = Auxiliar->proximo;

            if(Auxiliar == NULL){
                printf("!!!ESSE PRODUTO NÃO ESTÁ NO CÁDAPIO!!!\n");
                sleep(2);
                return 1;
            }
        }    

    do{

        printf("Digite a quantidade do item selecionado\n");
        scanf("%d",&QuantidadeDeItens);

            if(QuantidadeDeItens <=0){
                printf("Essa quantidade não é válida! \n");
            }
            
    } while (QuantidadeDeItens <=0);


    *ValorTotal += Auxiliar->preco * QuantidadeDeItens;
    printf("\n%dx R$ %.2f = %.2f\n",QuantidadeDeItens, Auxiliar->preco, Auxiliar->preco * QuantidadeDeItens);
    sleep(2);

    return 1; 
    
    
}

// Exibe o menu de pagamento e controla o fluxo de quitação da conta
// Permite pagamentos parciais até que o valor total seja zerado

void ExibirMenuFinal(float *ValorTotal){

    int OpcaoMenuFinal=0;

    printf("\n//---Menu final---//\n\n");
    printf("Total á pagar R$: %.2f\n", *ValorTotal);

        if(*ValorTotal == 0){

            printf("Sua conta está zerada. Nada á pagar!\n\n");

        }
    do
    {
    printf("Escolha a forma de pagamento\n");
    printf("1.Dinheiro\n");
    printf("2.Crédito\n");
    printf("3.Débito\n");
    printf("4.Pix\n");

    scanf("%d",&OpcaoMenuFinal);

    switch (OpcaoMenuFinal)
    {
        case 1:
            printf("Pagamento em dinheiro:\n");
        
            FazerPagamentoDinheiro(ValorTotal);
            printf("Valor restante %.2f\n\n", *ValorTotal);

            break;
        case 2:
            printf("Pagamento no crédito:\n");

            FazerPagamentoParcelado(ValorTotal);
            printf("Valor restante %.2f\n\n", *ValorTotal);

            break;
    
        case 3:
            printf("Pagamento no débito:\n");
        
            FazerPagamentoEletronico(ValorTotal);
            printf("Valor restante %.2f\n\n", *ValorTotal);

            break;

        case 4:
            printf("Pagamento no pix:\n");
        
            FazerPagamentoEletronico(ValorTotal);
            printf("Valor restante %.2f\n\n", *ValorTotal);

            break;
    
        default:
            break;
    }


    } while (*ValorTotal > 0);
    
    printf("Sua conta foi paga com sucesso!\n");

}

// Processa o pagamento em dinheiro
// Valida o valor informado, calcula o troco e quita a conta

float FazerPagamentoDinheiro(float *ValorTotal){
    float ValorPgtoDinheiro;

    do{
        printf("Digite o valor em R$ que será pago:\n");
        scanf("%f",&ValorPgtoDinheiro);
        
        if(ValorPgtoDinheiro <= 0){
            printf("Esse valor é inválido! Digite um valor positivo.\n");
        }
        else if(ValorPgtoDinheiro < *ValorTotal){
            printf("Valor insuficiente! Falta R$ %.2f para completar o pagamento.\n", *ValorTotal - ValorPgtoDinheiro);
        }

    }while(ValorPgtoDinheiro <= 0 || ValorPgtoDinheiro < *ValorTotal);

    float troco = ValorPgtoDinheiro - *ValorTotal;

    if(troco > 0){
        printf("Troco: R$ %.2f\n", troco);
    } else {
        printf("Pagamento exato! Sem troco.\n");
    }
    
    *ValorTotal = 0;
    sleep(2);
    return ValorPgtoDinheiro;

    
}

// Processa pagamentos eletrônicos (débito ou pix)
// Permite pagamentos parciais e atualiza o valor restante da conta

float FazerPagamentoEletronico(float *ValorTotal){
    float ValorPGTO;

    do{
        printf("Digite o valor em R$ que será pago:\n");
        scanf("%f",&ValorPGTO);
        if(ValorPGTO<=0){
            printf("Esse valor é inválido! \n");
        }

        if(ValorPGTO > *ValorTotal){
            printf("O valor a ser pago é maior do que o valor da conta!");
        }
    }while(ValorPGTO <=0 || ValorPGTO > *ValorTotal);
    
    *ValorTotal = *ValorTotal - ValorPGTO;
    
    sleep(2);
    return ValorPGTO;

    
}

// Simula pagamento parcelado no crédito a partir de pagamento eletrônico
// Calcula e exibe o valor das parcelas

void FazerPagamentoParcelado(float *ValorTotal){

    int parcelas;
    float ValorDoPagamento;
    do{

        printf("Digite a quantidade de parcelas\n");
        scanf("%d",&parcelas);

        if(parcelas<=0){
            printf("As aprcelas não podem ser zero ou valores negativos! \n");
        }

    }while(parcelas<=0);
   

    ValorDoPagamento = FazerPagamentoEletronico(ValorTotal);

    printf("Valor do pagamento %dX R$ %.2f\n\n",parcelas,ValorDoPagamento/parcelas);

    sleep(2);
}