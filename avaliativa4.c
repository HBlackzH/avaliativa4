#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum{
    ALCOOL,
    DIESEL,
    GASOLINA
} Combustivel;

typedef struct Veiculo
{
    char proprietario[50];
    Combustivel combustivel;
    char modelo[50];
    char cor[20];
    char nChassi[17];
    int ano;
    char placa[7]; 
    struct Veiculo *prox;
} Veiculo;

Combustivel validaCombustivel(char combustivel)
{
    switch (combustivel)
    {
    case 'a':
        return ALCOOL;
    case 'd':
        return DIESEL;
    case 'g':
        return GASOLINA;
    default:
        printf("Combustivel invalido! Tente novamente\n");
        exit(EXIT_FAILURE);
    }
}

Veiculo *criarVeiculo(char proprietario[], Combustivel combustivel, 
        char modelo[], char cor[], char nChassi[17], int ano, char placa[])
{
    Veiculo *novoVeiculo = (Veiculo *)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL)
    {
        perror("Erro ao alocar memória para o veículo");
        exit(EXIT_FAILURE);
    }

    // Copiar os campos para o novo veículo
    strcpy(novoVeiculo->proprietario, proprietario);
    novoVeiculo->combustivel = combustivel;
    strcpy(novoVeiculo->modelo, modelo);
    strcpy(novoVeiculo->cor, cor);
    stpcpy(novoVeiculo->nChassi, nChassi);
    novoVeiculo->ano = ano;
    strcpy(novoVeiculo->placa, placa);
    novoVeiculo->prox = NULL;

    return novoVeiculo;
}

int validarPlaca(char placa[])
{
    if (strlen(placa) != 7)
    {
        printf("A placa nao possui 7 caracteres.\n");
        return 0;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (!((placa[i] >= 'A' && placa[i] <= 'Z') || (placa[i] >= 'a' && placa[i] <= 'z')))
        {
            printf("Os tres primeiros caracteres nao sao alfabeticos.\n");
            return 0;
        }
    }

    for (int i = 3; i < 7; ++i)
    {
        if (!(placa[i] >= '0' && placa[i] <= '9'))
        {
            printf("Os quatro ultimos caracteres nao sao numericos.\n");
            return 0;
        }
    }

    printf("Placa valida!\n");
    return 1;
}

void cadastrarVeiculo(Veiculo **lista)
{
    char proprietario[50];
    Combustivel combustivel;
    char modelo[50];
    char cor[20];
    char nChassi[17];
    int ano;
    char placa[7];

    printf("Proprietário: ");
    scanf("%s", proprietario);
    printf("Combustível (a - Álcool, d - Diesel, g - Gasolina): ");
    scanf(" %c", &combustivel);
    combustivel = validaCombustivel(combustivel);
    printf("Modelo: ");
    scanf("%s", modelo);
    printf("Cor: ");
    scanf("%s", cor);
    printf("Número do Chassi: ");
    scanf("%s", nChassi);
    printf("Ano: ");
    scanf("%d", &ano);
    int placaValida;
    do
    {
        printf("Placa: (somente 7 caracteres)");
        scanf("%s", placa);
        placaValida = validarPlaca(placa);

    } while (!placaValida);
    validarPlaca(placa);

    Veiculo *novoVeiculo = criarVeiculo(proprietario, combustivel, modelo, cor, nChassi, ano, placa);

    novoVeiculo->prox = *lista;
    *lista = novoVeiculo;
}

void imprimirLista(Veiculo *lista)
{
    Veiculo *atual = lista;
    while (atual != NULL)
    {
        printf("Proprietário: %s\n", atual->proprietario);
        printf("Combustível: ");
        switch (atual->combustivel)
        {
        case ALCOOL:
            printf("Álcool\n");
            break;
        case DIESEL:
            printf("Diesel\n");
            break;
        case GASOLINA:
            printf("Gasolina\n");
            break;
        }
        printf("Modelo: %s\n", atual->modelo);
        printf("Cor: %s\n", atual->cor);
        printf("Número do Chassi: %.2s\n", atual->nChassi);
        printf("Ano: %d\n", atual->ano);
        printf("Placa: %s\n", atual->placa);
        printf("\n");

        atual = atual->prox;
    }
}
void funcaoA(Veiculo *lista)
{
    Veiculo *atual = lista;
    printf("Proprietarios cujos carros sao do ano de 2010 ou mais e que sejam movidos a diesel\n");

    while (atual != NULL)
    {
        if (atual->ano >= 2010 && atual->combustivel == DIESEL)
        {
            printf("Proprietário: %s\n", atual->proprietario);
            printf("Combustível: Diesel\n");
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("Número do Chassi: %.2s\n", atual->nChassi);
            printf("Ano: %d\n", atual->ano);
            printf("Placa: %s\n", atual->placa);
            printf("\n");
        }

        atual = atual->prox;
    }
}
void funcaoB(Veiculo *lista)
{
    Veiculo *atual = lista;
    printf("As placas que comecam com j e terminam com 0, 2, 4 ou 7\n");

    while (atual != NULL)
    {
        if (atual->placa[0] == 'j' && (atual->placa[6] == '0' ||
             atual->placa[6] == '2' || atual->placa[6] == '4' || atual->placa[6] == '7'))
        {
            printf("Placa: %s\n", atual->placa);
            printf("Proprietário: %s\n", atual->proprietario);
            printf("\n");
        }

        atual = atual->prox;
    }
}
void funcaoC(Veiculo *lista)
{
    Veiculo *atual = lista;
    printf("Modelo e cor dos veículos que as placas possuem vogal no "
            "segundo caractere e a soma de valores numericos da placa seja numero par\n");

    while (atual != NULL)
    {
        int somaN = 0;
        for (int i = 3; i < 7; i++)
        {
            somaN += atual->placa[i] - '0';
        }

        if ((atual->placa[1] == 'a' || atual->placa[1] == 'e' || atual->placa[1] == 'i' 
                || atual->placa[1] == 'o' || atual->placa[1] == 'u') && somaN % 2 == 0){
            printf("Modelo: %s\n", atual->modelo);
            printf("Cor: %s\n", atual->cor);
            printf("\n");
        }

        atual = atual->prox;
    }
}

void funcaoD(Veiculo *lista, char nChassi[])
{
    Veiculo *atual = lista;
    int encontrado = 0;

    while (atual != NULL)
    {
        int temZero = 0;
        for (int i = 0; i < 7; i++)
        {
            if (atual->placa[i] == '0')
            {
                temZero = 1;
                break;
            }
        }

        if (temZero == 0 && strcmp(atual->nChassi, nChassi) == 0)
        {
            printf("Troca de proprietário com o fornecimento do número do chassi "
            "apenas para carros com placas que não possuam nenhum dígito igual a zero\n");
            printf("Número do Chassi: %.2s\n", atual->nChassi);
            printf("Placa: %s\n", atual->placa);
            printf("Digite o novo proprietário: ");
            scanf("%s", atual->proprietario);
            printf("Troca de proprietário realizada com sucesso!\n");

            encontrado = 1;
            break;
        }
        atual = atual->prox;
    }

    if (!encontrado)
    {
        printf("Veículo com o número do chassi fornecido não encontrado ou placa possui dígito igual a zero.\n");
    }
}

int main(void)
{
    Veiculo *listaVeiculos = NULL;
    int opcao;

    do
    {
        printf("Escolha uma opcao\n");
        printf("1:Cadastrar veiculo\n");
        printf("2:Imprimir lista\n");
        printf("3:Funcao A\n");
        printf("4:Funcao B\n");
        printf("5:Funcao C\n");
        printf("6:Funcao D\n");
        printf("0:Sair\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarVeiculo(&listaVeiculos);
            break;
        case 2:
            imprimirLista(listaVeiculos);
            break;
        case 3:
            funcaoA(listaVeiculos);
            break;
        case 4:
            funcaoB(listaVeiculos);
            break;
        case 5:
            funcaoC(listaVeiculos);
            break;
        case 6:
            printf("Digite o número do Chassi para a troca de proprietário: ");
            char nChassi[20];
            scanf("%s", nChassi);
            funcaoD(listaVeiculos, nChassi);
            break;
        default:
            break;
        }
    } while (opcao != 0);

    while (listaVeiculos != NULL)
    {
        Veiculo *temp = listaVeiculos;
        listaVeiculos = listaVeiculos->prox;
        free(temp);
    }
}
