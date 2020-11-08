Anna Kurach

Prototype of File Manager application. Executable is runnable only on Windows OS.

This application is already able to:
- Show a catalogue inside every window.
- Show an appropriate icon for different file types.
- Show files attributes (file name, extension, file size, date created etc).
- Support file/folders operations: copy, move, rename, delete.
- Copying like in Total Commander from one window to another(only files, not directories).
- Show dialog windows (like confirm deleting etc.)

Features, that are still in development:
- Ability to show/hide some file attributes.
- Ability to sort files by name, size etc.
- Show progress bar during the operation.
- Documentation: requirements specification, software design documentation (application
modules description, UML diagrams).
- “make” file to compile application.
- Cross-compile issue.

To build the app, open FileManager.pro file in QtCreator and build using qmake.