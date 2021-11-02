
/**********************************************************************************/
/*****************************INCLUDES*********************************************/
/**********************************************************************************/

#include "socket.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>



/**********************************************************************************/
/*****************************DEFINITIONS******************************************/
/**********************************************************************************/

/*Define the error status*/
#define ERROR_TRUE	(-1)



/**********************************************************************************/
/*****************************TYPEDEFS*********************************************/
/**********************************************************************************/


/*Re definition the of socket address defined in the sytem sockets library*/
typedef struct sockaddr_in socketAddress_s;




/**********************************************************************************/
/*****************************APIS DEFS*********************************************/
/**********************************************************************************/




/*
* Service Name: createSocket
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: None
*
*		In/Out: SocketConfig_s* (Address to the socket configuration structure)
*
*		Out: None
*
* Return: error Return
*				0  : Success
*				-1 : Fail
*
* Description: 	Opens any type of socket
*
*/
errorReturn createSocket(SocketConfig_s* socketConfigInit_s)
{
	/*Declare two address structures (local and remote), remote is only used in case of TCP server*/
	socketAddress_s socketAddr, remoteSocketAddr;
	
	/*Get the lengthes of the two address structures*/
	socklen_t socketAddrLen = sizeof(socketAddr);
	socklen_t remoteSocketAddrLen = sizeof(remoteSocketAddr); 


	/*Set the default protocol to UDP*/
	Protocol_t protocol = IPPROTO_UDP;

	/*Declare an error status*/	
	errorReturn errorStatus;

	/*Check if the Transport protocol TCP, rechange the UDP default to TCP*/
	if(socketConfigInit_s->tpType == TCP)
	{
		protocol = 0;
	}

	/*Create a local socket using:
	*	Domain family
	*	Coonection/Connectionless type
	*	Transport Protocol
	*/
	errorStatus	= socket(socketConfigInit_s->localSocketAddr.domainFamily,
						 socketConfigInit_s->tpType,
						 protocol);

	if(errorStatus == ERROR_TRUE)
	{
		/*Do nothing*/
	}
	else
	{

		/*The error status representes the returned socket descriptor in case of success*/
		socketConfigInit_s->socketId = errorStatus;

		/*Check if the required socket is server*/
		if(socketConfigInit_s->socketType == SERVER)
		{
			/*********SERVER********/
			
			/*Configure the local socket address structure with the provided configs*/
			socketAddr.sin_family = AF_INET;
			socketAddr.sin_addr.s_addr = socketConfigInit_s->localSocketAddr.ipAddr;
			socketAddr.sin_port = htons(socketConfigInit_s->localSocketAddr.portNumber);


			/*Bind the local socket with the local IP and port number*/
			errorStatus = bind(socketConfigInit_s->socketId,(const struct sockaddr*)(&socketAddr),socketAddrLen);


			/*Check if the Server is TCP to configure it as a listening socket*/
			if((socketConfigInit_s->tpType == TCP) && (errorStatus != ERROR_TRUE))
			{
				
				/*Listening server socket*/
				errorStatus = listen(socketConfigInit_s->socketId,socketConfigInit_s->maxNumSoCons);

				/*Check if there is an error*/
				if(errorStatus != ERROR_TRUE)
				{

					/*The listening socket should wait/accept for any remote TCP client socket trying to connect
					* 	Another socket is opened for the connection instead of using the listening socket
					*/
					errorStatus = accept(socketConfigInit_s->socketId
									,(struct sockaddr *)(&remoteSocketAddr),&remoteSocketAddrLen);

					/*Check if there is an error*/
					if(errorStatus != ERROR_TRUE)
					{
						/*Set the new connected socket Id (The configuration pass structure mustn't be constant)*/
						socketConfigInit_s->connectedTcpSocketId = errorStatus;
						/*Set the remote socket IP address, port number and family (connection oriented pipe)*/
						socketConfigInit_s->connectedTcpSocketAddr.ipAddr = remoteSocketAddr.sin_addr.s_addr;
						socketConfigInit_s->connectedTcpSocketAddr.domainFamily = remoteSocketAddr.sin_family;
						socketConfigInit_s->connectedTcpSocketAddr.portNumber = remoteSocketAddr.sin_port;
					}

				}

			}

		}
		else
		{	
			/*******CLIENT******/

			/*Check if the client socket is TCP (in order to perform the connection)*/
			if(socketConfigInit_s->tpType == TCP)
			{	
				/*Set the data of the remote socket to be connected with (connection oriented pipe)*/
				remoteSocketAddr.sin_family = AF_INET;
				remoteSocketAddr.sin_addr.s_addr = socketConfigInit_s->remoteSocketAddr.ipAddr;
				remoteSocketAddr.sin_port = htons(socketConfigInit_s->remoteSocketAddr.portNumber);
			
				/*Connect to the remote server listening socket*/
				errorStatus = connect(socketConfigInit_s->socketId,
									  (const struct sockaddr*)(&remoteSocketAddr),remoteSocketAddrLen);
            }


            /*In case of UDP (No connection or any futher processes)*/

		}

	}

	/*Return the error status of the funciton*/
	return errorStatus;
}




/*
* Service Name: sendData_tcp
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: 
*			SocketDesc_t 			(Socket Id)
*			const char*  			(Data buffer to be sent)
*			SocketBufferlen_t		(Size of data buffer)
*
*		In/Out: None
*
*		Out: None
*
* Return: error Return
*				0  : Success
*				-1 : Fail
*
* Description: 	Sends data using TCP
*
*/
errorReturn sendData_tcp(SocketDesc_t socketDescId, const char* dataBuffer, SocketBufferLen_t dataSize)
{
	/*Declare an error status flag*/
	errorReturn errorStatus;

	/*Send data using tcp*/
	errorStatus = send(socketDescId,(const void *)dataBuffer,(size_t)dataSize,0);

	/*return the error status*/
	return errorStatus;

}





/*
* Service Name: sendData_tcp
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: 
*			SocketDesc_t 			(Socket Id)
*			SocketBufferlen_t		(Size of data buffer)
*
*		In/Out: None
*
*		Out: 
*			const char*  			(Data buffer to be sent)
*
* Return: error Return
*				0  : Success
*				-1 : Fail
*
* Description: 	reads data using TCP
*
*/
errorReturn readData_tcp(SocketDesc_t socketDescId, char* dataBuffer, SocketBufferLen_t dataSize)
{

	/*Declare an error status flag*/
	errorReturn errorStatus;

	/*Send data using tcp*/
	errorStatus = read(socketDescId,(void *)dataBuffer,(size_t)dataSize);

	/*return the error status*/
	return errorStatus;

}



/*
* Service Name: sendData_udp
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: 
*			SocketDesc_t 			(Socket Id)
*			const char*  			(Data buffer to be sent)
*			SocketBufferlen_t		(Size of data buffer)
*			const SocketAddr_s*		(Reference to the remote socket Address (connectionless))
*
*		In/Out: None
*
*		Out: None
*
* Return: error Return
*				0  : Success
*				-1 : Fail
*
* Description: 	Sends data using UDP
*
*/
errorReturn sendData_udp(SocketDesc_t socketDescId, char* dataBuffer, SocketBufferLen_t dataSize, const SocketAddr_s* remoteSocketAddr)
{

	/*Declare an error status flag*/
	errorReturn errorStatus;

	/*Define the socket address pre-defined structure by the original sockets lib*/
	socketAddress_s socketAddr =
	{
		.sin_family = remoteSocketAddr->domainFamily,
		.sin_port = htons(remoteSocketAddr-> portNumber),
		.sin_addr.s_addr = remoteSocketAddr-> ipAddr
	};


	/*Send data using udp*/
	errorStatus = sendto(socketDescId,(const void *)dataBuffer,(size_t)dataSize,MSG_WAITALL,(const struct sockaddr*)(&socketAddr),(socklen_t)(sizeof(struct sockaddr_in)));

	/*return the error status*/
	return errorStatus;


}



/*
* Service Name: readData_udp
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: 
*			SocketDesc_t 			(Socket Id)
*			SocketBufferlen_t		(Size of data buffer)
*			const SocketAddr_s*		(Reference to the remote socket Address (connectionless))
*
*		In/Out: None
*
*		Out: 
*			const char*  			(Data buffer to receive data into)
*
* Return: error Return
*				0  : Success
*				-1 : Fail
*
* Description: 	Receives data using UDP
*
*/
errorReturn readData_udp(SocketDesc_t socketDescId, char* dataBuffer, SocketBufferLen_t dataSize, SocketAddr_s* remoteSocketAddr)
{

	/*Declare an error status flag*/
	errorReturn errorStatus;

	/*Define the socket address pre-defined structure by the original sockets lib*/
	socketAddress_s socketAddr;

	/*Get the size/length of the address structure*/
	socklen_t socketAddrLen = sizeof(socketAddress_s);

	/*Read data using udp*/
	errorStatus = recvfrom(socketDescId,(void *)dataBuffer,(size_t)dataSize,MSG_WAITALL,(struct sockaddr*)(&socketAddr),(&socketAddrLen));

	/*Get the remoteSocketAddr elements*/
	remoteSocketAddr->domainFamily =socketAddr.sin_family ;
	remoteSocketAddr->portNumber = ntohs(socketAddr.sin_port);
	remoteSocketAddr->ipAddr= ntohl(socketAddr.sin_addr.s_addr);

	/*return the error status*/
	return errorStatus;

}




/*
* Service Name: closeSocket
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: SocketDec_t (Socket Id to be closed)
*
*		In/Out: None
*
*		Out: None
*
* Return: error Return
*				0  : Success
*				-1 : Fail
*
* Description: 	Close the pre opened socket using the socket id
*
*/
errorReturn closeSocket(SocketDesc_t socketDescId)
{
	
	/*Declare an error status flag*/
	errorReturn errorStatus;

	/*Close socket*/
	errorStatus = close(socketDescId);

	/*return the error status*/
	return errorStatus;

}



/*
* Service Name: ipV4Str
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: const Char* (constant string address)
*
*		In/Out: None
*
*		Out: None
*
* Return: IpAddr_t
*
* Description: 	Convert the ip dotted string format into the network integer format
*
*/
IpAddr_t ipV4Str(const char* ipString)
{
	/*Convert the ip dotted string format into the network integer format*/
	return inet_addr(ipString);
}



/*
* Service Name: ipV4Int
*
* Synchronous/Asynchronous: Syn
* 
* Re-entrant/Non Re-entrant: Rentrant
*
* Parameters:
*		In: uint32_t (integer Ip)
*
*		In/Out: None
*
*		Out: None
*
* Return: IpAddr_t
*
* Description: Convert the host integer ip format into the network integer format
*
*/
IpAddr_t ipV4Int(uint32_t ipInt)
{
	/*Convert the host integer ip format into the network integer format*/
	return htonl(ipInt);
}
