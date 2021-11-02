
/**********************************************************************************/
/*****************************INCLUDES*********************************************/
/**********************************************************************************/


/*Include all the needed types*/
#include "socket_types.h"



/**********************************************************************************/
/*****************************APIs' Prototypes*************************************/
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
errorReturn createSocket(SocketConfig_s* socketConfigInit_s);






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
errorReturn sendData_tcp(SocketDesc_t socketDescId, const char* dataBuffer, SocketBufferLen_t dataSize);



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
*			const char*  			(Data buffer to receive into)
*
* Return: error Return
*				0  : Success
*				-1 : Fail
*
* Description: 	Receives data using TCP
*
*/
errorReturn readData_tcp(SocketDesc_t socketDescId, char* dataBuffer, SocketBufferLen_t dataSize);





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
errorReturn sendData_udp(SocketDesc_t socketDescId, char* dataBuffer, SocketBufferLen_t dataSize, const SocketAddr_s* remoteSocketAddr);



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
errorReturn readData_udp(SocketDesc_t socketDescId, char* dataBuffer, SocketBufferLen_t dataSize, SocketAddr_s* remoteSocketAddr);





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
errorReturn closeSocket(SocketDesc_t socketDescId);



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
IpAddr_t ipV4Str(const char* ipString);




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
IpAddr_t ipV4Int(uint32_t ipInt);




