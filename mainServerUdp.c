

/**********************************************************************************/
/*****************************Functions' Prototypes********************************/
/**********************************************************************************/
#include "socket.h"
#include "stdio.h"



/**********************************************************************************/
/*****************************Defines**********************************************/
/**********************************************************************************/

#define TRUE 	(1U)
#define FALSE 	(0U)


/**********************************************************************************/
/*****************************Functions' Prototypes********************************/
/**********************************************************************************/

void input(void);
void clearDataBuffer(char* dataBuffer);
bool checkIfExit(char* dataBuffer);




/**********************************************************************************/
/*****************************Global Data Buffers**********************************/
/**********************************************************************************/

/*Chatting data send/receive buffer*/
char dataBuffer[500];




/**********************************************************************************/
/*****************************Main Function****************************************/
/**********************************************************************************/
int main(void)
{

	SocketConfig_s socketConfigInitStruct =
	{
		.localSocketAddr=
		{
			.ipAddr = ipV4Int(INADDR_ANY),				/*Receive from any IP address*/
			.domainFamily = IP_V4,						/*IP version 4 internet protocols family*/
			.portNumber = (8080U)						/*Set the port number to any chosen value*/
		},
		.tpType = UDP,									/*UDP socket*/
		.socketType = SERVER 							/*Server socket*/

	};


	/*Declare an error status*/	
	errorReturn errorStatus;

	/*Create a new server local socket*/	
	errorStatus = createSocket(&socketConfigInitStruct);

	while(1)
	{
		
		/*Receive data from client to server*/
		errorStatus = readData_udp(socketConfigInitStruct.socketId,dataBuffer,(SocketBufferLen_t)(sizeof(dataBuffer)),&socketConfigInitStruct.remoteSocketAddr);

		/*Print the received data*/	
		printf("\nFrom Client: %s\n",dataBuffer);

		/*Check if there is an "exit" input string*/
		if( (checkIfExit(dataBuffer)) )
		{	
			/*Exit*/
			break;
		}

		/*Clear the data recv/send buffer*/	
		clearDataBuffer(dataBuffer);

		input();

		/*Adjust the returned remote ip address from the readData_udp from host to network form*/
		socketConfigInitStruct.remoteSocketAddr.ipAddr = htonl(socketConfigInitStruct.remoteSocketAddr.ipAddr);		
		
		/*Send the input data from server to the client*/
		errorStatus = sendData_udp(socketConfigInitStruct.socketId,dataBuffer,(SocketBufferLen_t)(sizeof(dataBuffer)),&socketConfigInitStruct.remoteSocketAddr);


	}

	/*Close the pre-opened server socket*/
	errorStatus = closeSocket(socketConfigInitStruct.socketId);
	

	return 0;
}





/**********************************************************************************/
/*****************************Functions' Definitions*******************************/
/**********************************************************************************/


/*Function used to get the input data string from the user CLI and save it into the global data buffer*/
void input(void)
{
	printf("\nTo Client:");
	int counterIndex = 0;
	char character;

	do
	{
	  character = getchar();
	  dataBuffer[counterIndex] = character;
	  counterIndex++;

	}while(character != '\n');
	--counterIndex;
	dataBuffer[counterIndex] ='\0';
	counterIndex = 0;

}




/*Function used to clear the global data recv/send buffer*/
void clearDataBuffer(char* dataBuffer)
{
	while(*dataBuffer != '\0')
	{
		dataBuffer++; 
	}
	*dataBuffer = 'x';

}


/*Function used to check if there any "exit" sequence in the input data string to disconnect*/
bool checkIfExit(char* dataBuffer)
{

        char exit[] = "exit";
        int counterIndex = 0;

        while(dataBuffer[counterIndex] != '\0')
        {
                if ( !(exit[counterIndex] == dataBuffer[counterIndex]) )
                {
                        return FALSE;
                }
                counterIndex++;

        }

        return TRUE;
}

