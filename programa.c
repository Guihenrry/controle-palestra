#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"

struct dados { // Estrutura de dados
    int id;
    char nome[50];
    char email[50];
    char sexo[10];
    char rg[20];
    char convidado[3];
    char especial[3];
    int assento;
};
int op, i, j, nassento, linha, coluna;
int  idEspecial[3], statusEspeciais[3];// assentos especiais
int  idConvidados[10], statusConvidados[10];// assentos resevados para os convidados
int  idAssentos[4][10], statusAssentos[4][10]; // matriz assentos comun
int idg = 0; // id global


struct dados visitante[53];// Declaração do numero de visitante

// Funções
void mostrarAssentos();

main()
{

    // prencher os vetores e matriz com 0
    for(i = 0; i < 3; i++)
    {
        statusEspeciais[i] = 0;
    }

    for(i = 0; i < 10; i++)
    {
        statusConvidados[i] = 0;
    }

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 10; j++)
        {
            statusAssentos[i][j] = 0;
        }
    }

    setlocale(LC_ALL, "Portuguese");
    int logincerto = 0;
    char usuario[20];
    char senha[10];
    char user[] = "admin";
    char password[] = "admin";


    while(logincerto != 1)// Repete ate acertar usuario e senha
    {
        system("cls");
        printf("\n Usuario: ");
        gets(usuario);
        printf("\n Senha: ");
        gets(senha);
        if(strcmp(usuario, user) == 0)// verifica se o usuario esta correto
        {
            if(strcmp(senha, password) == 0) // verifica se a senha esta correta
            {
                logincerto = 1;
            }
            else
            {
                printf("\n Senha invalida");
                getch();
            }
        }
        else
        {
           printf("\n Usuario ou senha invalida");
           getch();
        }
    }// End while do login

    op = 0;
    while(op != 4) {
        system("cls");
        printf("\n |1| Gerenciar visitante");
        printf("\n |2| Realizar sorteio");
        printf("\n |3| Enviar comunicado por e-mail");
        printf("\n |4| Sair");
        printf("\n Digite a opção desejada: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:// gerenciar visitante
                do
                {
                    system("cls");
                    printf("\n |1| Incluir visitante");
                    printf("\n |2| Excluir visitante");
                    printf("\n |3| Listar lugares livres");
                    printf("\n |4| Listar lugares ocupados");
                    printf("\n |5| Mostar todos os lugares");
                    printf("\n |6| Retornar ao menu inicial");
                    printf("\n Digite a opção desejada: ");
                    scanf("%d", &op);
                    switch(op)
                    {
                        case 1:// formulario de cadastro e escolha do assento
                            system("cls");
                            printf("\n Nome: ");
                            fflush(stdin);
                            gets(visitante[idg].nome);
                            printf(" Email: ");
                            gets(visitante[idg].email);
                            printf(" Sexo(m/f):");
                            gets(visitante[idg].sexo);
                            printf(" RG: ");
                            gets(visitante[idg].rg);
                            printf(" Convidado (s/n): ");
                            gets(visitante[idg].convidado);
                            printf(" Portador de necessidades especiais(s/n): ");
                            gets(visitante[idg].especial);
                            visitante[idg].id = idg;
                            mostrarAssentos();
                            if(strcmp(visitante[idg].convidado, "s") == 0)// verifica se é convidado
                            {
                                printf("\n Informe um assento da linha dos convidados(1 a 10): ");
                                scanf("%d", &nassento);
                                if(statusConvidados[nassento - 1] == 1)// Verifica se o assento ja esta reservado
                                {
                                   printf("\n Assento ja reservado. Verifique outra opção");
                                   getch();
                                }
                                else // assento livre
                                {
                                    statusConvidados[nassento - 1] = 1;
                                    idConvidados[nassento - 1] = idg; // guarda o id do vissitante que esta alocado nesse assento
                                    idg = idg + 1; // gera um novo id
                                    printf("\n Reserva realizada com sucesso!");
                                    getch();
                                }
                            }
                            else
                            {
                                if(strcmp(visitante[idg].especial, "s") == 0) // Verifica se é especial
                                {
                                    printf("\n Informe um assento da linha dos assentos especiais(1 a 3): ");
                                    scanf("%d", &nassento);
                                    if(statusEspeciais[nassento - 1] == 1)// assento ja reservadp
                                    {
                                        printf("\n Assento ja reservado. Verifique outra opção");
                                        getch();
                                    }
                                    else // assento livre
                                    {
                                        statusEspeciais[nassento - 1] = 1;
                                        idEspecial[nassento - 1] = idg; // guarda o id do vissitante que esta alocado nesse assento
                                        idg = idg + 1; // gera um novo id
                                        printf("\n Reserva realizada com sucesso!");
                                        getch();
                                    }
                                }
                                else // assento comun
                                {
                                    printf("\n Informe a linha e a coluna do assento desejado: ");
                                    printf("\n Linha(1 a 4): ");
                                    scanf("%d", &linha);
                                    printf(" Coluna(1 a 10): ");
                                    scanf("%d", &coluna);
                                    if(statusAssentos[linha - 1][coluna - 1] == 1)//assento
                                    {
                                        printf("\n Assento ja reservado. Verifique outra opção");
                                        getch();
                                    }
                                    else// assento livre
                                    {
                                        statusAssentos[linha - 1][coluna - 1] = 1;
                                        idAssentos[linha - 1][coluna - 1] = idg; // guarda o id do visitante no assento
                                        idg = idg + 1; // gera novo id
                                        printf("\n Reserva realizada com sucesso!");
                                        getch();
                                    }
                                    getch();
                                }
                            }
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            mostrarAssentos();
                            getch();
                            break;
                        case 6:
                            break;
                        default:
                            printf("\n Opção invalida ");
                            getch();
                        break;
                    }
                } while(op != 6);
                break;// End gerenciar visitante
            case 2:// Realizar sorteio
                do
                {
                    system("cls");
                    printf("\n |1| Realizar sorteio");
                    printf("\n |2| Retornanar ao menu inicial");
                    printf("\n Digite a opção desejada: ");
                    scanf("%d", &op);
                }while(op != 2);
                break;
            case 3:// Enviar comunicado por e-mail;
                do
                {
                    system("cls");
                    printf("\n |1| Escolher visitante");
                    printf("\n |2| Todos os visitantes");
                    printf("\n |3| Retornar ao menu inicial");
                    printf("\n Digite a opção desejada: ");
                    scanf("%d", &op);
                }while(op != 3);
                break;
            case 4: // sair
                break;
            default:
                printf("\n Opção invalida ");
                getch();
                break;
        } // End switch  menu inicial
    } // End while menu inicial
}// End main

void mostrarAssentos()
{
    printf("\n   | E - Assento especiais  |                         | C -  convidados |");
    printf("\n       1      2      3      4      5           6      7      8      9      10");
    printf("\n E -");
    for(i = 0; i < 3; i++)// mostrar assentos especiais
    {
        if(statusEspeciais[i] == 1)//poltrona ocupada
        {
            printf(" [---] ");
        }
        else// poltrona livre
        {
            printf(" [   ] ");
        }
    } // End mostrar assentos especiais
    printf("\n C -");
    for(i = 0; i < 10; i++)// mostrar convidados
    {
        if(statusConvidados[i] == 1)//poltrona ocupada
        {
            printf(" [---] ");
        }
        else// poltrona livre
        {
            printf(" [   ] ");
        }
        if(i == 4)
        {
            printf("     ");
        }
    }// End mostrar convidados
    putchar('\n');
    for(i = 0; i < 4; i++)// mostrar assentos comuns
    {
        printf(" %d -", i+1);
        for(j = 0; j < 10; j++)
        {
            if(statusAssentos[i][j] == 1)// assento ocupadp
            {
                printf(" [---] ");
            }
            else // assento livre
            {
                printf(" [   ] ");
            }
            if(j == 4)
            {
                printf("     ");
            }
        }
        putchar('\n');
    }// End assentos comun

}
