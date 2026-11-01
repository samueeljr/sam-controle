#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct {
    char nome[50];
    char telefone[20];
    char cpf[15];
} Cliente;

// Declaração da função do menu de clientes recebendo o perfil logado
void menuClientes(int tipoPerfilLogado);

#endif