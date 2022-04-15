# AsciiEngine
Little "Engine" for "Rendering" lines, shapes, text, etc anywhere on the windows console using ASCII characters.
This engine currently sucks, should not be used, and was only made as a learning experience. As I get better I may update it.


# Usage
1. Create Screen object
2. Use `screenObjectName.init();` to initialize the screen.
3. Put `std::cout << renderScreen(screenObjectName);` in a loop to constantly render the screen.

# Functions
`drawLine(Screen, x, y, x1, y1, character);` Draw a line.
`placePoint(Screen, x, y, character);` Place a point.
`rect(Screen, x1, y1, x2, y2, character, FILL);` Draw a rectangle. Fill is optional, will fill the rectangle if its set to a non-zero number.
`square(Screen, x, y, size, character, FILL);` Same as `rect();` but only draws squares of side length SIZE. This is because characters tend to be only half as wide as they are tall. If your characters are differently sized, then this wont make perfect squares.
`placeText(Screen, x, y, str);` Places a `std::string str;` on the screen at x, y. Text will ALWAYS be on top, as it uses a seperate array to store and render. Don't overlap text, it breaks.

