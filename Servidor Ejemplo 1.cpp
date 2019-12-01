#include <iostream>
#include <winsock2.h>

using namespace std;

class Server{
public:
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    char buffer[1024];
    Server()
    {
        WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);

        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(5555);

        bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        listen(server, 0);

        cout << "Escuchando para conexiones entrantes." << endl;
        int clientAddrSize = sizeof(clientAddr);
        if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Cliente conectado!" << endl;
        }
    }

    string Recibir()
    {
      recv(client, buffer, sizeof(buffer), 0);
      cout << "El cliente dice: " << buffer << endl;
      string buf=buffer;
      memset(buffer, 0, sizeof(buffer));
      return buf;
    }
    void Enviar(char mensaje)
    {
        this->buffer[0]=mensaje;
        send(client, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        cout << "Mensaje enviado!" << endl;
    }
    void CerrarSocket()
    {
        closesocket(client);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }
};

class Matrix{
public:
    char matriz[9]={'1','2','3','4','5','6','7','8','9'};
    Matrix()
    {
    }
    void Mostrar()
    {
        cout<<endl<<endl;
        int contador=0;
        for (int i = 0; i<9 ; i++)
        {
            if(contador==3)
            {
                cout<<endl<<endl<<endl;
                cout<<"\t\t"<<matriz[i]<<"  ";
                contador=1;
            }
            else
            {
                cout<<"\t\t"<<matriz[i]<<"  ";
                contador++;
            }
        }
        cout<<endl<<endl<<endl;
    }
    void Agregar(char elemento,int pos)
    {
        this->matriz[pos-1]=elemento;
        system("cls");
        Mostrar();
    }
    int cast(char pos)
    {
        int num;
        return num=(int)pos-48;
    }

};

int main()
{
  Server *Servidor = new Server();
  Matrix *matrix = new Matrix();
  matrix->Mostrar();
  int pos;
  char charpos;
  while (true){
    cout<<"Turno del jugador Cliente X."<<endl;
    charpos=Servidor->Recibir()[0];
    pos=matrix->cast(charpos);
    matrix->Agregar('X',pos);

    cout<<"\tEs tu turno jugador O."<<endl<<endl;
    cout<<"Inserta la posicion: ";
    cin>>charpos;
    pos=matrix->cast(charpos);
    matrix->Agregar('O',pos);
    Servidor->Enviar(charpos);
  }
}
