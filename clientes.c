#include <stdio.h>
#include <string.h>
#include "clientes.h"

#define MAX_CLIENTES 5000

// Função auxiliar para carregar os clientes do ficheiro txt para a memória
int carregarClientes(Cliente lista[]) {
    FILE *arquivo = fopen("dados/clientes.txt", "r");
    int total = 0;

    if (arquivo == NULL) {
        arquivo = fopen("dados/clientes.txt", "w");
        if (arquivo != NULL) {
            fclose(arquivo);
        }
        return 0;
    }

    while (total < MAX_CLIENTES && fscanf(arquivo, "%49s %19s %14s", lista[total].nome, lista[total].telefone, lista[total].cpf) == 3) {
        total++;
    }
    
    fclose(arquivo);
    return total;
}

// Função auxiliar para salvar um novo cliente no final do ficheiro
void salvarNovoCliente(Cliente c) {
    FILE *arquivo = fopen("dados/clientes.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %s %s\n", c.nome, c.telefone, c.cpf);
        fclose(arquivo);
    }
}

// Função auxiliar para reescrever o ficheiro inteiro (usado após exclusões)
void atualizarFicheiroClientes(Cliente lista[], int total) {
    FILE *arquivo = fopen("dados/clientes.txt", "w");
    if (arquivo != NULL) {
        int i;
        for (i = 0; i < total; i++) {
            fprintf(arquivo, "%s %s %s\n", lista[i].nome, lista[i].telefone, lista[i].cpf);
        }
        fclose(arquivo);
    }
}

void menuClientes(int tipoPerfilLogado) {
    // Validação de segurança: Apenas Admin (1) ou Atendente (2) podem aceder
    if (tipoPerfilLogado == 0) {
        printf("\n[ACESSO NEGADO] Deve efetuar login primeiro para gerenciar clientes!\n");
        return;
    }

    int opcao;
    Cliente listaClientes[MAX_CLIENTES];
    int totalClientes = 0;

    totalClientes = carregarClientes(listaClientes);

    do {
        printf("\n========================================\n");
        printf("         GESTAO DE CLIENTES             \n");
        printf("========================================\n");
        printf("1. Consultar Cliente (por CPF)\n");
        printf("2. Registar Novo Cliente\n");
        printf("3. Excluir Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch(opcao) {
            case 1: { // Consultar
                printf("\n--- CONSULTAR CLIENTE ---\n");
                if (totalClientes == 0) {
                    printf("Nao ha clientes registados no sistema.\n");
                    break;
                }
                char cpfBusca[15];
                printf("Digite o CPF a procurar: ");
                scanf("%s", cpfBusca);

                int encontrado = -1;
                int i;
                for (i = 0; i < totalClientes; i++) {
                    if (strcmp(listaClientes[i].cpf, cpfBusca) == 0) {
                        encontrado = i;
                        break;
                    }
                }

                if (encontrado != -1) {
                    printf("\n[ENCONTRADO] Cliente ja cadastrado!\n");
                    printf("Nome     : %s\n", listaClientes[encontrado].nome);
                    printf("Telefone : %s\n", listaClientes[encontrado].telefone);
                    printf("CPF      : %s\n", listaClientes[encontrado].cpf);
                } else {
                    printf("\n[INFO] Cliente com CPF '%s' nao encontrado.\n", cpfBusca);
                }
                break;
            }

            case 2: { // Cadastrar
                if (totalClientes < MAX_CLIENTES) {
                    printf("\n--- REGISTO DE NOVO CLIENTE ---\n");
                    Cliente novo;
                    
                    printf("Nome (sem espacos, ex: Joao): ");
                    scanf("%s", novo.nome);
                    printf("Telefone: ");
                    scanf("%s", novo.telefone);
                    printf("CPF: ");
                    scanf("%s", novo.cpf);

                    // Verifica se o CPF ja existe antes de salvar
                    int duplicado = 0;
                    int i;
                    for (i = 0; i < totalClientes; i++) {
                        if (strcmp(listaClientes[i].cpf, novo.cpf) == 0) {
                            duplicado = 1;
                            break;
                        }
                    }

                    if (duplicado) {
                        printf("\n[ERRO] Ja existe um cliente registado com este CPF!\n");
                    } else {
                        listaClientes[totalClientes] = novo;
                        salvarNovoCliente(novo);
                        totalClientes++;
                        printf("\n[SUCESSO] Cliente registado e gravado no disco!\n");
                    }
                } else {
                    printf("\n[AVISO] Limite maximo de clientes atingido!\n");
                }
                break;
            }

            case 3: { // Excluir
                printf("\n--- EXCLUIR CLIENTE ---\n");
                if (totalClientes == 0) {
                    printf("Nao ha clientes para excluir.\n");
                    break;
                }

                char cpfExcluir[15];
                printf("Digite o CPF do cliente a excluir: ");
                scanf("%s", cpfExcluir);

                int pos = -1;
                int i;
                for (i = 0; i < totalClientes; i++) {
                    if (strcmp(listaClientes[i].cpf, cpfExcluir) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos != -1) {
                    // Desloca os elementos seguintes para tras
                    for (i = pos; i < totalClientes - 1; i++) {
                        listaClientes[i] = listaClientes[i + 1];
                    }
                    totalClientes--;
                    
                    // Atualiza o ficheiro em disco
                    atualizarFicheiroClientes(listaClientes, totalClientes);
                    printf("\n[SUCESSO] Cliente removido com sucesso!\n");
                } else {
                    printf("\n[ERRO] Cliente com este CPF nao foi encontrado.\n");
                }
                break;
            }

            case 0:
                printf("\nA retornar ao Menu Principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}