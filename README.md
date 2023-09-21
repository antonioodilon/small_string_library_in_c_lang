# small_string_library_in_c_lang
====== HOW TO RUN ======
1) Install GCC on your machine: https://gcc.gnu.org/  
   1a) For the Windows OS: https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j  
   1b) For Linux OS (although many times Linux already comes with GCC installed by default): https://www.geeksforgeeks.org/how-to-install-gcc-compiler-on-linux/  
   1c) For Mac: https://osxdaily.com/2023/05/02/how-install-gcc-mac/  
2) Install Git: https://git-scm.com/  
3) On your computer, navigate to a folder of your choice where you will download this repository, and open the Terminal or CMD there.  
4) Enter the following command: "git clone https://github.com/antonioodilon/small_string_library_in_c_lang.git " (without the quotation marks).  
5) Navigate to the folder created there. The name of the folder is "small_string_library_in_c_lang".  
6) There will already be an executable for Linux-based operating systems there, but in case you want to build it again (for example, if you are using Windows), then go to step 7. Otherwise, just execute the program by opening the terminal and entering the command ./main and you're good to go.  
7) Build the program by opening the terminal on the "small_string_library_in_c_lang" folder and entering the command "gcc -o the_name_of_my_executable main.c " (again, without quotation marks). 
8) Execute the program by double clicking on it or doing ./the_name_of_my_executable  

====== OVERVIEW ======  

This is a small group of functions that I wrote in C for the String data type (named StringOfChars in the program), define as a struct with 3 members:
1) A pointer of type uint8_t (unsigned 8-bit integer);
2) Length of type size_t (unsigned 64-bit integer);
3) Capacity also of type size_t.

In this small program, the user will find functions to initialize a StringOfChars, create a StringOfChars with any number of characters as input and concatenate two StringOfChars. The user will also find functions that pertain to the modification and creation of actual arrays of chars (that is, not the struct StringOfChars, but a series of null-terminated unsigned 8-bit characters), such as transferring chars from one buffer to another, transforming 64-bit unsigned integers into arrays of chars, and transforming arrays of chars into 8-byte unsigned integers.

====== DESCRIPTION OF THE PROGRAM ======  
In order to show how these functions work in practice, the program starts by asking the user to enter the number of dynamic text strings she/he would like to insert, with no limit in terms of number of characters (hence, functions like malloc() and realloc() are very important in the program). The user will then enter a loop and be prompted to insert those texts; each of those strings will then be inserted into a dynamic vector (using malloc()) of type StringOfChars (that is, a series of pointers, each of those pointing to an instance of the struct StringOfChars). The strings are printed, and then concatenated with a small hardcoded array of characters from the program itself inside of an instance of the StringOfChars data type.

The concatenated string is afterwards printed character by character by skipping lines, as well as their index positions inside the buffer and the ASCII values of those characters. The next step is to select 8 random characters in the buffer in order to create a new array, and then transform this array into a 64-bit integer number in big endian format, and then into another 8-byte integer in little endian. For example, an array with the values {0x4D, 0xFC, 0x89, 0x1A, 0xFF, 0xCE, 0xB7, 0x4A} will generate two 64-bit integers: 0x4DFC891AFFCEB74A (big endian) and 0x4AB7CEFF1A89FC4D (little endian), and those can be printed like regular integers, using the %llx and %llu format specifiers.

Finally, the program grabs the address of the first character of the buffer inside the concatenated string, casts it into a 64-bit unsigned integer and stores this value into a variable. This integer is then transformed into two 8-byte character arrays: one in big endian format, and another in little endian format; both arrays are then printed char by char using the %c, %x and %d format specifiers, with the program warning that those values won't necessarily have a correspondent in letters (after all, different from the input string by the user, often times they don't have a human-readable counterpart in ASCII).

====== MOTIVATION FOR WRITING THE PROGRAM ======  
The nature of this small project may come across as strange for many programmers out there. After all, why write a series of functions that, at the end, do very basic string operations that are nowadays common to most of the high-level languages that are used in real-world projects? For example, in Java or C#, if we want to concatenate two strings, we may see something like:  
	String name = "Helena";  
 	String last_name = " Smith";  
  	String full_name = name + last_name;  
   	System.out.println(full_name);  
    	// Output: Helena Smith  
Whereas in Python we don't even need to declare a type!  

However, our program was coded was in C, and this language doesn't have many built-in functions for performing the sorts of operations that in other languages are much more simple to implement. Therefore, a C programmer needs to know how to implement those functionalities him/herself. And this is why I personally believe that C is a great high-level language for learning algorithms and data structures from scratch, while at the same time learning about some very important low-level aspects of computers. The motivation for writing the program is, thus, clear: to exercise and understand how dynamic character strings (with data located on the heap rather than the stack, thus forcing the programmer to directly deal with the former section of memory) work internally, as well as to show this ability to potential recruiters. And this is why I decided not to use C++ (which has many useful functionalities for dealing with arrays, vectors and strings), even though this would make a lot more sense in a real-world project, as I am certain Bjarne Stroustrup and the team that develops this language did an infinitely better job than me!  

But how does the concatenation of strings allocated on the heap really work? If 'name' and 'last_name' in the example program in Java/C# (very similar in C++, by the way) I wrote before aren't really numbers, and therefore 'name' + 'last_name' does not yield the same result as 2 + 3, then what does that '+' sign really mean? The answer is that the '+' sign hides, behind its high-level nature, the low-level features of dynamic memory allocation, and a constant request by the program to the operating system, which constantly needs to find more memory, as new strings of unknown size need to be allocated (and later freed manually by the programmer). If a C programmer knows how to do basic things like this, then this is a very important first step towards building a career in low-level programming! And as a programmer whose desire is to work closer to the machine level (in fact, this applies to any programmer in this level), I believe it is paramount for me to know how certain basic data types work internally, and to exercise its inner workings. Frameworks, built-in tools and third-party libraries and software components are definitely our allies in being more productive programmers, and we shouldn't be afraid to use them, even if we don't understand their inner workings completely. But, as it is known, this is not always the case, and often times programmers need to know how to build their own tools, or modify/improve the ones that already exist in order to adapt to different scenarios.  

On a final note, I would like to thank you if you could contact me for any potential bugs or memory leaks that you see in this program, and what I could do to improve it!  
