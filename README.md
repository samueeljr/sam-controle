# SAM Controle

Sistema desktop de console em linguagem C para gestão de clientes, equipamentos e serviços da oficina SAMáquinas e Motores, desenvolvido como Projeto Integrado Multidisciplinar (PIM II) do curso de Análise e Desenvolvimento de Sistemas da UNIP.

## Como executar

1. Compile dentro da pasta `SamControle` (Windows, com MinGW/GCC, Dev-C++ ou Code::Blocks):
   ```bash
   cd SamControle
   gcc *.c -o sam_controle.exe
   ```
   Também é possível usar o `sam_controle.exe` já incluído na pasta.
2. Execute **de dentro da pasta `SamControle`**, pois os dados ficam em `dados/`:
   ```bash
   sam_controle.exe
   ```
3. Acesse o menu `1. Gerenciar Usuarios` e faça login com o usuário `admin`, senha `1234` (Administrador).
4. Use os menus numerados para gerenciar usuários, clientes, equipamentos e serviços. Digite os campos de texto sem espaços (use `_`).

## Documentação

| Documento | Conteúdo |
|---|---|
| [Requisitos.md](./docs/Scrum/Requisitos.md) | Fonte oficial dos requisitos (RF, RNF, RN) |
| [Backlog.md](./docs/Scrum/Backlog.md) | Backlog do produto, ligado aos requisitos e às sprints |
| [user-stories.md](./docs/Scrum/Backlog.md) | User stories detalhando cada item do backlog |
| [Definition-of-Done.md](./docs/Scrum/Definition-of-Done.md) | Definition of Done da equipe |
| [sprints/](./docs/Scrum/Sprints) | Um documento por Sprint (objetivo, tarefas, review, retrospectiva) |

Documentação acadêmica completa (Word/PDF) em [/docs/README.md](./docs/).

### Integrantes do grupo

| Papel | Nome | RA |
|---|---|---|
| P.O | Samuel de Oliveira Júnior | R318JE0 |
| S.M | Geovana Ferreira Mira | R314685 |
| Dev | Ana Júlia Tenório Pedroso | R277933 |
| Dev | Diogo Issao Andrade Okuda | H967GH9 |
| Dev | Gustavo Paiva de Oliveira | R240IE4 |
| Dev | João Vitor Soares de Moraes | R344290 |

<!-- ## Estrutura do Repositório

```text
sam-controle/
├── README.md                  <-- Apresentação principal do projeto
├── SamControle/               <-- Código-fonte em C (módulos do sistema)
│   ├── main.c
│   ├── usuarios.c
│   ├── usuarios.h
│   ├── clientes.c
│   ├── clientes.h
│   ├── equipamentos.c
│   ├── equipamentos.h
│   ├── servicos.c
│   ├── servicos.h
│   ├── sam_controle.exe       <-- Executável compilado
│   └── dados/                 <-- Ficheiros .txt gerados (ex: usuarios.txt)
└── docs/                      <-- Toda a documentação académica e de gestão
    ├── README.md              <-- Índice de navegação da documentação
    ├── manual-pim-II/         <-- Relatório acadêmico oficial completo (Word/PDF)
    ├── scrum/                 <-- Requisitos (RF, RNF) e Histórias de Utilizador
    └── diagramas/             <-- Imagens exportadas do Astah (Casos de Uso, Classes)
        ├── caso-de-uso.png
        └── diagrama-classes.png
```
ADICIONAR NO README ASSIM QUE ESTIVER COMPLETO E ATUALIZADO!
-->

