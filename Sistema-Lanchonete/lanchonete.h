#ifndef LANCHONETE_H
#define LANCHONETE_H

typedef struct produto{

    int codigo;
    float preco;
    char nome[20];
    struct produto *proximo;

}produto;  


// protótipo model
float FazerPagamentoDinheiro(float *valorTotal);
float FazerPagamentoEletronico(float *valorTotal);
void FazerPagamentoParcelado(float *valorTotal);

// protótipo view
void ExibirBoasVindas();
int ExibirMenuInicial(int *senhaGerente, struct produto **Li,float *valorTotal);
void ExibirCardapio(struct produto **Li, float *valorTotal);
void ExibirMenuFinal(float *valorTotal);
void MenuGerente(struct produto **Li, int *senhagerente);
void VerificarAcessoGerente(int *senhagerente);

// protótipo controler
int FazerPedido(struct produto **Li, float *ValorTotal);
void CriarNovoProduto(struct produto **Li);
void ExcluirProduto(struct produto **Li);

// validações
float InserirPrecoNovoProduto();
int InserirCodigoNovoProduto(struct produto **Li);
void InserirNomeNovoProduto(char nome[]);

// lista
void InserirFinalCardapio(struct produto **Li,int codigoProduto, float precoProduto, char nomeproduto[]);
void LiberarCardapio(struct produto **Li);


#endif