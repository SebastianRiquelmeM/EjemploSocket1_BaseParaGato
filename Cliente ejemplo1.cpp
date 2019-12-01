#include <iostream>
#include <winsock2.h>

using namespace std;

class Client{
public:
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    char buffer[1024];
    Client()
    {
        WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);

        addr.sin_addr.s_addr = inet_addr("192.168.1.82");
        addr.sin_family=AF_INET;
        addr.sin_port = htons(5555);

        connect(server, (SOCKADDR *)&addr, sizeof(addr));
        cout << "Connected to server!" << endl;
    }
    void Enviar(char mensaje)
    {
        this->buffer[0]=mensaje;
        send(server, buffer, sizeof(buffer), 0);
        cout << "Mensaje enviado!" << endl;
        memset(buffer, 0, sizeof(buffer));
    }
    string Recibir()
    {
        recv(server, buffer, sizeof(buffer), 0);
        cout << "El Servidor dice: " << buffer << endl;
        string buf=buffer;
        memset(buffer, 0, sizeof(buffer));
        return buf;
    }
    void Cerrar()
    {
        closesocket(server);
        WSACleanup();
        cout << "Socket cerrado." << endl << endl;
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
  Client *Cliente = new Client();
  Matrix *matrix = new Matrix();
  matrix->Mostrar();
  int pos;
  char charpos;
  while (true){
    cout<<"\tEs tu turno."<<endl<<endl;
    cout<<"Inserta la posicion: ";
    cin>>charpos;
    pos=matrix->cast(charpos);
    matrix->Agregar('X',pos);
    Cliente->Enviar(charpos);

    cout<<"Turno del jugador Servidor."<<endl;
    charpos=Cliente->Recibir()[0];
    pos=matrix->cast(charpos);
    matrix->Agregar('O',pos);
  }
}
