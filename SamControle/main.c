#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "usuarios.h"
#include "clientes.h"
#include "equipamentos.h"
#include "servicos.h"

// Variável global de sessão para controlar quem está logado no sistema
int perfilGlobalLogado = 1; // 0 - Não logado, 1 - Administrador, 2 - Atendente 

// Atualiza a assinatura do menuClientes para aceitar o parâmetro
void menuUsuarios();
void menuClientes(int tipoPerfilLogado); // CORRIGIDO AQUI
void menuEquipamentos();
void menuServicos();

int main() {
    int opcao;
    
    do {
        printf("\n==============================\n");
        printf("        SAM CONTROLE          \n");
        printf("==============================\n");
        printf("1. Gerenciar Usuarios\n");
        printf("2. Gerenciar Clientes\n");
        printf("3. Gerenciar Equipamentos\n");
        printf("4. Gerenciar Servicos\n");
        printf("0. Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                menuUsuarios();
                // Nota: se quiseres que o menuUsuarios atualize o perfilGlobalLogado, 
                // podes ajustar o menuUsuarios para devolver o tipo de perfil logado!
                break;
            case 2:
                menuClientes(perfilGlobalLogado);
                break;
            case 3:
                printf("Gerenciar Equipamentos selecionado.\n");
                break;
            case 4:
                printf("Gerenciar Servicos selecionado.\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}