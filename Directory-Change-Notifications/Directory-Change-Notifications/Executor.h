#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "Watcher.h"

public ref class Executor{
private:
	static Executor^ inst;
	Watcher^ watch;
	Executor(){
		
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
		watch->stopWatching();
	}

	//[PermissionSet(SecurityAction::Demand, Name = "FullTrust")]
	void static execute(){
		printf("execute\n");
		Watcher^ w = gcnew Watcher("C:\\Users\\dolev\\Desktop\\fol1");
		Executor::getInstance()->setWtcher(w);
		w->run();
	}
};

#endif