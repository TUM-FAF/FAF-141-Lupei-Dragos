Laboratory Work Nr.1
====================
Title
-----
Window. Window handling. Basic window’s form elements.
Introduction
------------
Main purposes of this lab work:

•understand Event-Driven Programming.

•study Win32 API.

Mandatory Objectives:
--------------------
•Create a Windows application

•Choose Programming Style Guidelines that you'll follow

•Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

•Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

•Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)


Creation steps of the app:
--------------------------
As a beginner in Windows Programming, I found very useful Charles Petzold's book- *"Programming Windows"*.It helped me a lot to get started. Reading it,I figured out the main concepts of an Windows application. During the development of my own app, [http://msdn.microsoft.com](http://msdn.microsoft.com) was also of great usage.

Analysing the structure of my program,it can be divided in two main parts:WinMain function,which represents the entry point in the program and WinProc, which is the function that processes all messages sent or posted to all windows of the class. So,in WinMain I've declared the main window,while in WinProc I've created a list of messages as WM_CREATE, WM_PAINT, WM_SYSCOMMAND,WM_SIZE and others.,that I used to generate buttons,edit boxes and dialog boxes. For the objects's interaction one with each other, I used various functions like SendMessage(),CreateFont(),GetClientRect() and others.




