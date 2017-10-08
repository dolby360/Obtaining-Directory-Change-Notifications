
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>

#include "Watcher.h"
#include "Executor.h"
void main(){
	
	System::Threading::Thread^ oThread = gcnew System::Threading::Thread(
		gcnew System::Threading::ThreadStart(&Executor::execute));

	printf("Initial commit\n");
	getch();
}