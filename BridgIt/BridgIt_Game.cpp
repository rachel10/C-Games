#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include<cstdlib>
#include<cstring>
#include<ctime>

#define MAX 20
#define FUNDAL CYAN
#define FUNDAL_TABLA RED
#define latura 100
using namespace std;

int TablaDeJoc[MAX][MAX];
int stanga,sus,width,height, dimensiuneTabla=5, jucator=2, culoare=2, player=1,nrmutari=0,nrjucatori=1,level_computer=2;

struct buton {
    int x1, y1, x2, y2, mx, my;
    char text[20];
};

void initializareTablaDeJoc();
void afisareTablaInConsola();
void desenButon(buton &b, int textsize=3, int color=LIGHTGRAY);
void desenCopertaJoc();
void desenTabla();
void trasareLinie(int linia, int coloana);
void stergeLinia(int linia, int coloana);
void play();
void slaveplay(); 
void easyslave(int &linia,int &coloana);
void normalslave(int &linia,int &coloana);
void hardslave(int ultimalinie,int ultimacoloana,int &linia,int &coloana);
int victorie(int linia,int coloana);
void gameIncheiat();
void settings();
void informations();
void timer(clock_t start,int numarmutari);

int main()
{
    initwindow(1100,650,"Bridg-It Game",100,0);
    desenCopertaJoc();
    closegraph();
    return 0;
}

void initializareTablaDeJoc()//teo
{

    int i,j;                    //galben=1
    for(i=0;i<=2*dimensiuneTabla;i++)     //rosu=2
       for(j=0;j<=2*dimensiuneTabla;j++)
          if((i%2==1)&&(j%2==0))
              TablaDeJoc[i][j]=1;
          else if((i%2==0)&&(j%2==1))
                  TablaDeJoc[i][j]=2;
                else
                  TablaDeJoc[i][j]=0;
    for( i=0;i<=2*dimensiuneTabla;i++)
    {
        TablaDeJoc[0][i]=2;
        TablaDeJoc[i][0]=1;
        TablaDeJoc[2*dimensiuneTabla][i]=2;
        TablaDeJoc[i][2*dimensiuneTabla]=1;
    }
}

void afisareTablaInConsola()
{
    for(int i=0;i<=2*dimensiuneTabla;i++)
    {
        for(int j=0;j<=2*dimensiuneTabla;j++)
            cout<<TablaDeJoc[i][j]<<' ';
        cout<<endl;
    }
}

void desenButon(buton &b, int textsize, int color)
{
    settextstyle(DEFAULT_FONT,HORIZ_DIR,textsize);
    int inaltime=textheight(b.text);
    int lungime=textwidth(b.text);
    b.x1=b.mx-lungime/2;
    b.y1=b.my-inaltime/2;
    b.x2=b.x1+lungime+14;
    b.y2=b.y1+inaltime+14;

    setcolor(color);
    outtextxy(b.x1+7,b.y1+7,b.text);
}

void desenCopertaJoc()
{
    setbkcolor(FUNDAL); clearviewport();
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 10);
    outtextxy(200,100,"Bridg-It");

    bool gata=0, b1_status=0, b2_status=0, b3_status=0, b4_status=0;
    int x, y;
    buton B1, B2, B3, B4;

    B1.mx=500; B1.my=260; strcpy(B1.text, "Play");
    B2.mx=500; B2.my=330; strcpy(B2.text, "Settings");
    B3.mx=500; B3.my=400; strcpy(B3.text, "Info");
    B4.mx=500; B4.my=470; strcpy(B4.text, "Exit");
    desenButon(B1, 4);
    desenButon(B2, 4);
    desenButon(B3, 4);
    desenButon(B4, 4);

    while(!gata)
    {
        x=mousex(); y=mousey();

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);

            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                gata=1;
                initializareTablaDeJoc();
                desenTabla();
                if(nrjucatori==1)
                   slaveplay();
                else
                    play();
            }
            else
                if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
                {
                    settings();
                    setbkcolor(FUNDAL); clearviewport();
                    setcolor(WHITE);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 10);
                    outtextxy(200,100,"Bridg-It");
                    desenButon(B1, 4);
                    desenButon(B2, 4);
                    desenButon(B3, 4);
                    desenButon(B4, 4);
                }
                else
                    if(x>=B3.x1 && x<=B3.x2 && y>=B3.y1 && y<=B3.y2)
                    {
                        informations();
                        setbkcolor(FUNDAL); clearviewport();
                        setcolor(WHITE);
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 10);
                        outtextxy(200,100,"Bridg-It");
                        desenButon(B1, 4);
                        desenButon(B2, 4);
                        desenButon(B3, 4);
                        desenButon(B4, 4);
                    }
                    else
                        if(x>=B4.x1 && x<=B4.x2 && y>=B4.y1 && y<=B4.y2)
                            gata=1;
        }
        else
        {
            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                if(b1_status==0)
                {
                    desenButon(B1, 5);
                    b1_status=1;
                }
            }
            else
                if(b1_status==1)
                {
                    desenButon(B1, 5, FUNDAL);
                    desenButon(B1, 4);
                    b1_status=0;
                }

            if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
            {
                if(b2_status==0)
                {
                    desenButon(B2, 5);
                    b2_status=1;
                }
            }
            else
                if(b2_status==1)
                {
                    desenButon(B2, 5, FUNDAL);
                    desenButon(B2, 4);
                    b2_status=0;
                }

            if(x>=B3.x1 && x<=B3.x2 && y>=B3.y1 && y<=B3.y2)
            {
                if(b3_status==0)
                {
                    desenButon(B3, 5);
                    b3_status=1;
                }
            }
            else
                if(b3_status==1)
                {
                    desenButon(B3, 5, FUNDAL);
                    desenButon(B3, 4);
                    b3_status=0;
                }

            if(x>=B4.x1 && x<=B4.x2 && y>=B4.y1 && y<=B4.y2)
            {
                if(b4_status==0)
                {
                    desenButon(B4, 5);
                    b4_status=1;
                }
            }
            else
                if(b4_status==1)
                {
                    desenButon(B4, 5, FUNDAL);
                    desenButon(B4, 4);
                    b4_status=0;
                }
        }
    }
}

void desenTabla()
{
    setbkcolor(FUNDAL); clearviewport();

    int i,j;
    width=height=latura*dimensiuneTabla;
    sus=(getmaxy()-width)/2;
    stanga=(getmaxx()-height)/2+100;

    setfillstyle(SOLID_FILL,FUNDAL_TABLA);
    bar(stanga-20+3, sus-20+3, stanga+width +20-2, sus+height +20-2);

    int x=stanga;
    int y=sus;
    int nrBulineLinie;
    for(int i=1; i<=2*dimensiuneTabla+1; i++)
    {
        if(i%2)
        {
            setcolor(LIGHTRED); setfillstyle(SOLID_FILL,LIGHTRED);
            x=stanga+latura/2;
            nrBulineLinie=dimensiuneTabla;
        }
        else
        {
            setcolor(YELLOW); setfillstyle(SOLID_FILL,YELLOW);
            x=stanga;
            nrBulineLinie=dimensiuneTabla+1;
        }
        for(int j=1; j<=nrBulineLinie; j++)
        {

            fillellipse(x, y,19,19);
            x+=latura;
        }
        y+=latura/2;
    }
    setcolor(YELLOW);setlinestyle(SOLID_LINE,0 ,20);
    line(stanga-10,sus+latura/2-10,stanga-10,sus+height-latura/2+10);
    line(stanga+width+10,sus+latura/2-10,stanga+width+10,sus+height-latura/2+10);

    setcolor(LIGHTRED);setlinestyle(SOLID_LINE,0 ,20);
    line(stanga+latura/2-10,sus-10,stanga+width-latura/2+10,sus-10);
    line(stanga+latura/2-10,sus+height+10,stanga+width-latura/2+10,sus+height+10);

    setcolor(BLACK); setlinestyle(SOLID_LINE,0,3); rectangle(stanga-20,sus-20,stanga+width +20,sus+height +20);
}

void trasareLinie(int linia, int coloana)
{

    if(jucator==1)
    {
        settextstyle(3,HORIZ_DIR,4);setcolor(YELLOW);
        outtextxy(10,10,"Yellow's turn...");
        jucator=2;
        setcolor(LIGHTRED);setlinestyle(SOLID_LINE,0 ,5);
    }
    else
    {

        setcolor(FUNDAL);settextstyle(3,HORIZ_DIR,4);
        outtextxy(10,10,"Yellow's turn...");

        settextstyle(3,HORIZ_DIR,4);setcolor(LIGHTRED);
        outtextxy(10,10,"Red's turn...");
        jucator=1;
        setcolor(YELLOW);setlinestyle(SOLID_LINE,0 ,5);
    }
    TablaDeJoc[linia][coloana]=-1*jucator;

    if(TablaDeJoc[linia][coloana-1]==jucator)
        line(stanga+(coloana-1)*(latura/2), sus+linia*(latura/2), stanga+(coloana+1)*(latura/2), sus+linia*(latura/2));

    else
        line(stanga+coloana*(latura/2), sus+(linia-1)*(latura/2), stanga+coloana*(latura/2), sus+(linia+1)*(latura/2));
}

void stergeLinia(int linia, int coloana)
{

    setcolor(FUNDAL_TABLA);setlinestyle(SOLID_FILL,0 ,5);
    if(TablaDeJoc[linia][coloana]==-1*jucator)
    {
        TablaDeJoc[linia][coloana]=0;
        if(TablaDeJoc[linia][coloana-1]==jucator)
            {line(stanga+(coloana-1)*(latura/2)+22, sus+linia*(latura/2), stanga+(coloana+1)*(latura/2)-21, sus+linia*(latura/2));
             nrmutari--;}
        else
            {line(stanga+coloana*(latura/2), sus+(linia-1)*(latura/2)+22,stanga+coloana*(latura/2), sus+(linia+1)*(latura/2)-21);
             nrmutari--;
            }
     }

     if(jucator==1)
     {
        jucator=2;

        settextstyle(3,HORIZ_DIR,4);setcolor(YELLOW);
        outtextxy(10,10,"Yellow's turn...");
     }

     else
     {
        jucator=1;

        setcolor(FUNDAL);settextstyle(3,HORIZ_DIR,4);
        outtextxy(10,10,"Yellow's turn...");


        settextstyle(3,HORIZ_DIR,4);setcolor(LIGHTRED);
        outtextxy(10,10,"Red's turn...");
     }
}

void play()
{
    nrmutari=0;
    if(jucator==1)
    {
        setcolor(LIGHTRED); settextstyle(3,HORIZ_DIR,4);
        outtextxy(10,10,"Red's turn...");
    }
    else
    {
        setcolor(YELLOW); settextstyle(3,HORIZ_DIR,4);
        outtextxy(10,10,"Yellow's turn...");
    }

    bool gata=false, undo=1, b1_status=0, b2_status=0;
    int linia, coloana, x, y, last_line, last_column;
    buton B1, B2;

    B1.mx=150; B1.my=400; strcpy(B1.text, "Restart");
    B2.mx=150; B2.my=470; strcpy(B2.text, "Menu");

    desenButon(B1);
    desenButon(B2);
    nrmutari=0;
    clock_t duration ;
    clock_t start;
    start=clock();
    while(!gata)
    {
        x=mousex();
        y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);

            if(x>=stanga && x<=stanga+width && y>=sus&&y<=sus+height)
            {
                linia=(y-sus+20)/(latura/2);
                coloana=(x-stanga+20)/(latura/2);
                if(TablaDeJoc[linia][coloana]==0)
                {
                    last_line=linia;
                    last_column=coloana;
                    undo=0;
                    trasareLinie(linia, coloana);
                    nrmutari++;
                    int castigator=victorie(linia,coloana);
                    if(castigator)
                    {
                        jucator=castigator;
                        gata=true;
                        timer(start,nrmutari);
                        gameIncheiat();
                    }
                }
            }
            else
                if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
                {
                    if(player==culoare)
                        jucator=1;
                    else
                        jucator=2;
                    gata=1;
                    initializareTablaDeJoc();
                    desenTabla();
                    play();
                }
                else
                    if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
                    {
                        gata=1;
                        desenCopertaJoc();
                    }
        }
        else
        {
            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                if(b1_status==0)
                {
                    desenButon(B1, 4);
                    b1_status=1;
                }
            }
            else
                if(b1_status==1)
                {
                    desenButon(B1, 4, FUNDAL);
                    desenButon(B1);
                    b1_status=0;
                }

            if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
            {
                if(b2_status==0)
                {
                    desenButon(B2, 4);
                    b2_status=1;
                }
            }
            else
                if(b2_status==1)
                {
                    desenButon(B2, 4, FUNDAL);
                    desenButon(B2);
                    b2_status=0;
                }
        }

        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            if(undo==0)
            {
                undo=1;
                stergeLinia(last_line, last_column);
            }
        }
    }
}

void slaveplay()
{
    nrmutari=0;
    if(jucator==1)
    {
        setcolor(LIGHTRED); settextstyle(3,HORIZ_DIR,4);//player
        outtextxy(10,10,"Red's turn...");
    }
    else
    {
        setcolor(YELLOW); settextstyle(3,HORIZ_DIR,4);//PC
        outtextxy(10,10,"Yellow's turn...");
    }

    bool gata=false, undo=1, b1_status=0, b2_status=0;
    int linia, coloana, x, y, last_line, last_column, ultimalinie, ultimacoloana;
    buton B1, B2;

    B1.mx=150; B1.my=400; strcpy(B1.text, "Restart");
    B2.mx=150; B2.my=470; strcpy(B2.text, "Menu");

    desenButon(B1);
    desenButon(B2);
    nrmutari=0;
    clock_t duration ;
    clock_t start;
    start=clock();
    while(!gata)
    {
        x=mousex();
        y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);

            if(x>=stanga && x<=stanga+width && y>=sus&&y<=sus+height)
            {
                linia=(y-sus+20)/(latura/2);
                coloana=(x-stanga+20)/(latura/2);
                if(TablaDeJoc[linia][coloana]==0)
                {
                    last_line=linia;
                    last_column=coloana;
                    undo=0;
                    trasareLinie(linia, coloana);
                    nrmutari++;
                    int castigator=victorie(linia,coloana);
                    if(castigator)
                    {
                        jucator=castigator;
                        gata=true;
                        timer(start,nrmutari);
                        gameIncheiat();
                    }
                    else
                    {
                        if(level_computer==1)
                            easyslave(linia,coloana);
                        else
                            if(level_computer==2)
                              normalslave(linia, coloana);
                            else
                                hardslave(ultimalinie,ultimacoloana,linia,coloana);
                        ultimalinie=linia;
                        ultimacoloana=coloana;
                        trasareLinie(linia, coloana);
                        nrmutari++;

                        castigator=victorie(linia, coloana);
                        if(castigator)
                        {
                            jucator=castigator;
                            gata=true;
                            timer(start,nrmutari);
                            gameIncheiat();
                        }
                    }
                }
            }
            else
                if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
                {
                    if(player==culoare)
                        jucator=1;
                    else
                        jucator=2;
                    gata=1;
                    initializareTablaDeJoc();
                    desenTabla();
                    slaveplay();
                }
                else
                    if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
                    {
                        gata=1;
                        desenCopertaJoc();
                    }
        }
        else
        {
            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                if(b1_status==0)
                {
                    desenButon(B1, 4);
                    b1_status=1;
                }
            }
            else
                if(b1_status==1)
                {
                    desenButon(B1, 4, FUNDAL);
                    desenButon(B1);
                    b1_status=0;
                }

            if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
            {
                if(b2_status==0)
                {
                    desenButon(B2, 4);
                    b2_status=1;
                }
            }
            else
                if(b2_status==1)
                {
                    desenButon(B2, 4, FUNDAL);
                    desenButon(B2);
                    b2_status=0;
                }
        }

        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            if(undo==0)
            {
                undo=1;
                stergeLinia(ultimalinie, ultimacoloana);
                stergeLinia(last_line, last_column);
            }
        }
}
}

void easyslave(int &linia,int &coloana)
{
int mutare=0;
while(mutare==0)
{linia=rand()%(2*dimensiuneTabla)+1;
 coloana=rand()%(2*dimensiuneTabla)+1;
if(TablaDeJoc[linia][coloana]==0)
    {
    TablaDeJoc[linia][coloana]=jucator;
    mutare=1;
    }
}
}

void normalslave(int &linia,int &coloana)
{
if(nrmutari==0)
easyslave(linia,coloana);
else {
int mutare=0;
    if((TablaDeJoc[linia][coloana-1]!=jucator)&&(TablaDeJoc[linia][coloana+1]!=jucator))//orizontal
    {                                                                    //linia si coloana reprezinta pozitia "mijlocului" liniei oponentului
    for(int i=1;i<=dimensiuneTabla;i++)                                      // !jucator nu poate fi 0
    {if((TablaDeJoc[linia-i][coloana]==0)&&(mutare==0)&&(linia-i>0))
        {
        TablaDeJoc[linia-i][coloana]=jucator;
        mutare=1;
        linia=linia-i;
        }
    if((TablaDeJoc[linia+i][coloana]==0)&&(mutare==0)&&(linia+i<2*dimensiuneTabla+1))
        {
        TablaDeJoc[linia+i][coloana]=jucator;
        mutare=1;
        linia=linia+i;
        }
    }
    }
  else if((TablaDeJoc[linia-1][coloana]!=jucator)&&(TablaDeJoc[linia+1][coloana]!=jucator))
    {
    for(int i=1;i<=dimensiuneTabla;i++)
    {
    if((TablaDeJoc[linia][coloana-i]==0)&&(mutare==0)&&(coloana-i>0))
        {
        TablaDeJoc[linia][coloana-i]=jucator;
        mutare=1;
        coloana=coloana-i;
        }
    if((TablaDeJoc[linia][coloana+i]==0)&&(mutare==0)&&(coloana+i<2*dimensiuneTabla+1))
        {
        TablaDeJoc[linia][coloana+i]=jucator;
        mutare=1;
        coloana=coloana+i;
        }
        }
    }
if(mutare==0)
easyslave(linia,coloana);
}
}

void hardslave(int ultimalinie,int ultimacoloana,int &linia,int &coloana)
{
int coditai[100]={0},coditaj[100]={0},k=1;
int di[4]={0,0,1,-1};
int dj[4]={1,-1,0,0};
coditai[1]=ultimalinie;
coditaj[1]=ultimacoloana;
if((nrmutari==0)||(nrmutari==1))   //Daca este prima sau a doua mutare , va accesa o pozitie cu ajutorul functiei random
easyslave(linia,coloana);
else                             //Daca nu , adauga toti vecinii pozitiei anterioare in coada
{int miscare=0;
if((TablaDeJoc[ultimalinie][ultimacoloana-1]==jucator)&&(TablaDeJoc[ultimalinie][ultimacoloana+1]==jucator))
    {
    coditaj[++k]=ultimacoloana-1;//ultimalinie=linia jucatorului
    coditai[k]=ultimalinie;      //ultimacoloana=coloana jucatorului
    coditaj[++k]=ultimacoloana+1;//linia = linia slavelui
    coditai[k]=ultimalinie;      //coloana=coloana slaveului
    }
if((TablaDeJoc[ultimalinie-1][ultimacoloana]==jucator)&&(TablaDeJoc[ultimalinie+1][ultimacoloana]==jucator))
    {
    coditai[++k]=ultimalinie-1;
    coditaj[k]=ultimacoloana;
    coditai[++k]=ultimalinie+1;
    coditaj[k]=ultimacoloana;
    }
    k=1;
    while((miscare==0)&&(coditai[k]!=0)&&(coditaj[k]!=0))
    {
    for(int i=0;i<=3;i++)
    if((TablaDeJoc[coditai[k]+di[i]][coditaj[k]+dj[i]]==jucator)&&(coditai[k]+di[i]>=0)&&(coditai[k]+di[i]<=2*dimensiuneTabla)&&(coditaj[k]+dj[i]>=0)&&(coditaj[k]+dj[i]<=2*dimensiuneTabla))
    {
        coditai[++k]=coditai[k]+di[i];
        coditaj[k]=coditaj[k]+dj[i];
    }
    for(int i=0;i<=3;i++)
    if(TablaDeJoc[coditai[k]+di[i]][coditaj[k]+dj[i]]==0) //daca pozitia este libera atunci "trage linie"
    {
    TablaDeJoc[coditai[k]+di[i]][coditaj[k]+dj[i]]=jucator;
    linia=coditai[k];
    coloana=coditaj[k];
    miscare=1;
    }
    k++;
    }
    if(miscare==0)
    normalslave(linia,coloana);
}
}

int victorie(int linia,int coloana)
{
    int coadai[50]={0},coadaj[50]={0},prim=1,ultim=1,i,j,aux[12][12]={0};

//    debug(aux);
    coadai[prim]=linia;
    coadaj[prim]=coloana;
    while(prim<=ultim)
    {
        i=coadai[prim];
        j=coadaj[prim];
        aux[i][j]=1;
        if((abs(TablaDeJoc[i][j+1])==abs(TablaDeJoc[i][j]))&&(aux[i][j+1]!=1)&&(i!=2*dimensiuneTabla)&&(i!=0)&&(j+1!=0)&&(j+1!=2*dimensiuneTabla))
      {
        aux[i][j+1]=1;
        ultim++;
        coadai[ultim]=i;
        coadaj[ultim]=j+1;
      }
        if((abs(TablaDeJoc[i][j-1])==abs(TablaDeJoc[i][j]))&&(aux[i][j-1]!=1)&&(i!=2*dimensiuneTabla)&&(i!=0)&&(j-1!=0)&&(j-1!=2*dimensiuneTabla))
        {
        aux[i][j-1]=1;
        ultim++;
        coadai[ultim]=i;
        coadaj[ultim]=j-1;
      }
        if((abs(TablaDeJoc[i+1][j])==abs(TablaDeJoc[i][j]))&&(aux[i+1][j]!=1)&&(i+1!=2*dimensiuneTabla)&&(i+1!=0)&&(j!=0)&&(j!=2*dimensiuneTabla))
      {
        aux[i+1][j]=1;
        ultim++;
        coadai[ultim]=i+1;
        coadaj[ultim]=j;
        }
        if((abs(TablaDeJoc[i-1][j])==abs(TablaDeJoc[i][j]))&&(aux[i-1][j]!=1)&&(i-1!=2*dimensiuneTabla)&&(i-1!=0)&&(j!=0)&&(j!=2*dimensiuneTabla))
    {
        aux[i-1][j]=1;
        ultim++;
        coadai[ultim]=i-1;
        coadaj[ultim]=j;
    }
    prim++;
    }

    if(jucator==2)//rosu
    {
        int cond1=0,cond2=0;
        for(int i=1;i<=ultim;i++)
            {
                if(coadai[i]==1)
                    cond1=1;
                if(coadai[i]==2*dimensiuneTabla-1)
                    cond2=1;
            }
        if((cond1==1)&&(cond2==1))
        {
            return jucator;
        }
    }
    if(jucator==1)//galben
    {
        int cond1=0,cond2=0;
        for(int j=1;j<=ultim;j++)
            {
                if(coadaj[j]==1)
                    cond1=1;
                if(coadaj[j]==2*dimensiuneTabla-1)
                    cond2=1;
            }
        if((cond1==1)&&(cond2==1))
        {
            return jucator;
        }
    }
    return 0;
}

void gameIncheiat()
{
    settextstyle(3,HORIZ_DIR,4);
    setcolor(LIGHTGRAY);
    outtextxy(10,10,"Congratulations!");
    if(jucator==1)
    {
        setcolor(YELLOW);
        outtextxy(10,50,"Yellow has won!");
    }
    else
    {
        setcolor(LIGHTRED);
        outtextxy(10,50,"Red has won!");
    }

    buton B1, B2, B3;
    B1.mx=150; B1.my=400; strcpy(B1.text, "Play again");
    B2.mx=150; B2.my=470; strcpy(B2.text, "Menu");
    B3.mx=150; B3.my=540; strcpy(B3.text, "Exit");

    desenButon(B1);
    desenButon(B2);
    desenButon(B3);
    bool gata=0, b1_status=0, b2_status=0, b3_status=0;
    int x, y;

    while(!gata)
    {
        x=mousex(), y=mousey();

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);

            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                gata=1;
                if(player==culoare)
                    jucator=1;
                else
                    jucator=2;
                initializareTablaDeJoc();
                desenTabla();
                if (nrjucatori==1)
                    slaveplay();
                else
                    play();
            }
            else
                if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
                {
                    gata=1;
                    desenCopertaJoc();
                }
                else
                    if(x>=B3.x1 && x<=B3.x2 && y>=B3.y1 && y<=B3.y2)
                        gata=1;
        }
        else
        {
            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                if(b1_status==0)
                {
                    desenButon(B1, 4);
                    b1_status=1;
                }
            }
            else
                if(b1_status==1)
                {
                    desenButon(B1, 4, FUNDAL);
                    desenButon(B1);
                    b1_status=0;
                }

            if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
            {
                if(b2_status==0)
                {
                    desenButon(B2, 4);
                    b2_status=1;
                }
            }
            else
                if(b2_status==1)
                {
                    desenButon(B2, 4, FUNDAL);
                    desenButon(B2);
                    b2_status=0;
                }

            if(x>=B3.x1 && x<=B3.x2 && y>=B3.y1 && y<=B3.y2)
            {
                if(b3_status==0)
                {
                    desenButon(B3, 4);
                    b3_status=1;
                }
            }
            else
                if(b3_status==1)
                {
                    desenButon(B3, 4, FUNDAL);
                    desenButon(B3);
                    b3_status=0;
                }
        }
    }

}

void settings()
{
    setfillstyle(SOLID_FILL, FUNDAL);
    bar(270, 90, 830, 490);

    setlinestyle(SOLID_LINE, 0, 9);
    setcolor(BLACK);
    rectangle(270, 90, 830, 490);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(450,100,"SETTINGS");

    buton one,two,red1, yellow1, red2, yellow2, player1, player2, ok, smal, medium, large, crazy,easy,normal,hard;

    one.x1=580;one.y1=165;one.x2=600;one.y2=180;
    two.x1=310;two.y1=165;two.x2=330;two.y2=180;
    red1.x1=390; red1.y1=240; red1.x2=420; red1.y2=270;
    yellow1.x1=440; yellow1.y1=240; yellow1.x2=470; yellow1.y2=270;
    red2.x1=620; red2.y1=240; red2.x2=650; red2.y2=270;
    yellow2.x1=670; yellow2.y1=240; yellow2.x2=700; yellow2.y2=270;

    ok.mx=770; ok.my=450; strcpy(ok.text, "OK");
    desenButon(ok, 3, BLACK);

    player1.x1=340; player1.y1=320; player1.x2=360; player1.y2=335;
    player2.x1=570; player2.y1=320; player2.x2=590; player2.y2=335;
    smal.x1=340; smal.y1=375; smal.x2=360; smal.y2=390;
    medium.x1=340; medium.y1=400; medium.x2=360; medium.y2=415;
    large.x1=340; large.y1=425; large.x2=360; large.y2=440;
    crazy.x1=340; crazy.y1=450; crazy.x2=360; crazy.y2=465;
    easy.x1=570;easy.y1=375;easy.x2=590;easy.y2=390;
    normal.x1=570;normal.y1=400;normal.x2=590;normal.y2=415;
    hard.x1=570;hard.y1=425;hard.x2=590;hard.y2=440;

    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(285,140,"How many players?");
    outtextxy(285,190,"Choose colors:");
    outtextxy(285,290,"Which player begins?");
    outtextxy(285,350,"Table dimension:");
    outtextxy(560,350,"Computer level:");

    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    setcolor(LIGHTGRAY);
    outtextxy(370,210,"Player 1");
    outtextxy(600,210,"Player 2");
    outtextxy(340,165,"Two players");
    outtextxy(610,165,"One player");

    outtextxy(370,320,"Player 1");
    outtextxy(600,320,"Player 2");

    setfillstyle(SOLID_FILL,LIGHTRED);
    bar(red1.x1,red1.y1,red1.x2,red1.y2);
    bar(red2.x1,red2.y1,red2.x2,red2.y2);

    setfillstyle(SOLID_FILL,YELLOW);
    bar(yellow1.x1,yellow1.y1,yellow1.x2,yellow1.y2);
    bar(yellow2.x1,yellow2.y1,yellow2.x2,yellow2.y2);

    setlinestyle(SOLID_LINE, 0, 4);
    setcolor(BLACK);
    if(culoare==1)
    {
        rectangle(red1.x1, red1.y1, red1.x2, red1.y2);
        rectangle(yellow2.x1, yellow2.y1, yellow2.x2, yellow2.y2);
    }
    else
    {
        rectangle(red2.x1, red2.y1, red2.x2, red2.y2);
        rectangle(yellow1.x1, yellow1.y1, yellow1.x2, yellow1.y2);
    }

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(340,320,360,335);//coordonate player1
    bar(570,320,590,335);//coordonate player2
    bar(one.x1,one.y1,one.x2,one.y2);
    bar(two.x1,two.y1,two.x2,two.y2);

    outtextxy(370, 375,"Small");
    outtextxy(370, 400,"Medium");
    outtextxy(370, 425,"Large");
    outtextxy(370, 450,"Crazy");
    outtextxy(600,375,"Easy");
    outtextxy(600,400,"Normal");
    outtextxy(600,425,"Hard");

    bar(340,375,360,390);//coordonate Small
    bar(340,400,360,415);//coordonate Medium
    bar(340,425,360,440);//coordonate Large
    bar(340,450,360,465);//coordonate Crazy
    bar(easy.x1,easy.y1,easy.x2,easy.y2);
    bar(normal.x1,normal.y1,normal.x2,normal.y2);
    bar(hard.x1,hard.y1,hard.x2,hard.y2);

    setbkcolor(LIGHTGRAY);
    setcolor(BLACK);
    if(player==1 || nrjucatori==1)
        outtextxy(player1.x1,player1.y1,"x");
    else
        outtextxy(player2.x1,player2.y1,"x");

    if(dimensiuneTabla==4)
        outtextxy(smal.x1,smal.y1,"x");
    else
        if(dimensiuneTabla==5)
            outtextxy(medium.x1,medium.y1,"x");
        else
            if(dimensiuneTabla==6)
                outtextxy(large.x1,large.y1,"x");
            else
                outtextxy(crazy.x1,crazy.y1,"x");

    if(nrjucatori==2)
        outtextxy(two.x1,two.y1,"x");
    else
    {
        outtextxy(one.x1,one.y1,"x");
    }


    if( level_computer==1)
        outtextxy(easy.x1,easy.y1,"x");
    else
        if(level_computer==2)
          outtextxy(normal.x1,normal.y1,"x");
        else
            if(level_computer==3)
                outtextxy(hard.x1,hard.y1,"x");

    bool gata=0, ok_status=0;
    while(!gata)
    {
        int x=mousex(), y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
          if(x>=one.x1 && x<=one.x2 && y>=one.y1 && y<=one.y2)
          {
            if(nrjucatori==2)
            {
                nrjucatori=1;
                setbkcolor(LIGHTGRAY);
                setcolor(BLACK);
                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                outtextxy(one.x1,one.y1,"x");
                setfillstyle(SOLID_FILL,LIGHTGRAY);
                bar(two.x1, two.y1, two.x2, two.y2);
                if(player==2)
                {
                    player=1;
                    setbkcolor(LIGHTGRAY);
                    setcolor(BLACK);
                    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                    outtextxy(player1.x1,player1.y1,"x");
                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                    bar(player2.x1, player2.y1, player2.x2, player2.y2);
                }
            }
           }
           else
               if(x>=two.x1 && x<=two.x2 && y>=two.y1 && y<=two.y2)
                {
                    if(nrjucatori==1)
                    {
                        nrjucatori=2;
                        setbkcolor(LIGHTGRAY);
                        setcolor(BLACK);
                        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                        outtextxy(two.x1,two.y1,"x");
                        setfillstyle(SOLID_FILL,LIGHTGRAY);
                        bar(one.x1, one.y1, one.x2, one.y2);
                    }
                }
                else

            if((x>=red1.x1 && x<=red1.x2 && y>=red1.y1 && y<=red1.y2) || (x>=yellow2.x1 && x<=yellow2.x2 && y>=yellow2.y1 && y<=yellow2.y2))
            {
                if(culoare==2)
                {
                    culoare=1;

                    rectangle(red1.x1, red1.y1, red1.x2, red1.y2);
                    rectangle(yellow2.x1, yellow2.y1, yellow2.x2, yellow2.y2);

                    setfillstyle(SOLID_FILL,LIGHTRED);
                    bar(red2.x1-1,red2.y1-1,red2.x2+1,red2.y2+1);
                    setfillstyle(SOLID_FILL,YELLOW);
                    bar(yellow1.x1-1,yellow1.y1-1,yellow1.x2+1,yellow1.y2+1);
                }
            }
            else
                if((x>=red2.x1 && x<=red2.x2 && y>=red2.y1 && y<=red2.y2) || (x>=yellow1.x1 && x<=yellow1.x2 && y>=yellow1.y1 && y<=yellow1.y2))
                {
                    if(culoare==1)
                    {
                        culoare=2;

                        rectangle(red2.x1, red2.y1, red2.x2, red2.y2);
                        rectangle(yellow1.x1, yellow1.y1, yellow1.x2, yellow1.y2);

                        setfillstyle(SOLID_FILL,LIGHTRED);
                        bar(red1.x1-1,red1.y1-1,red1.x2+1,red1.y2+1);
                        setfillstyle(SOLID_FILL,YELLOW);
                        bar(yellow2.x1-1,yellow2.y1-1,yellow2.x2+1,yellow2.y2+1);
                    }
                }
                else
                    if(x>=ok.x1 && x<=ok.x2 && y>=ok.y1 && y<=ok.y2)
                        gata=1;
                    else
                        if(nrjucatori==2 && x>=player1.x1 && x<=player1.x2 && y>=player1.y1 && y<=player1.y2)
                        {
                            if(player==2)
                            {
                                player=1;

                                setbkcolor(LIGHTGRAY);
                                setcolor(BLACK);
                                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                outtextxy(player1.x1,player1.y1,"x");
                                setfillstyle(SOLID_FILL,LIGHTGRAY);
                                bar(player2.x1, player2.y1, player2.x2, player2.y2);
                            }
                        }
                        else
                            if(nrjucatori==2 && x>=player2.x1 && x<=player2.x2 && y>=player2.y1 && y<=player2.y2)
                            {
                                if(player==1)
                                {
                                    player=2;

                                    setbkcolor(LIGHTGRAY);
                                    setcolor(BLACK);
                                    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                    outtextxy(player2.x1,player2.y1,"x");
                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                    bar(player1.x1, player1.y1, player1.x2, player1.y2);
                                }
                            }
                            else
                                if(x>=smal.x1 && x<=smal.x2 && y>=smal.y1 && y<=smal.y2)
                                {
                                    if(dimensiuneTabla!=4)
                                    {
                                        dimensiuneTabla=4;
                                        setbkcolor(LIGHTGRAY);
                                        setcolor(BLACK);
                                        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                        outtextxy(smal.x1,smal.y1,"x");
                                        setfillstyle(SOLID_FILL,LIGHTGRAY);
                                        bar(medium.x1, medium.y1, medium.x2, medium.y2);
                                        bar(large.x1, large.y1, large.x2, large.y2);
                                        bar(crazy.x1, crazy.y1, crazy.x2, crazy.y2);
                                    }
                                }
                                else
                                    if(x>=medium.x1 && x<=medium.x2 && y>=medium.y1 && y<=medium.y2)
                                    {
                                        if(dimensiuneTabla!=5)
                                        {
                                            dimensiuneTabla=5;
                                            setbkcolor(LIGHTGRAY);
                                            setcolor(BLACK);
                                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                            outtextxy(medium.x1,medium.y1,"x");
                                            setfillstyle(SOLID_FILL,LIGHTGRAY);
                                            bar(smal.x1, smal.y1, smal.x2, smal.y2);
                                            bar(large.x1, large.y1, large.x2, large.y2);
                                            bar(crazy.x1, crazy.y1, crazy.x2, crazy.y2);
                                        }
                                    }
                                    else
                                        if(x>=large.x1 && x<=large.x2 && y>=large.y1 && y<=large.y2)
                                        {
                                            if(dimensiuneTabla!=6)
                                            {
                                                dimensiuneTabla=6;
                                                setbkcolor(LIGHTGRAY);
                                                setcolor(BLACK);
                                                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                                outtextxy(large.x1,large.y1,"x");
                                                setfillstyle(SOLID_FILL,LIGHTGRAY);
                                                bar(smal.x1, smal.y1, smal.x2, smal.y2);
                                                bar(medium.x1, medium.y1, medium.x2, medium.y2);
                                                bar(crazy.x1, crazy.y1, crazy.x2, crazy.y2);
                                            }
                                        }
                                        else
                                            if(x>=crazy.x1 && x<=crazy.x2 && y>=crazy.y1 && y<=crazy.y2)
                                            {
                                                if(dimensiuneTabla!=2)
                                                {
                                                    dimensiuneTabla=2;
                                                    setbkcolor(LIGHTGRAY);
                                                    setcolor(BLACK);
                                                    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                                    outtextxy(crazy.x1,crazy.y1,"x");
                                                    setfillstyle(SOLID_FILL,LIGHTGRAY);
                                                    bar(smal.x1, smal.y1, smal.x2, smal.y2);
                                                    bar(medium.x1, medium.y1, medium.x2, medium.y2);
                                                    bar(large.x1, large.y1, large.x2, large.y2);
                                                }
                                            }
                                            else
                                                if(nrjucatori==1 && x>=easy.x1 && x<=easy.x2 && y>=easy.y1 && y<=easy.y2)
                                                {
                                                    if(level_computer!=1)
                                                    {
                                                        level_computer=1;
                                                        setbkcolor(LIGHTGRAY);
                                                        setcolor(BLACK);
                                                        settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                                        outtextxy(easy.x1,easy.y1,"x");
                                                        setfillstyle(SOLID_FILL,LIGHTGRAY);
                                                        bar(normal.x1, normal.y1, normal.x2, normal.y2);
                                                        bar(hard.x1, hard.y1, hard.x2, hard.y2);
                                                    }
                                                }
                                                else
                                                    if(nrjucatori==1 && x>=normal.x1 && x<=normal.x2 && y>=normal.y1 && y<=normal.y2)
                                                     {
                                                         if(level_computer!=2)
                                                         {
                                                             level_computer=2;
                                                             setbkcolor(LIGHTGRAY);
                                                            setcolor(BLACK);
                                                            settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                                            outtextxy(normal.x1,normal.y1,"x");
                                                            setfillstyle(SOLID_FILL,LIGHTGRAY);
                                                            bar(easy.x1,easy.y1, easy.x2, easy.y2);
                                                            bar(hard.x1, hard.y1, hard.x2, hard.y2);
                                                         }
                                                     }
                                                     else
                                                        if(nrjucatori==1 && x>=hard.x1 && x<=hard.x2 && y>=hard.y1 && y<=hard.y2)
                                                         {
                                                             if(level_computer!=3)
                                                             {
                                                                 level_computer=3;
                                                                  setbkcolor(LIGHTGRAY);
                                                                setcolor(BLACK);
                                                                settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
                                                                outtextxy(hard.x1,hard.y1,"x");
                                                                setfillstyle(SOLID_FILL,LIGHTGRAY);
                                                                bar(easy.x1,easy.y1, easy.x2, easy.y2);
                                                                bar(normal.x1, normal.y1, normal.x2, normal.y2);
                                                             }
                                                         }
        }
        else
            if(x>=ok.x1 && x<=ok.x2 && y>=ok.y1 && y<=ok.y2)
            {
                if(ok_status==0)
                {
                    ok_status=1;
                    setbkcolor(FUNDAL);
                    desenButon(ok, 4, BLACK);
                }
            }
            else
                if(ok_status==1)
                {
                    ok_status=0;
                    setbkcolor(FUNDAL);
                    desenButon(ok, 4, FUNDAL);
                    desenButon(ok, 3, BLACK);
                }

    }
    if(player==culoare)
        jucator=1;
    else
        jucator=2;
}

void informations()
{
    setfillstyle(SOLID_FILL, FUNDAL);
    bar(270, 145, 830, 490);

    setlinestyle(SOLID_LINE, 0, 9);
    setcolor(BLACK);
    rectangle(270, 145, 830, 490);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
    outtextxy(400,155,"INFORMATIONS");

    setfillstyle(SOLID_FILL,RED);
    bar(810,140,835,165);

    setlinestyle(SOLID_LINE,0,2);
    setcolor(WHITE);
    line(817,144,830,158);
    line(817,158,830,144);

    settextstyle(4,HORIZ_DIR,2);
    setcolor(LIGHTRED);
    outtextxy(297,190,"Bridg-It");
    outtextxy(360,275,"RULES");
    setcolor(WHITE);
    outtextxy(400,190," is a simple connection board");
    outtextxy(288,215,"game that was created around 1960");
    outtextxy(288,240,"by a man named David Gale.");
    outtextxy(297,275,"The");
    outtextxy(470,275,"of Bridg-It are as follows:");
    outtextxy(288,305,"1. players take turns connecting");
    outtextxy(288,330,"two adjacent dots of their own color");
    outtextxy(288,355,"with a bridge,");
    outtextxy(288,385,"2. a newly formed bridge can NOT");
    outtextxy(288,410,"cross a bridge already played,");
    outtextxy(288,440,"3. whoever connects their opposite");
    outtextxy(288,465,"edges of the board first wins.");

    bool gata=false;
    while(!gata)
    {
        int x=mousex(), y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            if(x>810 && x<835 && y>140 &&y<165)
                gata=1;
        }
    }

}

void timer(clock_t start,int numarmutari)
{
    char charscor[10];
    int scor,penalty;
    clock_t duration;
    duration=difftime(clock(),start);
    //cout<<duration/1000<<","<<duration%1000<<" secunde";
    scor=(int)duration/100+nrmutari;

    penalty=1000-scor;
    if(penalty<0)
    penalty=0;
    itoa(penalty,charscor,10);
    //cout<<scor;
    outtextxy(10,100,"SCOR :");
    outtextxy(150,100,charscor);

}
