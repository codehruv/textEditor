# Text Editor

Coding this to understand how computer applications are developed.
Following the guide here: http://viewsourcecode.org/snaptoken/kilo/

Beyond simply following the steps, I will figure out which decisions were design-based, in an attempt to personalize the editor.

## Setup

Basic C language usage

## Entering Raw Mode

Terminal has a set of commands it takes from the keyboards for output-input features.

For the text editor, we need to scrape all the features so as to implement our own. Then reset them back, once we are done with our process.

Flag | Function removed | Keypress removed
--- | --- | --- |
ECHO | Constant printing of typed in characters | 
ICANON | Line by line reading | 
ISIG | Interrupt and end by force | Ctrl-C & Ctrl-V
IXON | Software/data flow control | Ctrl-S & Ctrl-Q
