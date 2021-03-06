#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char** argv)
{
	int server_socket;
	int portno;
	
	int choice;
	
	int i;
	
	int *X;
	int n;
	float r;
	float average;
	int max_and_min[2];
	float *prod;
	
	struct sockaddr_in serv_addr;
	
	struct hostent *server;
	
	char buffer[256];
	
	portno=atoi(argv[2]);
	
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	
	server=gethostbyname(argv[1]);
	
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port=htons(portno);
	
	connect(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	
	printf("--------------------------------------------------------------------\n");
	
	int flag=1;

	do
	{
		printf("==========================\n");
		printf("=====Dummy Operations=====\n");
		printf("==========================\n");
		printf("1. average of X[]      			  \n");
		printf("2. max & min of X[]                          \n");
		printf("3. r*X[]                                               \n");
		printf("4. Exit                                                  \n");
		printf("==========================\n");
		printf("Choice: ");
		scanf("%d", &choice);
		printf("==========================\n");
		
		send(server_socket,&choice,sizeof(int),0);

		if(choice==1)
		{	
				////////////////////////////////////////////////////////
				//sending the number of elements (n)...
				////////////////////////////////////////////////////////
				printf("Number of elements: ");
				scanf("%d", &n);
				
				send(server_socket, &n, sizeof(int), 0);
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
			
			
				////////////////////////////////////////////////////////
				//initializing and sending the array...
				////////////////////////////////////////////////////////
				X=(int *)malloc(n*sizeof(int));
			
				for(i=0;i<n;i++)
				{
					printf("X[%d] = ", i);
					scanf("%d", &X[i]);
				}
				
				send(server_socket,X,n*sizeof(int),0);
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
		
				////////////////////////////////////////////////////////
				//receiving average...
				////////////////////////////////////////////////////////
				recv(server_socket,&average,sizeof(float),0);
				
				printf("******************************\n");	
				printf("Average: %.2f \n", average);
				printf("******************************\n");	
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
		}
		else if(choice==2)
		{
				////////////////////////////////////////////////////////
				//sending the number of elements (n)...
				////////////////////////////////////////////////////////
				printf("Number of elements: ");
				scanf("%d", &n);
				
				send(server_socket, &n, sizeof(int), 0);
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
			
			
				////////////////////////////////////////////////////////
				//initializing and sending the array...
				////////////////////////////////////////////////////////
				X=(int *)malloc(n*sizeof(int));
			
				for(i=0;i<n;i++)
				{
					printf("X[%d] = ", i);
					scanf("%d", &X[i]);
				}
				
				send(server_socket,X,n*sizeof(int),0);
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////

				////////////////////////////////////////////////////////
				//receiving max and min elements...
				////////////////////////////////////////////////////////
				recv(server_socket,max_and_min,2*sizeof(int),0);
				
				printf("******************************\n");	
				printf("Max element: %d \n", max_and_min[0]);
				printf("Min element: %d \n", max_and_min[1]);
				printf("******************************\n");	
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
		
		}
		else if(choice==3)
		{
				////////////////////////////////////////////////////////
				//sending the number of elements (n)...
				////////////////////////////////////////////////////////
				printf("Number of elements: ");
				scanf("%d", &n);
				
				send(server_socket, &n, sizeof(int), 0);
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
			
			
				////////////////////////////////////////////////////////
				//sending the number r...
				////////////////////////////////////////////////////////
				printf("Real number r: ");
				scanf("%f", &r);

				send(server_socket, &r, sizeof(float), 0);
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
			
			
				////////////////////////////////////////////////////////
				//initializing and sending the array...
				////////////////////////////////////////////////////////
				X=(int *)malloc(n*sizeof(int));
			
				for(i=0;i<n;i++)
				{
					printf("X[%d] = ", i);
					scanf("%d", &X[i]);
				}
				
				send(server_socket,X,n*sizeof(int),0);
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
		
		
				////////////////////////////////////////////////////////
				//receiving prod=r*X...
				////////////////////////////////////////////////////////
				prod=(float *)malloc(n*sizeof(float));
				
				recv(server_socket,prod,n*sizeof(float),0);
				
				printf("******************************\n");	
				for(i=0;i<n;i++)
					printf("X[%d]*r = %.2f \n", i, prod[i]);
				printf("******************************\n");	
				////////////////////////////////////////////////////////
				////////////////////////////////////////////////////////
		}
		else if(choice==4)
		{
				flag=0;
		}
		else
		{
				printf("Invalid Choice. Terminating in 3...2...1....\n");
				exit(1);
		}
	}while(flag);

	printf("--------------------------------------------------------------------\n");

	return 0;
}
