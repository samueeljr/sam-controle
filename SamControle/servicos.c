#include <stdio.h>
#include <string.h>
#include "servicos.h"
#include "equipamentos.h"

// Adiciona esta linha para o compilador saber que a função existe noutro módulo:
int clienteExiste(char *cpfBuscado);
void salvarServico(Servico s) {
    FILE *arquivo = fopen("dados/servicos.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %d %d %s %.2f\n", s.cpfCliente, s.numeroSerieEquipamento, s.quantidade, s.descricao, s.precoFinal);
        fclose(arquivo);
    }
}

// 1. Registo de Serviço com itens múltiplos até digitar 0 na quantidade
void menuServicos() {
    int opcao;
    Servico s;

    do {
        printf("\n===============================\n");
        printf("      MODULO DE SERVICOS       \n");
        printf("===============================\n");
        printf("1. Registar Ficha de Servico\n");
        printf("2. Consultar Servicos por Equipamento\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }

        switch(opcao) {
            case 1:
                {
                    printf("\n--- NOVO REGISTO DE SERVICO ---\n");
                    printf("CPF do Cliente Proprietario: ");
                    scanf("%s", s.cpfCliente);

                    // Valida se o cliente existe (importado do equipamentos.h)
                    if (!clienteExiste(s.cpfCliente)) {
                        printf("\n[ERRO] Cliente com o CPF '%s' nao encontrado!\n", s.cpfCliente);
                        break;
                    }

                    // Mostra as máquinas deste cliente
                    FILE *arqEq = fopen("dados/equipamentos.txt", "r");
                    if (arqEq == NULL) {
                        printf("\n[ERRO] Nao existem equipamentos registados no sistema.\n");
                        break;
                    }

                    char cpfLido[20], tipoLido[30], marcaLido[30], modeloLido[40], linha[256];
                    int serieLido, encontradas = 0;

                    printf("\n--- Maquinas do Cliente (CPF: %s) ---\n", s.cpfCliente);
                    while (fgets(linha, sizeof(linha), arqEq) != NULL) {
                        if (sscanf(linha, "%s %d %s %s %s", cpfLido, &serieLido, tipoLido, marcaLido, modeloLido) >= 5) {
                            if (strcmp(cpfLido, s.cpfCliente) == 0) {
                                printf("-> Numero Serie: [%d] | Tipo: %s | Marca: %s | Modelo: %s\n", serieLido, tipoLido, marcaLido, modeloLido);
                                encontradas++;
                            }
                        }
                    }
                    fclose(arqEq);

                    if (encontradas == 0) {
                        printf("[AVISO] Este cliente nao possui maquinas registadas.\n");
                        break;
                    }

                    printf("\nDigite o Numero de Serie da maquina para o servico: ");
                    scanf("%d", &s.numeroSerieEquipamento);

                    printf("\n--- ADICIONAR ITENS AO SERVICO ---\n");
                    printf("Insira os itens (Digite Quantidade '0' para encerrar e somar o total):\n");

                    float precoUnitario;
                    float valorTotalServico = 0.0;

                    while (1) {
                        printf("\nQuantidade (ou 0 para terminar): ");
                        scanf("%d", &s.quantidade);

                        if (s.quantidade == 0) {
                            break;
                        }

                        printf("Descricao / Peca: ");
                        scanf("%s", s.descricao);

                        printf("Preco Unitario (R$): ");
                        scanf("%f", &precoUnitario);

                        float subtotal = s.quantidade * precoUnitario;
                        valorTotalServico += subtotal;

                        s.precoFinal = subtotal; 
                        salvarServico(s);

                        printf("[ITEM ADICIONADO] %d x %s - R$ %.2f (Subtotal acumulado: R$ %.2f)\n", 
                               s.quantidade, s.descricao, subtotal, valorTotalServico);
                    }

                    printf("\n[SUCESSO] Ficha de servico encerrada! Valor Total da Ordem: R$ %.2f\n", valorTotalServico);
                }
                break;

            case 2:
                {
                    int serieBusca;
                    printf("\n--- CONSULTAR SERVICOS POR NUMERO DE SERIE ---\n");
                    printf("Digite o Numero de Serie do equipamento: ");
                    scanf("%d", &serieBusca);

                    FILE *arquivo = fopen("dados/servicos.txt", "r");
                    if (arquivo == NULL) {
                        printf("\n[INFO] Nenhum servico registado no sistema.\n");
                        break;
                    }

                    char linha[256];
                    Servico sLido;
                    int count = 0;
                    float somaTotalGeral = 0.0;

                    printf("\n--- HISTORICO DE SERVICOS DA MAQUINA [%d] ---\n", serieBusca);
                    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                        if (sscanf(linha, "%s %d %d %s %f", sLido.cpfCliente, &sLido.numeroSerieEquipamento, &sLido.quantidade, sLido.descricao, &sLido.precoFinal) >= 5) {
                            if (sLido.numeroSerieEquipamento == serieBusca) {
                                printf("- %d x %s | Preco: R$ %.2f\n", sLido.quantidade, sLido.descricao, sLido.precoFinal);
                                somaTotalGeral += sLido.precoFinal;
                                count++;
                            }
                        }
                    }
                    fclose(arquivo);

                    if (count > 0) {
                        printf("----------------------------------------\n");
                        printf("VALOR TOTAL GASTO NA MAQUINA: R$ %.2f\n", somaTotalGeral);
                    } else {
                        printf("[INFO] Nenhum historico de servico encontrado para este equipamento.\n");
                    }
                }
                break;

            case 0:
                printf("\nA retornar...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

// 2. Portal do Cliente
void portalClienteServicos() {
    char cpfCliente[20];
    printf("\n===========================================\n");
    printf("     PORTAL DE CONSULTA DO CLIENTE         \n");
    printf("===========================================\n");
    printf("Digite o seu CPF para ver as suas maquinas: ");
    scanf("%s", cpfCliente);

    if (!clienteExiste(cpfCliente)) {
        printf("\n[ERRO] CPF nao encontrado no sistema.\n");
        return;
    }

    FILE *arqEq = fopen("dados/equipamentos.txt", "r");
    if (arqEq == NULL) {
        printf("\n[INFO] Nao existem equipamentos registados.\n");
        return;
    }

    char linha[256], cpfLido[20], tipo[30], marca[30], modelo[40];
    int serie, temEquipamentos = 0;

    printf("\n========================================\n");
    printf("   OS SEUS APARELHOS E SERVICOS (CPF: %s)\n", cpfCliente);
    printf("========================================\n");

    while (fgets(linha, sizeof(linha), arqEq) != NULL) {
        if (sscanf(linha, "%s %d %s %s %s", cpfLido, &serie, tipo, marca, modelo) >= 5) {
            if (strcmp(cpfLido, cpfCliente) == 0) {
                temEquipamentos = 1;
                printf("\n[Maquina #%d] %s %s %s\n", serie, marca, modelo, tipo);
                
                FILE *arqServ = fopen("dados/servicos.txt", "r");
                if (arqServ != NULL) {
                    char linhaServ[256];
                    Servico serv;
                    int temServico = 0;
                    float totalMaquina = 0.0;

                    while (fgets(linhaServ, sizeof(linhaServ), arqServ) != NULL) {
                        if (sscanf(linhaServ, "%s %d %d %s %f", serv.cpfCliente, &serv.numeroSerieEquipamento, &serv.quantidade, serv.descricao, &serv.precoFinal) >= 5) {
                            if (serv.numeroSerieEquipamento == serie) {
                                printf("   -> %d x %s | R$ %.2f\n", serv.quantidade, serv.descricao, serv.precoFinal);
                                totalMaquina += serv.precoFinal;
                                temServico = 1;
                            }
                        }
                    }
                    fclose(arqServ);
                    if (temServico) {
                        printf("   [Total Gasto neste Aparelho: R$ %.2f]\n", totalMaquina);
                    } else {
                        printf("   -> Nenhum servico registado para este aparelho.\n");
                    }
                }
            }
        }
    }
    fclose(arqEq);

    if (!temEquipamentos) {
        printf("[INFO] Nao existem equipamentos associados a este CPF.\n");
    }
    printf("----------------------------------------\n");
}