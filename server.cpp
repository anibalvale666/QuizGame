#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <utility>
#include <string.h>
#include <vector>
#include <sstream>
#include "funciones.h"

#define TAM_MSG 1000
using namespace std;
string cierre = "adios";
string userID;
vector<int> active_users;
vector<pair<int, int> > pos_users;



int crearSocket(int &SocketFD1)
{
    SocketFD1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int SocketFD2 = SocketFD1;
   struct sockaddr_in stSockAddr;
   if(-1 == SocketFD2)
   {
     perror("can not create socket");
     exit(EXIT_FAILURE);
   }

   memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

   stSockAddr.sin_family = AF_INET;
   stSockAddr.sin_port = htons(45550);
   stSockAddr.sin_addr.s_addr = INADDR_ANY;

   if(bind(SocketFD1,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
   {
     perror("error bind failed");
     close(SocketFD1);
     exit(EXIT_FAILURE);
   }

   if(-1 == listen(SocketFD1, 10))
   {
     perror("error listen failed");
     close(SocketFD1);
     exit(EXIT_FAILURE);
   }
   return SocketFD2;
 }


void cli(int &ConnectFD,int &SocketFD1,int &_socket)
{
_socket = crearSocket(SocketFD1);

}


int n;
void writing(int ConnectFD, char buffer[])
{

  string mssg = "";
  do
  {
    bzero(buffer,TAM_MSG);
    getline(cin,mssg);
    if(mssg =="exit")
      break;
    mssg = "[" + userID + "] " + mssg;
    int aux = mssg.size();
    strcpy(buffer,mssg.c_str());
    n = write(ConnectFD,buffer,aux);

 }
 while(int(mssg.find(cierre)) < 0);
   /* perform read write operations ... */
}
  vector<pair<string,int> > list_users;


void reading(int ConnectFD, char buffer[])
{
  cout<<"gg"<<endl;
  string mssg;
  do
  {
    bzero(buffer,TAM_MSG);
    n=read(ConnectFD, buffer, 3);
    mssg = buffer;

    cout<<"r "<<mssg<<endl;

    if (mssg[0] == '1')
    {
      if (mssg[1] == '1')
      {
        if (mssg[2] == '1')
        {
          pos_users[0].second = pos_users[0].second - 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];
          cout<<"e "<<enviar<<endl;
          n=write(ConnectFD, enviar, 9);
        }
        else if (mssg[2] == '2')
        {
          pos_users[0].second = pos_users[0].second + 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];

          n=write(ConnectFD, enviar, 9);
        }

        else if (mssg[2] == '3')
        {
          pos_users[0].first = pos_users[0].first - 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];

          n=write(ConnectFD, enviar, 9);
        }

        else if (mssg[2] == '4')
        {
          pos_users[0].first = pos_users[0].first + 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];

          n=write(ConnectFD, enviar, 9);
        }

      }

      if (mssg[1] == '2')
      {
        if (mssg[2] == '1')
        {
          pos_users[0].second = pos_users[0].second - 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];

          cout<<"gg "<<enviar<<endl;

          n=write(ConnectFD, enviar, 9);
        }
        else if (mssg[2] == '2')
        {
          pos_users[0].second = pos_users[0].second + 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];

          n=write(ConnectFD, enviar, 9);
        }

        else if (mssg[2] == '3')
        {
          pos_users[0].first = pos_users[0].first - 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];

          n=write(ConnectFD, enviar, 9);
        }

        else if (mssg[2] == '4')
        {
          pos_users[0].first = pos_users[0].first + 1;
          char enviar[9];
          enviar[0] = '2';

          string t = to_string(pos_users[0].first);

          enviar[1] = t[0];
          enviar[2] = t[1];

          t = to_string(pos_users[0].second);
          enviar[3] = t[0];
          enviar[4] = t[1];

          t = to_string(pos_users[1].first);
          enviar[5] = t[0];
          enviar[6] = t[1];

          t = to_string(pos_users[1].second);
          enviar[7] = t[0];
          enviar[8] = t[1];

          n=write(ConnectFD, enviar, 9);
        }

      }

    }
  }
  while(int(mssg.find(cierre)) < 0);

}


int main()
{
  userID = "server";

  int socketFD1;
  int ConnectFD;
  int _socket;


  cli(ConnectFD,socketFD1,_socket);


  char buffer[TAM_MSG];


  int i=1;


  for(;;){
    int ConnectClient = accept(socketFD1, NULL, NULL);
    bzero(buffer,TAM_MSG);
    //inicializando comando NICK
    read(ConnectClient,buffer,1); // read command


    if ( buffer[0] == '1' )
    {
      active_users.push_back(i);
      i+=1;

      pos_users.push_back(make_pair(10, 10));
      pos_users.push_back(make_pair(10, 20));

      char pos[9];
      pos[0] = '2';
      pos[1] = '1';
      pos[2] = '0';
      pos[3] = '1';
      pos[4] = '0';
      pos[5] = '1';
      pos[6] = '0';
      pos[7] = '2';
      pos[8] = '0';
      cout<<"anadido"<<endl;
      n = write(ConnectClient,buffer, 9);
      std::thread (reading,ConnectClient,buffer).detach();
    }
    //  ------------------------------------------------------
    // comando list-------------------------------------------
    else {
      string error = "ingrese primero comando: 'nickname'";
      string final = "4035" + error;
      strcpy(buffer,final.c_str());
      buffer[final.size()] = '\0';
      n = write(ConnectClient,buffer,final.size());
    }


  }
  shutdown(ConnectFD, SHUT_RDWR);

  close(ConnectFD);


  close(_socket);
  return 0;
}
