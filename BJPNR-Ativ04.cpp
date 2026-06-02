//BJPNR - Ativ4

#include <stdio.h>
#include <stdlib.h>



char tab[21][15];

//Prototipos (declaracoes antecipadas)
void fInicializar();
void fMapaHotel();
void fCheckOut(int andar, int ap);
void fCReserva(int andar, int ap);
void fMapaReserva(int andar, int ap);
void fMapaCheckin(int andar, int ap);

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


// Preenche toda a matriz com '.'  
void fInicializar()
{
    int i, j;
    for (i = 1; i <= 20; i++)
        for (j = 1; j <= 14; j++)
            tab[i][j] = '.';
}

// Exibe o mapa atual do hotel usando a matriz global 
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

// Valida se andar e apartamento estão dentro dos limites 
static int fValidar(int andar, int ap)
{
    if (andar < 1 || andar > 20 || ap < 1 || ap > 14) {
        printf("\nApartamento invalido. Andar: 1-20, Apto: 1-14.\n");
        return 0;
    }
    return 1;
}

// Marca o apartamento como ocupado "O" 
void fMapaCheckin(int andar, int ap)
{
    if (!fValidar(andar, ap))
        return;
    if (tab[andar][ap] == 'O') {
        printf("\nApartamento ja esta ocupado.\n");
       
        return;
	}
    if(tab[andar][ap] == 'R')
	{
    	printf("\nO apartamento antes reservado recebeu seu checkin!\n");
    	tab[andar][ap] = 'O';
	}
	else
		tab[andar][ap] = 'O';
    
    printf("\nCheck-in realizado: Andar %d, Apto %d.\n", andar, ap);
    system("pause");
}
// Marca o apartamento como reservado "R" 
void fMapaReserva(int andar, int ap)
{
    if (!fValidar(andar, ap))
        return;

    if (tab[andar][ap] != '.') {
        printf("\nApartamento nao esta livre (status: %c).\n", tab[andar][ap]);
        system("pause");
        return;
    }

    tab[andar][ap] = 'R';
    printf("\nReserva realizada: Andar %d, Apto %d.\n", andar, ap);
    system("pause");
}
// Libera o apartamento (checkout ou cancelamento de reserva) 
void fCheckOut(int andar, int ap)
{
    if (!fValidar(andar, ap))
        return;

    if (tab[andar][ap] == '.') {
        printf("\nApartamento ja esta livre.\n");
        system("pause");
        return;
    }else if(tab[andar][ap] == 'R')
    	printf("\nNao e possivel fazer checkout pois este apto esta reservado\n");
    	
   if(tab[andar][ap] == 'O')
   {
	 
    	tab[andar][ap] = '.';
    	printf("\nApartamento liberado: Andar %d, Apto %d.\n", andar, ap);
	}
    system("pause");
}

void fCReserva(int andar, int ap)
{
    if (!fValidar(andar, ap))
        return;

    if (tab[andar][ap] == '.') {
        printf("\nApartamento ja esta livre.\n");
        system("pause");
        return;
    }else if(tab[andar][ap] == 'O')
    	printf("\nNao e possivel cancelar esta reserva pois este apto esta ocupado\n");
    	
   if(tab[andar][ap] == 'R')
   {
	 
    	tab[andar][ap] = '.';
    	printf("\nApartamento liberado: Andar %d, Apto %d.\n", andar, ap);
	}
    system("pause");
}
