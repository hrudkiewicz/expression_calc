#include <iostream>
#include "onp_zamiana.h"

using namespace std;

int main()
{

    //stałe, potem zamiana na dynamiczne
    const int N =9;           //rozmiar tablicy;
   // int const* n = &N;

    char c[] = { '5','-', '(', 's','3','0','-','1',')'};
    char *wsk_c = c;

    onp_zamiana(wsk_c, N);
    return 0;
}
