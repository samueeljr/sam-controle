# User Stories

## US01 – Gerenciar Usuários

PBI relacionado: HU01

Como administrador, quero cadastrar e gerenciar usuários, para controlar quem tem acesso ao sistema.

### Critérios de aceitação

- Login com credenciais válidas libera o menu de acordo com o nível de acesso
- Credenciais inválidas exibem mensagem de erro e pedem os dados novamente
- A opção "Gerenciar Usuários" aparece somente para o administrador
- Não é possível cadastrar dois usuários com o mesmo login
- A senha nunca é exibida na consulta de usuários

## US02 – Gerenciar Clientes

PBI relacionado: HU02

Como atendente, quero cadastrar, consultar, alterar e excluir clientes, para que a oficina tenha um registro organizado de quem são os donos dos equipamentos.

### Critérios de aceitação

- O cadastro exige nome, CPF e telefone
- CPF inválido ou já cadastrado é recusado com mensagem clara
- É possível consultar, alterar e excluir clientes
- Os dados continuam salvos depois que o programa é fechado

## US03 – Gerenciar Equipamentos

PBI relacionado: HU03

Como atendente da assistência técnica, quero cadastrar ou selecionar máquinas e vinculá-las ao respectivo cliente, para que eu possa iniciar o atendimento e o registro do orçamento.

### Critérios de aceitação

- O equipamento é cadastrado com tipo, marca e modelo
- Todo equipamento fica vinculado a um cliente já cadastrado
- O número de série é gerado automaticamente
- Os equipamentos de um cliente podem ser listados
- A exclusão de um cliente não deixa equipamentos sem dono

## US04 – Consultar Serviços Finalizados

PBI relacionado: HU04

Como atendente ou cliente da assistência técnica, quero registrar, editar e consultar as fichas de serviço e pedidos finalizados, para que haja controle dos reparos e acesso seguro ao histórico de cada máquina.

### Critérios de aceitação

- A ficha só é registrada para um equipamento já cadastrado
- A ficha guarda descrição do serviço, observações e preço final
- Os dados da ficha são validados antes de gravar
- O histórico de serviços de cada equipamento pode ser consultado, com serviços, orçamentos e preços
- O cliente enxerga apenas as fichas finalizadas dos seus próprios equipamentos
