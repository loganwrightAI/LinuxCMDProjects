#include <ncurses.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(void) {
	WINDOW *mainwin, *childwin;
	int ch;



	// Some dimensions of the screen
	int width = 23, height = 7, rows = 25, cols = 80;
	int x = (cols - width) / 2;
	int y = (rows - height) / 2;

	// Begin ncurses component
	if ((mainwin = initscr()) == NULL) {
		fprintf(stderr, "ncurses intialization failed!");
		exit(EXIT_FAILURE);
	}

	// Switch echoing and enav=ble keypad for input
	noecho();
	keypad(mainwin, TRUE);

	// Build the child window for main text and display
	childwin = subwin(mainwin, height, width, y, x);
	box(childwin, 0, 0);
	mvwaddstr(childwin, 1, 4, "Move the Window");
	mvwaddstr(childwin, 2, 2, "With the Arrow Keys");
	mvwaddstr(childwin, 3, 6, "Or Home/End");
	mvwaddstr(childwin, 5, 3, "Press 'q' to quit");

	refresh();

	// Build the main loop until the user quits the program

	while (( ch = getch() ) != 'q' ) {
		switch (ch) {
			case KEY_UP:
				if ( y > 0 ) --y;
	    			break;
 
			case KEY_DOWN:
	    			if ( y < (rows - height) ) ++y;
				break;
 
			case KEY_LEFT:
	    			if ( x > 0 ) --x;
				break;
 
			case KEY_RIGHT:
				if ( x < (cols - width) ) ++x;
				break;
 
			case KEY_HOME:
	    			x = 0;
	    			y = 0;
	    			break;
 
			case KEY_END:
				x = ( cols - width );
				y = ( rows - height );
				break;
		}
	// Inside of the loop, refresh the page after alterations are made
	mvwin( childwin, y, x );
	wrefresh(childwin);
	}

	// When the program ends, remove the ncurses tool from the terminal (cleanup)
	delwin( childwin );
	delwin( mainwin );
	endwin();
	return EXIT_SUCCESS;
}
