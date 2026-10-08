#ifndef EQUIPAMENTOS_H
#define EQUIPAMENTOS_H

typedef struct {
    char cpfCliente[20];      // Vínculo com o cliente
    int numeroSerie;          // Gerado automaticamente pelo sistema (1, 2, 3...)
    char tipo[30];            // Ex: Motosserra, Roçadeira, Soprador (RF02)
    char marca[30];           // Ex: Husqvarna, Stihl (RF02)
    char modelo[40];          // Ex: MS 170, FS 55 (RF02)
} Equipamento;

void menuEquipamentos();

#endif