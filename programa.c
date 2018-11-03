#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "time.h"
#define SIZE 5

char nome[SIZE][50];
char email[SIZE][50];
char datahora[SIZE][50];
int cadastrado[SIZE];
int op, i, flag, sorteioate = 0;
void cadastro();
void pesquisa();
void listar();
void sorteio();

main()
{
    setlocale(LC_ALL, "Portuguese");
    do
    {
        system("cls");
        printf("\n======================================");
        printf("\n          MENU PRINCIPAL ");
        printf("\n======================================");
        printf("\n |1| Cadastrar");
        printf("\n |2| Asentos Disponiveis");
        printf("\n |3| Pesquisar Participante");
        printf("\n |4| Listar Todos os Participantes");
        printf("\n |5| Sorteio");
        printf("\n |6| Sair");
        printf("\n----------------------------------------");
        printf("\n Escolha uma opção: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:
                cadastro();
                break;
            case 2:
                break;
            case 3:
                pesquisa();
                break;
            case 4:
                listar();
                break;
            case 5:
                sorteio();
                break;
            case 6:
                break;
            default:
                printf(" Opção invalida");
                getch();
        }
    }
    while(op != 6);
}// End main

void cadastro()
{
    static int linha = 0;
    if(linha < SIZE)
    {
        system("cls");
        printf("\n============ FORMULARIO DE CADASTRO ============");
        printf("\n Nome: ");
        fflush(stdin);
        gets(nome[linha]);
        printf("\n Email: ");
        gets(email[linha]);

        time_t agora;
        /* Recupera a quantidade de segundos desde 01/01/1970 */
        agora = time(NULL);

        /* Formata a data e a hora da forma desejada */
        strftime(datahora[linha], sizeof(datahora[linha]), "\n Data: %d/%m/%Y \n Hora: %H:%M:%S", localtime( &agora ));

        cadastrado[linha] = 1;

        system("cls");
        printf("\n------------ Ticket ------------");
        printf("\n Nome: %s", nome[linha]);
        printf("\n Email: %s", email[linha]);
        printf("%s", datahora[linha]);
        printf("\n--------------------------------");
        getch();
        linha++;
        // acomula a quantidade de cadastrada para fazer o sorteio
        sorteioate = sorteioate + 1;

    }
    else
    {
        printf("\n Todas as vagas ja estão prenchidas!");
        getch();
    }

}// End cadastro

void pesquisa()
{
    char emailpesquisa[50];
    flag = 0;
    system("cls");
    printf("\n============ PESQUISA POR E-MAIL ============");
    printf("\n E-mail: ");
    scanf("%s", emailpesquisa);
    for(i = 0; i < SIZE; i++)
    {
        if(strcmp(email[i], emailpesquisa) == 0)
        {
            printf("\n------------ Ticket ------------");
            printf("\n Nome: %s", nome[i]);
            printf("\n Email: %s", email[i]);
            printf("%s", datahora[i]);
            printf("\n--------------------------------");
            flag = 1;
            getch();
        }
    }
    if(flag == 0)
    {
        printf("\n Não exite cadastro neste e-mail  ");
        getch();
    }
}// End pesquisa

void listar()
{
    flag = 0;
    system("cls");
    printf("\n============ LISTA DE TODOS CADASTRADOS ============");
    for(i = 0; i < SIZE; i++)
    {
        if(cadastrado[i] == 1)
        {
            printf("\n------------ Ticket ------------");
            printf("\n Nome: %s", nome[i]);
            printf("\n Email: %s", email[i]);
            printf("%s", datahora[i]);
            printf("\n--------------------------------\n");
            flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("\n Não possui ninguém cadastrado! ");
    }
    getch();
} // End listar

void sorteio(){
    int sorteado;
    system("cls");
    printf("\n=================== SOTEIO ===================");
    printf("\n Tecle qualquer tecla para realizar o sorteio");
    printf("\n==============================================");
    getch();
    // funcção rand() pega numeros aleatorio de 0 ate o numero informado depois do %
    sorteado = rand() % sorteioate;

    // mostrar ticket do sorteado
    system("cls");
    printf("\n=================== SOTEIO ===================");
    printf("\n        O vencedor do sorteio foi: ");
    printf("\n==============================================");
    printf("\n------------ Ticket ------------");
    printf("\n Nome: %s", nome[sorteado]);
    printf("\n Email: %s", email[sorteado]);
    printf("%s", datahora[sorteado]);
    printf("\n--------------------------------\n");
    getch();

}
