// /*

// ###########################################
// #                                         #
// #    Alexandre Augusto - 150056940        #
// #    Andrey Galvao Mendes - 180097911     #
// #                                         #
// ###########################################

// */

// #include "../include/menu.hpp"

// int menu(void)
// {
//   int op, idioma;
//   std::string chave, msg, cifra;

//   while (true)
//   {

//     std::cout << "\n\tMENU" << std::endl;
//     std::cout << "1 - Cifrar" << std::endl;
//     std::cout << "2 - Decifrar" << std::endl;
//     std::cout << "3 - Recuperar chave" << std::endl;
//     std::cout << "4 - Sair" << std::endl;

//     std::cin >> op;

//     switch (op)
//     {
//     case 1:
//       std::cout << "Escreva o texto: " << std::endl;
//       std::cin.ignore();
//       getline(std::cin, msg);

//       std::cout << "Escreva a chave: " << std::endl;
//       std::cin >> chave;

//       msg = cipher(normText(msg), normText(chave));

//       std::cout << std::endl
//                 << msg << std::endl;
//       break;

//     case 2:
//       std::cout << "Escreva o texto cifrado: " << std::endl;

//       std::cin.ignore();
//       getline(std::cin, msg);

//       std::cout << "Escreva a chave: " << std::endl;

//       std::cin >> chave;

//       msg = decipher(normText(msg), normText(chave));

//       std::cout << std::endl
//                 << msg << std::endl;
//       break;

//     case 3:
//       std::cout << "Escreva o texto cifrado: " << std::endl;

//       std::cin.ignore();
//       getline(std::cin, msg);

//       std::cout << "Idioma do texto:\n1 - inglês\n2 - portugues" << std::endl;
//       std::cin >> idioma;

//       if (idioma != 1 && idioma != 2)
//         break;

//       descChave(msg, idioma);
//       break;

//     case 4:
//       return 0;
//     }
//   }
// }