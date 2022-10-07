/* Author: Juan Sebastian Peña Angarita */

/*--------------------------------------------------------------------------------------------------------------------*/

										/* inclusion of libraries */
										
#include<stdio.h>
#include<string.h>
#include<locale.h>

/*--------------------------------------------------------------------------------------------------------------------*/
										/* Declaration of constants */
										
#define MAXLABEL 12
#define PREFIX "@"
#define POSFIX "_end"
#define MAXARG 3
#define COMPREFIX '-'
#define COMPREFIXTWO 'c'

/*--------------------------------------------------------------------------------------------------------------------*/
							/* section start buffer and section end buffer respectively */
							
char sectionB[sizeof(PREFIX) + MAXLABEL ],		 
	 sectionE[sizeof(PREFIX) + MAXLABEL + sizeof(POSFIX) ],
	 comment[MAXLABEL];

/*--------------------------------------------------------------------------------------------------------------------*/
									/* main(alternative) function prototype */
									
int inputText(char *argv[], int len, char *comment, char *sectionB, char *sectionE);

/*--------------------------------------------------------------------------------------------------------------------*/
										/* auxiliar functions prototype */
										
/* in this function the start and end section labels are create */	
int makeLabel(char *root, char *bLabel, char *eLabel );
/* This function counts the arguments entered on the command line parameter and evaluates if they are valid. */
int countArg(char *arguments[], int len, char *argForLabel);
/* if the user entered a comment as parameter, this function finds it */
int searchComm(char *arguments[], int size, char *comm);
/* this function check if the comment is being applied */ 
int applyComm (char *text, char *comm);

/*--------------------------------------------------------------------------------------------------------------------*/
												/* main */
												
int main(int argc, char* argv[]){       
	setlocale(LC_CTYPE, "spanish" );
	/* storing in a variable the number of arguments passed or entered in the command parameter line */
	int len = argc; 
	/* calling the function that receives the text entered by the user */
	inputText(argv, len, comment, sectionB, sectionE);
	
	return 0;
}

/*--------------------------------------------------------------------------------------------------------------------*/
												/* declaration of functions */

/* this funtion scan the text, and have other functions to create the labels, create a comment if it is necessary, 
   and printf the text between the start and end labels */
int inputText(char *argv[], int len, char *comment, char *sectionB, char *sectionE) {
	/* declaración */
	char name[BUFSIZ];
	char text[BUFSIZ];
	       												 
	name[0] = '\0';
	
	/* 1er paso: interpreta linea de comandos */
	if ( !countArg(argv, len, name ) ) {
		goto exit;
	}
	/* segundo: si encuentra un comentario válido lo asigna a la variable comentario */
	if (len == 3) {
		if (!searchComm(argv, len, comment)) {
			fprintf(stderr, "\nERROR: THE COMMENT IS INVALID, TRY -cCHARACTERES" );
			goto exit;
		}		
	}	
	/* 2do paso: construye la etiqueta */
	if ( !makeLabel(name, sectionB, sectionE ) )  {
		fprintf(stderr, "\nERROR: THE LABEL IS TOO LONG" );	
		goto exit;
	} 
	
	/* DBG: 
	printf("\nsectionB es: %s", sectionB);
	printf("\nsectionE es: %s", sectionE);	*/
	
	/* Lectura del dispositivo lógico de entrada */ 
	while (scanf("%s", &text ) ){	
	/* condición para entrar a la sección */
		if (strcmp(text, sectionB ) == 0 ){
			/* empieza a imprimir el texto dentro de la sección */
			fflush( stdin );
			while (gets(text) && strcmp(text, sectionE ) != 0 ){
				if (strlen(comment) > 0) {
					if (!applyComm (text, comment)) { 
					printf("%s\n", text);
					}				
				}else { 
					printf("%s\n", text);
				}				 
			}				
		}			/* cierra la condición para imprimir */	
	}  

exit:
		
	return 0;
}

/* function that takes the root string and from it creates the start and end labels

  input: root string with name
        bLabel pointer to the buffer for the start label
		eLabel pointer to the buffer for the end label

  output:
     start and end tags output to buffer
   
  back 1 OK
       0 ERROR: There is no space in the buffer
    
*/
int makeLabel(char *root, char *bLabel, char *eLabel ) {
	
	if ( MAXLABEL < strlen(root) ) {
		return 0;
	}  
	/* create bLabel tag */
	strcpy(bLabel, PREFIX);
	strcat(bLabel, root );
	
	/* create eLabel tag */
	strcpy(eLabel, bLabel );
	strcat(eLabel, POSFIX );
	
	/* DBG: 
	printf("bLbl='%s', eLbl='%s'", bLabel, eLabel); */
	
	return 1;
}

/* This function iterates over the arguments passed in the command line parameters
   and extracts the name of the section taking as a condition that the argument is not the first and evaluating if the number of arguments
   passed is accepted or not, returning 1 and 0 respectively */
int countArg(char *arguments[], int len, char *argForLabel ) {
	int i;

	if (len > MAXARG ) {
		fprintf(stderr, "\nTOO MUCH ARGUMENTS");
		return 0;
	}
	else if (len <= 1) {
		fprintf(stderr, "\nNOT EXIST ENOUGH ARGUMENTS");
		return 0;
	}
	
	else if (len == 2) {
		strcpy(argForLabel, arguments[1] );
		/* 	DEBUG: printf("\n the name of the label will be %s", argForLabel); */
		return 1;
	}
	else if (len == 3) {
		strcpy(argForLabel, arguments[2] );
		/* DEBUG: printf("\n the name of the label will be %s", argForLabel); */
		return 1;
	}
} /* cierra la función */

/* esta función se encarga de encontrar un comentraio en los argumentos pasados en la linea de comandos y que este
   comentario sea válido **/
int searchComm(char *arguments[], int size, char *comm ) {

	/* local variables*/
	int i;
	int indexComm = 0;
	char commCpy[MAXLABEL];
	/* DEBUG: printf("\n arguments[1] is: %s", arguments[1]); */
	strcpy(commCpy, arguments[1]);
	/* DEBUG: printf("\n commCpy is: %s", commCpy); */
	/* if the size of the comment entered is less or equal than 2 counting the characters "-c", the comment is invalid */ 
	if (strlen(commCpy) <= 2 ) {
		fprintf(stderr, "\nERROR: THE COMMENT NEEDS MORE CHARACTERS");
		return 0;
	}
	/* if the size of the comment entered is greater than MAXLABEL(12) counting the characters "-c", the comment is inválid too */ 
	else if (strlen(commCpy) > MAXLABEL) {
		fprintf(stderr, "\nERROR: THE COMMENT IS TOO LONG, THE MAXIMUM CHARACTERS IS 10");
		return 0;
	}
	/* if the size of the comment is valid, assing the string as comment (ignoring the characters '-' and 'c') */
	else if (strlen(commCpy) > 2 ) {
		if (commCpy[0] == COMPREFIX && commCpy[1] == COMPREFIXTWO) {
		/* I start from 2 because it is useful to ignore the first two characters */
			for (i = 2; i != strlen(commCpy); i++) {
				comm[indexComm] = commCpy[i];
				indexComm = indexComm + 1;
			}
			/* DEBUG: printf("\n The definitive comment is: %s", comm); */
			return 1;
		}
	}
	
	return 0;
} /* close the function */

/* This function is responsible for seeing if the comment is correctly applied to the entered text,
   and if so, the function returns 0 so that the line is not taken into account, that is, it is not printed */ 
int applyComm (char *text, char *comm) {
	int i;
	int commSize = strlen(comm);
	/* DEBUG: printf("\n this is the size of comm: %d", commSize); */

	for (i = 0; i != commSize; i++) {
		if(text[i] != comm[i]) {
		/* DEBUG: printf("\n there is not a comment here!"); */
			return 0;
		}
	}	
	
	return 1;
}


