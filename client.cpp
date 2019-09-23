 #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <iostream>
  #include <thread>
  #include <string.h>
#include "funciones.h"
#include <termios.h>

#define TAM_MSG 1000

using namespace std;
int SocketFD = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
int Res;
string cierre = "adios";
string userID;
int id;
char  p[100][100];
int c,f,x=0;
int posx=0,posy=0,posx2=0,posy2=0;
int posx_p=0,posy_p=0;
char pasado;

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(1);
}


int crearSocket()
{
  struct sockaddr_in stSockAddr;

  if (-1 == SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(45550);
    Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);

    if (0 > Res)
    {
      perror("error: first parameter is not a valid address family");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    else if (0 == Res)
    {
      perror("char string (second parameter does not contain valid ipaddress");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }


  return SocketFD;
}

int _socket = crearSocket();
int n;

char buffer[TAM_MSG];
bool termino = true;


void writing()
{
  string mssg;
  do
  {
    bzero(buffer,TAM_MSG);
    mssg ="";
    //getline(cin,mssg);
    char c;
    //mssg = "[" + userID + "] " + mssg;
    //int aux = mssg.size();
    //strcpy(buffer,mssg.c_str());
    //buffer[mssg.size()] = '\0';
    //n = write(SocketFD,buffer,aux);
    c = getch();

    if(c == 'w')
    {
      string final = "1";
      final += id;
      final += "1";
      strcpy(buffer,final.c_str());
      buffer[final.size()] = '\0';
      n = write(SocketFD,buffer,final.size());
      //cout<<"ggg "<<final<<endl;
    }
    if(c == 's')
    {
      string final = "1";
      final += id;
      final += "2";
      strcpy(buffer,final.c_str());
      buffer[final.size()] = '\0';
      n = write(SocketFD,buffer,final.size());
    }
    if(c == 'a')
    {
      string final = "1";
      final += id;
      final += "3";
      strcpy(buffer,final.c_str());
      buffer[final.size()] = '\0';
      n = write(SocketFD,buffer,final.size());
    }
    if(c == 'd')
    {
      string final = "1";
      final += id;
      final += "4";
      strcpy(buffer,final.c_str());
      buffer[final.size()] = '\0';
      n = write(SocketFD,buffer,final.size());
    }

    else if(mssg == "exit")
    {
      buffer[0] = '8';
      buffer[1] = '\0';
      n = write(SocketFD,buffer,1);
      termino=false;
    }



  } while(termino/*int(mssg.find(cierre)) < 0*/);

}

void reading()
{
  string mssg;

  do
  {
    bzero(buffer,TAM_MSG);
    n = read(SocketFD,buffer,1);
    //cout << buffer << endl;
    mssg = buffer;
    if(buffer[0] == '0')
    {
      n = read(SocketFD,buffer,1);
      buffer[n] = '\0';
      id = atoi(buffer);

      n = read(SocketFD,buffer,2);
      buffer[n] = '\0';
      posx = atoi(buffer);

      n = read(SocketFD,buffer,2);
      buffer[n] = '\0';
      posy = atoi(buffer);

      int cant;
      n = read(SocketFD,buffer,1);
      buffer[n] = '\0';
      cant = atoi(buffer);

      /*for(int i=0;i< cant;i++)
      players*/
    }
    if(buffer[0] == '2')
    {

      n= read(SocketFD,buffer,8); // read size
      //cout<<"r "<<buffer<<endl;
      char ja[2];

      ja[0] = buffer[0];
      ja[1] = buffer[1];
      posx = atoi(ja);
      ja[0] = buffer[2];
      ja[1] = buffer[3];
      posy = atoi(ja);
      ja[0] = buffer[4];
      ja[1] = buffer[5];
      posx2 = atoi(ja);
      ja[0] = buffer[6];
      ja[1] = buffer[7];
      posy2 = atoi(ja);
    }
    else if(buffer[0] == '5') //el server envia OK
    {
      cout << "OK" << endl;
    }
//----------------------------

//-----------------------------


  } while(termino);
}


int main()
{
  //-----------------nickname ----------------------------------------------------//
  string nickname;
  cout << "Nickname: ";
  cin >> nickname;

  string final = "0";
  final += int_to_char_spaces(nickname.size(),2);
  final += nickname;
  strcpy(buffer,final.c_str());
  buffer[final.size()] = '\0';
  n = write(SocketFD,buffer,final.size());
  //-----------------nickname ----------------------------------------------------//

  write(SocketFD,"1",1);
  strcpy(p[x++],"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
  strcpy(p[x++],"||||||||||||||||||||||||||||||||  |||||||||        |||||||||");
  strcpy(p[x++],"|||||| ||||||||||||||||||||||||    ||||||||        |||||||||");
  strcpy(p[x++],"|||||   ||||||||||||||||||||||      ||||||||        ||||||||");
  strcpy(p[x++],"||||     ||||||||||||||| ||||        |||||||||       ||  | |");
  strcpy(p[x++]," ||      ||||||||| ||||   |||         |||||||            |  ");
  strcpy(p[x++]," |        ||||||    ||    |||         ||||||                ");
  strcpy(p[x++],"          |||||            |          ||||||                ");
  strcpy(p[x++],"           |||                         ||||                 ");
  strcpy(p[x++],"           ||                          ||||                 ");
  strcpy(p[x++],"                                        ||                  ");
  strcpy(p[x++],"                                        ||                  ");
  strcpy(p[x++],"                                                            ");
  strcpy(p[x++],"                                --                          ");
  strcpy(p[x++],"      |                        |##|                    |    ");
  strcpy(p[x++],"     |#|                      |####|            |      |    ");
  strcpy(p[x++],"    |###|               |    |######|          |#|____|#|   ");
  strcpy(p[x++],"   |####|         |    |#|   |#######|       |###########|  ");
  strcpy(p[x++],"  |######|      |##|  |##|   |########|      |############| ");
  strcpy(p[x++],"|########|     |####-|####| |########|      |##############|");
  strcpy(p[x++],"##########|   |###########||###########|    |###############");
  strcpy(p[x++],"##########|  |#########################|    |###############");
  strcpy(p[x++],"###########-|###########################|  |################");
  strcpy(p[x++],"########################################|  |################");


    std::thread hilo1(writing);
    std::thread hilo2(reading);


        do
        {
          for(f=0;f<=24;f++)
          {
           p[f][60]=p[f][0];
          }
          for(f=0;f<=24;f++)
          {
              for(c=0;c<=60;c++)
              {

                if(p[f][c+1] != 'O')
                 p[f][c]=p[f][c+1];

              }
          }
          p[posy][posx] = 'O';
          for(f=0;f<=24;f++){
             printf("%s\n",p[f]);
          }
          
          usleep(500000);
        
        }while(1);

    hilo1.join();
    hilo2.join();





    shutdown(SocketFD, SHUT_RDWR);

    close(_socket);

	return 0;
}
