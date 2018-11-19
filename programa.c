/* Programa em c de controle de visitantes em uma palestra*/
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "time.h"

/* Estrutura dos dados do visitante */
struct dados {
    int id;
    char nome[50];
    char email[50];
    char sexo[10];
    char rg[20];
    char convidado[3];
    char especial[3];
    char datahora[50];
    char assento[50];
};

/* Variaveis globais*/
int i, j;// Variaveis de incrementos
int idg = 0; // id global
int idEspecial[3], statusEspeciais[3];// assentos especiais
int idConvidados[10], statusConvidados[10];// assentos resevados para os convidados
int idAssentos[4][10], statusAssentos[4][10]; // matriz assentos comun

/* Funções */
void mostrarAssentos();// mostra na tela os assentos [   ] = livre [---] = ocupado
void ticket(int id);//  mostra na tela ticket com nome, assento data e hora
void sorteio();// realiza sorteio colcocando de fora os convidado
void enviarEmail(int id);// mostar tela de email para id informado


/* Declaração do numero de visitante */
struct dados visitante[53];

main()
{
    setlocale(LC_ALL, "Portuguese");
    /* Inicialização das variaveis */
    int op;//variavel de escolha de opção
    int nassento;// Escolher o numero de um assento especial ou convidado
    int linha;// Escolher a linha do assento comum
    int coluna;//Escolher a coluna do assento comun
    int encontrou;// flag para verificar se encontrou
    int ativasorteio;// quando alguem esta apto o flag vale 1
    int pos;// guarda a posição do assento
    char pesquisa[50];//pesquisar nome ou email para enviar email

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

    /* variaveis do login*/
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
        /* Carregar menu inicial*/
        system("cls");
        printf("\n======================================");
        printf("\n          MENU INICIAL ");
        printf("\n======================================");
        printf("\n |1| Gerenciar visitante");
        printf("\n |2| Realizar sorteio");
        printf("\n |3| Enviar comunicado por e-mail");
        printf("\n |4| Sair");
        printf("\n--------------------------------------");
        printf("\n Escolha uma opção: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:// gerenciar visitante
                do
                {
                    /* Carregar menu do gerenciamento do visitante*/
                    system("cls");
                    printf("\n======================================");
                    printf("\n          GERENCIAR VISITANTE ");
                    printf("\n======================================");
                    printf("\n |1| Incluir visitante");
                    printf("\n |2| Excluir visitante");
                    printf("\n |3| Listar lugares livres");
                    printf("\n |4| Listar lugares ocupados");
                    printf("\n |5| Mostar disposição dos assentos");
                    printf("\n |6| Retornar ao menu inicial");
                    printf("\n----------------------------------------");
                    printf("\n Escolha uma opção: ");
                    scanf("%d", &op);
                    switch(op)
                    {
                        case 1://
                            /* Formulario de Cadastro */
                            system("cls");
                            printf("\n======================================");
                            printf("\n      FORMULARIO DE CADASTRO ");
                            printf("\n======================================");
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
                            /* Recupera a quantidade de segundos desde 01/01/1970 */
                            time_t agora;
                            agora = time(NULL);
                            /* Formata a data e a hora da forma desejada e guarda na variavel datahora do visitante */
                            strftime(visitante[idg].datahora, sizeof(visitante[idg].datahora), " Data: %d/%m/%Y \n Hora: %H:%M:%S", localtime( &agora ));
                            visitante[idg].id = idg;
                            /* Mostrar e escolher assento */
                            system("cls");
                            printf("\n                                ESCOLHA UM ASSENTO \n\n");
                            mostrarAssentos();
                            if(strcmp(visitante[idg].convidado, "s") == 0)// verifica se é convidado
                            {
                                printf("\n----------------------------------------------------");
                                printf("\n  INFORME A COLUNA DO ASSENTO DE CONVIDADO DESEJADA ");
                                printf("\n----------------------------------------------------");
                                printf("\n Coluna(1 - 10): ");
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
                                    /* Guardar o assento */
                                    sprintf(visitante[idg].assento,"Linha C coluna %d", nassento);// guarda o valor no char
                                    system("cls");
                                    ticket(idg);
                                    printf("\n\n Reserva realizada com sucesso.");
                                    printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                                    getch();
                                    idg = idg + 1; // gera novo id
                                }
                            }
                            else
                            {
                                if(strcmp(visitante[idg].especial, "s") == 0) // Verifica se é especial
                                {
                                    printf("\n--------------------------------------------------");
                                    printf("\n  INFORME A COLUNA DO ASSENTO ESPECIAL DESEJADA ");
                                    printf("\n--------------------------------------------------");
                                    printf("\n Coluna(1 - 3): ");
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
                                        /* Guardar o assento */
                                        sprintf(visitante[idg].assento,"Linha E coluna %d", nassento);// guarda o valor no char
                                        system("cls");
                                        ticket(idg);
                                        printf("\n\n Reserva realizada com sucesso.");
                                        printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                                        getch();
                                        idg = idg + 1; // gera novo id
                                        ativasorteio = 1;// ativa o sorteio
                                    }
                                }
                                else // assento comum
                                {
                                    printf("\n--------------------------------------------------");
                                    printf("\n   INFORME A LINHA E A COLUNA DO ASSENTO COMUM ");
                                    printf("\n--------------------------------------------------");
                                    printf("\n Linha(1 - 4): ");
                                    scanf("%d", &linha);
                                    printf(" Coluna(1 - 10): ");
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
                                        /* Guardar o assento */
                                        sprintf(visitante[idg].assento,"Linha %d coluna %d", linha, coluna);// guarda o valor no char
                                        system("cls");
                                        ticket(idg);
                                        printf("\n\n Reserva realizada com sucesso.");
                                        printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                                        getch();
                                        idg = idg + 1; // gera novo id
                                        ativasorteio = 1;// ativa o sorteio
                                    }
                                    getch();
                                }
                            }
                            break;
                        case 2:// Excluir visitante
                            system("cls");
                            printf("\n=========================================");
                            printf("\n    TIPO DE ASSENTO QUE DESEJA LIBERAR");
                            printf("\n=========================================");
                            printf("\n |1| Covidado");
                            printf("\n |2| Assentos especiais");
                            printf("\n |3| Comum");
                            printf("\n----------------------------------------");
                            printf("\n Escolha uma opção: ");
                            scanf("%d", &op);
                            /* Mostrar e escolher assento */
                            system("cls");
                            printf("\n                             ESCOLHA UM ASSENTO PARA LIBERAR\n\n");
                            mostrarAssentos();
                            if(op == 1)// se for um convidado
                            {
                                printf("\n----------------------------------------------------");
                                printf("\n  INFORME A COLUNA DO ASSENTO DE CONVIDADO DESEJADA ");
                                printf("\n----------------------------------------------------");
                                printf("\n Coluna(1 - 10): ");
                                scanf("%d", &nassento);
                                if(statusConvidados[nassento - 1] == 1)// verifica se esta ocupada
                                {
                                    statusConvidados[nassento - 1] = 0;// liberar assento
                                    printf("\n Assento liberado com sucesso!");
                                    printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                                    getch();
                                }
                                else// se ja estiver liberado
                                {
                                    printf("\n Assento ja liberado. verifique outra opção.");
                                    getch();
                                }
                            }

                            if(op == 2)// Assentos Especiais
                            {
                                printf("\n--------------------------------------------------");
                                printf("\n  INFORME A COLUNA DO ASSENTO ESPECIAL DESEJADA ");
                                printf("\n--------------------------------------------------");
                                printf("\n Coluna(1 - 3): ");
                                scanf("%d", &nassento);
                                if(statusEspeciais[nassento - 1] == 1)// virifica se esta ocupado
                                {
                                    statusEspeciais[nassento - 1] = 0;
                                    printf("\n Assento liberado com sucesso!");
                                    printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                                    getch();
                                }
                                else // Se ja estiver liberado
                                {
                                    printf("\n Assento ja liberado. verifique outra opção.");
                                    getch();
                                }
                            }

                            if(op == 3)// Assento comun
                            {
                                printf("\n--------------------------------------------------");
                                printf("\n   INFORME A LINHA E A COLUNA DO ASSENTO COMUM ");
                                printf("\n--------------------------------------------------");
                                printf("\n Linha(1 - 4): ");
                                scanf("%d", &linha);
                                printf(" Coluna(1 - 10): ");
                                scanf("%d", &coluna);
                                if(statusAssentos[linha - 1][coluna - 1] == 1)// Se estiver ocupado
                                {
                                    statusAssentos[linha - 1][coluna - 1] = 0;
                                    printf("\n Assento liberado com sucesso!");
                                    printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                                    getch();
                                }
                                else
                                {
                                    printf("\n Assento ja liberado. verifique outra opção.");
                                    getch();
                                }
                            }
                            getch();
                            break;
                        case 3:// listar lugares livres
                            encontrou = 0;// algum assento livre
                            system("cls");
                            printf("\n=========================");
                            printf("\n    ASSENTOS LIVRES");
                            printf("\n=========================");
                            /* Assentos especiais*/
                            for(i = 0; i < 3; i++)
                            {
                                if(statusEspeciais[i] == 0)// verifica se esta livre
                                {
                                    encontrou = 1;
                                    printf("\n Linha E Coluna %d: Livre", i+1);
                                }
                            }
                            putchar('\n');
                            /* Assentos convidados*/
                            for(i = 0; i < 10; i++)
                            {
                                if(statusConvidados[i] == 0)// verifica se esta livre
                                {
                                    encontrou = 1;
                                    printf("\n Linha C coluna %d: Livre", i+1);
                                }
                            }
                            putchar('\n');
                            /* Assentos Comuns */
                            for(i = 0; i < 4; i++)
                            {
                                for(j = 0; j < 10; j++)
                                {
                                    if(statusAssentos[i][j] == 0)// verifica se esta livre
                                    {
                                        encontrou = 1;
                                        printf("\n Linha %d Coluna %d: Livre", i+1, j+1);
                                    }
                                }
                                putchar('\n');
                            }
                            if(encontrou == 0)
                            {
                                printf("/n Todos os Assentos estão ocupados.");
                            }
                            printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                            getch();
                            break;
                        case 4:// listar lugares ocupados
                            encontrou = 0;// algum assento ocupado
                            system("cls");
                            printf("\n============================");
                            printf("\n     ASSENTOS OCUPADOS");
                            printf("\n============================");
                            /* Assentos especiais */
                            for(i = 0; i < 3; i++)
                            {
                                if(statusEspeciais[i] == 1)// verifica se esta ocupado
                                {
                                    encontrou = 1;
                                    printf("\n Linha E coluna %d: Ocupada ", i+1);
                                }
                            }
                            putchar('\n');
                            /* Assentos convidados */
                            for(i = 0; i < 10; i++)
                            {
                                if(statusConvidados[i] == 1)// verifica se esta ocupado
                                {
                                    encontrou = 1;
                                    printf("\n Linha C coluna %d: Ocupada", i+1);
                                }
                            }
                            putchar('\n');
                            /* Assentos comuns */
                            for(i = 0; i < 4; i++)
                            {
                                for(j = 0; j < 10; j++)
                                {
                                    if(statusAssentos[i][j] == 1)// verifica se esta ocupado
                                    {
                                        encontrou = 1;
                                        printf("\n Linha %d Coluna %d: Ocupada", i+1, j+1);
                                    }
                                }
                                putchar('\n');
                            }

                            if(encontrou == 0)
                            {
                                printf("\n Todos os Assentos estão livres.");
                            }
                            printf("\n Precione qualquer tecla para voltar para o menu do visitante...");
                            getch();
                            break;
                        case 5:// Dispossição dos assentos
                            system("cls");
                            printf("\n                             DISPOSIÇÃO DOS ASSENTOS \n\n");
                            mostrarAssentos();
                            printf("\n\n\n\n Precione qualquer tecla para voltar para o menu do visitante...");
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
                    printf("\n======================================");
                    printf("\n              SORTEIO ");
                    printf("\n======================================");
                    printf("\n |1| Realizar sorteio");
                    printf("\n |2| Retornar ao menu inicial");
                    printf("\n----------------------------------------");
                    printf("\n Escolha uma opção: ");
                    scanf("%d", &op);
                    if(op == 1)
                    {
                        if(idg == 0)// Não possui niguem cadastrado ainda
                        {
                            printf("\n Não possui ninguem cadastrado ");
                            getch();
                        }
                        else
                        {
                            if(ativasorteio == 1)// vrifica se possui alguem apto para ser sorteado
                            {
                                sorteio();// sorteia alguem que não é convidado
                            }
                            else
                            {
                                printf("\n Não possui ninguem apto ao sorteio no momento.");
                                getch();
                            }

                        }
                    }
                    else
                    {
                        if(op != 2)
                        {
                            printf("\n Opção invalida. Verifique outra opção.");
                            getch();
                        }
                    }

                }while(op != 2);
                break;
            case 3:// Enviar comunicado por e-mail;
                do
                {
                    system("cls");
                    printf("\n======================================");
                    printf("\n             ENVIAR E-MAIL ");
                    printf("\n======================================");
                    printf("\n |1| Escolher visitante");
                    printf("\n |2| Todos os visitantes");
                    printf("\n |3| Retornar ao menu inicial");
                    printf("\n----------------------------------------");
                    printf("\n Escolha uma opção: ");
                    scanf("%d", &op);
                    switch(op)
                    {
                        case 1:
                            system("cls");
                            printf("\n======================================");
                            printf("\n         ESCOLHER VISITANTE POR ");
                            printf("\n======================================");
                            printf("\n |1| Nome");
                            printf("\n |2| Email");
                            printf("\n |3| Assento");
                            printf("\n----------------------------------------");
                            printf("\n Escolha uma opção: ");
                            scanf("%d", &op);
                            switch(op)// Escolher visitante por
                            {
                                case 1:// por nome
                                    encontrou = 0;// verificar se encontrou
                                    printf("\n Nome: ");
                                    fflush(stdin);
                                    gets(pesquisa);
                                    for(i = 0; i < idg; i++)// laço de repetiçao para encontar alguem com esse nome
                                    {
                                        if(strcmp(pesquisa, visitante[i].nome) == 0)// verifica se o nome é igual
                                        {
                                            encontrou = 1;
                                            pos = i;
                                        }
                                    }
                                    if(encontrou == 1)// enviar o email na pos guardada
                                    {
                                        enviarEmail(pos);
                                    }
                                    else
                                    {
                                        printf("\n Não foi encotrado ninguem com esse nome.");
                                        getch();
                                    }
                                    break;
                                case 2:// por email
                                    encontrou = 0;// verifica se encontrou
                                    printf("\n Email: ");
                                    fflush(stdin);
                                    gets(pesquisa);
                                    for(i = 0; i < idg; i++)
                                    {
                                        if(strcmp(pesquisa, visitante[i].email) == 0)// verifica se o email esta cadastrado
                                        {
                                            encontrou = 1;
                                            pos = i;
                                        }
                                    }

                                    if(encontrou == 1)// Enviar o email na posição encontrada
                                    {
                                        enviarEmail(pos);
                                    }
                                    else
                                    {
                                        printf("\n Não foi encotrado ninguem com esse nome.");
                                        getch();
                                    }
                                    break;
                                case 3:// Por Assento
                                    system("cls");
                                    printf("\n=========================================");
                                    printf("\n            TIPO DE ASSENTO ");
                                    printf("\n=========================================");
                                    printf("\n |1| Covidado");
                                    printf("\n |2| Assentos especiais");
                                    printf("\n |3| Comum");
                                    printf("\n----------------------------------------");
                                    printf("\n Escolha uma opção: ");
                                    scanf("%d", &op);
                                    /* Mostrar e escolher assento */
                                    system("cls");
                                    printf("\n                          ESCOLHA UM ASSENTO PARA ENVIAR O EMAIL\n\n");
                                    mostrarAssentos();
                                    if(op == 1)// se for um convidado
                                    {
                                        printf("\n----------------------------------------------------");
                                        printf("\n  INFORME A COLUNA DO ASSENTO DE CONVIDADO DESEJADA ");
                                        printf("\n----------------------------------------------------");
                                        printf("\n Coluna(1 - 10): ");
                                        scanf("%d", &nassento);

                                        if(statusConvidados[nassento - 1] == 1)// verifica se esta ocupada
                                        {
                                            pos = idConvidados[nassento - 1];
                                            enviarEmail(pos);
                                        }
                                        else// se ja estiver liberado
                                        {
                                            printf("\n Não tem ninguem neste assento.");
                                            getch();
                                        }
                                    }
                                    if(op == 2)// Assento especial
                                    {
                                        printf("\n--------------------------------------------------");
                                        printf("\n  INFORME A COLUNA DO ASSENTO ESPECIAL DESEJADA ");
                                        printf("\n--------------------------------------------------");
                                        printf("\n Coluna(1 - 3): ");
                                        scanf("%d", &nassento);
                                        if(statusEspeciais[nassento - 1] == 1)//verifica se esta ocupada se tiver envia o email
                                        {
                                            pos = idEspecial[nassento - 1];
                                            enviarEmail(pos);
                                        }
                                        else
                                        {
                                            printf("\n Não tem ninguem neste assento.");
                                            getch();
                                        }
                                    }
                                    if(op == 3)//Assento comun
                                    {
                                        printf("\n--------------------------------------------------");
                                        printf("\n   INFORME A LINHA E A COLUNA DO ASSENTO COMUM ");
                                        printf("\n--------------------------------------------------");
                                        printf("\n Linha(1 - 4): ");
                                        scanf("%d", &linha);
                                        printf(" Coluna(1 - 10): ");
                                        scanf("%d", &coluna);
                                        if(statusAssentos[linha - 1][coluna - 1] == 1)//verifica se esta ocupado se tiver envia o email
                                        {
                                            pos = idAssentos[linha - 1][coluna - 1];
                                            enviarEmail(pos);
                                        }
                                        else
                                        {
                                            printf("\n Não tem ninguem neste assento.");
                                            getch();
                                        }
                                    }
                                    op = 0;
                                    break;
                                default:
                                    printf("\n Opção invalida.");
                                    break;
                            }
                            break;
                        case 2:// Todos os visitante
                            if(idg > 0)//ja tem alguem cadastrado
                            {
                                system("cls");
                                printf("\n------------------------ ENVIAR E-MAIL ------------------------");
                                printf("\n\n PARA: ");
                                for(i = 0; i < idg; i++)// for que peccore todos os visitantes
                                {
                                    printf(" %s; ", visitante[i].email);//mostar email na tela
                                }
                                printf("\n ASSUNTO: Direito Humanos                              \n");
                                printf("\n---------------------------------------------------------------");
                                printf("\n\n                O que são direitos humanos \n\n  Direitos humanos são os direitos básicos de todos os seres\n humanos. São direitos civis e políticos; direitos\n econômicos, sociais e culturais;");
                                printf("\n\n\n Precione qualquer tecla para enviar o email...");
                                getch();
                            }
                            else
                            {
                                printf("\n Não possui ninguem cadastrado ");
                                getch();
                            }

                            break;
                        case 3:
                            break;
                        default:
                            printf("\n Opção invalida.");
                            getch();
                            break;
                    }
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
     printf("\n         E - ASSENTOS ESPECIAIS               C -  CONVIDADOS \n");

}// End mostrarAssentos()


void ticket(int id)
{
    printf("\n------------ Ticket ------------");
    printf("\n Nome: %s", visitante[id].nome);
    printf("\n Assento: ");
    puts(visitante[idg].assento);
    printf("%s", visitante[id].datahora);
    printf("\n--------------------------------");
}// End ticket

void sorteio()
{
    int sorteado;
    sorteado = rand() % idg;
    if(strcmp(visitante[sorteado].convidado, "s") == 0)// verifica se é convidado se for sorteia novamente
    {
        sorteio();
    }
    else// se nao for convidado mostar quem foi o sortudoo
    {
        system("cls");
        printf("\n==========================================");
        printf("\n           VENCEDOR DO SORTEIO");
        printf("\n===========================================");
        printf("\n\n Nome: %s", visitante[sorteado].nome);
        printf("\n Email: %s", visitante[sorteado].email);
        printf("\n Assento: %s", visitante[sorteado].assento);
        printf("\n\n------------------------------------------");
        getch();
    }
}// End sorteio

void enviarEmail(int id)
{
    system("cls");
    printf("\n------------------------ ENVIAR E-MAIL ------------------------");
    printf("\n\n PARA: %s;                                              ", visitante[id].email);
    printf("\n ASSUNTO: Direito Humanos                              \n");
    printf("\n---------------------------------------------------------------");
    printf("\n\n                O que são direitos humanos \n\n  Direitos humanos são os direitos básicos de todos os seres\n humanos. São direitos civis e políticos; direitos\n econômicos, sociais e culturais;");
    printf("\n\n\n Precione qualquer tecla para enviar o email...");
    getch();
}// End enviarEmail
