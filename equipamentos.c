#include <stdio.h>
#include <string.h>
#include "equipamentos.h"

int clienteExiste(char *cpfBuscado) {
    FILE *arquivo = fopen("dados/clientes.txt", "r");
    if (arquivo == NULL) {
        arquivo = fopen("clientes.txt", "r");
    }

    if (arquivo == NULL) {
        return 0; 
    }

    char linha[256];
    char cpfLimpo[100];
    strcpy(cpfLimpo, cpfBuscado);
    cpfLimpo[strcspn(cpfLimpo, "\r\n")] = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') {
            continue;
        }

        char t1[100] = "", t2[100] = "", t3[100] = "";
        // Lê as 3 colunas da linha: Nome, CPF/Telefone e o ID/Número (ex: 1)
        sscanf(linha, "%s %s %s", t1, t2, t3);

        t1[strcspn(t1, "\r\n")] = 0;
        t2[strcspn(t2, "\r\n")] = 0;
        t3[strcspn(t3, "\r\n")] = 0;

        // Compara com qualquer uma das 3 colunas (garantindo que apanha o '1' da terceira coluna)
        if (strcmp(t1, cpfLimpo) == 0 || strcmp(t2, cpfLimpo) == 0 || strcmp(t3, cpfLimpo) == 0) {
            fclose(arquivo);
            return 1; // Cliente encontrado!
        }
    }

    fclose(arquivo);
    return 0; 
}
// Função para gerar automaticamente o próximo número de série sequencial
int gerarProximoNumeroSerie() {
    FILE *arquivo = fopen("dados/equipamentos.txt", "r");
    if (arquivo == NULL) {
        return 1; // Se o ficheiro não existe, este é o primeiro equipamento (Série 1)
    }

    char linha[256];
    int ultimoId = 0;
    char cpf[20];
    int serie;
    char tipo[30], marca[30], modelo[40];

    // Lê todas as linhas para encontrar o maior número de série já registado
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%s %d %s %s %s", cpf, &serie, tipo, marca, modelo) >= 2) {
            if (serie > ultimoId) {
                ultimoId = serie;
            }
        }
    }

    fclose(arquivo);
    return ultimoId + 1; // Retorna o próximo número sequencial
}

// Função para salvar o equipamento no ficheiro dados/equipamentos.txt
void salvarEquipamento(Equipamento eq) {
    FILE *arquivo = fopen("dados/equipamentos.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %d %s %s %s\n", eq.cpfCliente, eq.numeroSerie, eq.tipo, eq.marca, eq.modelo);
        fclose(arquivo);
    }
}

// Submenu do Módulo de Equipamentos
void menuEquipamentos() {
    int opcao;
    Equipamento eq;

    do {
        printf("\n===============================\n");
        printf("      MODULO DE EQUIPAMENTOS    \n");
        printf("===============================\n");
        printf("1. Cadastrar Novo Equipamento\n");
        printf("2. Consultar Equipamentos por CPF\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida! Insira um numero.\n");
            while (getchar() != '\n'); 
            opcao = -1;
            continue;
        }

        switch(opcao) {
            case 1:
                printf("\n--- CADASTRO DE EQUIPAMENTO ---\n");
                printf("CPF do Cliente Proprietario: ");
                scanf("%s", eq.cpfCliente);

                if (!clienteExiste(eq.cpfCliente)) {
                    printf("\n[ERRO] Cliente com o CPF '%s' nao encontrado! Cadastre o cliente primeiro.\n", eq.cpfCliente);
                    break;
                }

                // ATRIBUIÇÃO AUTOMÁTICA DO NÚMERO DE SÉRIE
                eq.numeroSerie = gerarProximoNumeroSerie();

                printf("Tipo de Equipamento (ex: Motosserra): ");
                scanf("%s", eq.tipo);
                printf("Marca (ex: Stihl): ");
                scanf("%s", eq.marca);
                printf("Modelo (ex: MS 170): ");
                scanf("%s", eq.modelo);

                salvarEquipamento(eq);
                printf("\n[SUCESSO] Equipamento registado com o Nro de Serie [%d] e vinculado ao CPF %s!\n", eq.numeroSerie, eq.cpfCliente);
                break;

            case 2:
                {
                    char cpfBusca[20];
                    printf("\n--- CONSULTAR EQUIPAMENTOS POR CPF ---\n");
                    printf("Digite o CPF do cliente: ");
                    scanf("%s", cpfBusca);

                    FILE *arquivo = fopen("dados/equipamentos.txt", "r");
                    if (arquivo == NULL) {
                        printf("\n[INFO] Nenhum equipamento registado no sistema.\n");
                        break;
                    }

                    char linha[256];
                    int encontrados = 0;

                    printf("\n--- APARELHOS DO CLIENTE (CPF: %s) ---\n", cpfBusca);
                    
                    // Lê linha a linha de forma segura e flexível
                    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') {
                            continue;
                        }

                        char cpfLido[20], serieLido[20], tipoLido[30], marcaLido[30], modeloLido[40];
                        
                        // Lê os 5 elementos da linha do equipamento
                        int lidos = sscanf(linha, "%s %s %s %s %s", cpfLido, serieLido, tipoLido, marcaLido, modeloLido);

                        if (lidos >= 5) {
                            // Compara o CPF do proprietário com o CPF pesquisado
                            if (strcmp(cpfLido, cpfBusca) == 0) {
                                printf("Nro Serie: %s | Tipo: %s | Marca: %s | Modelo: %s\n", 
                                       serieLido, tipoLido, marcaLido, modeloLido);
                                encontrados++;
                            }
                        }
                    }
                    fclose(arquivo);

                    if (encontrados == 0) {
                        printf("[INFO] Nenhum equipamento encontrado para este CPF.\n");
                    }
                }
                break;

            case 0:
                printf("\nA retornar ao Menu Principal...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}