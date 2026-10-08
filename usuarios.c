#include <stdio.h>
#include <string.h>
#include "usuarios.h"

extern int perfilGlobalLogado; // Declaração da variável global de sessão

typedef struct {
    char login[30];
    char senha[30];
    int tipoPerfil; // 1 - Administrador, 2 - Usuario Comum
} Usuario;

// Função auxiliar para carregar os utilizadores do ficheiro txt para a memória
int carregarUsuarios(Usuario lista[]) {
    FILE *arquivo = fopen("dados/usuarios.txt", "r");
    int total = 0;

    // se o ficheiro não existir, cria um novo
    if (arquivo == NULL) {
        arquivo = fopen("dados/usuarios.txt", "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "admin 1234 1\n");
            strcpy(lista[0].login, "admin");
            strcpy(lista[0].senha, "1234");
            lista[0].tipoPerfil = 1;
            total = 1;
            fclose(arquivo);
        }
        return total;
    }

    // Lê os dados do ficheiro linha a linha até atingir o limite ou o fim do ficheiro
    while (total < 10 && fscanf(arquivo, "%s %s %d", lista[total].login, lista[total].senha, &lista[total].tipoPerfil) == 3) {
        total++;
    }
    
    fclose(arquivo);
    return total;
}
// Função auxiliar para salvar um novo utilizador no final do ficheiro txt
void salvarNovoUsuario(Usuario u) {
    FILE *arquivo = fopen("dados/usuarios.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s %s %d\n", u.login, u.senha, u.tipoPerfil);
        fclose(arquivo);
    };
}

void menuUsuarios(){
    int opcaoUsuario;
    Usuario listaUsuarios[10];
    int totalUsuarios = 0;
    int encontrou = -1;

    //carrega os utilizadores gravados no ficheiro assim que o módulo abre
    totalUsuarios = carregarUsuarios(listaUsuarios);

    char loginInput[30];
    char senhaInput[30];
    int logadoIndex = -1;
    int i;
    int encontrado;

    do{
        printf("\n===============================\n");
        printf("        MODULO DE UTILIZADORES       \n");
        printf("===============================\n");
        if (logadoIndex == -1){
            printf("Status: Nao autenticado");
        } else {
            printf("Status: Logado com '%s' (%s)\n",
                listaUsuarios[logadoIndex].login,
                (listaUsuarios[logadoIndex].tipoPerfil == 1) ? "Administrador" : "Atendente");
        }
        printf("----------------------------------------\n");
        printf("1. Efetuar Login\n");
        printf("2. Registar Novo Utilizador (Apenas Admin)\n");
        printf("3. Terminar Sessao\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcaoUsuario);

        switch(opcaoUsuario) {
            // case 1 ==============================================================================
            case 1:
                printf("\n--- AUTORIZACAO DE SISTEMA ---\n");
                printf("LOGIN: ");
                scanf("%s", loginInput);
                printf("SENHA: ");
                scanf("%s", senhaInput);

                encontrado = -1;
                for (i = 0; i < totalUsuarios; i++) {
                    if (strcmp(listaUsuarios[i].login, loginInput) == 0 &&
                        strcmp(listaUsuarios[i].senha, senhaInput) == 0) {
                        encontrado = i;
                        break;
                    }
                }
                
                if (encontrado != -1) {
                    logadoIndex = encontrou;
                    // Atualiza a sessão global com base no utilizador logado
                    perfilGlobalLogado = listaUsuarios[logadoIndex].tipoPerfil;
                    printf("\n[SUCESSO] Acesso autorizado!\n");
                } else {
                    printf("\n[ERRO] Login ou senha incorretos!\n");
                }
                break;
             //FIM case 1 ==========================================================================
            // case 2 ==============================================================================
            case 2:
            if (logadoIndex != -1 && listaUsuarios[logadoIndex].tipoPerfil == 1){
                if (totalUsuarios < 15) { //AQUI DEFINe O LIMITE DE CADASTRO DE ATENDENTE/ADMIN
                    printf("\n--- REGISTO DE NOVO UTILIZADOR ---\n");
                    printf("Novo Login: ");
                    scanf("%s", listaUsuarios[totalUsuarios].login);
                    printf("Nova Senha: ");
                    scanf("%s", listaUsuarios[totalUsuarios].senha);
                    printf("Tipo de Perfil (1 - Administrador | 2 - Atendente): ");
                    scanf("%d", &listaUsuarios[totalUsuarios].tipoPerfil);

                     // Guarda permanentemente no ficheiro usuarios.txt
                    salvarNovoUsuario(listaUsuarios[totalUsuarios]);

                    totalUsuarios++;
                    printf("\n[SUCESSO] Utilizador registado e gravado no disco!\n");
                    } else {
                        printf("\n[AVISO] Limite maximo de utilizadores atingido!\n");
                    }
                } else {
                    printf("\n[ACESSO NEGADO] Apenas um Administrador autenticado pode registar utilizadores!\n");
                }
                break;
            // FIM case 2 ==============================================================================
            // case 3 ==================================================================================
            case 3:
                if (logadoIndex != -1) {
                    logadoIndex = -1;
                    perfilGlobalLogado = 0;
                    printf("\n[INFO] Sessao terminada com sucesso.\n");
                } else {
                    printf("\n[INFO] Nao ha nenhuma sessao ativa.\n");
                }
                break;
            // FIM case 3 ==============================================================================
            // case 0 ==================================================================================
            case 0:
                printf("\nA retornar ao Menu Principal...\n");
                break;
            // FIM case 0 ==============================================================================
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcaoUsuario != 0);
}