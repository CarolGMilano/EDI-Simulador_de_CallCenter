# Simulador de Atendimento de Chamadas com Prioridade

Projeto desenvolvido para a disciplina de Estrutura de Dados I, que consiste em um sistema de atendimento de chamadas telefônicas com filas de prioridade e histórico de chamadas.

## Sumário

- [Descrição do Projeto](#descrição-do-projeto)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Estruturas de Dados](#estruturas-de-dados)
- [Funcionalidades](#funcionalidades)
- [Compilação e Execução](#compilação-e-execução)
- [Demonstração do Sistema](#demonstração-do-sistema)

## Descrição do Projeto

Este projeto foi desenvolvido para a disciplina **Estrutura de Dados I** e consiste em um **Simulador de Atendimento de Chamadas com Prioridade para uma Central de Atendimento Telefônico**.

O objetivo é criar uma aplicação em linguagem C que utilize estruturas de dados dinâmicas — filas com prioridade para organizar as chamadas e pilhas para armazenar o histórico de atendimentos.

O sistema permite o cadastro de chamadas com diferentes níveis de prioridade, a organização das chamadas na fila conforme urgência, o atendimento das chamadas na ordem correta, o registro do histórico dos atendimentos realizados, e a geração de relatórios com estatísticas sobre o serviço prestado.

O contexto do projeto é uma central de atendimento que prioriza os chamados mais urgentes, garantindo que as reclamações graves ou cancelamentos sejam atendidos antes de dúvidas ou orientações gerais, otimizando o tempo e a eficiência do atendimento.


## Estrutura do Projeto

O projeto está organizado em pastas separadas para facilitar a manutenção e organização do código. A estrutura possui:

```
src/              
├── atendimento/   
│   ├── atendimento.h
│   └── atendimento.c
├── chamada/
│   ├── chamada.h
│   └── chamada.c
├── dados_teste/
│   ├── dados_teste.h
│   └── dados_teste.c
├── historico/
│   ├── historico.h
│   └── historico.c
├── model/
│   ├── prioridade.h
│   └── prioridade.c
└── main.c      
```
- **`chamada/`**  
  - **`chamada.h`**: cabeçalho com as definições das funções e estruturas para manipulação da fila de chamadas com prioridade.  
  - **`chamada.c`**: implementação das funções para criação, destruição, cadastro e remoção das chamadas na fila, além de exibição da fila de espera.

- **`dados_teste/`**
  - Contém dados de entrada fictícios e scripts simples para simular chamadas e facilitar o teste da aplicação durante o desenvolvimento.

- **`atendimento/`**  
  - **`atendimento.h`**: cabeçalho com as definições da função e da estrutura de atendimento.  
  - **`atendimento.c`**: implementação da função de atendimento de chamada por prioridade.

- **`historico/`**  
  - **`historico.h`**: cabeçalho com as definições das funções e estruturas para a pilha de histórico de atendimentos realizados.  
  - **`historico.c`**: implementação das funções de criação, destruição e empilhamento da pilha de histórico, além da listagem de atendimentos realizados e geração de relatório.

- **`model/`**  
  - **`prioridade.h`**: definição do enum de prioridades e funções auxiliares relacionadas (como conversão para string e tempo de atendimento).  
  - **`prioridade.c`**: implementação dessas funções auxiliares.

- **`main.c`**  
  - Arquivo principal que contém o menu de interação com o usuário, controlando o fluxo geral do programa.

## Estruturas de Dados

O projeto utiliza duas estruturas de dados principais para organizar as chamadas e atendimentos no sistema de Call Center:

- **Fila com prioridade usando lista simplesmente encadeada** para gerenciar as chamadas de atendimento. Cada nó armazena os dados de uma chamada e um ponteiro para o próximo nó na fila.

  ```
  typedef struct {
    char nomeCliente[MAX_NOME];
    char motivo[MAX_MOTIVO];
    Prioridade prioridade;
    Horario horario;
  } Chamada;
  ```

  ```
  typedef struct NoChamada {
    Chamada chamada;
    struct NoChamada *prox;
  } NoChamada;
  ```

  ```
  typedef struct {
    NoChamada* inicio;
    NoChamada* fim;
    Horario horarioUltimoCadastro;
  } FilaChamada;
  ```

- **Pilha para histórico de atendimentos usando lista simplesmente encadeada**, onde cada nó representa um atendimento realizado.

  ```
  typedef struct {
    Chamada chamada;
    Horario horarioFimAtendimento;
  } Atendimento;
  ```
  ```
  typedef struct NoAtendimento {
    Atendimento* atendimento;
    struct NoAtendimento* prox;
  } NoAtendimento;
  ```

  ```
  typedef struct {
    NoAtendimento* topo;
    Horario horarioUltimoAtendimento;
  } PilhaHistorico;
  ```
- **Enumeração para nível de prioridade**, que define três níveis distintos para as chamadas recebidas

  ```
  typedef enum {
    alta = 1,
    media = 2,
    baixa = 3
  } Prioridade;
  ```

## Funcionalidades

Abaixo, as funcionalidades implementadas, separadas por arquivo.

### 📞 chamadas.c

- **`criarFilaChamada`**  
  Cria uma nova fila para chamadas.  
- **`destruirFila`**  
  Libera toda a memória da fila de chamadas. 
- **`cadastrarChamada`**  
  Cadastra uma nova chamada posicionando na fila conforme prioridade.
- **`removerChamada`**  
  Remove a chamada com maior prioridade, ou seja, a que está no topo da fila. 
- **`exibirFilaEspera`**  
  Exibe a lista de espera das chamadas.  

### ✅ atendimento.c

- **`atenderProximaChamada`**  
  Atende a chamada do topo da fila, ou seja, a de maior prioridade.  

### 🧾 historico.c

- **`criarPilhaHistorico`**  
  Cria uma nova pilha para histórico de atendimentos.  
- **`destruirPilha`**  
  Libera toda a memória da pilha de atendimentos. 
- **`empilharAtendimentos`**  
  Empilha os atendimentos realizados por ordem de chegada.
- **`listarHistoricoAtendimentos`**  
  Lista todos os atendimentos realizados por ordem de atendimento. 
- **`gerarRelatorio`**  
  Gera relatório com os atendimentos realizados, quantidade de atendimentos por prioridade e média de tempo de espera para os atendimentos.   

## Compilação e Execução

1. Clone o repositório:  
```bash
git clone https://github.com/CarolGMilano/EDI-Simulador_de_CallCenter.git
```

2. Compile o projeto:

```bash
gcc chamada/chamada.c atendimento/atendimento.c historico/historico.c model/prioridade.c  dados_teste/dados_teste.c main.c -o sistemaCallCenter
```

3. Execute o projeto:

```bash
./sistemaCallCenter
```

## Demonstração do Sistema

📽️ [Clique aqui para assistir à demonstração no Google Drive](https://drive.google.com/file/d/1mjLi2nDO3YPNbhaah-eMtHdC03e-Y8eA/view?usp=sharing)

---

Este projeto foi desenvolvido por [Carolina Milano](https://github.com/CarolGMilano) como parte das atividades da disciplina de **Estrutura de Dados I** para o curso de graduação em **Análise e Desenvolvimento de Sistemas** da **Universidade Federal do Paraná - UFPR**.   
