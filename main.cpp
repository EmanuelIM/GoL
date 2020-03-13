#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <cstdio>

using namespace std;

int k,a[100][100],b[100][100];
char msg[100];


int verifvecini(int c[][100],int i,int j)
{
    int nr=0;
    if(c[i-1][j-1]==1) nr++;
    if(c[i-1][j]==1) nr++;
    if(c[i-1][j+1]==1) nr++;
    if(c[i][j-1]==1) nr++;
    if(c[i][j+1]==1) nr++;
    if(c[i+1][j-1]==1) nr++;
    if(c[i+1][j]==1) nr++;
    if(c[i+1][j+1]==1) nr++;
    return nr;
}

void deseninit(int c[][100])
{
    setcolor(RED);
    int i,j,i1,j1;
    for(i=100,i1=1;i<=100+(10*40),i1<=10;i+=40,i1++)
        for(j=100,j1=1;j<=100+(10*40),j1<=10;j+=40,j1++)
        {
        rectangle(j,i,j+40,i+40);
        if(c[i1][j1]==1)
        {
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(j+1,i+1,RED);
        }
        else
        {
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(j+1,i+1,RED);
        }
        }
    setcolor(GREEN);
    rectangle(500,520,600,570);
    settextstyle(8,0,3);
    outtextxy(510,530,"START");
    setcolor(RED);
}

void intro()
{
    cout<<"Salut!\nAcesta este un simulator al jocului Life (Conway),care presupune";
    cout<<" simularea evolutiei unor celule intr-un spatiu bidimensional.\nJocul,in acest caz";
    cout<<" se desfasoara intr-un grid de dimensiuni 10x10,avand o configuratie initiala de celule de la care porneste simularea.\n";
    cout<<"Multiplicarea celulelor urmeaza cateva reguli:\n";
    cout<<"1.Orice celula cu mai putin de doua celule vecine moare de singuratate\n";
    cout<<"2.Orice celula cu mai mult de trei celule vecine moare din cauza supraaglomerarii\n";
    cout<<"3.Orice celula cu doua sau trei celule vecine supravietuieste\n";
    cout<<"4.O celula noua este creata daca are exact trei celule vecine\n";
    cout<<"Scrie in aceasta consola de la tastatura numarul de etape pe care vrei sa le urmaresti,apoi in consola care";
    cout<<" apare apasa pe fiecare casuta in parte pentru a marca celulele initiale,dupa care apasa butonul START si minuneaza-te";
    cout<<" de viata palpitanta a celulelor!\n ATENTIE! NU MUTA FEREASTRA CU GRAFICA DIN POZITIA INITIALA.POATE GENERA ERORI DE FUNCTIONARE.\n";
    cout<<"Numarul de etape:";
}



int main()
{
    intro();cin>>k;
    int gd=DETECT,gm;
    POINT cursor;
    initgraph(&gd,&gm, " ");
    initwindow(800,600,"WINDOWS BGI'",0,0);
    settextstyle(8,0,5);
    deseninit(a);
    int etapa=1,ok=0;
    sprintf(msg,"ZIUA: %d",etapa);
    outtextxy(20,20,msg);
    setcolor(WHITE);
    outtextxy(300,20,"JOCUL LIFE (CONWAY)");
    setcolor(RED);
    while(!ok)
    {
        GetCursorPos(&cursor);
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            if(cursor.x>=500&&cursor.x<=600&&cursor.y>=540&&cursor.y<=600) ok=1;
            else if(cursor.x>=100&&cursor.x<=600&&cursor.y>=100&&cursor.y<=600)
            {
                int detecti,detectj;
                detectj=((cursor.x+5)-100)/40;
                detecti=((cursor.y-25)-100)/40;
                setfillstyle(SOLID_FILL,WHITE);
                floodfill(cursor.x+5,cursor.y-25,RED);
                a[detecti+1][detectj+1]=1;
            }
        }
        if(GetAsyncKeyState(VK_RBUTTON))
        {
            if(cursor.x>=100&&cursor.x<=600&&cursor.y>=100&&cursor.y<=600)
            {
                int detecti,detectj;
                detectj=((cursor.x+5)-100)/40;
                detecti=((cursor.y-25)-100)/40;
                setfillstyle(SOLID_FILL,BLACK);
                floodfill(cursor.x+5,cursor.y-25,RED);
                a[detecti+1][detectj+1]=0;
            }
        }
    }
     for(etapa=1;etapa<=k-1;etapa++)
    {
        int i,j,i1,j1;
        for(i1=100,i=1;i1<=100+(10*40),i<=10;i1+=40,i++)
           for(j1=100,j=1;j1<=100+(10*40),j<=10;j1+=40,j++)
            if(etapa%2==1)
        {
            sprintf(msg,"ZIUA: %d",etapa+1);
            outtextxy(20,20,msg);
            b[i][j]=0;
            int vecini=verifvecini(a,i,j);
            if(a[i][j]==0&&vecini==3){setfillstyle(SOLID_FILL,WHITE);
            floodfill(j1+1,i1+1,RED);b[i][j]=1;}
            else if(a[i][j]==1)
            {
                if(vecini<2){ setfillstyle(SOLID_FILL,BLACK);
            floodfill(j1+1,i1+1,RED);b[i][j]=0;}
                if(vecini==2||vecini==3){setfillstyle(SOLID_FILL,WHITE);
            floodfill(j1+1,i1+1,RED);b[i][j]=1;}
                if(vecini>3){ setfillstyle(SOLID_FILL,BLACK);
            floodfill(j1+1,i1+1,RED);b[i][j]=0;}
            }
            delay(25);
        }
        else
        {
            sprintf(msg,"ZIUA: %d",etapa+1);
            outtextxy(20,20,msg);
            a[i][j]=0;
            int vecini=verifvecini(b,i,j);
             if(b[i][j]==0&&vecini==3){setfillstyle(SOLID_FILL,WHITE);
            floodfill(j1+1,i1+1,RED);a[i][j]=1;}
            else if(b[i][j]==1)
            {
                if(vecini<2){ setfillstyle(SOLID_FILL,BLACK);
            floodfill(j1+1,i1+1,RED);a[i][j]=0;}
                if(vecini==2||vecini==3){setfillstyle(SOLID_FILL,WHITE);
            floodfill(j1+1,i1+1,RED);a[i][j]=1;}
                if(vecini>3){ setfillstyle(SOLID_FILL,BLACK);
            floodfill(j1+1,i1+1,RED);a[i][j]=0;}
            }
            delay(25);

        }
    }
    outtextxy(600,300,"SFARSIT!");
    getch();
    closegraph();
    return 0;
}
