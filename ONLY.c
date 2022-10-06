/*	Integrantes:
-Juan Sebastian Peña Angarita
-Isabel Pérez Santos
-Irving Fernando Cmacho Baltazar  */

/*Inclusión de bibliotecas*/
#include<stdio.h>
#include<string.h>
#include<locale.h>

/*Declaración de constantes*/
#define MAXLABEL 12
#define PREFIX "@"
#define POSFIX "_end"
#define MAXARG 3
#define COMPREFIX '-'
#define COMPREFIXTWO 'c'

/* buffer de inicio de la sección y buffer de fin de la sección respectivamente */
char sectionB[sizeof(PREFIX) + MAXLABEL ],		 
	 sectionE[sizeof(PREFIX) + MAXLABEL + sizeof(POSFIX) ],
	 comment[MAXLABEL];

/* Prototipo de las funciones auxiliares */	
int makeLabel(char *root, char *bLabel, char *eLabel );

int countArg(char *arguments[], int len, char *argForLabel);

int searchComm(char *arguments[], int size, char *comm);

/* Inicio de la función principal */
int main(int argc, char* argv[]){       
	setlocale(LC_CTYPE, "spanish" );

/* declaración */	
	char name[BUFSIZ];
	char text[BUFSIZ];
	
	int len = argc;        												 
	name[0] = '\0';
	
	/* 1er paso: interpreta linea de comandos */
	if ( !countArg(argv, len, name ) ) {
		goto exit;
	}
	
	if (len == 3) {
		searchComm(argv, len, comment);
	}
	
	/* 2do paso: construye la etiqueta */
	if ( !makeLabel(name, sectionB, sectionE ) )  {
		fprintf(stderr, "ERROR: La etiqueta es demasiado grande" );
		
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
				printf("%s\n", text); 
			}
					
		}			/* cierra la condición para imprimir */
		
	}  /*cierra while */ 

exit:
		
	return 0;	
}

/* función que toma la cadena raíz y apartir de ella crea la etiqueta inico y de final 

  entrada: root   cadena con el nombre 
           bLabel puntero al buffer para la etiqueta de inicio
		   eLabel puntero al buffer para la etiqueta de fin 

  salida:
     las etiquetas de inicio y de fin salen al buffer
   
  retorna 1  OK
          0 ERROR: No hay espacio en el buffer 
    
*/
int makeLabel(char *root, char *bLabel, char *eLabel ) {
	
	if ( MAXLABEL < strlen(root) ) {
		return 0;
	}  
	/* hace la etiqueta bLabel */
	strcpy(bLabel, PREFIX);
	strcat(bLabel, root );
	
	/* hace la etiqueta eLabel */
	strcpy(eLabel, bLabel );
	strcat(eLabel, POSFIX );
	
	/* DBG: 
	printf("bLbl='%s', eLbl='%s'", bLabel, eLabel); */
	
	return 1;
}

/* Esta función itera sobre los argumentos pasados en en los parámetros de la línea de comandos
   y extrae el nombre de la sección tomando como condición que el argumento no sea el primero y evaluando si el número de argumentos
   pasados es aceptado o no, refresando 1 y 0 respectivamente */
int countArg(char *arguments[], int len, char *argForLabel ) {
	int i;

	if (len > MAXARG ) {
		fprintf(stderr, "TOO MUCH ARGUMENTS");
		return 0;
	}
	else if (len <= 1) {
		fprintf(stderr, "NOT EXIST ENOUGH ARGUMENTS");
		return 0;
	}
	
	if (len == 2) {
		strcpy(argForLabel, arguments[1] );
		printf("\n the name of the label will be %s", argForLabel);
		return 1;
	}
	else if (len == 3){
		strcpy(argForLabel, arguments[2] );
		printf("\n the name of the label will be %s", argForLabel);
		return 1;
	}
} /* cierra la función */

int searchComm(char *arguments[], int size, char *comm) {
	strcpy(comm, arguments[1]);
	printf("\n comm is: %s", comm);
	if (comm[0] == COMPREFIX && comm[1] == COMPREFIXTWO) {
		return 1;
	}
	else {
		return 0;
	}
}




