//BJNR - Ativ05
//Bruna Samy Freming Quispilaya 
//João Pedro Freitas Vilar
//Nathalia Pedraça Pinho
//Rafaella Castro Zandoná Alves de Lima

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
} tipohospedes;

char tab[21][15];
tipohospedes hospedes[21][15];
int diaria;

void fInicializar();
void fMapaHotel();
void fCheckOut(int andar, int ap);
void fCReserva(int andar, int ap);
void fMapaReserva(int andar, int ap);
void fMapaCheckin(int andar, int ap);
void fTaxaOcupacao();
void fCadastrarHospede(int andar, int ap);
void fVerApartamento(int andar, int ap);

int main()
{
    int x, y;
    int opcao;

    fInicializar();

    do {
        system("cls");
        fMapaHotel();

        printf("\n1 - Realizar CheckIn\n");
        printf("2 - Realizar CheckOut\n");
        printf("3 - Reservar Apto\n");
        printf("4 - Cancelar Reserva\n");
        printf("5 - Visualizar Ocupacao:\n");
        printf("6 - Consultar Apartamento: \n");
        printf("0 - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                printf("\n===========================================\n");
                printf("\tCheckIn do Apartamento\n");
                printf("===========================================\n\n");
                printf("Andar (1-20): ");
                scanf("%d", &x);
                printf("Apartamento (1-14): ");
                scanf("%d", &y);
                printf("Diarias: ");
                scanf("%d", &diaria);
                while (getchar() != '\n');
                fMapaCheckin(x, y);
                break;

            case 2:
                printf("\n===========================================\n");
                printf("\tCheckOut do Apartamento\n");
                printf("===========================================\n\n");
                printf("Andar (1-20): ");
                scanf("%d", &x);
                printf("Apartamento (1-14): ");
                scanf("%d", &y);
                fCheckOut(x, y);
                break;

            case 3:
                printf("\n===========================================\n");
                printf("\tReserva de Apartamento\n");
                printf("===========================================\n\n");
                printf("Andar (1-20): ");
                scanf("%d", &x);
                printf("Apartamento (1-14): ");
                scanf("%d", &y);
                printf("Diarias: ");
                scanf("%d", &diaria);
                fMapaReserva(x, y);
                break;

            case 4:
                printf("\n===========================================\n");
                printf("\tCancelar Reserva\n");
                printf("===========================================\n\n");
                printf("Andar (1-20): ");
                scanf("%d", &x);
                printf("Apartamento (1-14): ");
                scanf("%d", &y);
                fCReserva(x, y);
                break;

            case 5:
                printf("\n===========================================\n");
                printf("\tVisualizar Ocupacao e Reserva");
                printf("\n===========================================\n");
                fTaxaOcupacao();
                break;

            case 6:
                printf("\n===========================================\n");
                printf("\tConsultar Apartamento\n");
                printf("===========================================\n\n");
                printf("Andar (1-20): ");
                scanf("%d", &x);
                printf("Apartamento (1-14): ");
                scanf("%d", &y);
                fVerApartamento(x, y);
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
        return 0;
    }
    return 1;
}

void fMapaCheckin(int andar, int ap)
{
    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] == 'O') {
        printf("\nApartamento ja esta ocupado.\n");
        system("pause");
        return;
    }

    if (tab[andar][ap] == 'R') {
        // Hóspede já cadastrado na reserva: reutiliza os dados sem perguntar de novo
        printf("\nApartamento estava RESERVADO. Realizando Check-in para o hospede:\n");
        printf("Nome:          %s\n", hospedes[andar][ap].nome);
        printf("CPF:           %s\n", hospedes[andar][ap].cpf);
        printf("Cafe da manha: %s\n", hospedes[andar][ap].cafe_manha == 'S' ? "Incluso" : "Nao incluso");
        tab[andar][ap] = 'O';
        printf("\nCheck-in realizado: Andar %d, Apto %d.\n", andar, ap);
    } else {
        // Apartamento livre: cadastra hóspede normalmente (inclui pergunta do café)
        tab[andar][ap] = 'O';
        printf("\nCheck-in realizado: Andar %d, Apto %d.\n", andar, ap);
        fCadastrarHospede(andar, ap);
    }

    system("pause");
}

void fMapaReserva(int andar, int ap)
{
    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] != '.') {
        printf("\nApartamento nao esta livre (status: %c).\n", tab[andar][ap]);
        system("pause");
        return;
    }
    tab[andar][ap] = 'R';
    printf("\nReserva realizada: Andar %d, Apto %d.\n", andar, ap);
    while (getchar() != '\n');
    fCadastrarHospede(andar, ap);
    system("pause");
}

void fCheckOut(int andar, int ap)
{
    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] == '.') {
        printf("\nApartamento ja esta livre.\n");
        system("pause");
        return;
    } else if (tab[andar][ap] == 'R') {
        printf("\nNao e possivel fazer checkout pois este apto esta reservado\n");
        system("pause");
        return;
    }
    tab[andar][ap] = '.';
    printf("\nApartamento liberado: Andar %d, Apto %d.\n", andar, ap);
    system("pause");
}

void fCReserva(int andar, int ap)
{
    if (!fValidar(andar, ap)) return;

    if (tab[andar][ap] == '.') {
        printf("\nApartamento ja esta livre.\n");
        system("pause");
        return;
    } else if (tab[andar][ap] == 'O') {
        printf("\nNao e possivel cancelar esta reserva pois este apto esta ocupado\n");
        system("pause");
        return;
    }
    tab[andar][ap] = '.';
    printf("\nReserva cancelada: Andar %d, Apto %d.\n", andar, ap);
    system("pause");
}

void fTaxaOcupacao()
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
    printf("Ocupados  (O)         : %d (%.1f%%)\n", ocupados, (double)ocupados / total * 100.0);
    printf("Reservados (R)        : %d (%.1f%%)\n", reservados, (double)reservados / total * 100.0);
    printf("Livres    (.)         : %d (%.1f%%)\n",
           total - ocupados - reservados,
           (double)(total - ocupados - reservados) / total * 100.0);
    printf("\n");
    system("pause");
}

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

    // Pergunta sobre café da manhã
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

void fVerApartamento(int andar, int ap)
{
    if (!fValidar(andar, ap)) return;

    printf("\n===========================================\n");
    printf("Apartamento %d - Andar %d\n", ap, andar);
    printf("===========================================\n");

    if (tab[andar][ap] == '.') {
        printf("Status: LIVRE\n");
        printf("\n");
        system("pause");
        return;
    }

    // Exibe dados para apartamento ocupado ou reservado
    char status_str[12];
    if (tab[andar][ap] == 'R') strcpy(status_str, "RESERVADO");
    else strcpy(status_str, "OCUPADO");

    printf("Status: %s\n", status_str);
    printf("\n--- Dados do Hospede ---\n");
    printf("CPF:           %s\n", hospedes[andar][ap].cpf);
    printf("Nome:          %s\n", hospedes[andar][ap].nome);
    printf("Endereco:      %s\n", hospedes[andar][ap].endereco);
    printf("Telefone:      %s\n", hospedes[andar][ap].telefone);
    printf("E-mail:        %s\n", hospedes[andar][ap].email);
    printf("Diarias:       %d\n", diaria);
    printf("Cafe da manha: %s\n", hospedes[andar][ap].cafe_manha == 'S' ? "Incluso" : "Nao incluso");

    // Opção de alterar o café da manhã
    char alterar;
    printf("\nDeseja alterar a opcao de cafe da manha? (S/N): ");
    while (getchar() != '\n'); // limpa buffer do scanf anterior
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
