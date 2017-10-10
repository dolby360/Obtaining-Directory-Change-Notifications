#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <sys\timeb.h>
#include <sys\types.h>
#include "Watcher.h"

#pragma comment(lib, "Ws2_32.lib")
struct timeval tv;
fd_set s_rd;

public ref class Executor{
private:
	static Executor^ inst;
	Watcher^ watch;
	enum class settings{ unInitialized = 0,	initializing = 1, done = 2};
	settings status;
	Executor(){
		//Initialize file descriptor for terminal;
		FD_ZERO(&s_rd);
		FD_SET(fileno(stdin), &s_rd);
		status = settings::unInitialized;
	}

public:
	void setWtcher(Watcher^ newWatch){ watch = newWatch; }
	static Executor^ getInstance(){
		if (inst != nullptr){
			return inst;
		}
		inst = gcnew Executor();
		return inst;
	}

	void stopTheThread(){
		if (watch == nullptr){
			return;
		}
		watch->killMe();
	}

	void static getExitFromUser(){
		tv.tv_sec = 2;
		tv.tv_usec = 0;

		if (Executor::getInstance()->status != settings::done){
			System::Threading::Thread::Sleep(4000);
			return;
		}

		if (/*FD_ISSET(fileno, s_rd)*/true){
			while (true){
				//System::Threading::Thread::Sleep(timeToSleepIn_ms);
				switch (select(fileno(stdin), &s_rd, NULL, NULL, &tv)){
				case -1:
					printf("error\n");
					//error
					break;
				case 0:
					printf("nothing\n");
					//no input
				default:{
					Executor::getInstance()->watch->killMe();
					System::Threading::Thread::Sleep(20);
					return;
				}break;
				}
			}
		}
	}

	//[PermissionSet(SecurityAction::Demand, Name = "FullTrust")]
	void static execute(){
		char path[256];
		int choose;
		Watcher^ w;

		Executor::getInstance()->status = settings::initializing;

		printf("Enter 0 for default\n");
		scanf("%d",&choose);
		if (choose == 0){
			strcpy(batFile,"C:\\Users\\zerbib\\Downloads\\dolev\\MCN_helper.bat");
			w = gcnew Watcher
				("C:\\Users\\zerbib\\Downloads\\dolev\\VxWorksProjects\\MCN4\\FCTECM\\ARMARCH5gnu\\fctEcm\\Debug");
		}else{
			printf("Please enter bat file path\n");
			scanf("%s",batFile);
			printf("Please enter folder to watch\n");
			scanf("%s", &path);
			w = gcnew Watcher(gcnew System::String(path));
		}
		printf("Executing the thread, if you want to quit enter any character and then press enter\n");
		Executor::getInstance()->status = settings::done;
		
		fflush(stdout);
		Executor::getInstance()->setWtcher(w);
		w->run();		
	}
};

#endif