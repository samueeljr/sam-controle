#ifndef SERVICOS_H
#define SERVICOS_H

typedef struct {
    int idServico;
    char cpfCliente[15];
    int numeroSerieEquipamento;
    int quantidade;
    char descricao[100];
    float precoUnitario;
    float precoFinal;
} Servico;

void menuServicos();

#endif