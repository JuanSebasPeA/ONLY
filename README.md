#ONLY: Juan Sebastian Peña Angarita

ONLY program

this program Receive 2 arguments in the command parameter line (3 if you want to add a character to ignore a line):

--> The first argument is the name of the program(ONLY), and the second parameter say what will be the name of the labels(start and end labels). 
--> if the user writes something, the text will be ignored, but if the user enter the name of the start label (@second parameter), the next text entered 
    will be printed. --> if the user enter the name of the end label(@second parameter) the next text will be ignored again. 
--> if the user wants to use an optional comment, the user has to enter 3 parameters and the second parameter must be -cANYCHARACTER(this caracter will be 
    the comment, and now the the name of the labels will be the third parameter. 
--> to ignore a text line, the user has to write the comment firstly and then write the text that be ignored. (e.g): if the user entered(-c!), to ignore 
    a text line would be !this is the text to ignore.
