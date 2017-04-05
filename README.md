README.md

-------
Credits
-------

Created by Theodore Champ

All ncurses information came from a tutorial by Pradeep Padala. This tutorial can be found
at http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/

Further, Elsa Roeber heavily contributed to the interface design of this program.

Finally, all the code is of my design unless otherwise noted.

---------
Compiling
---------

The first thing to note about this program is it requires a library called ncurses to run.
Without this library, it will not even compile. Because ncurses only works on unix systems
(i.e. not Windows) it does not work on Windows systems. It was designed to work with linux
systems, specifically ubuntu 16.04 LTS. It should also work on OSX versions, although I'm
sure if you go back far enough it'll eventually break.

INSTALLING NCURSES
Ubuntu/Debian:
	Type the following command into terminal
	sudo apt-get install libncurses5-dev libncursesw5-dev

CentOS/RHEL/Scientific Linux 6.x/7.x+ and Fedora Linux 21 or older:
	Type the following command into terminal
	sudo yum install ncurses-devel

Fedora Linux 22.x+:
	Type the following command into terminal:
	sudo dnf install ncurses-devel

MacOSX:
	Type the following commands into terminal:
	$ curl -O ftp://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz
	$ tar -xzvf ncurses-5.9.tar.gz
	$ cd ./ncurses-5.9
	$ ./configure --prefix=/usr/local \
	  --without-cxx --without-cxx-binding --without-ada --without-progs --without-curses-h \
  	--with-shared --without-debug \
  	--enable-widec --enable-const --enable-ext-colors --enable-sigwinch --enable-wgetch-events\
	&& make
	$ sudo make install

For other operating systems, google should provide an answer quickly. I followed the tutorial at
https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/

COMPILING PROGRAM
The actual command to compile the program will vary slightly based on which compiler the user
uses and which operating system they have. However, there are two very important details. First,
every file that is either a .cpp or a .h file in this folder must be put in the compile statement
after your compile command. Second, in order to get ncurses to compile properly, the option
-lncurses must be included. The command that I used on an ubuntu system with g++ as the compiler
was:

g++ main.cpp Simulation.h Simulation.cpp Window.h Menu.cpp Menu.h SelectFile.cpp SelectFile.h -o run -lncurses -I.

Then, the program can be run with the command: ./run

-------------
Functionality
-------------

I tried to make the functionality of this program as simple to follow as possible but both the
complexity and the limited time (it could probably use a rewrite) might hinder it's readability.
That said, the program basically consists of 3 different menus: the main menu, the file select
menu, and the simulation itself. Each of these is a seperate class and they can be activated at
any point by creating an object of the cooresponding file type. Each of these classes has three
functions in common: logic, display, and input. The purpose of these functions is pretty self
explanatory. Both Menu and Simulation, after an init call, enter a loop in which all of these
functions are called, and then there is a wait command. For Menu, this wait just improves the
programs stability and reduces its resources. For Simulation, this sets the pace of the simulation

SUGGESTED METHOD OF READING:
If I was grading this project, I would read the Menu.cpp, SelectFile.cpp, and Simulation.cpp files
seperately. I would start with the constructors, and then read the init functions, and finally read
the logic, display, and input functions. As I read through these three functions, I would only look
at the other functions in the program as they were called. Finally, with the Simulation class
specifically, I would glance over the .h file because the variables are fairly important. Otherwise,
the .h files for the other classes can be largely ignored. Also, theres really not much value in
looking at the Window.h and Cell.h files, as they are pretty self explanatory and mostly there to
fulfill project requirements.

USING THE PROGRAM:
I attempted to make the program as user friendly as possible. That said, there are a few things to
note. First, the second screen of the program asks the user to input the file location of the initial
config that they want to simulate off of. In order to select a file, the user must either type the full
name of a file included in the same folder as the program itself, or the full file location if it is
located elsewhere. I have included several files for the user to test out this functionality. These
files are as follows:
acorn.txt
glider.txt
triangle.txt
u.txt
I would strongly recommend simulating u.txt, because it's really the only interesting config. The
user can also create their own configs, just be sure to use capital Os and not zeros. Finally, if
no file is entered or an incorrect file name is entered, the simulation starts with a default
configuration, which is just random alive cells. I find this to be the most interesting part of
the program, especially if the user lets this run for a little while. After the file name is entered,
the user must push the up arrow to advance.

On the simulation screen, in order to begin the program, the user must press any key.

LOCATION OF REQUIREMENTS
Loops: Throughout code, specifically look at constructors
if/else: Present throughout
Variables: Throughout, start with header files and go from there
I/O: For input, see Simulation.cpp, specifically the bottom of init().
     For output, see Menu.cpp init() under the KEY_END if statement.
Classes and Member functions: See .h files
Friend function: The friend function is a little contrived. But, it's located in both SelectFile.h
		 and Menu.cpp. It's definition is at the bottom of the file and it's use is in the init function.
