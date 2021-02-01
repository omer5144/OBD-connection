#include "OBD.h"
#include <pthread.h>

void * func(void* argv);

typedef struct args
{
	int *stop; // the thread will run until stop changes to 1 
	int pd;
} Args;

int main(void)
{
		
	int pd, stop = 0;
	char buf[MAX_MESSEGE_SIZE*sizeof(char)] = "";
	pthread_t tid; 
	
	creatLog();
	pd = OBD();
	if(pd < 0){return 0;}
	// --------------------------------------------------------------
	// OBD communication
	// --------------------------------------------------------------
	
	Commands commands = getCommands();

	command(pd, commands.echo_off, NULL ,buf);
	Args arg = {&stop, pd};
    pthread_create(&tid, NULL, func, (void*)&arg); 
	pthread_join(tid , NULL);

	stop = 1;
	disconnect(pd);
	closeLog();
	printf("BYE BYE!\n");
	return 0;
}

void * func (void* args)
{
    Args* arg = (Args*)args;
	Commands commands = getCommands();
	char unit[20];
	float value =-1;
	printf("engine speed\tspeed\t\tthrotle\t\tengine load\tfuel\t\tair temperature\n");
    while(!(*(arg->stop)))
	{
		//printf("engine speed:");
		if(command(arg->pd, commands.rpm,&value ,unit)!=SUCCESS){break;}
		//printf("speed:");
		if(command(arg->pd, commands.speed,&value ,unit)!=SUCCESS){break;}
		//printf("throtle:");
		if(command(arg->pd, commands.throtle,&value ,unit)!=SUCCESS){break;}
		//printf("engine load:");
		if(command(arg->pd, commands.engine_load,&value ,unit)!=SUCCESS){break;}
		//printf("fuel:");
		if(command(arg->pd, commands.fuel,&value ,unit)!=SUCCESS){break;}
		//printf("air temperature:");
		printf("\t");
		if(command(arg->pd, commands.air_temperature,&value ,unit)!=SUCCESS){break;}
		printf("\n");
	}
	printf("\n");
	return NULL;
}