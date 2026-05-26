//Projeto final de LIC

#include <stdio.h>

main()
{
int ent, andar, apto;

	printf("(1) - Check In");
	printf("\n(2) - Check Out");
	printf("\n(3) - Reservar Apartamento");
	printf("\n(4) - Cancelar uma reserva");
	printf("\n(5) - Informações do hospede");
	printf("\n(6) - Taxa de ocupacao e de reservas de hotel");
	printf("\n(7) - Encerrar programa");
	printf("\nBem vindo(a) ao Hotel BJPNR, selecione uma opcao acima: ");
	scanf("%d", &ent);
	
	if (ent == 1)
		printf("Informe o andar e apartamento: ")
		scanf("%d %d", &andar, &apto);
		//Parte do codigo que transforma um apto reservado em ocupado na matriz
		printf("Check In ")
}
