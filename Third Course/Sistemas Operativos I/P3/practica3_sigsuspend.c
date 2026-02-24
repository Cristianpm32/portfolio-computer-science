#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>

#define PRESONER1_ID 1
#define PRESONER2_ID 2
#define NUM_OPCIONS 2
#define NUM_PAGAMENTS 4
#define MAX_LEN 100
#define COOPERA 0
#define TRAICIONA 1
#define COOPERA_DESCRIPCIO "coopera"
#define TRAICIONA_DESCRIPCIO "traiciona"
#define NUM_ESTRATEGIES 6
#define ESTRATEGIA_RANDOM 0
#define ESTRATEGIA_COOPERA 1
#define ESTRATEGIA_TRAICIONA 2
#define ESTRATEGIA_TIT_FOR_TAT 3
#define ESTRATEGIA_GRIM_TRIGGER 4
#define ESTRATEGIA_PAVLOV 5

typedef struct
{
    int opcio_pr1;
    int opcio_pr2;
    int pagament_pr1;
    int pagament_pr2;
} pagament;

int sigusr1 = 0;
sigset_t mask, mask2;

int llegir_pagaments(const char *filename, pagament *array, int max_size);
void sigusr1_handler(int sig);
void funcio_presoner_generica(int estrategia_presoner, int n, int fdFillToPare[2], int fdPareToFill[2]);
void funcio_pare(int n, int fdFillToPare[2], int fdPareToFill[2], int presoner1, int presoner2, pagament p_array[NUM_PAGAMENTS], int anys_pena_pr1, int anys_pena_pr2);

int main(int argc, char *argv[])
{
    char *fitxer_pagaments;
    int estrategia_pr1, estrategia_pr2, N;
    int anys_pena_pr1 = 0, anys_pena_pr2 = 0;
    pagament p_array[NUM_PAGAMENTS];

    // Llegir parameters
    if (argc != 5)
    {
        printf("%s <fitxer_pagaments> <estrategia_pr1> <estrategia_pr2> <N>\n", argv[0]);
        exit(1);
    }

    fitxer_pagaments = argv[1];
    estrategia_pr1 = atoi(argv[2]); // Quina estrategia segueix el presoner1
    estrategia_pr2 = atoi(argv[3]); // Quina estrategia segueix el presoner2
    N = atoi(argv[4]);

    if (N < 1)
    {
        printf("N no pot ser zero o negatiu!\n");
        exit(1);
    }

    // Llegir fitxer amb pagaments
    if (llegir_pagaments(fitxer_pagaments, p_array, 100) == -1)
    {
        printf("Error llegint el fitxer de pagaments!\n");
        exit(1);
    }

    if (estrategia_pr1 > NUM_ESTRATEGIES - 1 || estrategia_pr2 > NUM_ESTRATEGIES - 1)
    {
        printf("Error en la selecció de l'estrategia\n");
        exit(1);
    }

    int fdFillToPare[2];
    int fdPareToFill[2];
    pipe(fdFillToPare);
    pipe(fdPareToFill);

    signal(SIGUSR1, sigusr1_handler); // Potser s'ha de fer fora de la funcio aixo!

    sigemptyset(&mask2);
    sigaddset(&mask2, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask2, &mask);

    int presoner1 = fork();

    if (presoner1 == 0)
    {
        funcio_presoner_generica(estrategia_pr1, N, fdFillToPare, fdPareToFill);
    }
    else
    {
        int presoner2 = fork();
        if (presoner2 == 0)
        {
            funcio_presoner_generica(estrategia_pr2, N, fdFillToPare, fdPareToFill);
        }
        else
        {
            funcio_pare(N, fdFillToPare, fdPareToFill, presoner1, presoner2, p_array, anys_pena_pr1, anys_pena_pr2);
        }
    }

    // TO-BE-DONE

    return 0;
}

void funcio_presoner_generica(int estrategia_presoner, int n, int fdFillToPare[2], int fdPareToFill[2])
{
    int decisio_altre_presoner;
    srand(getpid()); // Li passem el PID del proces com a lllavor?¿?--
    bool haTraitGrim = false;
    bool haTraitPavlov = false;

    for (int i = 0; i < n; i++)
    {

        sigsuspend(&mask);

        if (i > 0)
        {
            read(fdPareToFill[0], &decisio_altre_presoner, sizeof(decisio_altre_presoner));
        }
        int decisio;
        switch (estrategia_presoner)
        {
        case ESTRATEGIA_RANDOM:
            decisio = rand() % NUM_OPCIONS;
            break;

        case ESTRATEGIA_COOPERA:
            decisio = COOPERA;
            break;

        case ESTRATEGIA_TRAICIONA:
            decisio = TRAICIONA;
            break;

        case ESTRATEGIA_TIT_FOR_TAT:
            if (i == 0)
            {
                decisio = COOPERA;
            }
            else
            {
                decisio = decisio_altre_presoner;
            }
            break;

        case ESTRATEGIA_GRIM_TRIGGER:
            if (i == 0)
            {
                decisio = COOPERA;
            }
            else
            {
                if (haTraitGrim == false && decisio_altre_presoner == COOPERA)
                {
                    decisio = COOPERA;
                }
                else
                {
                    haTraitGrim = true;
                    decisio = TRAICIONA;
                }
            }
            break;

        /*
        ###############################
        # ESTRATÈGIA ALTERNATIVA      
        ###############################
        */
        
        case ESTRATEGIA_PAVLOV:
            if (i == 0)
            {
                decisio = COOPERA;
            }
            else
            {
                if (haTraitPavlov == false && decisio_altre_presoner == COOPERA)
                {
                    decisio = COOPERA;
                }
                else
                {
                    haTraitPavlov = true;
                    decisio = decisio_altre_presoner == COOPERA ? TRAICIONA : COOPERA;
                }
            }
            break;
        default:

            break;
        }

        write(fdFillToPare[1], &decisio, sizeof(decisio));
    }
    // TO-BE-DONE
}

void funcio_pare(int n, int fdFillToPare[2], int fdPareToFill[2], int presoner1, int presoner2, pagament p_array[NUM_PAGAMENTS], int anys_pena_pr1, int anys_pena_pr2)
{
    int decisio_pr1;
    int decisio_pr2;
    int decisio_pr1_torn_anterior;
    int decisio_pr2_torn_anterior;

    sigprocmask(SIG_UNBLOCK, &mask2, &mask);
    for (int i = 0; i < n; i++)
    {
        printf("Ha començat el torn %d\n", i);

        // TORN DEL PRESONER 1
        if (i > 0)
        {
            write(fdPareToFill[1], &decisio_pr2_torn_anterior, sizeof(decisio_pr2_torn_anterior));
        }
        kill(presoner1, SIGUSR1); // Aixo en teoria hauria d'anar abans del write (pero no te sentit enviar el torn abans d'enviar la jugada anterior)

        read(fdFillToPare[0], &decisio_pr1, sizeof(decisio_pr1));

        printf("El presoner 1 ha escollit %d\n", decisio_pr1);

        // TORN DEL PRESONER 2
        if (i > 0)
        {
            write(fdPareToFill[1], &decisio_pr1_torn_anterior, sizeof(decisio_pr1_torn_anterior));
        }
        kill(presoner2, SIGUSR1);

        read(fdFillToPare[0], &decisio_pr2, sizeof(decisio_pr2));

        printf("El presoner 2 ha escollit %d\n", decisio_pr2);

        for (int i = 0; i < NUM_PAGAMENTS; i++)
        {
            if (p_array[i].opcio_pr1 == decisio_pr1 && p_array[i].opcio_pr2 == decisio_pr2)
            {

                anys_pena_pr1 += p_array[i].pagament_pr1; // Anem acumulant els anys de pena del prisoner 1
                anys_pena_pr2 += p_array[i].pagament_pr2; // Anem acumulant els anys de pena del prisoner 2
                break;
            }
        }

        printf("El presoner 1 ha estat condemnat a %d anys de presó\n", anys_pena_pr1);
        printf("El presoner 2 ha estat condemnat a %d anys de presó\n", anys_pena_pr2);

        decisio_pr1_torn_anterior = decisio_pr1; // Assignam la jugada del presoner 1 per a que el presoner 2 pugui saber quina ha estat la jugada anterior
        decisio_pr2_torn_anterior = decisio_pr2; // Assignam la jugada del presoner 2 per a que el presoner 1 pugui saber quina ha estat la jugada anterior
    }

    //

    printf("Final");

    close(fdFillToPare[0]);
    close(fdFillToPare[1]);
    close(fdPareToFill[0]);
    close(fdPareToFill[1]);
    // print
}

void sigusr1_handler(int sig) {}

int llegir_pagaments(const char *filename, pagament *array, int max_size)
{
    FILE *fp;
    char line[MAX_LEN];
    char *token;
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return -1;
    }

    while (fgets(line, MAX_LEN, fp) != NULL && count < max_size)
    {
        token = strtok(line, ",");
        array[count].opcio_pr1 = atoi(token);
        token = strtok(NULL, ",");
        array[count].opcio_pr2 = atoi(token);
        token = strtok(NULL, ",");
        array[count].pagament_pr1 = atoi(token);
        token = strtok(NULL, ",");
        array[count].pagament_pr2 = atoi(token);
        count++;
    }

    fclose(fp);
    return count;
}
