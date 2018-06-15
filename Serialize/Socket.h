#pragma once

#define	_USE_BSD
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <netdb.h>

#include <arpa/inet.h>

#define	QLEN		  32		// maximum connection queue length	

unsigned short	portbase = 0;	// port base, for non-root servers	

int connectTCP(const char *host, const char *service);
int connectsock(const char *host, const char *service, const char *transport);
int passiveTCP(const char *service, int qlen);
int passivesock(const char *service, const char *transport, int qlen);
int errexit(const char *format, ...);

//------------------------------------------------------------------------
// connectTCP - connect to a specified TCP service on a specified host
//------------------------------------------------------------------------
int connectTCP(const char *host, const char *service)
/*
* Arguments:
*      host    - name of host to which connection is desired
*      service - service associated with the desired port
*/
{
	return connectsock(host, service, "tcp");
}

//------------------------------------------------------------------------
// connectsock - allocate & connect a socket using TCP or UDP
//------------------------------------------------------------------------
int connectsock(const char *host, const char *service, const char *transport)
/*
* Arguments:
*      host      - name of host to which connection is desired
*      service   - service associated with the desired port
*      transport - name of transport protocol to use ("tcp" or "udp")
*/
{
	struct hostent	*phe;	/* pointer to host information entry	*/
	struct servent	*pse;	/* pointer to service information entry	*/
	struct protoent *ppe;	/* pointer to protocol information entry*/
	struct sockaddr_in sin;	/* an Internet endpoint address			*/
	int	s, type;			/* socket descriptor and socket type	*/


	memset(&sin, 0, sizeof(sin));	// 初始化
	sin.sin_family = AF_INET;

	/* Map service name to port number */
	if (pse = getservbyname(service, transport))
		sin.sin_port = pse->s_port;
	else if ((sin.sin_port = htons((unsigned short)atoi(service))) == 0)
		errexit("can't get \"%s\" service entry\n", service);

	/* Map host name to IP address, allowing for dotted decimal */
	if (phe = gethostbyname(host))									// DNS解析域名或者局域网下的主机名
		memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
	else if ((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)	// 点分十进制转换函数，转换失败返回INADDR_NONE
		errexit("can't get \"%s\" host entry\n", host);

	/* Map transport protocol name to protocol number */
	if ((ppe = getprotobyname(transport)) == 0)
		errexit("can't get \"%s\" protocol entry\n", transport);

	/* Use protocol to choose a socket type */
	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;

	/* Allocate a socket */
	s = socket(PF_INET, type, ppe->p_proto);
	if (s < 0)
		errexit("can't create socket: %s\n", strerror(errno));

	/* Connect the socket */
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't connect to %s.%s: %s\n", host, service,
			strerror(errno));
	return s;
}

/*----------------------------------------------------------------------*
Function:		passiveTCP
Description:	create a passive socket for use in a TCP server
Arguments:
service - service associated with the desired port
qlen    - maximum server request queue length
*----------------------------------------------------------------------*/
int passiveTCP(const char *service, int qlen)
{
	return passivesock(service, "tcp", qlen);
}

/*----------------------------------------------------------------------*
Function:		passivesock
Description:	allocate & bind a server socket using TCP or UDP
Arguments:
service   - service associated with the desired port
transport - transport protocol to use ("tcp" or "udp")
qlen      - maximum server request queue length
*----------------------------------------------------------------------*/
int passivesock(const char *service, const char *transport, int qlen)
{
	struct servent *pse;			// pointer to service information entry	
	struct protoent *ppe;   		// pointer to protocol information entry
	struct sockaddr_in sin; 		// an Internet endpoint address			
	int s, type;					// socket descriptor and socket type

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;

	/********* Map service name to port number *********/
	if (pse = getservbyname(service, transport))
		sin.sin_port = htons(ntohs((unsigned short)pse->s_port)
			+ portbase);
	else if ((sin.sin_port = htons((unsigned short)atoi(service))) == 0)
		errexit("can't get \"%s\" service entry\n", service);

	/********* Map protocol name to protocol number *********/
	if ((ppe = getprotobyname(transport)) == 0)
		errexit("can't get \"%s\" protocol entry\n", transport);

	/********* Use protocol to choose a socket type *********/
	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else
		type = SOCK_STREAM;

	/****************** Allocate a socket ******************/
	s = socket(PF_INET, type, ppe->p_proto);
	if (s < 0)
		errexit("can't create socket: %s\n", strerror(errno));

	/******************* Bind the socket *******************/
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't bind to %s port: %s\n", service,
			strerror(errno));
	if (type == SOCK_STREAM && listen(s, qlen) < 0)
		errexit("can't listen on %s port: %s\n", service,
			strerror(errno));
	return s;
}

/*----------------------------------------------------------------------*
Function:		errexit
Description:	print an error message and exit
/*----------------------------------------------------------------------*/
int errexit(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	exit(1);
}