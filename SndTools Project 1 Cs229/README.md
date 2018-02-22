Project 1 Part 1

Author: Coleman Jackson

### PLEASE NOTE THERE ARE STILL  BUGS, ALL CODE IS PRESENTED AS-IS, AND WAS WRITTEN FOR PERSONAL USE ONLY. ###


This project was done in two weeks as the first part of project 1 for Com Sci 229. The code is essentially broken down into two parts


1) sndinfo: sndinfo takes a CS229 or AIFF sound file as function parameters and returns information about that sound file, including duration, bitdepth, number of samples, sample rate, and the filetype and name.
   it is comprised of a main method and several subfunctions required for its use. The subfunctions are as follows:
	
	sndinfomain.c: The main method file, which calls every other requried function listed in this readme in order to calculate the information about the sound file. It also handles the inital
		      Opening of that file.

	parser.c: parser.c contains a single function which returns an int value. It takes an audio file as a parameter, and is 
		 designed to decide if the filetype being passed in is a cs229 format or an aiff format. It is called at the beginning of the main method.


	keyvaluefinder.c :  a C file containing a single void method, keyValueFinder229, which takes a self-defined AUDIO struct and the file being read from.
			  it finds and parses the information returned by sndinfo and stores them in the struct to be returned
			  in the main method. its .h counterpart contains the struct used by both sndinfo and sndconv to store their respective data.
	
	keyvaluefinderaiff.c : Exactly the same as the 229 key value finding method, except for aiff files. It stores it's data in the keyvaluefinder.h struct as well.
	
	durationcalc.c   : Durationcalc takes a keyvaluefinder.h struct and a integer value representing how many seconds are in each file. it updates the keyvaluefinder.h struct 
			 with the number of hours, minutes, and seconds the sound file is in length.
_________________________________________________________________________________________________________
	
2) sndconv: sndconv takes a CS229 or AIFF formatted file and converts it into its respective counterpart, AIFF for CS229, and CS229 for AIFF. While this version is not working as well as I would have hoped,
	   
	   sndconvmain.c: The main method of the converter, which takes the other functions and converts the file to its opposite.
	
	   cstoa.c: this function takes an output file to write to, the input file, and a keyvaluefinder.h struct as its functional parameters.
		   it then parses a cs229 file and converts it to an aiff file, written to the output file. 

	   atocs.c: same as above, but vice-versa. This function converts an aiff file to a cs229 file format, written to the outputfile.
_________________________________________________________________________________________________________
3) sndcat:
This program reads all sound les passed as arguments, and writes a single sound le where the sample data
is the concatenation of the sample data in the inputs. The resulting sound le should be written directly to
standard output. If no les are passed as arguments, then the standard input stream should be treated as
the input le. Any messages should be written to standard error.

support of switches:
-h : Display a short help screen to standard error, and then terminate cleanly.
-a : Output should be AIFF.
-c : Output should be CS229.

it uses every file listed for sndconv and sndcat barring main methods, with two additions:
	snddatacalc.c: contains functions and helper methods used to calculate the data.
	sndcatmain.c: 
_________________________________________________________________________________________________________
4) sndcut:
This program reads a sound file from the standard input stream, and writes the sound file to the standard
output stream in the same format, after removing all samples specified as arguments. Any messages should
be written to standard error. Specifically, arguments may be passed as:
$ sndcut [switches] [low..high] [low..high] ...
where low..high species that all samples numbered between low and high, inclusive, are to be removed.

support of switches:
-h : Display a short help screen to standard error, and then terminate cleanly

this file is compriesed of every C file listed above barring main methods, with one addition:
	sndchecklib.c: contains functions and helper methods used to calculate the cut data.
	sndcutmain.c: the main method of the cutter.
_________________________________________________________________________________________________________
5) sndshow:
This program reads a sound le from the standard input stream, and displays an \ASCII art" representation
of the sample data. Your output should be formatted as follows. The rst 9 characters are used to display the
sample number which should be \right justied". Next comes a pipe character (\|"). The next x characters
are used for \plotting" negative values. Next comes a pipe character that represents the value 0. The next x
characters are used for \plotting" positive values. The nal character is another pipe character. The value
of x is dictated by the desired total output width; see the program switches.


support of switches:
-h : Display a short help screen to standard error, and then terminate cleanly. Use -h to learn the use of other switches and the formatting of the program.


5) sndedit:
Sound Edit is the top of the soundfile tool list, it combines the previous elements into one application for editing sound, 
complete with updating sound information, sndedit is a command line gui based sound editing tool built using the ncurses library.
to use, the following switches can be provided to get you started:
-h: displays a help message and terminates the program
