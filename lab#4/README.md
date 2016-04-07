Laboratory Work Nr.4
====================

Title
-----
Windows Timer. Animation.
------------
Main purposes of this lab work:

•Windows timer

What I did?
--------------------
•Created an animation based on Windows timer which involves at least 5 different drawn objects

•I added the possibility to Increase and decrease animation speed using mouse wheel/from keyboard

•Solved flicking problem.

The primary cause of  flickering is erasing the background, then immediately drawing over it. Since we are apparently drawing the whole client area of our window in WM_PAINT, I added a handler for WM_ERASEBKGND that does nothing but return TRUE to indicate that the background has been erased.

•Added 2 animated objects which will interact with each other. Balls that have different velocity and moving angles. They should behave based on following rules:
	
	On interaction with each other, circles and squares changes their color.
	
	On interaction with the right and left wall (the margins of the window), the circles are transformed into the squares.
	
	On interaction with the top and bottom of the window - the figures increases their velocity.

•I hooked 3 keyboard inputs:

	When you press the UP button the speed of balls are increasing.

	When you press the DOWN button the speed of balls are increasing.

	When you press the SPACEBAR you draw new circles with an increased velocity.
