#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>

#include "Watcher.h"
#include "Executor.h"

char *batFile;

void main(){
	batFile = (char*)malloc(sizeof(char)*64);
	memset(batFile,0,sizeof(batFile));

	System::Threading::Thread^ executingThread = gcnew System::Threading::Thread(
		gcnew System::Threading::ThreadStart(&Executor::execute));

	System::Threading::Thread^ exit = gcnew System::Threading::Thread(
		gcnew System::Threading::ThreadStart(&Executor::getExitFromUser));

	//TODO: Realese it after you solved select function issue.  
	//exit->Start();
	executingThread->Start();

	executingThread->Join();

	System::Threading::Thread::Sleep(20);
	printf("Enter somthing if you want to exit\n");
	getch();
	executingThread->Abort();
	delete batFile;
}