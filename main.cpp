/* 

###########################################
#                                         #
#    Alexandre                            #
#    Andrey Galvao Mendes  - 180097911    #
#                                         #
###########################################

*/


#include "trab1.hpp"

int main(void){
  int op, idioma;
  string chave, msg, cifra;

  while(true){
    
    cout << "\n\tMENU" << endl;
    cout << "1 - Cifrar" << endl;
    cout << "2 - Decifrar" << endl;
    cout << "3 - Recuperar chave" << endl;
    cout << "4 - Sair" << endl;

    cin >> op;
    
    switch (op){
      case 1:
        cout << "Escreva o texto: " << endl;
        cin.ignore();
        getline(cin,msg);

        cout << "Escreva a chave: " << endl;
        cin >> chave;

        msg = cifrador(normText(msg), normText(chave));

        cout << endl << msg << endl;
        break;

      case 2:
        cout << "Escreva o texto cifrado: " << endl;

        cin.ignore();
        getline(cin,msg);

        cout << "Escreva a chave: " << endl;
      
        cin >> chave;
      
        msg = decifrador(normText(msg), normText(chave));

        cout << endl << msg << endl;
        break;

      case 3:
        cout << "Escreva o texto cifrado: " << endl;

        cin.ignore();
        getline(cin, msg);
        
        cout << "Idioma do texto:\n1 - inglês\n2 - portugues" << endl;
        cin >> idioma;
        
        if(idioma != 1 && idioma != 2)
          break;

        descChave(msg, idioma);
        break;

      case 4:
        return 0;
    }
  }
}