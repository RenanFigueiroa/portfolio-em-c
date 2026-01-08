# Sistema de Lanchonete — Linguagem C

Projeto desenvolvido em linguagem C com o objetivo de praticar conceitos de **Estrutura de Dados**, alocação dinâmica de memória e organização de código em módulos.

O sistema foi inspirado em uma atividade acadêmica cujo objetivo inicial era exercitar **estruturas de repetição**, mas foi expandido para incluir **listas simplesmente encadeadas**, controle de fluxo por menus e sistema de pagamento.

O sistema já inicia com um **cardápio pré-definido**, permitindo testar o funcionamento sem a necessidade de cadastrar produtos manualmente.

---

## 🎯 Objetivo do Projeto

- Consolidar o uso de ponteiros e ponteiros duplos
- Trabalhar com listas simplesmente encadeadas
- Aplicar alocação e liberação dinâmica de memória
- Simular um sistema real de pedidos e pagamentos
- Evoluir um exercício simples para um projeto funcional

---

## ⚙️ Funcionalidades

### 🧾 Cliente
- Visualização do cardápio
- Realização de pedidos com quantidade variável
- Cálculo automático do valor total
- Finalização do pedido
- Sistema de pagamento com:
  - Dinheiro (com cálculo de troco)
  - Débito
  - Pix
  - Crédito parcelado

### 🔐 Gerente
- Acesso protegido por senha
- Cadastro de novos produtos
- Exclusão de produtos existentes
- Alteração dinâmica do cardápio (lista encadeada)

---

## 🔑 Acesso ao Perfil do Gerente

Para acessar o **perfil do gerente**, utilize a senha padrão: 1234


---
## Como Compilar e Executar

### 🔧 Compilação
Utilizando o compilador GCC:  gcc main.c lanchonete.c -o lanchonete

## ▶️ Execução: 
./lanchonete

---
## 📚 Observações

Durante o desenvolvimento, foram utilizadas ferramentas de apoio (como IA) para auxiliar na compreensão de lógica e correção de erros, sempre priorizando o entendimento do código e a construção de soluções compatíveis com o nível atual de aprendizado.

Este projeto representa um processo de evolução técnica, não apenas um código final.
