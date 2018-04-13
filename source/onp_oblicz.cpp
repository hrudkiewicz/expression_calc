#include <iostream>
#include <sstream> //ss;
#include <cmath> //pow, sin, cos

#include "onp_zamiana.h"
#include "onp_oblicz.h"

//czy dodac PI?

int onp_oblicz(int *wsk, string *wsk_sONP, /*int const *wsk_rozm,*/ int *wsk_o)
{
    double LICZBY[10];   //stos liczb
    int wsk_l = 0;      //wskaznik stosu liczb
    double v1, v2;      //argumenty operacji
    stringstream ss;

    for (int i=0; i< *wsk_o; i++)
    {
        ss.str("");         // usuwamy wszelki tekst ze strumienia
        ss.clear();         // czyścimy błędy konwersji z poprzednich wywołań
        ss << wsk_sONP[i];            // odczytany element umieszczamy w strumieniu

        if (ss >>v1)        // konwersja na liczbe i sprawdzenie czy sie da
            LICZBY[wsk_l] = v1; //umieszczenie na stosie

        else                // operator
        {
            if(wsk_sONP[i][0] == 's' || wsk_sONP[i][0] == 'c')
            {
                v2 = LICZBY[--wsk_l];
                switch(wsk_sONP[i][0])
                {
                    case 's' : v1 = sin(v2*PI/180); break;
                    case 'c' : v1 = cos(v2*PI/180); break;
                }
            }
            else
            {
                v2 = LICZBY[--wsk_l];
                v1 = LICZBY[--wsk_l];
                switch(wsk_sONP[i][0])
                {
                    case '+' : v1 += v2; break;
                    case '-' : v1 -= v2; break;
                    case '*' : v1 *= v2; break;
                    case '/' : v1 /= v2; break;
                    case '^' : v1 = pow(v1, v2); break;
                }
            }
        }
        LICZBY[wsk_l++] = v1;   //wynik umieszczony na stosie
    }
    cout << fixed << LICZBY[--wsk_l] <<endl;

    return 0;
}
