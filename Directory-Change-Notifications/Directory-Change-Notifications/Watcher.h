#ifndef WATCHER_H
#define WATCHER_H

#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>

#using <system.dll>


using namespace System::Diagnostics;
using namespace System::IO;

extern char *batFile;
 
public ref class Watcher{
private:
	System::String^ path;
	bool killThisThread;
	static int timeToSleepIn_ms = 5000;
	
private:
	// Define the event handlers.
	static void OnChanged(Object^ /*source*/, FileSystemEventArgs^ e){
		// Specify what is done when a file is changed, created, or deleted.
		//printf("File: %s %s", e->FullPath, e->ChangeType);
		System::Threading::Thread::Sleep(5000);
		printf("Executing batFile\n");
		if (system(batFile) == -1){
			printf("Error in system()\n");
		}
	}
	
	//void OnRenamed(Object^ /*source*/, RenamedEventArgs^ e){
	//	// Specify what is done when a file is renamed.
	//	printf("File: %s renamed to %s", e->OldFullPath, e->FullPath);
	//}

public:

	Watcher(){
		killThisThread = false;
	}
	Watcher(System::String^ filePath){
		killThisThread = false;
		path = filePath;
	}
	void setFilePath(System::String^ filePath){ path = filePath; }

	void killMe(){
		killThisThread = true;
	}

	//[PermissionSet(SecurityAction::Demand, Name = "FullTrust")]
	int run(){
		while (!killThisThread){

			if (path == nullptr){ return 0; }

			// Create a new FileSystemWatcher and set its properties.
			FileSystemWatcher^ watcher = gcnew FileSystemWatcher;
			watcher->Path = path;

			/* Watch for changes in LastAccess and LastWrite times, and
			the renaming of files or directories. */
			watcher->NotifyFilter = static_cast<NotifyFilters>(NotifyFilters::LastAccess |
				NotifyFilters::LastWrite | NotifyFilters::FileName | NotifyFilters::DirectoryName);

			// Only watch text files.
			watcher->Filter = "*.txt";

			// Add event handlers.
			watcher->Changed += gcnew FileSystemEventHandler(/*&Watcher::OnChanged,*/Watcher::OnChanged);
			//watcher->Created += gcnew FileSystemEventHandler(this->OnChanged);
			//watcher->Deleted += gcnew FileSystemEventHandler(this->OnChanged);
			//watcher->Renamed += gcnew RenamedEventHandler(this->OnRenamed);

			// Begin watching.
			watcher->EnableRaisingEvents = true;
		}
	}
};

#endif