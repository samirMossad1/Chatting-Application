/**********************************************************************************/
/*****************************INCLUDES*********************************************/
/**********************************************************************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>



/**********************************************************************************/
/*****************************TYPEDEFS*********************************************/
/**********************************************************************************/


typedef unsigned int 	uint32_t;
typedef unsigned int 	SocketBufferLen_t;
typedef unsigned short 	uint16_t;
typedef signed char 	errorReturn;
typedef unsigned char 	bool;

typedef int 	 IpAddr_t;
typedef uint32_t SocketDesc_t;
typedef uint32_t Protocol_t;
typedef uint32_t Backlog_t;
typedef uint16_t PortNumbet_t;


/**********************************************************************************/
/*****************************ENUMS************************************************/
/**********************************************************************************/

/*Enum to configure the type of the socket (Server,Client)*/
typedef enum 
{
	SERVER, /*0*/
	CLIENT	/*1*/
	
}SocketType_e;

/*Enum to configure the type of the socket (connection oriented / connectionless)*/
typedef enum
{
	TCP=SOCK_STREAM,	/*Piped socket (TCP is used)*/
	UDP=SOCK_DGRAM		/*Connectionless socket (UDP is used)*/

}TranportProtocol_e;

/*Enum to decide the domain family of the internet protocols (more families can be added)*/
typedef enum 
{	
	IP_V4=AF_INET	/*The IP version 4 network libraries*/

}DomainFamily_e;



/**********************************************************************************/
/*****************************STRUCTURES*******************************************/
/**********************************************************************************/


/*Structure to configue the address of the socket*/
typedef struct
{

	IpAddr_t	   ipAddr;			/*The Ip Addr (ipV4Str and ipV4Int are used)*/
	DomainFamily_e domainFamily;	/*The domain family*/
	PortNumbet_t   portNumber;		/*The port number*/

}SocketAddr_s;


/*Main configuration structure*/
typedef struct 
{

	SocketAddr_s 		localSocketAddr;			/*The local socket address*/
	SocketAddr_s 		remoteSocketAddr;			/*The remote socket address*/
	SocketAddr_s        connectedTcpSocketAddr;		/*The connected socket address (used in case of TCP server) - handles only 1 connection*/
	SocketDesc_t 		socketId;					/*The local socket identifier*/
	SocketDesc_t		connectedTcpSocketId;		/*The connected socket identifier (used in case of TCP server only)*/
	Backlog_t			maxNumSoCons;				/*The max number of connection a TCP listening server socket can handle (1 connection only is supported)*/
	TranportProtocol_e  tpType;						/*The transport protocol type (TCP/UDP)*/
	SocketType_e		socketType;					/*The socket type (Server/Client)*/
	
}SocketConfig_s;

