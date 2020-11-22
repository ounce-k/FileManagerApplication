Anna Kurach

Implement File Manager application.

Application should:
    - Should look visually like Total Commander (have two windows).
    - Show a catalogue inside every window.
    - Show an appropriate icon for different file types
    - Show files attributes (file name, extension, file size,  date created etc).
    - Ability to show/hide some file attributes.
    - Ability to sort files by name, size etc.
    - Support file/folders operations: copy, move, rename, delete.
    - Copying should be handled like in Total Commander from one window to another
    - Show progress bar during the operation
    - When file/folder is copying, user still can browse the app.
    - Show dialog windows (like confirm deleting etc.)

Project dependencies:
For Windows: A working C++ compiler, OpenGL drivers, Qt5, QtCerator. qmake. 
For Linux: A working C++ compiler, build-essentials, XCB and OpenGL drivers, Qt5, QtCerator, qmake.

Instruction for building:
1. #For Linux. Assuming you are in a folder that contains source files.
	> qmake         # You can also add the FileManager.pro file if needed
	> make          # qmake creates a Makefile, this runs make on it.
	> ./FileManager

2. Using QtCreator:
	Start QtCreator
	Select File -> Open project
	Choose your *.pro file from the disk.
	Select Build -> Run qmake.

To run application:
1. For Windows, run:
	FileManager.exe
2. For Linux, run:
	./FileManager

Before running app on Linux, install Qt. Run:
>wget http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
>chmod u+x qt-unified-linux-x64-online.run
>./qt-unified-linux-x64-online.run
Install the latest Qt version.
