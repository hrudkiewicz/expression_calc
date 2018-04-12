#include <iostream>
#include <sstream> //ss;

/* w tej wersji mozna przed uruchomieniem programu wprowadzic wyrazenie do tablicy znakow c[], zmieniajac wartosci stalych
 * program drukuje przetworzone wyrazenie na system ONP */
using namespace std;

const int N = 9;           //rozmiar tablicy;
const int S_MAX = 9;           //rozmiar stosu-tablicy;

int p(char ch)
{
    switch (ch)
    {
    case '+': return 1;
        //       case '-' : return 1;
    case '*': return 2;
    case '/': return 2;
    case '^': return 3;
    case 's': return 4;
    case 'c': return 4;
    }
    return 0;
}

int main()
{
    char c[] = { '-','4', '-', '(','-', '1', '+','3',')'};
    stringstream *ss;
    ss = new stringstream;
    ss->str( std::string() );
    ss->clear();
    *ss << " ";
    char S[S_MAX];
    int wsk_s = 0;              //wskaznik stosu;
    string liczba;
    bool czy_ujemna=false;      //ujemna zmienna;
    bool czy_uj_nawias=false;   //ujemna zawartosc nawiasu

    for(int i=0; i<N; i++)
    {
         if((c[i]>='0' && c[i]<='9') || c[i]=='.')
           *ss << c[i];
         else
         {
             switch(c[i])
             {
                case ' ': break;                //ignorowanie spacji;
                case '(': S[wsk_s++] = '(';     //na stos
                 if(czy_ujemna)
                 {
                     czy_uj_nawias=true;
                     czy_ujemna=false;
                 }
                 break;
                case ')': while (S[wsk_s - 1] != '(')
                 {
                     if (ss->str() != " ")
                     {
                         *ss >> liczba;

                         if (czy_ujemna && !czy_uj_nawias)
                             cout << "-" + liczba << endl;
                         else if (!czy_ujemna && czy_uj_nawias)
                             cout << "-" + liczba << endl;
                         else if (czy_ujemna && czy_uj_nawias)
                             cout << liczba << endl;
                         else
                             cout << liczba << endl;

                         czy_ujemna = false;
                          ss = new stringstream;
                          ss->str( std::string() );
                          ss->clear();
                          *ss << " ";
                     }
                 cout << S[--wsk_s] <<endl;
                 }
                 czy_uj_nawias = false;
                 wsk_s--;
                 break;
                case '-':
                 if (ss->str() != " ")
                   {
                       *ss >> liczba;

                       if (czy_ujemna && !czy_uj_nawias)
                           cout << "-" + liczba << endl;
                       else if (!czy_ujemna && czy_uj_nawias)
                           cout << "-" + liczba << endl;
                       else if (czy_ujemna && czy_uj_nawias)
                           cout << liczba << endl;
                       else
                           cout << liczba << endl;
                           ss = new stringstream;
                           ss->str( std::string() );
                           ss->clear();
                           *ss << " ";
                    }
                  czy_ujemna = true;
                  //jezeli stos pusty to nie zamieniać na +, - tylko zmienia charakter zmiennej
                  if(i==0 || c[i-1]=='(')
                      break;
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

                           if (czy_ujemna && !czy_uj_nawias)
                               cout << "-" + liczba << endl;
                           else if (!czy_ujemna && czy_uj_nawias)
                               cout << "-" + liczba << endl;
                           else if (czy_ujemna && czy_uj_nawias)
                               cout << liczba << endl;
                           else
                               cout << liczba << endl;
                             czy_ujemna = false;
                               ss = new stringstream;
                               ss->str( std::string() );
                               ss->clear();
                               *ss << " ";
                          }
                   } break;

                   cout << S[--wsk_s] <<endl;      //drukowanie operatorów o wyzszych priorytetach
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

        if (czy_ujemna && !czy_uj_nawias)
            cout << "-" + liczba << endl;
        else if (!czy_ujemna && czy_uj_nawias)
            cout <<"-" + liczba << endl;
        else if (czy_ujemna && czy_uj_nawias)
            cout << liczba << endl;
        else
            cout << liczba << endl;
          czy_ujemna = false;
            ss = new stringstream;
            ss->str( std::string() );
            ss->clear();
            *ss << " ";
       }
    while(wsk_s) cout << S[--wsk_s] << endl;

    return 0;
}
