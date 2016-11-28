/**
    C++ client example using sockets
*/
#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include<time.h> //clock-wait
#include <unistd.h> //close socket
 
using namespace std;

void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

/**
    TCP Client class
*/
class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;
     
public:
    tcp_client();
    ~tcp_client() { closeSock(); }
    bool conn(string, int);
    bool send_data(string data);
    string receive(int);
    int getSock() {return sock;}
    int closeSock();
};
 
tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}
 
/**
    Connect to a host on a certain port number
*/
bool tcp_client::conn(string address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }
         
        cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }
     
    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
         
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            cout<<"Failed to resolve hostname\n";
             
            return false;
        }
         
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;
 
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
             
            cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;
             
            break;
        }
    }
     
    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
     
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
     
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return false;
    }
     
    cout<<"Connected\n";
    return true;
}

int tcp_client::closeSock()
{
  if(sock != -1)
    close(sock);
  return 0;    
}

/**
    Send data to the connected host
*/
bool tcp_client::send_data(string data)
{
    //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    cout<<"Data send\n";
     
    return true;
}
 
/**
    Receive data from the connected host
*/
string tcp_client::receive(int maxsize=512)
{
    char buffer[maxsize];
    string reply;
     
    //Receive a reply from the server
    int len = recv(sock , buffer , sizeof(buffer) , 0);
    if(len < 0)
    {
        puts("recv failed");
    }
     
    buffer[len]='\0'; 
    reply = buffer;
    return reply;
}
 
int main(int argc , char *argv[])
{
    string host;
    long int iter = 0;
    string query = "UNH+1+DENBUQ:05:1:1A+510UH3UMNN DCD++KE58F22A+++DCR QTY+TO:5:SEC UNT+4+1'";
     
    host = "localhost";
    
    for(int i=0 ; i < 5 ; i++)
    {
        tcp_client c;
        iter++;
        
        //connect to host
        cout<<"\n-->>>>---------BEG------Loop[" << iter << "]-----------\n";
        cout << "Connecting to "<< host << "[" << currentDateTime() << "]\n";
        if(c.conn(host , 8080) == false) 
	{
	  cout << "Connect failed\n";
	  return 1;
	}
        //send some data
        //c.send_data("GET / HTTP/1.1\r\n\r\n"); if http header required
        cout << "Sending [" << query << "]\n";
        if(c.send_data(query) == false)
	{
	  cout << "Failed sending data\n";
	  return 1;
	}
         
        //receive and echo reply
        cout<< "Receiving from POD server [" << c.receive(1024) << "]\n";
        cout << "Closing connection\n";
        c.closeSock();
        
        //cout << "Waiting 1000 msec " << "[" << currentDateTime() << "]\n";
        wait(1);
        cout << "[" << currentDateTime() << "]\n";
        cout<<"--<<<<------END--------------------\n\n";
    }
    
    //done with success
    return 0;
}
