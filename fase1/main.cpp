#include "structures/source/linkedList.cpp"
#include "structures/source/queue.cpp"
#include "structures/source/stack.cpp"
#include "structures/source/circularDoublyLinkedList.cpp"
#include "modules/sha256.h"
#include "models/source/User.cpp"
#include "models/source/Shot.cpp"
#include "models/source/Articulo.cpp"
#include "modules/json/json.h"
#include "modules/jsoncpp.cpp"
#include <windows.h>
#include <limits>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;
int main()
{
  bool playing = true, logged = false;
  int resMainMenu, resSecMenu;
  string fileDir;
  ifstream entryFile;
  circularDoublyLinkedList<User> users;
  linkedList<linkedList<Articulo>> shop;
  queue<Shot> tutorialMovements;
  linkedList<Stack<Shot>> inGameMovements;
  linkedList<string> inGameMovementsNames;
  User player;
  int playerPositionInList;
  while (playing)
  {
    cout << "************MENU************\n";
    cout << "* 1) Carga Masiva          *\n";
    cout << "* 2) Registrar Usuario     *\n";
    cout << "* 3) Login                 *\n";
    cout << "* 4) Reportes              *\n";
    cout << "* 5) Salir del Juego       *\n";
    cout << "****************************\n";
    cout << "Ingresa una accion a realizar: \n";

    cin >> resMainMenu;
    if (!cin.good())
    {
      cout << "Ingresa unicamente numeros \n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
      switch (resMainMenu)
      {
        // PUEDO VALIDAR QUE NO VENGAN NODOS REPETIDOS ?
      case 1:
      {
        // cout << "Escribe la ruta para abrir el archivo JSON \n";
        // cin >> fileDir;
        ifstream entryFile("./documents/test.json");
        Json ::Value actualJson;
        Json::Reader reader;
        // Parsing the JSON
        reader.parse(entryFile, actualJson);

        //
        Json::Value articlesLoad, usersLoad, tutorialLoad, tutorialMovementsLoad;
        articlesLoad = actualJson["articulos"];
        tutorialLoad = actualJson["tutorial"];
        tutorialMovementsLoad = actualJson["tutorial"]["movimientos"];
        usersLoad = actualJson["usuarios"];
        if (articlesLoad.isArray())
        {
          for (int i = 0; i < articlesLoad.size(); i++)
          {
            linkedList<Articulo> actualList, newList;
            Articulo item;
            item.setData(std::stoi(articlesLoad[i]["id"].asString()), articlesLoad[i]["categoria"].asString(), std::stod(articlesLoad[i]["precio"].asString()), articlesLoad[i]["nombre"].asString(), articlesLoad[i]["src"].asString());
            if (shop.length == 0)
            {
              newList.insertFirst(item);
              shop.insertFirst(newList);
            }
            else
            {
              bool inserted = false;
              for (int j = 0; j < shop.length; j++)
              {
                actualList = shop.get(j);
                bool xd = actualList.first->data.categoria == item.categoria;
                if (actualList.first->data.categoria == item.categoria)
                {
                  actualList.insertFirst(item);
                  shop.update(actualList, j);
                  inserted = true;
                  j = shop.length;
                }
              }
              if (!inserted)
              {
                newList.insertFirst(item);
                shop.insertFirst(newList);
              }
            }
          }
        }
        else
        {
          cout << "ARTICULOS No es un array verifica tu archivo de ingreso" << endl;
        }

        if (usersLoad.isArray())
        {
          for (int i = 0; i < usersLoad.size(); i++)
          {
            string username, password, age, coins;
            username = usersLoad[i]["nick"].asString();
            password = usersLoad[i]["password"].asString();
            age = usersLoad[i]["edad"].asString();
            coins = usersLoad[i]["monedas"].asString();
            User newUser;
            newUser.setData(username, SHA256::cifrar(password), std::stoi(age), std::stod(coins));
            users.insertLast(newUser);
          }
          int cantidadItems = users.count;
        }
        else
        {
          cout << "USUARIOS No es un array verifica tu archivo de ingreso" << endl;
        }

        if (tutorialMovementsLoad.isArray())
        {
          Shot shot, boardDimension;
          boardDimension.setShot(std::stoi(tutorialLoad["ancho"].asString()), std::stoi(tutorialLoad["alto"].asString()));
          tutorialMovements.enqueue(boardDimension);
          for (int i = 0; i < tutorialMovementsLoad.size(); i++)
          {
            // cout << "I VALE: " << i << endl;
            // cout << "x: " << tutorialMovementsLoad[i]["x"].asInt() << " y:" << tutorialMovementsLoad[i]["y"].asInt() << endl;
            shot.setShot(std::stoi(tutorialMovementsLoad[i]["x"].asString()), std::stoi(tutorialMovementsLoad[i]["y"].asString()));
            // cout << "ESTA INSERTANDO CON X EN : " << shot.getX() << endl;
            tutorialMovements.enqueue(shot);
          }
        }
        else
        {
          cout << "TUTORIAL No es un array verifica tu archivo de ingreso" << endl;
        }
      }
      break;
      case 2:
      {
        User newUser;
        string username, password;
        int age;
        cout << "Ingrea un nombre de usuario" << endl;
        cin >> username;
        cout << "Ingresa tu contrasenia" << endl;
        cin >> password;
        password = SHA256::cifrar(password);
        cout << "Ingresa tu edad" << endl;
        cin >> age;
        newUser.setData(username, password, age, 0);
        bool userExists = false;
        node<User> *actualNode = users.first;
        if (actualNode != NULL)
        {
          do
          {
            User actualUser = actualNode->data;
            if (actualUser.getUsername() == username)
            {
              userExists = true;
              actualNode = users.last;
            }
            else
            {
              actualNode = actualNode->next;
            }
          } while (actualNode->next != users.first);
        }
        if (!userExists)
        {
          users.insertLast(newUser);
          cout << "CUENTA CREADA EXITOSAMENTE, YA PUEDES INGRESAR" << endl;
        }
        else
        {
          cout << "YA EXISTA UNA CUENTA CON ESTE NOMBRE DE USUARIO" << endl;
        }
      }
      break;
      case 3:
      {
        string username, password;
        cout << "Ingresa tu nombre de usuario" << endl;
        cin >> username;
        cout << "Ingresa su contrasenia" << endl;
        cin >> password;
        password = SHA256::cifrar(password);
        node<User> *actualNode = users.first;
        int cont = 0;
        if (actualNode == NULL)
        {
          cout << "NO EXISTE NINGUN USUARIO CARGADO" << endl;
        }
        else
        {
          do
          {
            cont++;
            User actualUser = actualNode->data;
            if (actualUser.getUsername() == username)
            {
              if (actualUser.validatePassword(password))
              {
                playerPositionInList = cont;
                player = actualUser;
                logged = true;
                actualNode = users.last;
              }
              else
              {
                cout << "CREDENCIALES INCORRECTAS" << endl;
                actualNode = users.last;
              }
            }
            else
            {
              actualNode = actualNode->next;
            }
          } while (actualNode->next != users.first);
          if (!logged)
          {
            cout << "NO SE HA ENCONTRADO NINGUN USUARIO CON ESE USERNAME";
          }
          while (logged)
          {
            cout << "***************MENU***************" << endl;
            cout << "* 1) Editar Informacion          *" << endl;
            cout << "* 2) Eliminar Cuenta             *" << endl;
            cout << "* 3) Ver el tutorial             *" << endl;
            cout << "* 4) Ver articulos de la tienda  *" << endl;
            cout << "* 5) Realizar Movimientos        *" << endl;
            cout << "* 6) Regresar al Menú principal  *" << endl;
            cout << "**********************************" << endl;
            cout << "Ingresa una accion a realizar:  " << endl;
            cin >> resSecMenu;
            if (!cin.good())
            {
              cout << "Ingresa unicamente numeros \n";
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
              switch (resSecMenu)
              {
              case 1:
              {
                string username, password;
                int age, option;
                cout << "QUE INFORMACION DESEAS EDITAR ?" << endl;
                cout << " 1) Nombre Usuario" << endl;
                cout << " 2) Contrasenia" << endl;
                cout << " 3) Edad" << endl;
                cin >> option;
                if (!cin.good())
                {
                  cout << "Ingresa unicamente numeros \n";
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                switch (option)
                {
                case 1:
                {
                  cout << "Ingrea un nombre de usuario" << endl;
                  cin >> username;
                  player.setUsername(username);
                  users.modify(player, playerPositionInList);
                }
                break;
                case 2:
                {
                  cout << "Ingresa tu contrasenia" << endl;
                  cin >> password;
                  password = SHA256::cifrar(password);
                  player.setPassword(password);
                  users.modify(player, playerPositionInList);
                }
                break;
                case 3:
                {
                  cout << "Ingresa tu edad" << endl;
                  cin >> age;
                  player.setAge(age);
                  users.modify(player, playerPositionInList);
                }
                break;
                default:
                  cout << "INGRESA UNICAMENTE NUMEROS DE 1 a 3" << endl;
                  break;
                }
              }
              break;
              case 2:
              {
                string resDelete;
                cout << "ESTAS SEGURO QUE DESEAS ELIMINAR TU CUENTA? INGRESA UNICAMENTE LA LETRA (y/n)" << endl;
                cin >> resDelete;
                if (resDelete == "y" || resDelete == "Y")
                {
                  users.remove(playerPositionInList);
                  cout << " DELETING ACCOUNT ... " << endl;
                  cout << " AHORA HAY " << users.count << " USERS EN LA LISTA" << endl;
                  logged = false;
                }
              }
              break;
              case 3:
              {
                queue<Shot> displayTutorialMovements = tutorialMovements;
                Shot shot, boardDimension;
                boardDimension = displayTutorialMovements.dequeue();
                cout << "BIENVENIDO AL TUTORIAL DE BATALLA NAVAL by USAC GAMES" << endl;
                cout << "     TABLERO:" << endl;
                cout << "          ANCHO: " << boardDimension.x << endl;
                cout << "          ALTO:  " << boardDimension.y << endl;
                cout << "     MOVIMIENTOS:" << endl;
                while (displayTutorialMovements.length > 1)
                {
                  shot = displayTutorialMovements.dequeue();
                  cout << "(" << shot.x << "," << shot.y << ") ->";
                }
                shot = displayTutorialMovements.dequeue();
                cout << "(" << shot.x << "," << shot.y << ")" << endl;
              }
              break;
              // AGREGAR ESPACIO PARA COMPRAR ITEM
              case 4:
              {
                cout << " ========================== TIENDA ==========================" << endl;
                cout << " Id    | Nombre                 | Categoria          | Precio" << endl;

                // cout << "HAY " << shop.length << " ITEMS EN LA TIENDA" << endl;
                for (int i = 0; i < shop.length; i++)
                {
                  linkedList<Articulo> actualCategory = shop.get(i);
                  for (int j = 0; j < actualCategory.length; j++)
                  {
                    Articulo item = actualCategory.get(j);
                    cout << item.id << "   | ";
                    cout << item.nombre << "   | ";
                    cout << item.categoria << "   | ";
                    cout << item.precio << endl;
                  }
                  // cout << "HAY " << actualCategory.length << " ITEMS EN LA CATEGORIA" << actualCategory.first->data.categoria << endl;
                }
                cout << "Ingresa el id del artículo a comprar o ingresa (S/s) para salir";
              }
              break;
              case 5:
              {
                Stack<Shot> plays;
                cout << " ============== Realizar Movimientos ============== " << endl;
                cout << " Ingresa las coordenadas del disparo de la siguiente forma X,Y" << endl;
                cout << " Si deseas dejar de ingresar coordenadas escribe una leta (T/t)" << endl;
                bool ingresarCoordenadas = true;
                int earnedTokens = 0;
                while (ingresarCoordenadas)
                {
                  string coordenadas;
                  cin >> coordenadas;
                  if (coordenadas == "T" || coordenadas == "t")
                  {
                    inGameMovements.insertFirst(plays);
                    ingresarCoordenadas = false;
                  }
                  else
                  {
                    earnedTokens++;
                    int coordQty = 0;
                    string coordX, coordY;
                    int delimiterPos = coordenadas.find(",");
                    coordX = coordenadas.substr(0, delimiterPos);
                    coordY = coordenadas.substr(delimiterPos + 1, coordenadas.length());
                    Shot newShot;
                    newShot.setShot(std::stoi(coordX), std::stoi(coordY));
                    plays.push(newShot);
                  }
                }
                cout << "Ingresa el Nombre para guardar los movimientos";
                string name;
                cin >> name;
                inGameMovementsNames.insertFirst(name);
                player.setCoins(player.getCoins() + earnedTokens);
                users.modify(player, playerPositionInList);
              }
              break;
              case 6:
              {
                // UPDATE AL USUARIO EN LA LISTA
                logged = false;
              }
              break;
              default:
                cout << "INGRESA UNICAMENTE LOS NUMEROS DE 1 A 6 " << endl;
                break;
              }
            }
          }
        }
      }
      break;
      case 4:
      {
        string dataUsers, dataTutorial, dataShop, dataMovements, nodes, nodesConnections;
        queue<Shot> auxQueue;
        auxQueue = tutorialMovements;
        dataUsers = "digraph Usuarios{rankdir = LR;node[shape = record, style = filled];";
        dataTutorial = "digraph Tutotial{rankdir = TD;node[shape = record, style = filled];";
        dataShop = "digraph Tienda{rankdir = LR;node[shape = record, style = filled];";
        dataMovements = "digraph Movimientos{rankdir = LR;node[shape = record, style = filled];";
        // CREACION DE INFORMACION DE USUARIOS
        node<User> *actualNode = users.first;
        if (actualNode != NULL)
        {
          do
          {
            User user = actualNode->data;
            nodes += user.getUsername() + "[label= \" Username " + user.getUsername() + "| Contrasenia" + user.getPass() + "| Monedas" + to_string(user.getCoins()) + "\"]\n";
            nodesConnections += user.getUsername() + "->" + actualNode->next->data.getUsername() + ";\n";
            nodesConnections += user.getUsername() + "->" + actualNode->prev->data.getUsername() + ";\n";
            actualNode = actualNode->next;
          } while (actualNode != users.first);
        }
        dataUsers += nodes;
        dataUsers += nodesConnections;
        dataUsers += "}";
        nodes = "";
        nodesConnections = "";
        // CREACION DE INFORMACION DE TUTORIAL
        Shot movement;
        movement = auxQueue.dequeue();
        nodes += "tablero [label= \" INICIO COLA | ANCHO:" + to_string(movement.x) + " ALTO:" + to_string(movement.y) + "\"];\n";
        int cont = 0;

        while (auxQueue.length > 0)
        {
          movement = auxQueue.dequeue();
          nodes += to_string(cont) + "[label= \" X:" + to_string(movement.x) + " Y:" + to_string(movement.y) + " \"];\n";
          if (cont == 0)
          {
            nodesConnections += "tablero->" + to_string(cont) + ";\n";
          }
          else
          {
            nodesConnections += to_string(cont - 1) + "->" + to_string(cont) + ";\n";
          }
          cont++;
        }
        nodes += to_string(cont) + "[label=\" FIN COLA\"];\n";
        nodesConnections += to_string(cont - 1) + "->" + to_string(cont) + ";\n";
        dataTutorial += nodes;
        dataTutorial += nodesConnections;
        dataTutorial += "}";
        nodes = "";
        nodesConnections = "";

        // CREACION DE INFORMACION DE TIENDA
        for (int i = 0; i < shop.length; i++)
        {
          linkedList<Articulo> listaArticulos = shop.get(i);
          nodes += listaArticulos.first->data.categoria + " [label= \" " + listaArticulos.first->data.categoria + " \"];\n";
          if (listaArticulos.length > 0)
          {
            nodesConnections += listaArticulos.first->data.categoria + "->" + listaArticulos.first->data.categoria + to_string(0) + ";\n";
          }
          for (int j = 0; j < listaArticulos.length; j++)
          {
            Articulo currentItem = listaArticulos.get(j);
            nodes += currentItem.categoria + to_string(j) + " [label= \" " + currentItem.nombre + " \"];\n";
            if ((j + 1) < listaArticulos.length)
            {
              nodesConnections += currentItem.categoria + to_string(j) + "->" + listaArticulos.get(j + 1).categoria + to_string(j + 1) + ";\n";
            }
          }
          if ((i + 1) < shop.length)
          {
            nodesConnections += listaArticulos.first->data.categoria + "->" + shop.get(i + 1).first->data.categoria + ";\n";
          }
        }
        dataShop += nodes;
        dataShop += nodesConnections;
        dataShop += "}";
        nodes = "";
        nodesConnections = "";
        // CREACION DE INFORMACION DE MOVIMIENTOS
        // for (int i = 0; i < inGameMovements.length; i++)
        // {
        //   Stack<Shot> stackMovimientos = inGameMovements.get(i);
        //   nodes += inGameMovementsNames.get(i) + " [label= \" " + inGameMovementsNames.get(i) + " \"];\n";
        //   if (stackMovimientos.length > 0)
        //   {
        //     nodesConnections += inGameMovementsNames.get(i) + "->" + inGameMovementsNames.get(i) + to_string(0) + ";\n";
        //   }
        //   int j = 0;
        //   while (stackMovimientos.length > 0)
        //   {
        //     Shot currentMov = stackMovimientos.pop();
        //     nodes += inGameMovementsNames.get(i) + to_string(j) + " [label= \" X: " + to_string(currentMov.x) + " Y: " + to_string(currentMov.y) + " \"];\n";
        //     nodesConnections += inGameMovementsNames.get(i) + to_string(j) + "->" + inGameMovementsNames.get(i) + to_string(j + 1) + ";\n";
        //     j++;
        //   }

        //   if ((i + 1) < inGameMovements.length)
        //   {
        //     nodesConnections += inGameMovementsNames.get(i) + "->" + inGameMovementsNames.get(i + 1) + ";\n";
        //   }
        // }
        cout << "REPORTES " << endl;
        cout << dataUsers << endl;
        cout << "TUTORIAL " << endl;
        cout << dataTutorial << endl;
        cout << "SHOP " << endl;
        cout << dataShop << endl;
        cout << "MOVEMENTS " << endl;
        cout << dataMovements << endl;
        ofstream outfile;
        outfile.open("documents/Usuarios.dot", ios::out | ios::trunc);
        outfile << dataUsers;
        outfile.open("documents/Tutorial.dot", ios::out | ios::trunc);
        outfile << dataTutorial;
        outfile.open("documents/Shop.dot", ios::out | ios::trunc);
        outfile << dataShop;
        outfile.open("documents/MovimientosPartida.dot", ios::out | ios::trunc);
        outfile << dataMovements;
        // system("dot -Tpng documents/Usuarios.dot -o documents/Usuarios.png -Gcharset=latin1");
        // system("PATH=$PATH:<YOUR PATH TO **dot**>;<**dot** and the rest>");
      }
      break;
      case 5:
      {
        playing = false;
      }
      break;
      default:
        cout << "Ingresa unicamente valores de 1 a 5 en numeros \n";
        break;
      }
    }
  }
  system("pause");
  return 0;
}
