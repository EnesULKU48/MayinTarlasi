#include <stdio.h>
#include <stdlib.h>

#define tabloBuyukluk 8

int altTablo[tabloBuyukluk+2][tabloBuyukluk+2];
char ustTablo[tabloBuyukluk+2][tabloBuyukluk+2];
int bayrakSay=0;

void AltTabloYap(int m);
void UstTabloYap();
void TabloBastir();
void AltTabloBastir();
void MayinYerlestir(int mayinSa);
void EtrafiAc(int satir, int sutun);
int Tekrarlama(int *durum);
int KontrolKazanma(int mayinSa);
int IstenilenAc(int satir, int sutun);
int Zorluk();

int main()
{
    int satir,sutun,durum,yeniden,mayin,zorluk;
    char tuslama;
    printf("Mayin Tarlasina Hos Geldiniz!\n");
    mayin=Zorluk();

    AltTabloYap(mayin);
    UstTabloYap();

    //AltTabloBastir();

    printf("\n");

    do
    {
        TabloBastir();
        printf("\n\033[32m(a) koordinat acma, (b) bayrak koyma (k) bayrak kaldir ---> (a,satir,sutun) seklinde giriniz\n");
        scanf("%c,%d,%d",&tuslama,&satir,&sutun);
        //durum=KontrolKazanma(mayin);
        if(tuslama == 'a')
        {
            durum=IstenilenAc(satir,sutun);
        }
        else if(tuslama == 'b')
        {
            if(mayin > bayrakSay)
            {
                bayrakSay++;
                ustTablo[satir][sutun] = 'B';
            }
            durum=KontrolKazanma(mayin);
        }
        else if(tuslama == 'k')
        {
            if(bayrakSay > 0)
            {
                bayrakSay--;
                ustTablo[satir][sutun]='#';
            }
        }


        if(durum==-1)
        {
            printf("\n\033[31mGAME OVER Kaybettin!!!");
            AltTabloBastir();
            do
            {
                yeniden=Tekrarlama(&durum);
                if(yeniden==0)
                    return 0;
            }
            while(yeniden!=0 && yeniden!=1);


        }
        else if(durum==1)
        {
            printf("\n\033[35mHARÝKA Kazandin.");
            AltTabloBastir();
            do
            {
                yeniden=Tekrarlama(&durum);
                if(yeniden==0)
                    return 0;
            }
            while(yeniden!=0 && yeniden!=1);

        }

    }
    while(1);


    return 0;
}

void AltTabloYap(int m)
{
    int i,j;

    for(i=1; i<=tabloBuyukluk; i++)
    {
        for(j=1; j<=tabloBuyukluk; j++)
            altTablo[i][j]=0;
    }

    for(i=0; i<=tabloBuyukluk+1; i++)
    {
        altTablo[0][i]=1;
        altTablo[tabloBuyukluk+1][i]=1;
    }
    for(i=1; i<=tabloBuyukluk; i++)
    {
        altTablo[i][0]=1;
        altTablo[i][tabloBuyukluk+1]=1;
    }
    MayinYerlestir(m);
}

void UstTabloYap()
{
    int i,j;

    for(i=1; i<=tabloBuyukluk; i++)
    {
        for(j=1; j<=tabloBuyukluk; j++)
            ustTablo[i][j]='#';
    }

    for(i=0; i<=tabloBuyukluk+1; i++)
    {
        ustTablo[0][i]='*';
        ustTablo[tabloBuyukluk+1][i]='*';
    }
    for(i=1; i<=tabloBuyukluk; i++)
    {
        ustTablo[i][0]='*';
        ustTablo[i][tabloBuyukluk+1]='*';
    }
}

void TabloBastir()
{
    int i,j;
    printf("\n");

    for(i=1; i<=tabloBuyukluk; i++)
        printf("\033[36m%4d",i);

    printf("\n");
    for(i=0; i<=tabloBuyukluk*4; i++)
        printf("-");

    printf("\n");
    printf("\n");
    for(i=1; i<=tabloBuyukluk; i++)
    {
        for(j=1; j<=tabloBuyukluk; j++)
        {
            if(ustTablo[i][j]=='B')
                printf("\033[31m   B");
            else
                printf("\033[37m%4c",ustTablo[i][j]);
        }
        printf("\033[36m  |%2d",i);
        printf("\n");
        printf("\n");
    }

    for(i=0; i<=tabloBuyukluk*4; i++)
        printf("-");

}

void AltTabloBastir()
{
    int i,j;
    printf("\n");

    for(i=1; i<=tabloBuyukluk; i++)
        printf("\033[36m%4d",i);

    printf("\n");
    for(i=0; i<=tabloBuyukluk*4; i++)
        printf("-");

    printf("\n");
    printf("\n");
    for(i=1; i<=tabloBuyukluk; i++)
    {
        for(j=1; j<=tabloBuyukluk; j++)
        {
            printf("\033[37m%4d",altTablo[i][j]);
        }
        printf("\033[36m  |%2d",i);
        printf("\n");
        printf("\n");
    }

    for(i=0; i<=tabloBuyukluk*4; i++)
        printf("-");
}
void MayinYerlestir(int mayinSa)
{
    srand(time(NULL));
    int i,k,p,satir=0,sutun=0;

    for(i=1; i<=mayinSa; i++)
    {
        satir=1+rand()%tabloBuyukluk;
        sutun=1+rand()%tabloBuyukluk;
        if(altTablo[satir][sutun]==-1)
            i--;
        else
        {
            altTablo[satir][sutun]=-1;

            for(k=-1; k<=1; k++)
            {
                for(p=-1; p<=1; p++)
                {
                    if(altTablo[satir+k][sutun+p]!=-1)
                        altTablo[satir+k][sutun+p]++;
                }
            }
        }

    }

}

void EtrafiAc(int satir, int sutun)
{
    int i,j;
    ustTablo[satir][sutun]=altTablo[satir][sutun] + '0';

    for(i=-1; i<=1; i++)
    {
        for(j=-1; j<=1; j++)
        {
            if (satir+i >= 1 && satir+i <= tabloBuyukluk && sutun+j >= 1 && sutun+j <= tabloBuyukluk)
            {
                if(altTablo[satir+i][sutun+j] > 0 && ustTablo[satir+i][sutun+j]=='#')
                    ustTablo[satir+i][sutun+j] = altTablo[satir+i][sutun+j] + '0';
                else if(altTablo[satir+i][sutun+j] == 0 && ustTablo[satir+i][sutun+j]=='#')
                    EtrafiAc(satir+i,sutun+j);
            }

        }
    }

}

int IstenilenAc(int satir, int sutun)
{
    int sonuc=0;

    if(altTablo[satir][sutun] == -1)
        sonuc=-1;
    else if(altTablo[satir][sutun] > 0)
    {
        ustTablo[satir][sutun] = altTablo[satir][sutun] + '0';
        sonuc=0;
    }
    else
        EtrafiAc(satir,sutun);

    return sonuc;
}

int KontrolKazanma(int mayinSa)
{
    int i,j,durum=0,bayrak=0;

    for(i=1; i<=tabloBuyukluk; i++)
    {
        for(j=1; j<=tabloBuyukluk; j++)
        {
            if(ustTablo[i][j]=='B' && altTablo[i][j]==-1)
            {
                bayrak++;
            }
        }
    }

    if(bayrak == mayinSa)
        durum=1;
    else
        durum=0;

    return durum;
}

int Tekrarlama(int *durum)
{
    int yeniden,may;
    printf("\n\033[32mOyunu tekrar oynamak istiyor musunuz? [1-Evet][0-Hayir]\n");
    scanf("%d",&yeniden);

    switch(yeniden)
    {
    case 0:
        printf("Gorusuruz...\n");
        break;
    case 1:
        bayrakSay=0;
        *durum=0;
        may=Zorluk();
        AltTabloYap(may);
        UstTabloYap();
        break;
    default:
        printf("Yanlis tuslama girdiniz. Tekrar deneyiniz..");
        scanf("%d",&yeniden);
        break;
    }
    return yeniden;
}
int Zorluk()
{
    int zorluk,mayin;

    printf("\n\n\033[33mOyun zorluk derecesini secin [1-kolay][2-orta][3-zor][4-cok zor]\n");
    scanf("%d",&zorluk);

    if(zorluk==1)
        mayin=1;
    else if(zorluk==2)
        mayin=8;
    else if(zorluk==3)
        mayin=14;
    else if(zorluk==4)
        mayin=20;
    return mayin;
}


