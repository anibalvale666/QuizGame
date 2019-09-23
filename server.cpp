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

vector<vector<int> > manage_users;
vector<pair<int, string> > list_users;
vector<pair<int, int> > initial_positions;

void fill_initial_positions()
{
  initial_positions.push_back(make_pair(10,10));
  initial_positions.push_back(make_pair(10,15));
  initial_positions.push_back(make_pair(10,20));
  initial_positions.push_back(make_pair(10,25));
  initial_positions.push_back(make_pair(10,30));
}

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

  if(::bind(SocketFD1,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
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
}
  
void reading(int ConnectFD, char buffer[])
{
  string received_message;
  do
  {
    bzero(buffer,TAM_MSG);
    n = read(ConnectFD, buffer, 3);
    received_message = buffer;

    cout<<"Received: "<<received_message<<endl;

  } while(int(received_message.find(cierre)) < 0);

}

void print_manage_users()
{
  cout<<"Manage Users"<<endl;
  for (int i=0; i<manage_users.size(); i++)
  {
    for (int j=0; j<manage_users[i].size(); j++)
    {
      cout<<manage_users[i][j]<<"\t";
    }
    cout<<endl;
  }
}

int main()
{
  int socketFD1;
  int ConnectFD;
  int _socket;

  cli(ConnectFD,socketFD1,_socket);

  char buffer[TAM_MSG];

  int id=1;

  int count = 0;

  fill_initial_positions();

  for(;;)
  {
    int ConnectClient = accept(socketFD1, NULL, NULL);
    bzero(buffer,TAM_MSG);
    
    //Adding new player in server.
    n = read(ConnectClient,buffer,1); 

    if ( buffer[0] == '0' )
    {
      n = read(ConnectClient,buffer,2);
      buffer[n] = '\0';

      int size_nickname = atoi(buffer);

      n = read(ConnectClient, buffer, size_nickname);
      buffer[n] = '\0';

      string nickname_rcv(buffer);

      cout<<"Nickname: "<<nickname_rcv<<endl;

      list_users.push_back(make_pair(id, nickname_rcv));

      vector<int> new_user;
      new_user.push_back(id);                           //ID
      new_user.push_back(ConnectClient);                //SocketID
      new_user.push_back(initial_positions[count % initial_positions.size()].first);             //Start position X
      new_user.push_back(initial_positions[count % initial_positions.size()].second);            //Start position Y
      new_user.push_back(0);                            //Initial Score
      new_user.push_back(1);                            //Bool: 1 (Alive) 0 (Dead)

      manage_users.push_back(new_user);

      print_manage_users();

      //Answer from server to new player added.
      string answer = "";

      answer += "0";
      answer += to_string(id);
      answer += int_to_char_spaces(manage_users[count][2], 2);
      answer += int_to_char_spaces(manage_users[count][3], 2);
      answer += to_string(count);

      for (int i=0; i<count; i++)
      {
        answer += int_to_char_spaces(manage_users[i][2], 2);
        answer += int_to_char_spaces(manage_users[i][3], 2);
      }

      id += 1;
      count += 1;

      cout<<"Answer: "<<answer<<endl;

      n = write(ConnectClient, answer.c_str(), answer.size());

      thread(reading, ConnectClient, buffer).detach();
    }
    
    else 
    {
      string error = "Escriba su nickname para entrar en el juego.";
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
