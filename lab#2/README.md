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

What I did?
--------------------
•Created a Windows application

•In the middle of the window inserted the following text: "Done with Pride and Prejudice by Lupei Dragos".

•On windows resize, text  reflow and it i in window's middle (vertically and horizontally)

•Added 2 buttons to window: one with default styles, one with custom styles ( background, text color)

•Added 2 text elements to window: one with default styles, one with custom styles (background, text color)

•I made elements to interact 
When you click on "Clear" button , the text from first box is deleted

When you click on "Copy Text" button, the text from box 1 is copied to box 2

•I changed  behavior of maximize and close buttons

•You should run this!!!"IT IS OBLIGATORY"

Creation steps of the app:
--------------------------
As a beginner in Windows Programming, I found very useful Charles Petzold's book- *"Programming Windows"*.It helped me a lot to get started. Reading it,I figured out the main concepts of an Windows application. During the development of my own app, [http://msdn.microsoft.com](http://msdn.microsoft.com) was also of great usage.

Analysing the structure of my program,it can be divided in two main parts:WinMain function,which represents the entry point in the program and WinProc, which is the function that processes all messages sent or posted to all windows of the class. So,in WinMain I've declared the main window,while in WinProc I've created a list of messages as WM_CREATE, WM_PAINT, WM_DRAWITEM,WM_GETMINMAXINFO: and others, that I used to generate buttons,text elements and dialog boxes. 

Conclusions:
--------------------------
I learned how the elements of the window are created, how their behavior can be changed. I worked with messages, understood how the elements and their actions are interconnected. This concepts can be applied not only in windows programming, but also in another systems of programming.

