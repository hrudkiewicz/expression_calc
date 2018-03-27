#include <iostream>
#include <sstream> //ss;
using namespace std;

const int N = 15;           //rozmiar tablicy;
const int S_MAX = 15;           //rozmiar stosu-tablicy;

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
    char c[] = { '(','1', '2', '.','3', '+', '4',')','/','(','s','5',')','^','6' };
    stringstream *ss;
    ss = new stringstream;
    ss->str( std::string() );
    ss->clear();
    *ss << " ";
    char S[S_MAX];
    int wsk_s = 0;          //wskaznik stosu;
    float liczba;
    bool czy_ujemna=false;

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
                 break;
                case ')': while (S[wsk_s - 1] != '(')
                 {
                     if (ss->str() != " ")
                     {
                         *ss >> liczba;

                         if (czy_ujemna)
                             cout << liczba * (-1) << endl;
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

                 wsk_s--;
                 break;
                case '-':
                 if (ss->str() != " ")
                   {
                       *ss >> liczba;

                       if (czy_ujemna)
                           cout << liczba * (-1) << endl;
                       else
                           cout << liczba << endl;
                           ss = new stringstream;
                           ss->str( std::string() );
                           ss->clear();
                           *ss << " ";
                    }
                  czy_ujemna = true;
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
                                 cout << liczba * (-1) << endl;
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

          if (czy_ujemna)
              cout << liczba * (-1) << endl;
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
