#ifdef _WIN32 
#include <windows.h>
#include <tchar.h>
#elif __linux__
#include <glob.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "log.h"


#define MAX_POTENTIALS_PORTS 10
#define MAX_MESSEGE_SIZE 1024

// -------
// SUCCESS
// -------

#define SUCCESS 0

// --------
// WARNINGS
// --------

#define ALLOCATION_WARNING 1
#define RICHED_MAX_POTENTIALS_PORTS_WARNING 2

// ------
// EVENTS
// ------

#define NOT_OBD 3

// ------
// ERRORS
// ------

#define ERROR 4

#define ALLOCATION_ERROR 5
#define WRITE_ERROR 7
#define READ_ERROR 8
#define CLOSE_ERROR 9
#define CAR_NOT_CONNECTED_ERROR 10

typedef struct connections
{
	char** list;
	int size;
} Connections;

typedef struct commands
{
	//at commands
	char* reset;
	char* echo_on;
	char* echo_off;
	char* header_on;
	char* header_off;
	char* describe_protocol;
	char* timing_off;
	char* timing_auto1;
	char* timing_auto2;
	char* linefeeds_off;
	char* linefeeds_on;
	char* set_protocol_auto;
	//mode1 commands
	char* rpm;
	char* speed;
	char* throtle;
	char* fuel;
	char* engine_load;
	char* air_temperature;

} Commands;

int scanSerial(Connections* connections);
void freeConnections(Connections* connection);
int connect(char* portname, int *pd);
void printError(int error);
int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);
int send(int pd, char* msg);
int recv(int pd, char* msg, int len);
int disconnect(int pd);
int OBD();
Commands getCommands();
int command(int pd, char* command,float* value ,char* unit);
int translateELMresponse(char* response , float* value , char* units);
int hexToDec(char* hex, int size);