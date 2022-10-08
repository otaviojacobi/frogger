#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>

#define LARGURA 56
#define ALTURA 28
#define VIDAS 3
#define MOVIMENTOS 50
typedef struct  TIPO_FASE
{
    char objeto;
    int tamanho;
    int espacamento;
    float velocidade;
    int linha_inicial;
    int coluna_inicial;
} FASE;
void jogo();
void jogo_carregado();
void matriz_colisao(int matriz[][LARGURA]);
void vitoria(int matriz[][LARGURA]);
void colisao_carro(int matriz[][LARGURA], FASE *carro);
void colisao_tronco(int matriz[][LARGURA], FASE *tronco);
void colisao_tartaruga(int matriz[][LARGURA], FASE *tartaruga, int *posicao);
void mexe_sapo(FASE *sapo, char *sair, int *movimentos);
void mexe_tronco(FASE *tronco);
void mexe_carro(FASE *carro);
void mexe_tartaruga(FASE *tartaruga,int *posicao);

void putchxy(int x, int y, char c) {
    gotoxy(x,y);
    putch(c);
}

void menu ()
{
    int escolha;
    char cursor;
    int x=29, y=13;
    clrscr();
    gotoxy(20,3);
    printf(" ______                               ");
    gotoxy(20,4);
    printf("|  ____|                              ");
    gotoxy(20,5);
    printf("| |__ _ __ ___   __ _  __ _  ___ _ __ ");
    gotoxy(20,6);
    printf("|  __| '__/ _ \\ / _` |/ _` |/ _ \\ '__|");
    gotoxy(20,7);
    printf("| |  | | | (_) | (_| | (_| |  __/ |   ");
    gotoxy(20,8);
    printf("|_|  |_|  \\___/ \\__, |\\__, |\\___|_|   ");
    gotoxy(20,9);
    printf("                 __/ | __/ |          ");
    gotoxy(20,9);
    printf("                |___/ |___/           ");


    gotoxy(30,13);
    printf("Novo Jogo\n");

    gotoxy(30,18);
    printf("Continuar jogo\n");

    gotoxy(30,23);
    printf("Sair\n");

    putchxy (x, y, '>');
    putchxy (x-1, y, '-');
    do
    {

        cursor=getch();
        if(cursor<0)
            cursor = getch();

        switch(cursor)
        {

        case 'w':
            if(y<23)
            {
                y=y+5;
                putchxy(x-1, y-5, ' ');
                putchxy(x, y-5, ' ');
                putchxy(x, y, '>');
                putchxy(x-1, y, '-');

            }


            break;

        case 's':
            if(y>13)
            {
                y=y-5;
                putchxy(x-1, y+5, ' ');
                putchxy(x, y+5, ' ');
                putchxy(x, y, '>');
                putchxy(x-1, y, '-');

            }

            break;
        }



    }
    while ((int)cursor!=10);

    if(y==13) escolha=1;
    if(y==18) escolha=2;
    if(y==23) escolha=3;





    switch(escolha)
    {
    case 1:
        jogo();
        break;
    case 2: //carrega jogo
        jogo_carregado();
        break;
    case 3:
        return 0;
    }
    menu();
}

void mexe_sapo(FASE *sapo, char *sair, int *movimentos)
{

    int x, y;
    char op;

    x=sapo->coluna_inicial;
    y=sapo->linha_inicial;
    fflush(stdin);

    op=getch();

    if(op<0)
        op=getch();


    switch(op)
    {
    case 'w':

        if(y>=4)
        {
            gotoxy(x,y);
            printf("  ");
            gotoxy(x,y+1 );
            printf("  ");
            y-=2;
            gotoxy(x,y);
            printf("@@");
            gotoxy(x,y + 1);
            printf("00");

            *movimentos-=1;

        }
        break;

    case 's':

        if(y<= ALTURA-2)
        {
            gotoxy(x,y);
            printf("  ");
            gotoxy(x,y + 1);
            printf("  ");
            y+=2;
            gotoxy(x,y);
            printf("@@");
            gotoxy(x,y + 1);
            printf("00");

            *movimentos-=1;

        }
        break;

    case 'a':

        if(x>=3)
        {
            gotoxy(x,y);
            printf("  ");
            gotoxy(x,y+1);
            printf("  ");
            x-=2;
            gotoxy(x,y);
            printf("@@");
            gotoxy(x,y+1);
            printf("00");

            *movimentos-=1;
        }
        break;

    case 'd':

        if(x<= LARGURA-2)
        {
            gotoxy(x,y);
            printf("  ");
            gotoxy(x,y+1);
            printf("  ");
            x+=2;
            gotoxy(x,y);
            printf("@@");
            gotoxy(x,y+1);
            printf("00");

            *movimentos-=1;
        }
        break;


    }

    sapo->coluna_inicial=x;//atualiza o valor da coluna inicial do sapo
    sapo->linha_inicial=y;//atualiza o valor da linha inicial do sapo
    *sair=op;//devolve o que o usuario digito para a main
}

void inicia_sapo(FASE *sapo)
{
    int x, y;

    x=sapo->coluna_inicial;
    y=sapo->linha_inicial;

    putchxy(x, y, '@');
    putchxy(x+1,y, '@');
    putchxy(x, y+1, '0');
    putchxy(x+1, y+1, '0');

}
void printa_agua()
{
    int j,i;
    for(j=5; j<15; j++)
    {
        for(i=1; i<=LARGURA; i++)
        {
            gotoxy(i,j);
            printf("~");
        }
    }
}

void mexe_tronco(FASE *tronco)
{
    int x,y,tamanho,i, j;
    float velocidade;

    x = tronco->coluna_inicial;
    y = tronco->linha_inicial;
    tamanho = tronco->tamanho;
    velocidade = tronco->velocidade;

    gotoxy(x,y);
    for(j=0; j<tamanho; j++)
    {
        gotoxy((x+j)%(LARGURA-1)+1,y);
        printf("~~");
        gotoxy((x+j)%(LARGURA-1)+1,y+1);
        printf("~~");
    }

    x+=2*velocidade;
    if(velocidade > 0 && x>LARGURA)
        x=1;
    if(velocidade< 0 && x<= 0)
        x= LARGURA-1;


    for(i=0; i<2*tamanho; i++)
    {
        gotoxy((x+i)%(LARGURA-1)+1,y);
        printf("#");
        gotoxy((x+i)%(LARGURA-1)+1,y+1);
        printf("#");
    }

    tronco->coluna_inicial= x;
    tronco->linha_inicial= y;

}

void jogo()
{
    int vida=VIDAS, i, j, tartaruga_disponivel=0,movimento;
    FILE *salvo;
    int colisao[ALTURA+3][LARGURA]= {};
    char cursor='c';
    int estado_sapo, ganhou=0;
    int dificuldade=-72000;
    FASE tronco[9]= {{'T',4,4,+1,5,3} , {'T',3,3,1,5,25}, {'T',4,4,+1,5,41},
        {'T',3,4,+1,9,1} , {'T',3,4,+1,9,19}, {'T',4,4,+1,9,37},
        {'T',3,3,+1,13,5} , {'T',4,4,+1,13,23}, {'T',4,4,+1,13,45},
    };
    FASE carro[11]=  {{'C',4,3,1,17,3} , {'C',4,3,1,17,25},{'C',4,3,1,17,43},
        {'C',4,3,-1,19,1} , {'C',4,3,-1,19,38},
        {'C',4,3,+1,21,19} ,
        {'C',4,3,+1,23,19} , {'C',4,3,+1,23,43},
        {'C',4,3,-1,25,1} , {'C',4,3,-1,25,41}, {'C',4,3,-1,25,23}
    };
    FASE tartaruga[6]= {{'R', 20, 6, -1, 7, 3}  , {'R', 5, 4, -1, 7, 19} , {'R', 2, 6, -1, 7, 42},
        {'R', 2, 4, -1, 11, 1} , {'R', 3, 6, -1, 11, 24}, {'R', 2, 6, -1, 11, 40}

    };
    FASE sapo= {'S',1,0,0,ALTURA-1,LARGURA/2};

    do
    {
        system("cls");

        movimento=MOVIMENTOS;

        sapo.coluna_inicial = LARGURA/2;
        sapo.linha_inicial = ALTURA-1;



        gotoxy(1,3);//printa as casinhas do sapo
        printf("  |**|        |**|        |**|        |**|        |**|  ");
        gotoxy(1,4);
        printf("  |**|        |**|        |**|        |**|        |**|  ");

        printa_agua();

        do
        {
            gotoxy(1,1);
            printf("Vidas: %d       Pontos: %d  ", vida, movimento);

            matriz_colisao(colisao);
            inicia_sapo(&sapo);

            tartaruga_disponivel++;
            if(tartaruga_disponivel==30)
                tartaruga_disponivel=3;

            vitoria(colisao);

            for(i=0; i<9; i++)
            {
                mexe_tronco(&tronco[i]);
                colisao_tronco(colisao, &tronco[i]);
            }
            inicia_sapo(&sapo);
            for(i=0; i<11; i++)
            {
                mexe_carro(&carro[i]);
                colisao_carro(colisao, &carro[i]);


            }
            for(i=0; i<6; i++)
            {
                mexe_tartaruga(&tartaruga[i],&tartaruga_disponivel);
                colisao_tartaruga(colisao,&tartaruga[i],&tartaruga_disponivel);
            }
            inicia_sapo(&sapo);
            i=0;


            estado_sapo=0;

            while(i<10000-(500*dificuldade))
            {



                if(kbhit())
                    mexe_sapo(&sapo,&cursor,&movimento);
                i++;
                if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==4) estado_sapo = 4;
                else
                {
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==1) movimento = 0;
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==1) movimento = 0;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial+1] ==1) movimento = 0;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial]==1) movimento = 0;


                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==2) estado_sapo = 2;
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==2) estado_sapo = 2;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial+1] ==2) estado_sapo = 2;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial]==2) estado_sapo = 2;

                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==3) estado_sapo = 3;
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==3) estado_sapo = 3;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial+1] ==3) estado_sapo = 3;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial]==3) estado_sapo = 3;

                }







                //if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==4) movimento=0;
            }
            if(estado_sapo==2)
                sapo.coluna_inicial-=2;
            if(estado_sapo==3)
                sapo.coluna_inicial+=2;
            if(estado_sapo == 4)
            {
                dificuldade++;
                ganhou++;
                movimento += 50;
                //inicia_sapo(&sapo);
                //aumentar dificuldade a.k.a. velocidade - pensei em uma função que retornasse um valor pra ser usado dentro do while e cada vez que atingisse uma casa diminuia esse valor
                sapo.coluna_inicial = LARGURA/2;
                sapo.linha_inicial = ALTURA-1;
            }

            //
            cursor=tolower(cursor);
            if(cursor=='f')
            {
                salvo=fopen("wiseman.bin","wb");
                if(!salvo)
                    printf("\aError ao abrir o aquivo");
                else
                {
                    for(i=0; i<9; i++)
                    {
                        if( fwrite(&tronco[i],sizeof(FASE),1,salvo) !=1)
                        {
                            clrscr();
                            printf("Erro ao salvar o arquivo");
                            fclose(salvo);
                            return 0;
                        }

                    }
                    for(i=0; i<11; i++)
                    {
                        if( fwrite(&carro[i],sizeof(FASE),1,salvo) !=1)
                        {
                            clrscr();
                            printf("Erro ao salvar o arquivo");
                            fclose(salvo);
                            return 0;
                        }

                    }
                    for(i=0; i<6; i++)
                    {
                        if( fwrite(&tartaruga[i],sizeof(FASE),1,salvo) !=1)
                        {
                            clrscr();
                            printf("Erro ao salvar o arquivo");
                            fclose(salvo);
                            return 0;
                        }

                    }
                    if(1 != fwrite(&sapo,sizeof(FASE),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&movimento,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&vida,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&ganhou,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&tartaruga_disponivel,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&dificuldade,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                }

                fclose(salvo);
            }
        }
        while(movimento>0 && cursor != 'q' && ganhou!=5 );
        vida--;
        if(ganhou == 5)
        {
            printf("Voce ganhou o jogo, sua pontuação foi de %d",movimento);
        }



    }
    while(vida>0 && cursor != 'q' && cursor != 'Q');

}

void mexe_carro(FASE *carro)
{
    int i;

    gotoxy(carro->coluna_inicial%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy(carro->coluna_inicial%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    gotoxy((carro->coluna_inicial+1)%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy((carro->coluna_inicial+1)%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    gotoxy((carro->coluna_inicial+2)%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy((carro->coluna_inicial+2)%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    gotoxy((carro->coluna_inicial+3)%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy((carro->coluna_inicial+3)%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    gotoxy((carro->coluna_inicial+4)%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy((carro->coluna_inicial+4)%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    gotoxy((carro->coluna_inicial+5)%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy((carro->coluna_inicial+5)%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    gotoxy((carro->coluna_inicial+6)%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy((carro->coluna_inicial+6)%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    gotoxy((carro->coluna_inicial+7)%(LARGURA-1)+1,carro->linha_inicial);
    printf(" ");
    gotoxy((carro->coluna_inicial+7)%(LARGURA-1)+1,carro->linha_inicial+1);
    printf(" ");

    carro->coluna_inicial += 2*carro->velocidade;

    if(carro->coluna_inicial>LARGURA-2 && carro->velocidade>0)
        carro->coluna_inicial=1;
    if(carro->coluna_inicial<2 && carro->velocidade<0)
        carro->coluna_inicial=LARGURA-1;

    if(carro->velocidade<0)
    {
        gotoxy(carro->coluna_inicial%(LARGURA-1)+1,carro->linha_inicial);
        printf(" ");
        gotoxy(carro->coluna_inicial%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("/");

        gotoxy((carro->coluna_inicial+1)%(LARGURA-1)+1,carro->linha_inicial);
        printf("_");
        gotoxy((carro->coluna_inicial+1)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial+2)%(LARGURA-1)+1,carro->linha_inicial);
        printf("_");
        gotoxy((carro->coluna_inicial+2)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("o");

        gotoxy((carro->coluna_inicial+3)%(LARGURA-1)+1,carro->linha_inicial);
        printf("/");
        gotoxy((carro->coluna_inicial+3)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial+4)%(LARGURA-1)+1,carro->linha_inicial);
        printf("=");
        gotoxy((carro->coluna_inicial+4)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial+5)%(LARGURA-1)+1,carro->linha_inicial);
        printf("|");
        gotoxy((carro->coluna_inicial+5)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("o");

        gotoxy((carro->coluna_inicial+6)%(LARGURA-1)+1,carro->linha_inicial);
        printf("_");
        gotoxy((carro->coluna_inicial+6)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial+7)%(LARGURA-1)+1,carro->linha_inicial);
        printf(" ");
        gotoxy((carro->coluna_inicial+7)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("\\");


    }

    if(carro->velocidade>0)
    {
        gotoxy((carro->coluna_inicial+7)%(LARGURA-1)+1,carro->linha_inicial);
        printf(" ");
        gotoxy((carro->coluna_inicial+7)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("\\");

        gotoxy((carro->coluna_inicial+6)%(LARGURA-1)+1,carro->linha_inicial);
        printf("_");
        gotoxy((carro->coluna_inicial+6)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial+5)%(LARGURA-1)+1,carro->linha_inicial);
        printf("_");
        gotoxy((carro->coluna_inicial+5)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("o");

        gotoxy((carro->coluna_inicial+4)%(LARGURA-1)+1,carro->linha_inicial);
        printf("\\");
        gotoxy((carro->coluna_inicial+4)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial+3)%(LARGURA-1)+1,carro->linha_inicial);
        printf("=");
        gotoxy((carro->coluna_inicial+3)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial+2)%(LARGURA-1)+1,carro->linha_inicial);
        printf("|");
        gotoxy((carro->coluna_inicial+2)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("o");

        gotoxy((carro->coluna_inicial+1)%(LARGURA-1)+1,carro->linha_inicial);
        printf("_");
        gotoxy((carro->coluna_inicial+1)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("_");

        gotoxy((carro->coluna_inicial)%(LARGURA-1)+1,carro->linha_inicial);
        printf(" ");
        gotoxy((carro->coluna_inicial)%(LARGURA-1)+1,carro->linha_inicial+1);
        printf("/");

    }
}

void mexe_tartaruga(FASE *tartaruga,int *posicao)
{

    int x,y,tamanho,i, j;
    float velocidade;

    x = tartaruga->coluna_inicial;
    y = tartaruga->linha_inicial;
    tamanho = tartaruga->tamanho;
    velocidade = tartaruga->velocidade;


    for(j=0; j<=tamanho; j++)
    {
        gotoxy((x+j)%(LARGURA-1)+1,y);
        printf("~~");
        gotoxy((x+j)%(LARGURA-1)+1,y+1);
        printf("~~");
    }

    x+=2*velocidade;
    if(velocidade > 0 && x>LARGURA)
        x=1;
    if(velocidade< 0 && x<= 0)
        x= LARGURA-1;

    if(*posicao<10)
    {
        //for(j=0; j<= tamanho; j++) - tentei fazer a tartaruga ter tamanho diferente de 2, mas n rolou
        //{
        gotoxy((x)% (LARGURA-1)+1,y);
        printf("\\");
        gotoxy((x)% (LARGURA-1)+1,y+1);
        printf("/");

        gotoxy((x+1)% (LARGURA-1)+1,y);
        printf("/");
        gotoxy((x+1)% (LARGURA-1)+1,y+1);
        printf("\\");

        gotoxy((x+2)% (LARGURA-1)+1,y);
        printf("\\");
        gotoxy((x+2)% (LARGURA-1)+1,y+1);
        printf("/");

        gotoxy((x+3)% (LARGURA-1)+1,y);
        printf("/");
        gotoxy((x+3)% (LARGURA-1)+1,y+1);
        printf("\\");

    }//}
    else
    {
        //for(j=0; j<= tamanho; j++){

        gotoxy((x)% (LARGURA-1)+1,y);
        printf("/");
        gotoxy((x)% (LARGURA-1)+1,y+1);
        printf("\\");

        gotoxy((x+1)% (LARGURA-1)+1,y);
        printf("\\");
        gotoxy((x+1)% (LARGURA-1)+1,y+1);
        printf("/");

        gotoxy((x+2)% (LARGURA-1)+1,y);
        printf("/");
        gotoxy((x+2)% (LARGURA-1)+1,y+1);
        printf("\\");

        gotoxy((x+3)% (LARGURA-1)+1,y);
        printf("\\");
        gotoxy((x+3)% (LARGURA-1)+1,y+1);
        printf("/");

    }//}


    tartaruga->coluna_inicial= x;
    tartaruga->linha_inicial= y;

}

void vitoria(int matriz[][LARGURA])
{
    matriz[3][4]=4;
    matriz[3][16]=4;
    matriz[3][28]=4;
    matriz[3][40]=4;
    matriz[3][52]=4;

}

void matriz_colisao(int matriz[][LARGURA])
{
    int i, j;

    for(j=0; j<ALTURA; j++)
        for(i=0; i<LARGURA; i++)
        {
            if(j<ALTURA/2 )
                matriz[j][i]=1;
            else
                matriz[j][i]=0;
        }

}

void colisao_carro(int matriz[][LARGURA], FASE *carro)
{

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+0)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+1)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+2)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+3)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+4)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+5)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+6)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial+1] [(carro->coluna_inicial+7)%(LARGURA-1)+2]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+0)%(LARGURA-1)]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+1)%(LARGURA-1)]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+2)%(LARGURA-1)]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+3)%(LARGURA-1)]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+4)%(LARGURA-1)]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+5)%(LARGURA-1)]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+6)%(LARGURA-1)]= 1;

    matriz[carro->linha_inicial] [(carro->coluna_inicial+7)%(LARGURA-1)]= 1;


}

void colisao_tronco(int matriz[][LARGURA], FASE *tronco)
{
    int i;
    int tamanho=tronco->tamanho;

    /*for(i=0; i<tamanho; i++)
    {
        gotoxy((x+i)%(LARGURA-1)+1,y);
        printf("##");
        gotoxy((x+i)%(LARGURA-1)+1,y+1);
        printf("##");
    }*/

    for(i=0; i<2*tamanho; i++)
    {
        matriz[tronco->linha_inicial][(tronco->coluna_inicial+i)%(LARGURA-1)+1] = 3;
        matriz[tronco->linha_inicial+1][(tronco->coluna_inicial+i)%(LARGURA-1)+1] = 3;
    }

}

void colisao_tartaruga(int matriz[][LARGURA], FASE *tartaruga, int *posicao)
{
    int i,a;
    int tamanho = tartaruga->tamanho;
    a=*posicao;
    if (a > 10 )
    {

        for(i = 0; i < 4; i++)
        {
            matriz[tartaruga->linha_inicial][(tartaruga->coluna_inicial+i)%(LARGURA-1)+1] = 2;
            matriz[tartaruga->linha_inicial+1][(tartaruga->coluna_inicial+i)%(LARGURA-1)+1] = 2;
        }

    }

}

void colisao_vitoria(int matriz[][LARGURA])
{
    int i;

    gotoxy(1,3);
    for(i=0; i < LARGURA - 3; i += 10)
    {
        matriz[1][i] = 4;
        matriz[1][i+1] = 4;
    }
    gotoxy(1,4);
http://pastebin.com/ve1m5YaU
    for(i=0; i < LARGURA - 3; i += 10)
    {
        matriz[1][i] = 4;
        matriz[1][i+1] = 4;
    }
}

int main ()
{
    menu();


    return 0;
}

void jogo_carregado()
{
    FILE *salvo;
    int vida=VIDAS, i, j, tartaruga_disponivel=0,movimento;
    int colisao[ALTURA+3][LARGURA]= {};
    char cursor='c';
    int estado_sapo, ganhou=0;
    int dificuldade=0,carregado=0;
    FASE tronco[9]= {};
    FASE carro[11]=  {};
    FASE tartaruga[6]= {};
    FASE sapo= {'S',1,0,0,ALTURA-1,LARGURA/2};



    do
    {
        system("cls");

        movimento=MOVIMENTOS;

        sapo.coluna_inicial = LARGURA/2;
        sapo.linha_inicial = ALTURA-1;



        gotoxy(1,3);//printa as casinhas do sapo
        printf("  |**|        |**|        |**|        |**|        |**|  ");
        gotoxy(1,4);
        printf("  |**|        |**|        |**|        |**|        |**|  ");

        printa_agua();

        if(carregado==0)
        {

        salvo=fopen("wiseman.bin","rb");
        if(!salvo)
            printf("\aError ao abrir o aquivo");
        else
        {

            for(i=0; i<9; i++)
            {
                if( fread(&tronco[i],sizeof(FASE),1,salvo) !=1)
                {
                    clrscr();
                    printf("Erro ao salvar o arquivo");
                    fclose(salvo);
                    return 0;
                }

            }
            for(i=0; i<11; i++)
            {
                if( fread(&carro[i],sizeof(FASE),1,salvo) !=1)
                {
                    clrscr();
                    printf("Erro ao salvar o arquivo");
                    fclose(salvo);
                    return 0;
                }

            }
            for(i=0; i<6; i++)
            {
                if( fread(&tartaruga[i],sizeof(FASE),1,salvo) !=1)
                {
                    clrscr();
                    printf("Erro ao salvar o arquivo");
                    fclose(salvo);
                    return 0;
                }

            }
            if(1 != fread(&sapo,sizeof(FASE),1,salvo))
            {
                clrscr();
                printf("Erro ao salvar o arquivo");
                fclose(salvo);
                return 0;
            }
            if(1 != fread(&movimento,sizeof(int),1,salvo))
            {
                clrscr();
                printf("Erro ao salvar o arquivo");
                fclose(salvo);
                return 0;
            }
            if(1 != fread(&vida,sizeof(int),1,salvo))
            {
                clrscr();
                printf("Erro ao salvar o arquivo");
                fclose(salvo);
                return 0;
            }
            if(1 != fread(&ganhou,sizeof(int),1,salvo))
            {
                clrscr();
                printf("Erro ao salvar o arquivo");
                fclose(salvo);
                return 0;
            }
            if(1 != fread(&tartaruga_disponivel,sizeof(int),1,salvo))
            {
                clrscr();
                printf("Erro ao salvar o arquivo");
                fclose(salvo);
                return 0;
            }
            if(1 != fread(&dificuldade,sizeof(int),1,salvo))
            {
                clrscr();
                printf("Erro ao salvar o arquivo");
                fclose(salvo);
                return 0;
            }
        }

        carregado=1;
        fclose(salvo);
        }

        do
        {
            gotoxy(1,1);
            printf("Vidas: %d       Pontos: %d  ", vida, movimento);

            matriz_colisao(colisao);
            inicia_sapo(&sapo);

            tartaruga_disponivel++;
            if(tartaruga_disponivel==30)
                tartaruga_disponivel=3;

            vitoria(colisao);

            for(i=0; i<9; i++)
            {
                mexe_tronco(&tronco[i]);
                colisao_tronco(colisao, &tronco[i]);
            }
            inicia_sapo(&sapo);
            for(i=0; i<11; i++)
            {
                mexe_carro(&carro[i]);
                colisao_carro(colisao, &carro[i]);


            }
            for(i=0; i<6; i++)
            {
                mexe_tartaruga(&tartaruga[i],&tartaruga_disponivel);
                colisao_tartaruga(colisao,&tartaruga[i],&tartaruga_disponivel);
            }
            inicia_sapo(&sapo);
            i=0;


            estado_sapo=0;

            while(i<10000-(500*dificuldade))
            {
                if(kbhit())
                    mexe_sapo(&sapo,&cursor,&movimento);
                i++;
                if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==4) estado_sapo = 4;
                else
                {
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==1) movimento = 0;
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==1) movimento = 0;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial+1] ==1) movimento = 0;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial]==1) movimento = 0;


                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==2) estado_sapo = 2;
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==2) estado_sapo = 2;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial+1] ==2) estado_sapo = 2;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial]==2) estado_sapo = 2;

                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==3) estado_sapo = 3;
                    if( colisao[sapo.linha_inicial][sapo.coluna_inicial] ==3) estado_sapo = 3;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial+1] ==3) estado_sapo = 3;
                    if( colisao[sapo.linha_inicial+1][sapo.coluna_inicial]==3) estado_sapo = 3;

                }
                //if( colisao[sapo.linha_inicial][sapo.coluna_inicial+1] ==4) movimento=0;
            }
            if(estado_sapo==2)
                sapo.coluna_inicial-=2;
            if(estado_sapo==3)
                sapo.coluna_inicial+=2;
            if(estado_sapo == 4)
            {
                dificuldade++;
                ganhou++;
                movimento += 50;
                //inicia_sapo(&sapo);
                //aumentar dificuldade a.k.a. velocidade - pensei em uma função que retornasse um valor pra ser usado dentro do while e cada vez que atingisse uma casa diminuia esse valor
                sapo.coluna_inicial = LARGURA/2;
                sapo.linha_inicial = ALTURA-1;
            }

            //
            cursor=tolower(cursor);
            if(cursor=='f')
            {
                salvo=fopen("wiseman.bin","wb");
                if(!salvo)
                    printf("\aError ao abrir o aquivo");
                else
                {
                    for(i=0; i<9; i++)
                    {
                        if( fwrite(&tronco[i],sizeof(FASE),1,salvo) !=1)
                        {
                            clrscr();
                            printf("Erro ao salvar o arquivo");
                            fclose(salvo);
                            return 0;
                        }

                    }
                    for(i=0; i<11; i++)
                    {
                        if( fwrite(&carro[i],sizeof(FASE),1,salvo) !=1)
                        {
                            clrscr();
                            printf("Erro ao salvar o arquivo");
                            fclose(salvo);
                            return 0;
                        }

                    }
                    for(i=0; i<6; i++)
                    {
                        if( fwrite(&tartaruga[i],sizeof(FASE),1,salvo) !=1)
                        {
                            clrscr();
                            printf("Erro ao salvar o arquivo");
                            fclose(salvo);
                            return 0;
                        }

                    }
                    if(1 != fwrite(&sapo,sizeof(FASE),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&movimento,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&vida,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&ganhou,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&tartaruga_disponivel,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                    if(1 != fwrite(&dificuldade,sizeof(int),1,salvo))
                    {
                        clrscr();
                        printf("Erro ao salvar o arquivo");
                        fclose(salvo);
                        return 0;
                    }
                }

                fclose(salvo);
            }
        }while(movimento>0 && cursor != 'q' && ganhou!=5 );
        if(movimento<=0)
            vida--;

    }
        while(vida>0 && cursor != 'q'  && ganhou!=5);
        if(ganhou == 5)
        {
            printf("Voce ganhou o jogo, sua pontuação foi de %d",movimento);
        }


}