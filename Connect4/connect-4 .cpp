#include <iostream>
#include <winbgim.h>
//#include<SFML/Audio.hpp>
using namespace std;

#define FUNDAL LIGHTBLUE
#define LUNGIME 1300
#define LATIME 700


//sf::SoundBuffer bufferForSunet;
//sf::Sound sunet;


int tabla_joc[6][7], jucator=1;

struct buton {
    int x1, y1, x2, y2, mx, my;
    char text[20];
};

void DesenJoc();

void desenButon(buton &b, int textsize=4, int color=WHITE)
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

void initializare()
{
    jucator=1; //incepe joc nou. jucatorul 1 va incepe jocul

    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            tabla_joc[i][j]=0;
        }
    }
   /*  if(!bufferForSunet.loadFromFile("audio/hit1.wav"))
     {
         cout<<"Nu s-a gasit fisierul hit1.wav!"<<endl;
     }
     sunet.setBuffer(bufferForSunet);
     */
}

void afisare()
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
            cout<<tabla_joc[i][j];
        cout<<endl;
    }
}

int actualizare_tabla(int coloana)
{
    for(int i=0;i< 6;i++)
    {
        if(tabla_joc[i][coloana] != 0)
        {
            tabla_joc[i-1][coloana] = jucator;
            return i-1;//returneaza linia pe care a fost asezata piesa
        }

    }
    if(tabla_joc[5][coloana]== 0)
    {
        tabla_joc[5][coloana] = jucator;
        return 5;//returneaza linia pe care a fost asezata piesa
    }
}

int validare_mutare(int mutare)
{
    if (mutare>=0 and mutare < 7)
    {
        for(int i=0;i<6;i++)
            if(tabla_joc[i][mutare] == 0)
                return 1;
            else
                return 0;
    }
    else
        return 0;
}

int victorie(int coloana)
{
    int i, j, ok, culoare, k, l;

    for(i=0; i<6, tabla_joc[i][coloana]==0; i++)
        ;
    culoare=tabla_joc[i][coloana];
    int linie=i;

    if(linie<3 && tabla_joc[linie+1][coloana]==culoare && tabla_joc[linie+2][coloana]==culoare && tabla_joc[linie+3][coloana]==culoare)
        return 1;

    if(coloana<3)//orizontal
        i=0;
    else
        i=coloana-3;
    for(; i<=coloana, i+3<7; i++)
    {
        ok=1;
        for(j=i; j<i+4; j++)
            if(tabla_joc[linie][j]!=culoare)
            {
                ok=0;
                break;
            }
        if(ok)
            return 1;
    }

    if(linie<3 || coloana<3) //diag principala
    {
        i=linie-min(linie, coloana);
        j=coloana-min(linie, coloana);
    }
    else
    {
        i=linie-3;
        j=coloana-3;
    }
    for(; i<=linie, j<=coloana, i+3<6, j+3<7; i++, j++)
    {
        ok=1;
        for(k=i, l=j; k<i+4; k++, l++)
            if(tabla_joc[k][l]!=culoare)
            {
                ok=0;
                break;
            }
        if(ok)
            return 1;
    }

    if(linie>2 || coloana<3) //diagonala sec
    {
        i=linie+min(5-linie, coloana);
        j=coloana-min(5-linie, coloana);
    }
    else
    {
        i=linie+3;
        j=coloana-3;
    }
    for(; i>=linie, j<=coloana, i-3>=0, j+3<7; i--, j++)
    {
        ok=1;
        for(k=i, l=j; k>i-4; k--, l++)
            if(tabla_joc[k][l]!=culoare)
            {
                ok=0;
                break;
            }
        if(ok)
            return 1;
    }


    return 0;
}

int remiza()
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(tabla_joc[i][j]==0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void desenCaderePiesa(int coloana,int linie)
{


    int x=150+coloana*100;
    int y=140;
    for(int i=0;i<=linie;i++)
    {
        fillellipse(x,y,35,35);
        delay(200);
        if(i!=linie)
        {
            setfillstyle(SOLID_FILL,FUNDAL);
            fillellipse(x,y,35,35);
        }
        if(jucator==1)
        {
            setfillstyle(SOLID_FILL,RED);
        }
        else
        {
             setfillstyle(SOLID_FILL,YELLOW);
        }

        y=y+100;
    }

    if(jucator==1)
    {
        jucator=2;
        setfillstyle(SOLID_FILL,YELLOW);
        setcolor(YELLOW);
        settextstyle(4,HORIZ_DIR,4);
        outtextxy(830,140,"Yellow's turn...");
        setcolor(WHITE);
    }
    else
    {
        jucator=1;

        setcolor(FUNDAL);
        settextstyle(4,HORIZ_DIR,4);
        outtextxy(830,140,"Yellow's turn...");

        setfillstyle(SOLID_FILL,RED);
        setcolor(RED);
        settextstyle(4,HORIZ_DIR,4);
        outtextxy(830,140,"Red's turn...");
        setcolor(WHITE);
    }
}

void gameIncheiat(int win)
{
    setcolor(FUNDAL);
    settextstyle(4,HORIZ_DIR,4);
    outtextxy(830,140,"Yellow's turn...");

    setcolor(WHITE);
    //cu comenzile de mai sus sterg scrisul ala
    if(win==1)
    {
       if(jucator==1)
        {
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            setcolor(YELLOW);
            outtextxy(50,30,"Yellow wins!");
        }
        else
        {
            settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
            setcolor(RED);
            outtextxy(50,30,"Red wins!");
        }
    }
    else
    {
        settextstyle(DEFAULT_FONT,HORIZ_DIR,4);
        setcolor(WHITE);
        outtextxy(50,30,"It is a draw!");
    }

    int x,y,exit=0;
    int statusB1=0,statusB2=0;
    buton B1, B2;

    B1.mx=1050; B1.my=510; strcpy(B1.text, "Replay");
    B2.mx=1050; B2.my=600; strcpy(B2.text, "Exit");
    desenButon(B1);
    desenButon(B2);

    do
    {
        x=mousex();
        y=mousey();
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                exit=1;//ies din functie, se incepe un joc nou
                initializare();
                DesenJoc();
            }

            if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
            {
                exit=1;//se incheie functia gameIncheiat(), si se ajunge in main la closegraph(), functie care inchide fereastra grafica
            }
        }
        else// nu este click ci doar cursorul este deasupra
        {
            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                if(statusB1==0)
                {
                   // sunet.play();
                    desenButon(B1,5);
                    statusB1=1;
                }
            }
            else
            {
                if(statusB1==1)
                {
                    desenButon(B1,5,FUNDAL);
                    desenButon(B1);
                    statusB1=0;
                }
            }
            if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
            {
                if(statusB2==0)
                {
                    //sunet.play();
                    desenButon(B2, 5);
                    statusB2=1;
                }
            }
            else
            {
                if(statusB2==1)
                {
                    desenButon(B2, 5, FUNDAL);
                    desenButon(B2);
                    statusB2=0;
                }
            }
        }

    }while(exit==0);
}

void play()
{


    int mutare,win=0,egal=0;

    int x,y,linie,coloana;
    int statusB1=0,statusB2=0;
    int x1=-1;
    buton B1, B2;

    B1.mx=1050; B1.my=510; strcpy(B1.text, "Replay");
    B2.mx=1050; B2.my=600; strcpy(B2.text, "Exit");
    desenButon(B1);
    desenButon(B2);

    setfillstyle(SOLID_FILL,RED);

    setcolor(RED);
    settextstyle(4,HORIZ_DIR,4);
    outtextxy(830,140,"Red's turn...");
    setcolor(WHITE);

    do
    {
        x=mousex();
        y=mousey();

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            //verificare daca apasa butoanele sau daca apasa in tabla pe coloane
            mutare=(x-100)/100;//daca este in interiorul matricei, mutare va fi egala cu coloana pe care s-a facut click
            if( x>=100 && validare_mutare(mutare) )
            {
                coloana=mutare;
                linie=actualizare_tabla(mutare);

                setfillstyle(SOLID_FILL,FUNDAL);
                setcolor(FUNDAL);
                fillellipse(150+mutare*100,55,35,35);
                setcolor(WHITE);
                if(jucator==1)
                {
                    setfillstyle(SOLID_FILL,RED);
                }
                else
                {
                    setfillstyle(SOLID_FILL,YELLOW);
                }

                desenCaderePiesa(coloana,linie);// schimb si jucatorii
                win=victorie(coloana);
                egal=remiza();
                if(win==1)
                {
                    setfillstyle(SOLID_FILL,FUNDAL);
                    setcolor(FUNDAL);
                    fillellipse(150+mutare*100,55,35,35);
                    // cu comenzile de mai sus sterg bila ce sta deasupra cand plimb mouse-ul

                    gameIncheiat(win);//cand se intoarce din functia gameIncheiat(), functia play se va incheia pt ca win=1 si se termina while-ul
                }
                else
                {
                    if(egal==1)
                    {
                         setfillstyle(SOLID_FILL,FUNDAL);
                        setcolor(FUNDAL);
                        fillellipse(150+mutare*100,55,35,35);
                        // cu comenzile de mai sus sterg bila ce sta deasupra cand plimb mouse-ul

                        gameIncheiat(win);//cand se intoarce din functia gameIncheiat(), functia play se va incheia pt ca win=1 si se termina while-ul

                    }

                }
            }
            else
            {

                if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
                 {
                     win=1;//inchei jocul curent si incep altul nou
                     initializare();
                     DesenJoc();
                 }

                if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
                {
                    win=1;//se incheie functia play, si se ajunge in main la closegraph(), functie care inchide fereastra grafica
                }
            }

        }
        else// nu este click ci doar cursorul este deasupra
        {

            mutare=(x-100)/100;

            if(mutare>=0 && mutare<7)
            {
                if(x1!=-1 && x1!=mutare)// x1 coloana ce a fost obtinuta din coordonatele anterioare ale mouse-ului
                {
                    setfillstyle(SOLID_FILL,FUNDAL);
                    setcolor(FUNDAL);
                    fillellipse(150+x1*100,55,35,35);
                }
                x1=mutare;
                if(jucator==1)
                {
                    setfillstyle(SOLID_FILL,RED);
                    setcolor(RED);
                }
                else
                {
                    setfillstyle(SOLID_FILL,YELLOW);
                    setcolor(YELLOW);
                }
                fillellipse(150+mutare*100,55,35,35);
                setcolor(WHITE);
            }


            if(x>=B1.x1 && x<=B1.x2 && y>=B1.y1 && y<=B1.y2)
            {
                if(statusB1==0)
                {
                   // sunet.play();
                    desenButon(B1,5);
                    statusB1=1;
                }
            }
            else
            {
                if(statusB1==1)
                {
                    desenButon(B1,5,FUNDAL);
                    desenButon(B1);
                    statusB1=0;
                }
            }
            if(x>=B2.x1 && x<=B2.x2 && y>=B2.y1 && y<=B2.y2)
            {
                if(statusB2==0)
                {
                    //sunet.play();
                    desenButon(B2, 5);
                    statusB2=1;
                }
            }
            else
            {
                if(statusB2==1)
                {
                    desenButon(B2, 5, FUNDAL);
                    desenButon(B2);
                    statusB2=0;
                }
            }
        }
    }while(win==0 && egal==0);


}
void DesenCoperta()
{
    readimagefile("img/connect4.jpg",0,0,LUNGIME,LATIME);

    settextstyle(10,HORIZ_DIR,3);

    while(!ismouseclick(WM_LBUTTONDOWN));
    clearmouseclick(WM_LBUTTONDOWN);

    DesenJoc();
}

void DesenJoc()
{
    setbkcolor(FUNDAL);clearviewport();

    setfillstyle(SOLID_FILL,BLUE);
    rectangle(100,90,800,690);
    floodfill(101,91,15);
    setfillstyle(SOLID_FILL,FUNDAL);
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {

            fillellipse(150+j*100,140+i*100,35,35);
        }
    }

    //readimagefile("img/muzica.jpg",1200,50,1230,80);

    play();
}

main()
{

    initwindow(LUNGIME,LATIME,"CONNECT4",30,0);
    initializare();
    DesenCoperta();
    closegraph();
    return 0;

}
