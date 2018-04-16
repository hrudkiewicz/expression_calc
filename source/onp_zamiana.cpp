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

using namespace std;

const int N =9;           //rozmiar tablicy;
const int S_MAX = 9;       //rozmiar stosu-tablicy;

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

int onp_zamiana(int *wsk)
{
    char S[S_MAX];              //stos do przechowywania operatorów
    int wsk_s = 0;              //wskaznik stosu operatorow;
    string ONP[S_MAX];            //stos do obliczania ONP
    int wsk_onp = 0;              //wskaznik stosu ONP
    string liczba;
    bool czy_ujemna = false;      //ujemna zmienna;
    char c[] = { '5','-', '(', 's','3','0','+','1',')'};

    stringstream *ss;
    ss = new stringstream;
    ss->str( std::string() );
    ss->clear();
    *ss << " ";

    for(int i=0; i<N; i++)
    {
         if((c[i]>='0' && c[i]<='9') || c[i]=='.')
           *ss << c[i];
         else
         {
             switch(c[i])
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
                          ss = new stringstream;
                          ss->str( std::string() );
                          ss->clear();
                          *ss << " ";
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

                           ss = new stringstream;
                           ss->str( std::string() );
                           ss->clear();
                           *ss << " ";
                    }
                  czy_ujemna = true;
                  //jezeli stos pusty to nie zamieniać na +, - tylko zmienia charakter zmiennej
                  if(i==0 || c[i-1]=='(')
                  {
                     if(c[i+1]=='(')
                     {
                       S[wsk_s++] = '*';
                       ONP[wsk_onp++] = "-1";
                       czy_ujemna = false;
                     }
                     break;
                   }
                  else if(c[i+1]=='(')
                  {
                      S[wsk_s++] = '+';
                      S[wsk_s++] = '*';
                      ONP[wsk_onp++] = "-1";
                      czy_ujemna = false;
                      break;
                  }
                  else
                      c[i] = '+';
                 case '+':;
                 case '*':;
                 case '/':;
                 case '^':;
                 case 's':;
                 case 'c': while (wsk_s)
                  {
                   if ((p(c[i]) == 4) || (p(c[i]) > p(S[wsk_s - 1])))
                   {
                       if (ss->str() != " ")
                         {
                             *ss >> liczba;

                           if (czy_ujemna)
                               ONP[wsk_onp++] =("-" + liczba);
                           else
                               ONP[wsk_onp++] =liczba;
                             czy_ujemna = false;

                               ss = new stringstream;
                               ss->str( std::string() );
                               ss->clear();
                               *ss << " ";
                          }
                   } break;

                    ONP[wsk_onp++] = S[--wsk_s];      //drukowanie operatorów o wyzszych priorytetach
                  }
                   S[wsk_s++] = c[i]; //operator umieszczamy na stosie
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
            ss = new stringstream;
            ss->str( std::string() );
            ss->clear();
            *ss << " ";
       }
    while(wsk_s) ONP[wsk_onp++] = S[--wsk_s];

    string *wsk_stos = ONP;      //wskaznik na stos ONP

    onp_oblicz(wsk, wsk_stos,/* &S_MAX,*/ &wsk_onp);

    return 0;
}
