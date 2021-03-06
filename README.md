# Text Editor

Coding this to understand how computer applications are developed.
Following the guide here: http://viewsourcecode.org/snaptoken/kilo/

Reading each chapter fully, sumarizing it, and then implementing it.

Beyond simply following the steps, I will figure out which decisions were design-based, in an attempt to personalize the editor.

### Chapter 1 - Setup

Basic C language usage
C is a pain -.-
You have to declare functions before using them.

### Chapter 2 - Entering Raw Mode

Terminal has a set of commands it takes from the keyboards for output-input features.

For the text editor, we need to scrape all the features so as to implement our own. Then reset them back, once we are done with our process.

Flag | Function removed | Keypress removed
--- | --- | --- |
ECHO | Constant printing of typed in characters | 
ICANON | Line by line reading | 
ISIG | Interrupt and end by force | Ctrl-C & Ctrl-V
IXON | Software/data flow control | Ctrl-S & Ctrl-Q
IEXTEN | Pausing input for character | Ctrl-V
ICRNL | Carriage return convert to new line | Ctrl-M
OPOST | Shifting cursor to start after new line |
BRKINT | Break conditions stop program |
INPCK | Parity checking (vestigial) |
ISTRIP | 8th bit is stripped (vestigial) |
CS8 | [Added] Set char size to 8 bits per byte | 
VMIN | [Set] Min number of input bytes before `read()` returns |
VTIME | [Set] Max time to wait before `read()` returns |

Lastly, some error handling is implemented.

This is interesting. I am beginning to see the terminal more as a C program than a "terminal."

### Chapter 3 - Raw Input & Output

Switching `Ctrl-Q` back on for quitting the program.

Modular Keyboard Input
- `editorReadKey()` : Reads and returns keypress
- `editorProcessKeypress()` : Maps keypress to editor operations

**Coding design decision**: Simple `main()`

**Coding decision**: Use VT100 escape sequences because supported by many terminals. Other option: ncurses library which figures out terminal escape sequences.

#### Screen Output Setup
- `write(STDIN_FILENO , "\x1b[2J", 4);` 
   - `\x1b` = escape character
   - `[` = specifies escape sequence after this

- when error occurs, screen refreshes
   - `atexit()` : can be used, but would erase error message

- vim like `~` on the sides
   - to retrieve terminal dimensions `editorConfig` is used

- retrieving terminal dimensions ( i.e. rows and columns )
	- Easy Way - `ioctl()` 
		- `TIOCGWINSZ` - Terminal IOCTL Get Window Size
		- Reason we can't stick only with this is because it doesn't work for all terminals
	- Hard way 
		- Send cursor to the bottom right corner of the screen
		- Import cursor position

- minimizing flicker effect
    - minimizing use of `write()` using buffers
        - `write()` doesn't have a regular callback, it can cause flickers
        - better to take the entire screen output as one buffer and then write it together
        - appending buffers used, one function uses `realloc()` to give more space to the appending buffer and uses `memcpy()` to pile on the string, and the other uses `free()` to free up the buffer
    - disabling cursor while printing screen, enabling after it
    - clearing and printing line by line, instead of clearing screen and printing all lines together

- welcome message
    - placed a third way in, center aligned
    - `snprintf()` used to find length of welcome message
    - they actually center align by placing spaces :P

Escape Sequences used / [Check this link](http://vt100.net/docs/vt100-ug/chapter3.html#ED)

Sequence | Effect 
--- | --- |
`J` | Erase In Display / `2` clear screen option |
`H` |  Shift Cursor / default option to (1,1) (sidenote: terminal coordinates start from 1) |
`C` | Cursor Forward |
`B` | Cursor Down |
`n` | Device Status Report / Option 6 returns cursor position |
`h` | Set Mode / Turn on features / Option `?25` turns on cursor |
`l` | Reset Mode / Turn off features / Option `?25` turns off cursor |
`K` | Clear line |

Input keypresses created for kilo

Keypress | Effect 
--- | --- |
wasd | Cursor Movement |
Arrow Keys | Mapped to wasd, hence, Cursor Movement |
Home, Del | Taking cursor to left/right |
Page Up, Page Down | Taking cursor to top/bottom |
 
The code is as much about error handling as it is about acutal coding.

Some of the code is a bit too cluttered. I will have to unclutter it.

### Chapter 4 - Text Editor

Finally after stripping away the terminal's features, initializing the editor with our own features, we can shift to creating and editing files. :D

The idea is to read files line by line using a newly defined data-type `erow` and other C file functionalities.


### Project Notes

While this was an easy challenge, it was just what I needed to ease into learning the vim key bindings, navigating tmux and using w3m. 

This is also my first time writing a long program. Every time I leave it alone for a day or two, I have to read my code till I understand where I left off. Thankfully, I have the handy step-by-step guide with me. Taking on a project like this with no guidance is the goal, but I don't think I am at that level yet.















