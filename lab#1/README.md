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


Secondary purposes of this lab work:

•use a Version Control Systems (GIT).

•write code according to a Programming Style Guide.

Mandatory Objectives:
--------------------
•Create a Windows application

•Choose Programming Style Guidelines that you'll follow

•Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

•Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

•Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

Objectives With Points:
----------------------
•Make elements to fit window on resize. (1 pt)

•Make elements to interact or change other elements. (2 pt)

•Change behavior of different window actions (at least 3). (1 pt)

•Write your own PSG. (1 pt)

Creation steps of the app:
--------------------------
As a beginner in Windows Programming, I found very useful Charles Petzold's book- *"Programming Windows"*.It helped me a lot to get started. Reading it,I figured out the main concepts of an Windows application. During the development of my own app, [http://msdn.microsoft.com](http://msdn.microsoft.com) was also of great usage.

Analysing the structure of my program,it can be divided in two main parts:WinMain function,which represents the entry point in the program and WinProc, which is the function that processes all messages sent or posted to all windows of the class. So,in WinMain I've declared the main window,while in WinProc I've created a list of messages as WM_CREATE, WM_PAINT, WM_SYSCOMMAND,WM_SIZE and others.,that I used to generate buttons,edit boxes and dialog boxes. For the objects's interaction one with each other, I used various functions like SendMessage(),CreateFont(),GetClientRect() and others.

Bellow I'll present the screenshot of the application:

 ![The app](https://raw.github.com/TUM-FAF/FAF-121-Gusan-Gina/master/WP/images/app1.png)

Features:
---------
My application consists of two Edit boxes: one for input text and another for output text.The Input Box has customized text color. The Output Box has customized font size.

It also has four Buttons:three of them responsible for fonts and one of them for a special purpose.
All the buttons have customized styles: text size, text font ,dimensions.
Functionality:
--------------
•	By clicking the Default Button, the text goes from Input Box to Output Box, having the default font.

•	By clicking the second button, the text goes from Input Box to Output Box, having the ‘Comic Sans’ font.

•	By clicking the third button, the text goes from Input Box to Output box, having the ‘Chaparral’ font.

•	If you press the minimize or maximize buttons, the window will not minimize nor maximize, instead an alerting message box will appear.

•	If you press the close button, the position of the  window will change and another message box will be displayed.

•	For minimizing the window, in Input box should be typed ‘MINIMIZE'.

•	For maximizing the window, in Input box should be typed ‘MAXIMIZE'.

•	For restoring the window after maximization, in Input box should be typed ‘RESTORE'.

•	For closing the window, in Input box should be typed ‘CLOSE'.

•	The window has a minimal size and also allows resizing.

•	All the objects from the window react at any dimension changes.



