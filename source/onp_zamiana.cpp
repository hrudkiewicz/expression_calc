#include <iostream>
#include <sstream> //ss;
#include "onp_zamiana.h"
#include "onp_oblicz.h"

/* w tej wersji mozna przed uruchomieniem programu wprowadzic wyrazenie do tablicy znakow c[], zmieniajac wartosci stalych
 * program drukuje przetworzone wyrazenie na system ONP
 * to do list:
 * ->zamiast cout to na stos FIFO do obliczania ONP
 * ->obliczanie onp W NOWYM MODULE
 * ->drukowanie wyniku
*/

int p(char ch)
{
    switch (ch)
    {
    case '+': return 1;
        //       case '-' : return 1;
    case '*': return 2;
    case '/': return 2;
    case '^': return 3;
    case 's': return 4;     //sin i cos podawane w stopniach
    case 'c': return 4;
    }
    return 0;
}

int onp_zamiana(char *wsk, const int rozmiar)
{
    //zmienne
    char S[rozmiar];              //stos do przechowywania operatorów
    int wsk_s = 0;              //wskaznik stosu operatorow;
    string ONP[rozmiar];          //stos do obliczania ONP
    int wsk_onp = 0;            //wskaznik stosu ONP
    string liczba;              //zamiana znaków na liczbe w stringu
    bool czy_ujemna = false;    //ujemna zmienna;
    bool czy_try = false;       //trygonometryczne inaczej traktowane w ONP

    //strumien
    stringstream *ss;
    ss = new stringstream;
    ss->str( std::string() );
    ss->clear();
    *ss << " ";

    for(int i=0; i<rozmiar; i++)
    {
         if((wsk[i]>='0' && wsk[i]<='9') || wsk[i]=='.')
           *ss << wsk[i];
         else
         {
             switch(wsk[i])
             {
                case ' ': break;                //ignorowanie spacji;
                case '(': S[wsk_s++] = '(';     //na stos i zwiekszenie wsk_s o 1
                 if(czy_ujemna)
                 {
                     czy_ujemna=false;
                 }
                 break;
                case ')': while (S[wsk_s - 1] != '(')
                 {
                     if (ss->str() != " ")
                     {
                         *ss >> liczba;

                         if (czy_ujemna)
                             ONP[wsk_onp++] =("-" + liczba);
                         else
                             ONP[wsk_onp++] =liczba;

                         czy_ujemna = false;
                          delete ss;
                          ss = new stringstream;
                          ss->str( std::string() );
                          ss->clear();
                          *ss << " ";
                          if(czy_try)
                          {
                              ONP[wsk_onp++] = S[--wsk_s];
                              czy_try = false;
                          }
                     }
                 ONP[wsk_onp++] = S[--wsk_s];
                 }
                 wsk_s--;
                 break;
                case '-':
                 if (ss->str() != " ")
                   {
                       *ss >> liczba;

                        if (czy_ujemna)
                            ONP[wsk_onp++] =("-" + liczba);
                        else
                            ONP[wsk_onp++] =liczba;

                           delete ss;
                           ss = new stringstream;
                           ss->str( std::string() );
                           ss->clear();
                           *ss << " ";
                           if(czy_try)
                           {
                               ONP[wsk_onp++] = S[--wsk_s];
                               czy_try = false;
                           }
                    }
                  czy_ujemna = true;
                  //jezeli stos pusty to nie zamieniać na +, - tylko zmienia charakter zmiennej
                  if(i==0 || wsk[i-1]=='(')
                  {
                     if(wsk[i+1]=='(')
                     {
                       S[wsk_s++] = '*';
                       ONP[wsk_onp++] = "-1";
                       czy_ujemna = false;
                     }
                     break;
                   }
                  else if(wsk[i+1]=='(')
                  {
                      S[wsk_s++] = '+';
                      S[wsk_s++] = '*';
                      ONP[wsk_onp++] = "-1";
                      czy_ujemna = false;
                      break;
                  }
                  else
                      wsk[i] = '+';
                 case '+':;
                 case '*':;
                 case '/':;
                 case '^':;
                 case 's':;
                 case 'c': while (wsk_s)
                  {
                     if (ss->str() != " ")
                       {
                           *ss >> liczba;

                         if (czy_ujemna)
                             ONP[wsk_onp++] =("-" + liczba);
                         else
                             ONP[wsk_onp++] =liczba;
                           czy_ujemna = false;

                             delete ss;
                             ss = new stringstream;
                             ss->str( std::string() );
                             ss->clear();
                             *ss << " ";
                             if(czy_try)
                             {
                                 ONP[wsk_onp++] = S[--wsk_s];
                                 czy_try = false;
                             }
                        }

                   if ((p(wsk[i]) == 4) || (p(wsk[i]) > p(S[wsk_s - 1])))
                   {
                    if(p(wsk[i]) == 4) czy_try = true;            //jeżeli 4 - cos/sin to inny system w ONP
                   } break;

                    ONP[wsk_onp++] = S[--wsk_s];      //drukowanie operatorów o wyzszych priorytetach
                  }
                   S[wsk_s++] = wsk[i]; //operator umieszczamy na stosie
                   break;
                  default:    break;
               }
          }
    }
    //drukowanie pozostałości
    if (ss->str() != " ")
      {
          *ss >> liczba;

        if (czy_ujemna)
            ONP[wsk_onp++] =("-" + liczba);
        else
            ONP[wsk_onp++] =liczba;
          czy_ujemna = false;
            delete ss;
            ss = new stringstream;
            ss->str( std::string() );
            ss->clear();
            *ss << " ";
            if(czy_try)
            {
                ONP[wsk_onp++] = S[--wsk_s];
                czy_try = false;
            }
       }
    while(wsk_s) ONP[wsk_onp++] = S[--wsk_s];
    delete ss;

    //przygotowanie do transportu do oblicz()
    string *wsk_stos = ONP;      //wskaznik na stos ONP
    onp_oblicz(wsk_stos, &wsk_onp);

    return 0;
}
