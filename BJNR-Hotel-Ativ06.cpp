//BJNR-Hotel-Ativ06
//Bruna Samy Freming Quispilaya
//Joao Pedro Freitas Vilar
//Nathalia Pedraca Pinho
//Rafaella Castro Zandona Alves de Lima
//Controle de Reservas e Ocupação de Hotel

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct cadastro {
    char cpf[15];
    char nome[60];
    char endereco[200];
    char telefone[20];
    char email[50];
    char cafe_manha; // 'S' ou 'N'
    int  diaria;
    float servico_quarto;
} tipohospedes;

char tab[21][15];
tipohospedes hospedes[21][15];
//Funções principais do menu
void fInicializar();
void fMapaHotel();
void fCheckOut(int andar, int ap);
void fCReserva(int andar, int ap);
void fMapaReserva(int andar, int ap, int diaria);
void fCheckinComReserva();
void fCheckinSemReserva();
void fTaxaOcupacao();
void fCadastrarHospede(int andar, int ap);
void fVerApartamento(int andar, int ap);
void fServicoQuarto(int andar, int ap);
static int fValidar(int andar, int ap);

//Funções para situações novas
void fMudancaApartamento();
void fAbandonoSemCheckout();
void fCheckinReservaParente();
void fExtensaoEstadia();
void fErroCadastro();
void fContestacaoServicoQuarto();

//Submenus (agrupam as situacoes e reduzem o menu principal)
void fMenuCheckin();
void fMenuCheckout();
void fMenuReservas();
void fMenuGestaoApartamento();
void fMenuServicoQuarto();

int main()
{
    int opcao;

    fInicializar();

    do {
        system("cls");
        fMapaHotel();

        printf("\n1 - Check-in\n");
        printf("2 - Check-out\n");
        printf("3 - Reservas\n");
        printf("4 - Gestao de Apartamento\n");
        printf("5 - Servico de Quarto\n");
        printf("6 - Visualizar Ocupacao\n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                fMenuCheckin();
                break;

            case 2:
                fMenuCheckout();
                break;

            case 3:
                fMenuReservas();
                break;

            case 4:
                fMenuGestaoApartamento();
                break;

            case 5:
                fMenuServicoQuarto();
                break;

            case 6:
                printf("\n===========================================\n");
                printf("\tVisualizar Ocupacao e Reserva");
                printf("\n===========================================\n");
                fTaxaOcupacao();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
                system("pause");
        }

    } while (opcao != 0);

    return 0;
}

//Submenu de Check In
void fMenuCheckin()
{
    int opcao;

    do {
        printf("\n===========================================\n");
        printf("\tCHECK-IN\n");
        printf("===========================================\n");
        printf("1 - Sem Reserva\n");
        printf("2 - Com Reserva\n");
        printf("3 - Com Reserva de Parente\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                while (getchar() != '\n');
                fCheckinSemReserva();
                break;
            case 2:
                while (getchar() != '\n');
                fCheckinComReserva();
                break;
            case 3:
                while (getchar() != '\n');
                fCheckinReservaParente();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida.\n");
                system("pause");
        }
    } while (opcao != 0);
}

//Submenu de Check Out
void fMenuCheckout()
{
    int opcao, andar, ap;

    do {
        printf("\n===========================================\n");
        printf("\tCHECK-OUT\n");
        printf("===========================================\n");
        printf("1 - Checkout Normal\n");
        printf("2 - Abandono sem Checkout\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Andar (1-20): ");
                scanf("%d", &andar);
                printf("Apartamento (1-14): ");
                scanf("%d", &ap);
                fCheckOut(andar, ap);
                break;
            case 2:
                fAbandonoSemCheckout();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida.\n");
                system("pause");
        }
    } while (opcao != 0);
}

//Submenu de Reservas
void fMenuReservas()
{
    int opcao, andar, ap, diaria;

    do {
        printf("\n===========================================\n");
        printf("\tRESERVAS\n");
        printf("===========================================\n");
        printf("1 - Reservar Apartamento\n");
        printf("2 - Cancelar Reserva\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Andar (1-20): ");
                scanf("%d", &andar);
                printf("Apartamento (1-14): ");
                scanf("%d", &ap);
                printf("Diarias: ");
                scanf("%d", &diaria);
                while (getchar() != '\n');
                fMapaReserva(andar, ap, diaria);
                break;
            case 2:
                printf("Andar (1-20): ");
                scanf("%d", &andar);
                printf("Apartamento (1-14): ");
                scanf("%d", &ap);
                fCReserva(andar, ap);
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida.\n");
                system("pause");
        }
    } while (opcao != 0);
}

//Submenu de Gestao de Apartamento
void fMenuGestaoApartamento()
{
    int opcao, andar, ap;

    do {
        printf("\n===========================================\n");
        printf("\tGESTAO DE APARTAMENTO\n");
        printf("===========================================\n");
        printf("1 - Consultar Apartamento\n");
        printf("2 - Mudanca de Apartamento\n");
        printf("3 - Extensao de Estadia\n");
        printf("4 - Corrigir Erro de Cadastro\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Andar (1-20): ");
                scanf("%d", &andar);
                printf("Apartamento (1-14): ");
                scanf("%d", &ap);
                fVerApartamento(andar, ap);
                break;
            case 2:
                fMudancaApartamento();
                break;
            case 3:
                fExtensaoEstadia();
                break;
            case 4:
                fErroCadastro();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida.\n");
                system("pause");
        }
    } while (opcao != 0);
}

//Submenu de Servico de Quarto
void fMenuServicoQuarto()
{
    int opcao, andar, ap;

    do {
        printf("\n===========================================\n");
        printf("\tSERVICO DE QUARTO\n");
        printf("===========================================\n");
        printf("1 - Registrar Consumo\n");
        printf("2 - Contestar Servico de Quarto\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Andar (1-20): ");
                scanf("%d", &andar);
                printf("Apartamento (1-14): ");
                scanf("%d", &ap);
                fServicoQuarto(andar, ap);
                break;
            case 2:
                fContestacaoServicoQuarto();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida.\n");
                system("pause");
        }
    } while (opcao != 0);
}

void fInicializar()
{
    int i, j;
    for (i = 1; i <= 20; i++)
        for (j = 1; j <= 14; j++)
            tab[i][j] = '.';
}

void fMapaHotel()
{
    int i, j;
    system("cls");
    printf("Apto ->\t\t");
    for (j = 1; j <= 14; j++)
        printf("%2d ", j);
    printf("\n\n");
    for (i = 20; i >= 1; i--) {
        printf("Andar %2d\t", i);
        for (j = 1; j <= 14; j++)
            printf("%2c ", tab[i][j]);
        printf("\n");
    }
}

static int fValidar(int andar, int ap)
{
    if (andar < 1 || andar > 20 || ap < 1 || ap > 14) {
        printf("\nApartamento invalido. Andar: 1-20, Apto: 1-14.\n");
        system("pause");
        return 0;
    }
    return 1;
}

//Check In sem reserva: pede andar, apto, diarias e todos os dados do hospede
void fCheckinSemReserva()
{
    int andar, ap, diaria;

    printf("Andar (1-20): ");
    scanf("%d", &andar);
    printf("Apartamento (1-14): ");
    scanf("%d", &ap);

    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] == 'O') {
        printf("\nApartamento ja esta ocupado.\n");
        system("pause");
        return;
    }
    if (tab[andar][ap] == 'R') {
        printf("\nApartamento esta RESERVADO. Use o CheckIn COM Reserva (opcao 2).\n");
        system("pause");
        return;
    }

    printf("Diarias: ");
    scanf("%d", &diaria);
    while (getchar() != '\n');

    hospedes[andar][ap].diaria = diaria;
    hospedes[andar][ap].servico_quarto = 0;

    fCadastrarHospede(andar, ap);

    tab[andar][ap] = 'O';

    printf("\n===========================================\n");
    printf("  CheckIn SEM reserva realizado com sucesso!\n");
    printf("===========================================\n");
    printf("Hospede : %s\n", hospedes[andar][ap].nome);
    printf("Andar   : %d  |  Apto: %d\n", andar, ap);
    printf("Diarias : %d\n", diaria);
    printf("Cafe da manha: %s\n",
           hospedes[andar][ap].cafe_manha == 'S' ? "Incluso" : "Nao incluso");

    system("pause");
}

/* Check In com reserva:
   - Pede apenas o NOME do hospede
   - Localiza a reserva automaticamente na matriz
   - Pede as diarias e confirma o check-in */
void fCheckinComReserva()
{
    char nome_busca[60];
    int i, j;
    int andar = -1, ap = -1;

    printf("Nome do hospede com reserva: ");
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = '\0';

    /* Busca na matriz quem tem reserva com esse nome */
    for (i = 1; i <= 20 && andar == -1; i++) {
        for (j = 1; j <= 14 && andar == -1; j++) {
            if (tab[i][j] == 'R' &&
                strcmp(hospedes[i][j].nome, nome_busca) == 0) {
                andar = i;
                ap    = j;
            }
        }
    }

    if (andar == -1) {
        printf("\nNenhuma reserva encontrada para o nome: %s\n", nome_busca);
        system("pause");
        return;
    }

    printf("\nReserva encontrada!\n");
    printf("Hospede : %s\n", hospedes[andar][ap].nome);
    printf("Andar   : %d  |  Apto: %d\n", andar, ap);
    printf("Cafe da manha: %s\n",
           hospedes[andar][ap].cafe_manha == 'S' ? "Incluso" : "Nao incluso");

    int diaria;
    printf("\nDiarias: ");
    scanf("%d", &diaria);

    hospedes[andar][ap].diaria = diaria;
    hospedes[andar][ap].servico_quarto = 0;
    tab[andar][ap] = 'O';

    printf("\n===========================================\n");
    printf("  CheckIn COM reserva realizado com sucesso!\n");
    printf("===========================================\n");
    printf("Hospede : %s\n", hospedes[andar][ap].nome);
    printf("Andar   : %d  |  Apto: %d\n", andar, ap);
    printf("Diarias : %d\n", diaria);

    system("pause");
}

void fMapaReserva(int andar, int ap, int diaria) //Mapa de reservas do hotel
{
    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] != '.') {
        printf("\nApartamento nao esta livre (status: %c).\n", tab[andar][ap]);
        system("pause");
        return;
    }
    hospedes[andar][ap].diaria = diaria;
    tab[andar][ap] = 'R';
    printf("\nReserva realizada: Andar %d, Apto %d.\n", andar, ap);
    fCadastrarHospede(andar, ap);
    system("pause");
}

void fCheckOut(int andar, int ap)  //Realizac1ão de Check Out do hotel
{
    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] == '.') {
        printf("\nApartamento ja esta livre.\n");
        system("pause");
        return;
    } else if (tab[andar][ap] == 'R') {
        printf("\nNao e possivel fazer checkout pois este apto esta reservado.\n");
        system("pause");
        return;
    }

    printf("\n===========================================\n");
    printf("\tRESUMO DO CHECK-OUT\n");
    printf("===========================================\n");
    printf("Hospede: %s\n", hospedes[andar][ap].nome);
    printf("CPF: %s\n", hospedes[andar][ap].cpf);
    printf("Diarias: %d\n", hospedes[andar][ap].diaria);
    printf("Servico de quarto: R$ %.2f\n", hospedes[andar][ap].servico_quarto);
    printf("Cafe da manha: %s\n",
           hospedes[andar][ap].cafe_manha == 'S' ? "Incluso" : "Nao incluso");

    tab[andar][ap] = '.';
    hospedes[andar][ap].servico_quarto = 0;
    hospedes[andar][ap].diaria = 0;

    printf("\nApartamento liberado: Andar %d, Apto %d.\n", andar, ap);
    system("pause");
}

void fCReserva(int andar, int ap) //Cancelamente de reserva do hotel
{
    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] == '.') {
        printf("\nApartamento ja esta livre.\n");
        system("pause");
        return;
    } else if (tab[andar][ap] == 'O') {
        printf("\nNao e possivel cancelar: apto esta ocupado.\n");
        system("pause");
        return;
    }
    tab[andar][ap] = '.';
    printf("\nReserva cancelada: Andar %d, Apto %d.\n", andar, ap);
    system("pause");
}

void fTaxaOcupacao()  //Checa a ocupacao do hotel e mostra o percentual de ocupacao, reservas e livres
{
    int i, j;
    int total = 20 * 14;
    int ocupados = 0, reservados = 0;

    for (i = 1; i <= 20; i++)
        for (j = 1; j <= 14; j++) {
            if (tab[i][j] == 'O') ocupados++;
            else if (tab[i][j] == 'R') reservados++;
        }

    printf("Total de apartamentos : %d\n", total);
    printf("Ocupados  (O)         : %d (%.1f%%)\n", ocupados,  (double)ocupados  / total * 100.0);
    printf("Reservados (R)        : %d (%.1f%%)\n", reservados,(double)reservados / total * 100.0);
    printf("Livres    (.)         : %d (%.1f%%)\n",
           total - ocupados - reservados,
           (double)(total - ocupados - reservados) / total * 100.0);
    printf("\n");
    system("pause");
}
//Cadastro dos hóspedes do hotel, com validação de CPF, nome, endereço, telefone e email
//Também pergunta se o café da manhã está incluso

void fCadastrarHospede(int andar, int ap)  
{
    printf("\n--- Cadastro do Hospede ---\n");

    do {
        printf("CPF (11 digitos numericos): ");
        fgets(hospedes[andar][ap].cpf, sizeof(hospedes[andar][ap].cpf), stdin);
        if (strchr(hospedes[andar][ap].cpf, '\n') == NULL)
            while (getchar() != '\n');
        hospedes[andar][ap].cpf[strcspn(hospedes[andar][ap].cpf, "\n")] = '\0';
        if (strlen(hospedes[andar][ap].cpf) != 11)
            printf("CPF invalido! Digite exatamente 11 digitos.\n");
    } while (strlen(hospedes[andar][ap].cpf) != 11);

    do {
        printf("Nome completo (min 3 caracteres): ");
        fgets(hospedes[andar][ap].nome, sizeof(hospedes[andar][ap].nome), stdin);
        if (strchr(hospedes[andar][ap].nome, '\n') == NULL)
            while (getchar() != '\n');
        hospedes[andar][ap].nome[strcspn(hospedes[andar][ap].nome, "\n")] = '\0';
        if (strlen(hospedes[andar][ap].nome) < 3)
            printf("Nome invalido! Digite um nome valido.\n");
    } while (strlen(hospedes[andar][ap].nome) < 3);

    do {
        printf("Endereco completo (min 5 caracteres): ");
        fgets(hospedes[andar][ap].endereco, sizeof(hospedes[andar][ap].endereco), stdin);
        if (strchr(hospedes[andar][ap].endereco, '\n') == NULL)
            while (getchar() != '\n');
        hospedes[andar][ap].endereco[strcspn(hospedes[andar][ap].endereco, "\n")] = '\0';
        if (strlen(hospedes[andar][ap].endereco) < 5)
            printf("Endereco invalido! Digite um endereco valido.\n");
    } while (strlen(hospedes[andar][ap].endereco) < 5);

    do {
        printf("Telefone celular (min 10 digitos): ");
        fgets(hospedes[andar][ap].telefone, sizeof(hospedes[andar][ap].telefone), stdin);
        if (strchr(hospedes[andar][ap].telefone, '\n') == NULL)
            while (getchar() != '\n');
        hospedes[andar][ap].telefone[strcspn(hospedes[andar][ap].telefone, "\n")] = '\0';
        if (strlen(hospedes[andar][ap].telefone) < 10)
            printf("Telefone invalido! Digite um telefone valido.\n");
    } while (strlen(hospedes[andar][ap].telefone) < 10);

    do {
        printf("E-mail: ");
        fgets(hospedes[andar][ap].email, sizeof(hospedes[andar][ap].email), stdin);
        if (strchr(hospedes[andar][ap].email, '\n') == NULL)
            while (getchar() != '\n');
        hospedes[andar][ap].email[strcspn(hospedes[andar][ap].email, "\n")] = '\0';
        if (strlen(hospedes[andar][ap].email) < 6 || strchr(hospedes[andar][ap].email, '@') == NULL)
            printf("E-mail invalido! Digite um e-mail valido (ex: nome@email.com).\n");
    } while (strlen(hospedes[andar][ap].email) < 6 || strchr(hospedes[andar][ap].email, '@') == NULL);

    char opcao_cafe;
    do {
        printf("Cafe da manha incluso? (S/N): ");
        opcao_cafe = getchar();
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        opcao_cafe = toupper((unsigned char)opcao_cafe);
        if (opcao_cafe != 'S' && opcao_cafe != 'N')
            printf("Opcao invalida! Digite S ou N.\n");
    } while (opcao_cafe != 'S' && opcao_cafe != 'N');

    hospedes[andar][ap].cafe_manha = opcao_cafe;
    printf("\nHospede cadastrado com sucesso!\n");
}

void fVerApartamento(int andar, int ap) //Situação do apartamento
{
    if (!fValidar(andar, ap)) return;

    printf("\n===========================================\n");
    printf("Apartamento %d - Andar %d\n", ap, andar);
    printf("===========================================\n");

    if (tab[andar][ap] == '.') {
        printf("Status: LIVRE\n\n");
        system("pause");
        return;
    }

    char status_str[12];
    if (tab[andar][ap] == 'R')
        strcpy(status_str, "RESERVADO");
    else
        strcpy(status_str, "OCUPADO");

    printf("Status: %s\n", status_str);
    printf("\n--- Dados do Hospede ---\n");
    printf("CPF:           %s\n", hospedes[andar][ap].cpf);
    printf("Nome:          %s\n", hospedes[andar][ap].nome);
    printf("Endereco:      %s\n", hospedes[andar][ap].endereco);
    printf("Telefone:      %s\n", hospedes[andar][ap].telefone);
    printf("E-mail:        %s\n", hospedes[andar][ap].email);
    printf("Diarias:       %d\n", hospedes[andar][ap].diaria);
    printf("Servico de quarto: R$ %.2f\n", hospedes[andar][ap].servico_quarto);
    printf("Cafe da manha: %s\n",
           hospedes[andar][ap].cafe_manha == 'S' ? "Incluso" : "Nao incluso");

    char alterar;
    printf("\nDeseja alterar a opcao de cafe da manha? (S/N): ");
    while (getchar() != '\n');
    alterar = getchar();
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    alterar = toupper((unsigned char)alterar);

    if (alterar == 'S') {
        char nova_opcao;
        do {
            printf("Cafe da manha incluso? (S/N): ");
            nova_opcao = getchar();
            while ((c = getchar()) != '\n' && c != EOF);
            nova_opcao = toupper((unsigned char)nova_opcao);
            if (nova_opcao != 'S' && nova_opcao != 'N')
                printf("Opcao invalida! Digite S ou N.\n");
        } while (nova_opcao != 'S' && nova_opcao != 'N');

        hospedes[andar][ap].cafe_manha = nova_opcao;
        printf("\nOpcao de cafe da manha atualizada para: %s\n",
               nova_opcao == 'S' ? "Incluso" : "Nao incluso");
    }

    printf("\n");
    system("pause");
}

void fServicoQuarto(int andar, int ap) //Registrar consumo do serviço de quarto para um apartamento ocupado
{
    float valor;

    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] != 'O') {
        printf("\nServico de quarto disponivel apenas para apartamentos ocupados.\n");
        system("pause");
        return;
    }

    printf("\nValor consumido: R$ ");
    scanf("%f", &valor);

    hospedes[andar][ap].servico_quarto += valor;

    printf("\nConsumo registrado com sucesso!\n");
    printf("Total acumulado: R$ %.2f\n", hospedes[andar][ap].servico_quarto);
    system("pause");
}

//Mudança de apartamento: Checkout + novo check-in com dados transferidos
void fMudancaApartamento()
{
    int andarOrig, apOrig, andarDest, apDest;

    printf("Andar atual (1-20): ");
    scanf("%d", &andarOrig);
    printf("Apartamento atual (1-14): ");
    scanf("%d", &apOrig);

    if (!fValidar(andarOrig, apOrig)) return;

    if (tab[andarOrig][apOrig] != 'O') {
        printf("\nApartamento de origem nao esta ocupado.\n");
        system("pause");
        return;
    }

    printf("Andar de destino (1-20): ");
    scanf("%d", &andarDest);
    printf("Apartamento de destino (1-14): ");
    scanf("%d", &apDest);

    if (!fValidar(andarDest, apDest)) return;

    if (tab[andarDest][apDest] != '.') {
        printf("\nApartamento de destino nao esta livre.\n");
        system("pause");
        return;
    }

    //Transfere todos os dados do hospede para o novo apartamento
    hospedes[andarDest][apDest] = hospedes[andarOrig][apOrig];

    //Libera (checkout) o apartamento de origem
    tab[andarOrig][apOrig] = '.';
    hospedes[andarOrig][apOrig].servico_quarto = 0;
    hospedes[andarOrig][apOrig].diaria = 0;

    //Novo check-in no destino com os dados transferidos
    tab[andarDest][apDest] = 'O';

    printf("\nMudanca realizada: %s movido do Andar %d/Apto %d para Andar %d/Apto %d.\n",
           hospedes[andarDest][apDest].nome, andarOrig, apOrig, andarDest, apDest);

    system("pause");
}


//Abandono sem Checkout: Checkout compulsorio apos tentativa de contato
void fAbandonoSemCheckout()
{
    int andar, ap, c;
    char resp;

    printf("Andar (1-20): ");
    scanf("%d", &andar);
    printf("Apartamento (1-14): ");
    scanf("%d", &ap);

    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] != 'O') {
        printf("\nApartamento nao esta ocupado.\n");
        system("pause");
        return;
    }

    printf("\nFoi feita tentativa de contato com o hospede? (S/N): ");
    while ((c = getchar()) != '\n' && c != EOF);
    resp = getchar();
    while ((c = getchar()) != '\n' && c != EOF);
    resp = toupper((unsigned char)resp);

    if (resp != 'S') {
        printf("\nE necessario tentar contatar o hospede antes do checkout compulsorio.\n");
        system("pause");
        return;
    }

    printf("\n===========================================\n");
    printf("\tCHECKOUT COMPULSORIO (Abandono)\n");
    printf("===========================================\n");
    printf("Hospede: %s\n", hospedes[andar][ap].nome);
    printf("Diarias: %d\n", hospedes[andar][ap].diaria);
    printf("Servico de quarto: R$ %.2f\n", hospedes[andar][ap].servico_quarto);

    tab[andar][ap] = '.';
    hospedes[andar][ap].servico_quarto = 0;
    hospedes[andar][ap].diaria = 0;

    printf("\nApartamento liberado.\n");

    system("pause");
}

/*CheckIn com reserva de parente:
     - Pede o nome do titular da reserva e o nome de quem esta chegando
     - Localiza a reserva do titular e confirma o check-in para o parente */
void fCheckinReservaParente()
{
    char nome_busca[60];
    char nome_titular[60];
    int i, j, c;
    int andar = -1, ap = -1;
    char confirmado;

    printf("Nome de quem esta chegando: ");
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = '\0';

    printf("Nome do titular da reserva: ");
    fgets(nome_titular, sizeof(nome_titular), stdin);
    nome_titular[strcspn(nome_titular, "\n")] = '\0';

    for (i = 1; i <= 20 && andar == -1; i++) {
        for (j = 1; j <= 14 && andar == -1; j++) {
            if (tab[i][j] == 'R' && strcmp(hospedes[i][j].nome, nome_titular) == 0) {
                andar = i;
                ap = j;
            }
        }
    }

    if (andar == -1) {
        printf("\nNenhuma reserva encontrada para o titular: %s\n", nome_titular);
        system("pause");
        return;
    }

    printf("\nReserva localizada em Andar %d / Apto %d.\n", andar, ap);
    printf("Confirmacao do titular obtida por telefone? (S/N): ");
    confirmado = getchar();
    while ((c = getchar()) != '\n' && c != EOF);
    confirmado = toupper((unsigned char)confirmado);

    if (confirmado != 'S') {
        printf("\nCheckin nao realizado - e necessario confirmar o titular antes.\n");
        system("pause");
        return;
    }

    /* O cadastro permanece em nome do titular, conforme a reserva original */
    tab[andar][ap] = 'O';

    printf("\nCheckin realizado para a reserva do titular %s (apartamento liberado para %s).\n",
           hospedes[andar][ap].nome, nome_busca);

    system("pause");
}

//Extensão de Estadia: Adicionar diarias extras para um apartamento ocupado.
void fExtensaoEstadia()
{
    int andar, ap, diasExtra;

    printf("Andar (1-20): ");
    scanf("%d", &andar);
    printf("Apartamento (1-14): ");
    scanf("%d", &ap);

    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] != 'O') {
        printf("\nExtensao de estadia disponivel apenas para apartamentos ocupados.\n");
        system("pause");
        return;
    }

    printf("Dias adicionais desejados: ");
    scanf("%d", &diasExtra);

    hospedes[andar][ap].diaria += diasExtra;

    printf("\nExtensao registrada no livro: +%d diaria(s). Total agora: %d diarias.\n",
           diasExtra, hospedes[andar][ap].diaria);

    system("pause");
}

//Erro de cadastro: Corrigir dados do hospede sem necessidade de gerente, mantendo o status original (O ou R)
void fErroCadastro()
{
    int andar, ap;
    char statusAnterior;

    printf("Andar (1-20): ");
    scanf("%d", &andar);
    printf("Apartamento (1-14): ");
    scanf("%d", &ap);

    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] == '.') {
        printf("\nApartamento livre - nao ha cadastro para corrigir.\n");
        system("pause");
        return;
    }

    statusAnterior = tab[andar][ap];

    printf("\nDados atuais   - Hospede: %s | CPF: %s\n",
           hospedes[andar][ap].nome, hospedes[andar][ap].cpf);
    printf("Refazendo o cadastro com os dados corretos...\n");

    fCadastrarHospede(andar, ap);

    tab[andar][ap] = statusAnterior; /* mantem o status original (O ou R) */

    printf("\nCadastro corrigido com sucesso (procedimento padrao, sem necessidade de gerente).\n");

    system("pause");
}

//Ajuste do servic1o de quarto: Permite ao hospede contestar um valor cobrado no serviço de quarto
   
void fContestacaoServicoQuarto()
{
    int andar, ap, opcao;
    float valor;

    printf("Andar (1-20): ");
    scanf("%d", &andar);
    printf("Apartamento (1-14): ");
    scanf("%d", &ap);

    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] != 'O') {
        printf("\nApartamento nao esta ocupado.\n");
        system("pause");
        return;
    }

    printf("Valor atual de servico de quarto: R$ %.2f\n", hospedes[andar][ap].servico_quarto);
    printf("\n1 - Adicionar valor\n");
    printf("2 - Diminuir valor\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    if (opcao != 1 && opcao != 2) {
        printf("\nOpcao invalida.\n");
        system("pause");
        return;
    }

    printf("Valor: R$ ");
    scanf("%f", &valor);

    if (opcao == 1) {
        hospedes[andar][ap].servico_quarto += valor;
    } else {
        hospedes[andar][ap].servico_quarto -= valor;
        if (hospedes[andar][ap].servico_quarto < 0)
            hospedes[andar][ap].servico_quarto = 0;
    }

    printf("\nValor atualizado: R$ %.2f\n", hospedes[andar][ap].servico_quarto);
    system("pause");
}