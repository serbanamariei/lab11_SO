#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<unistd.h>
#include"functii.h"

int main()
{
	int id_mayproduce=msgget(MAY_PRODUCE, IPC_CREAT | 0666);
	int id_mayconsume=msgget(MAY_CONSUME, IPC_CREAT | 0666);

	if(id_mayproduce==-1 || id_mayconsume==-1)
	{
		fprintf(stderr,"EROARE LA DESCHIDEREA COZILOR DE MESAJE\n");
		exit(1);
	}

	struct mesaj msg;
	msg.mtype=1;

	for(int i=0;i<CAPACITATE;++i)
	{
		msgsnd(id_mayproduce,&msg,sizeof(msg.continut),0);
	}

	int i=0;
	while(1)
	{
		msgrcv(id_mayproduce,&msg,sizeof(msg.continut),msg.mtype,0);
		sprintf(msg.continut,"mesaj %d",i);
		i++;
		sleep(1);
		msgsnd(id_mayconsume,&msg,sizeof(msg.continut),0);
	}


	return 0;
}
