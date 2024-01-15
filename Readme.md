* **Austin Van Braeckel - 1085829 - avanbrae@uoguelph.ca**
* **CIS1300 - Programming ( Deborah Stacey)**
* **Due: 11-18-2019**

* **Create all executables by running the following in the terminal: make all**

There are two programs, as they have slightly different command line arguments for execution:
* _cgol_ must have the seed file, but the number of ticks can specified (2 command line arguments maximum)
* _dynCGOL_ must have the seed file, but the number of ticks, rows, and columns can be specified (4 command line arguments maximum)

__Defaults__
* Number of Ticks: 50
* Number of Rows: 20
* Number of Columns: 40

**cgol (Conway's Game of Life):**

For this program, after creating the executables with _make all_ or _make cgol_, the user can run the executable, _cgol_, by typing some command line arguments. This will be demonstrated with examples pertaining to Linux. Furthermore, **the seed is required** for the program to work, but there is one optional argument; the number of ticks. Examples of the use of _cgol_ is demonstrated below:
1. ./cgol seedFileName
2. ./cgol seedFileName (Number of Ticks)

**dynCGOL (Dynamic Conway's Game of Life):**

For this program, after creating the executables with _make all_ or _make dynCGOL_, the user can run the executable, _dynCGOL_, by typing some command line arguments. This will be demonstrated with examples pertaining to Linux. Furthermore, **the seed, number of ticks, number of rows, and number of columns are _all_ required**:
1. ./dynCGOL seedFileName (Number of Ticks) (Number of Rows) (Number of Columns)
* _All information is specifed by the user_

**Description**

 The "seedFileName" can be any text file, but the program is intended to use seeds/files that consist of 0s and 1s separated by spaces; the 1 represents a living cell, while 0 represents a dead one. The user has the option of specifying the number of ticks for which they want the program to run; In _cgol_ only, if none are specified, the number of ticks is set to the default, 50. In _dynCGOL_ only, the user must specify the number of rows and columns in their given seed file, and they may be any size greater than 0, within the size restrictions of an unsigned long integer. After the user executes the program as described, they will see the starting grid, and will be asked if they want to start. The world evolves before the user's eyes, and after the ticks are complete, the user can choose to continue, which means the program will continue to run for the specified number of ticks. Instead, the user can also simply quit the program after the specified number of ticks are finished. However, if the grid reaches a point where it never changes, the program will end.


*In order to run properly, this program needs to be accompanied by deadOrAlive.c in its folder, along with any text files to use as seeds*

***Note: The user input options will always be described in square brackets, "()", after the questions.***