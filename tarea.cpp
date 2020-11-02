/*Optimizacion de Horarios*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define a 20
#define maxLineas	 3200
#define maxAlumnos 250

void validarArchivo(char nombreArchivo[a]);
int numeroLineas(char nombreArchivo[a]);
void almacenaLineas(char nombreArchivo[a], char cadena[maxLineas][maxAlumnos]);
void claveLarga(int numeroAlumnos, char datos[maxLineas][maxAlumnos], int claveAlumno[maxAlumnos], int salto[maxAlumnos]);
void carrera(int numeroAlumnos, char datos[maxLineas][maxAlumnos], char carreraAlumno[maxAlumnos][51], int salto[maxAlumnos]);
void separador(int numeroAlumnos, char datos[maxLineas][maxAlumnos], int salto[maxAlumnos]);
void saltoApivote(int salto[maxAlumnos], int pivote[maxLineas], int numeroAlumnos);
void indice (int lineas, char datos[maxLineas][maxAlumnos],int pivote[maxLineas]);
int horaOcio(int alumno, char datos[maxLineas][maxAlumnos],int pivote[maxLineas]);
int horaClase(int alumno, char datos[maxLineas][maxAlumnos],int pivote[maxLineas]);
void resultadosDia(int numeroAlumnos, int claveAlumno[maxAlumnos], int dias[6][maxAlumnos][2]);
void resultadosSemana(int numeroAlumnos, int claveAlumno[maxAlumnos], int dias[6][maxAlumnos][2]);
void resultadosCarrera(int numeroAlumnos, int claveAlumno[maxAlumnos], char carreraAlumno[maxAlumnos][51], int dias[6][maxAlumnos][2]);
int main(){
		char nombreArchivo[a] = {"Proyecto.txt"};
		char data[maxLineas][maxAlumnos];
		int claveAlumno[maxAlumnos];
		char carreraAlumno[maxAlumnos][51];
		int dias[6][maxAlumnos][2];
		int salto[maxAlumnos] , pivote[maxLineas];
		int i, lineas, numeroAlumnos;
		int alumno, aux; 
		
			validarArchivo(nombreArchivo);
			almacenaLineas(nombreArchivo,data);
			lineas = numeroLineas(nombreArchivo);
			numeroAlumnos = lineas / 14;
			claveLarga(numeroAlumnos, data, claveAlumno, salto); 
			carrera(numeroAlumnos, data, carreraAlumno, salto); 
			separador(numeroAlumnos, data,salto);	
			separador(numeroAlumnos, data,salto);	
			separador(numeroAlumnos, data,salto);
			saltoApivote(salto, pivote, numeroAlumnos);	/*lunes*/
				for (i = 0; i < numeroAlumnos; i++){
					dias[0][i][0] = horaOcio(i, data, pivote);
					dias[0][i][1] = horaClase(i, data, pivote);
//					printf("%d >> %d >> %d\n", i, dias[0][i][1], dias[0][i][0]);
				 }
			indice(lineas, data, pivote);	/*martes*/	
				for (i = 0; i < numeroAlumnos; i++){
					dias[1][i][0] = horaOcio(i, data, pivote);
					dias[1][i][1] = horaClase(i, data, pivote);
//					printf("%d >> %d >> %d\n", i, dias[1][i][1], dias[1][i][0]);
				}
			indice(lineas, data, pivote);	/*miercoles*/	
				for (i = 0; i < numeroAlumnos; i++){
					dias[2][i][0] = horaOcio(i, data, pivote);
					dias[2][i][1] = horaClase(i, data, pivote);
//					printf("%d >> %d >> %d\n", i, dias[2][i][1], dias[2][i][0]);		
				}
			indice(lineas, data, pivote);	/*jueves*/
				for (i = 0; i < numeroAlumnos; i++){
					dias[3][i][0] = horaOcio(i, data, pivote);
					dias[3][i][1] = horaClase(i, data, pivote);
//					printf("%d >> %d >> %d\n", i, dias[3][i][1], dias[3][i][0]);
				}	
			indice(lineas, data, pivote);	/*viernes*/	
			 	for (i = 0; i < numeroAlumnos; i++){
					dias[4][i][0] = horaOcio(i, data, pivote);
					dias[4][i][1] = horaClase(i, data, pivote);
//					printf("%d >> %d >> %d\n", i, dias[4][i][1], dias[4][i][0]);
				}
			indice(lineas, data, pivote);	/*sabado*/	
				for (i = 0; i < numeroAlumnos; i++){
					dias[5][i][0] = horaOcio(i, data, pivote);
					dias[5][i][1] = horaClase(i, data, pivote);
//					printf("%d >> %d >> %d\n", i, dias[5][i][1], dias[5][i][0]);
				}
	//	resultadosDia(numeroAlumnos, claveAlumno, dias);
	//	resultadosSemana(numeroAlumnos, claveAlumno, dias);
		resultadosCarrera(numeroAlumnos, claveAlumno, carreraAlumno, dias);
	
		
	return 0;
}
void resultadosCarrera(int numeroAlumnos, int claveAlumno[maxAlumnos], char carreraAlumno[maxLineas][51], int dias[6][maxAlumnos][2]){
	int i, k, escuela[numeroAlumnos] = {NULL}, ocio[numeroAlumnos] = {NULL};
	float porcentaje[numeroAlumnos] = {NULL};
	int escuelaCarrera[numeroAlumnos] = {NULL}, ocioCarrea[numeroAlumnos] = {NULL};
	float porcentajeCarrea[numeroAlumnos] = {NULL};
	char ic[] = "INGENIER÷A CIVIL", ig[] = "INGENIER÷A EN GEOLOG÷A";
	char imel[] = "INGENIER÷A MECµNICA ELêCTRICA", iagr[] = "INGENIER÷A AGROINDUSTRIAL";
	char ima[] = "INGENIER÷A MECµNICA ADMINISTRATIVA", ime[] = "INGENIER÷A MECµNICA";
	char icomp[] = "INGENIER÷A EN COMPUTACI‡N", imm[] = "INGENIER÷A METALÈRGICA Y DE MATERIALES";
	char iea[] = "INGENIER÷A EN ELECTRICIDAD Y AUTOMATIZACI‡N", itc[] = "INGENIER÷A EN TOPOGRAF÷A Y CONSTRUCCI‡N"; 
	char igi[] = "INGENIER÷A EN GEOINFORMµTICA", isi[]= "INGENIERIA EN SISTEMAS INTELIGENTES";
	char iamb[] = "INGENIER÷A AMBIENTAL";
	char *carrera[13] = {"ic","ig","imel","igr","ima","ime","icomp","imm","iea","itc","igi","isi","iamb"};
	int contador[3][13] = {0};
	
	printf("Carrera   NoAlumnos    PromHrOcio    PromHrEscuela \n");
	for (k = 0; k < 6; k++)/*dias*/
		for ( i = 0; i < numeroAlumnos; i++){
			escuela[i] += dias[k][i][1] + dias[k][i][0];
			ocio[i] += dias[k][i][0];
			if (escuela[i] != 0) porcentaje[i] += (float)ocio[i] / (float)escuela[i]* 100;
			else porcentaje[i] = 0;
		}

	for (i = 0; i < numeroAlumnos; i++){
			 if (strcmp(carreraAlumno[i], ic) == 0){
			 	contador[0][0] += 1;
			 	contador[1][0] += ocio[i];
			 	contador[2][0] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], ig) == 0) {
			 	contador[0][1] += 1;
			 	contador[1][1] += ocio[i];
			 	contador[2][1] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], imel) == 0){
			 	contador[0][2] += 1;
			 	contador[1][2] += ocio[i];
			 	contador[2][2] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], iagr) == 0){
			 	contador[0][3] += 1;
			 	contador[1][3] += ocio[i];
			 	contador[2][3] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], ima) == 0){
			 	contador[0][4] += 1;
			 	contador[1][4] += ocio[i];
			 	contador[2][4] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], ime) == 0){
			 	contador[0][5] += 1;
			 	contador[1][5] += ocio[i];
			 	contador[2][5] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], icomp) == 0){
			 	contador[0][6] += 1;
			 	contador[1][6] += ocio[i];
			 	contador[2][6] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], imm) == 0){
			 	contador[0][7] += 1;
			 	contador[1][7] += ocio[i];
			 	contador[2][7] += escuela[i];
			 }
		else if (strcmp(carreraAlumno[i], iea) == 0){
			 	contador[0][8] += 1;
			 	contador[1][8] += ocio[i];
			 	contador[2][8] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], itc) == 0){
			 	contador[0][9] += 1;
			 	contador[1][9] += ocio[i];
			 	contador[2][9] += escuela[i];
			 } 
		else if (strcmp(carreraAlumno[i], igi) == 0){
			 	contador[0][10] += 1;
			 	contador[1][10] += ocio[i];
			 	contador[2][10] += escuela[i];
			 }
		else if (strcmp(carreraAlumno[i], isi) == 0){
			 	contador[0][11] += 1;
			 	contador[1][11] += ocio[i];
			 	contador[2][11] += escuela[i];
			 }
		else if (strcmp(carreraAlumno[i], iamb) == 0){
			 	contador[0][12] += 1;
			 	contador[1][12] += ocio[i];
			 	contador[2][12] += escuela[i];
			 }
	} 
	for (i = 0; i < 13; i++) printf("%7s >> %8.0f >> %10.2f >> %13.2f\n", carrera[i], (float)contador[0][i], (float)contador[1][i]/(float)contador[0][i], (float)contador[2][i]/(float)contador[0][i]);
	printf("\n\t >> FIN");
}
void resultadosSemana(int numeroAlumnos, int claveAlumno[maxAlumnos], int dias[6][maxAlumnos][2]){
	int i, k, escuela[numeroAlumnos] = {NULL}, ocio[numeroAlumnos] = {NULL};
	float porcentaje[numeroAlumnos] = {NULL};
	printf("Alumno \n");
	for (k = 0; k < 6; k++)/*dias*/
		for ( i = 0; i < numeroAlumnos; i++){
			escuela[i] += dias[k][i][1] + dias[k][i][0];
			ocio[i] += dias[k][i][0];
			if (escuela[i] != 0) porcentaje[i] += (float)ocio[i] / (float)escuela[i]* 100;
			else porcentaje[i] = 0;
		}

	for (i = 0; i < numeroAlumnos; i++)			
	printf(">>clave: %d\n\t>> Sem[SumHrOcio,Summ%%HrOcio,SumHrEscuela]\n\t>> Sem[%10d, %12.2f, %10d]\n ", 
										claveAlumno[i], ocio[i], porcentaje[i], escuela[i]);	/*semana*/												
	printf("\n\t >> FIN");
}
void resultadosDia(int numeroAlumnos, int claveAlumno[maxAlumnos], int dias[6][maxAlumnos][2]){
	int i, k, escuela[numeroAlumnos][6], ocio[numeroAlumnos][6];
	float porcentaje[numeroAlumnos][6];
	printf("Alumno \n");
	for (k = 0; k < 6; k++)
		for ( i = 0; i < numeroAlumnos; i++){
			escuela[i][k] = dias[k][i][1] + dias[k][i][0];
			ocio[i][k] = dias[k][i][0];
			if (escuela[i][k] != 0) porcentaje[i][k] = (float)ocio[i][k] / (float)escuela[i][k] * 100;
			else porcentaje[i][k] = 0;
		}			
	for (i = 0; i < numeroAlumnos; i++)			
	printf(">>clave: %d\n >> dia[hrEscuela,hrOcio,%%hrOcio]\n >> L[%2d, %2d, %2.2f]\n >> M[%2d, %2d, %2.2f]\n >> X[%2d, %2d, %2.2f]\n >> J[%2d, %2d, %2.2f]\n >> V[%2d, %2d, %2.2f]\n >> S[%2d, %2d, %2.2f]\n", 
													claveAlumno[i], escuela[i][0], ocio[i][0], porcentaje[i][0],	/*lunes*/
																	escuela[i][1], ocio[i][1], porcentaje[i][1],	/*martes*/
																	escuela[i][2], ocio[i][2], porcentaje[i][2],	/*miercoles*/
																	escuela[i][3], ocio[i][3], porcentaje[i][3],	/*jueves*/
																	escuela[i][4], ocio[i][4], porcentaje[i][4],	/*viernes*/
																	escuela[i][5], ocio[i][5], porcentaje[i][5]);	/*sabado*/													
	printf("\n\t >> FIN");
}
int horaClase(int alumno, char datos[maxLineas][maxAlumnos],int pivote[maxLineas]){
	int res, aux, i, j, k, contador = 0;
	int min, max;
	int temp[14] = {NULL};
	char index;

	min = alumno * 14; 
	max = 14 + alumno * 14;

		for (i = min; i < max; i++){
			aux = pivote[i];
				for (j = aux; j < strlen(datos[i]); j++){
					index = datos[i][j];
					if (index == ';') {break;}
					if (index == '-') temp[i - 14 * alumno] = 1;
				}
		}
	for (k = 0; k < 14; k++) if (temp[k] == 0) contador += 1;
	return contador;
}
int horaOcio(int alumno, char datos[maxLineas][maxAlumnos],int pivote[maxLineas]){
	int res, aux, i, j, k, contador = 0;
	int min, max;
	int temp[14] = {0};
	char index;

	min = alumno * 14; 
	max = 14 + alumno * 14;

		for (i = min; i < max; i++){
			aux = pivote[i];
				for (j = aux; j < strlen(datos[i]); j++){
					index = datos[i][j];
					if (index == ';') {break;}
					if (index == '-') temp[i - 14 * alumno] = 1;
				}
		}
	k = 0;
    while(k < 12){	/*una hora de ocio*/
		if (temp[k] == 0 && temp[k + 1] == 1){
			if (temp[k + 2] == 0) contador += 1;
		}
		k++;
	}k = 0;
	while(k < 11){ 	/*dos horas de ocio*/
		if (temp[k] == 0 && temp[k + 1] == 1){
			if (temp[k + 2] == 1 && temp[k + 3] == 0) contador += 2;
		}
		k++;
	}k = 0;
	while(k < 10){ 	/*tres horas de ocio*/
		if (temp[k] == 0 && temp[k + 1] == 1){
			if (temp[k + 2] == 1 && temp[k + 3] == 1){
				if(temp[k + 4] == 0) contador += 3;
			}	
		}
		k++;
	}k = 0;
	while(k < 9){ 	/*cuatro horas de ocio*/
		if (temp[k] == 0 && temp[k + 1] == 1){
			if (temp[k + 2] == 1 && temp[k + 3] == 1){
				if (temp[k + 4] == 1 && temp[k + 5] == 0) contador += 4;
			}	
		}
		k++;
	}k = 0;
	while(k < 8){ 	/*cinco horas de ocio*/
		if (temp[k] == 0 && temp[k + 1] == 1)
			if (temp[k + 2] == 1 && temp[k + 3] == 1){
				if (temp[k + 4] == 1 && temp[k + 5] == 1){
					if(temp[k + 6] == 0) contador += 5;
				}
			}
		k++;
	}k = 0;
	while(k < 7){ 	/*seis horas de ocio*/
		if (temp[k] == 0 && temp[k + 1] == 1){
			if (temp[k + 2] == 1 && temp[k + 3] == 1){
				if (temp[k + 4] == 1 && temp[k + 5] == 1){
					if (temp[k + 6] == 1 && temp[k + 7] == 0) contador += 6;
				}	
			}	
		}
		k++;
	}k = 0;
	return contador;
}
void indice (int lineas, char datos[maxLineas][maxAlumnos],int pivote[maxLineas]){
	int res, i, j, k;
	char index, auxiliar[maxLineas][11] = {NULL};
		for (i = 0; i < lineas; i++){
			for (j = pivote[i]; j < strlen(datos[i]); j++){
				index = datos[i][j];
				if (index == ';') break;
				auxiliar[i][j - pivote[i]] = index;
			}pivote[i] += strlen(auxiliar[i]) + 1;
		}
}
void saltoApivote(int salto[maxAlumnos], int pivote[maxLineas], int numeroAlumnos){
	int i, j, k;
		for (i = 0; i < numeroAlumnos; i++)
				for (j = i * 14; j < 14 + (i) * 14; j++)
					pivote[j]= salto[i];			
}
void separador(int numeroAlumnos, char datos[maxLineas][maxAlumnos],int salto[maxAlumnos]){
	int res, i, j, k;
	char index, auxiliar[maxAlumnos][6] = {NULL};
		for (i = 0; i < numeroAlumnos; i++){
			res = 14 * i;
			for (j = salto[i]; j < strlen(datos[res]); j++){
				index = datos[res][j];
				if (index == ';') break;
				auxiliar[i][j - salto[i]] = index;
			}salto[i] += strlen(auxiliar[i]) + 1;
		}
}
void carrera(int numeroAlumnos, char datos[maxLineas][maxAlumnos], char carreraAlumno[maxAlumnos][51],int salto[maxAlumnos]){
	int res, i, j, k;
	char index;
		for (i = 0; i < numeroAlumnos; i++){
			res = 14 * i;
			for (j = salto[i]; j < strlen(datos[res]); j++){
				index = datos[res][j];
				if (index == ';') break;
				carreraAlumno[i][j - salto[i]] = index;
			}salto[i] += strlen(carreraAlumno[i]) + 1;
		}
}
void claveLarga(int numeroAlumnos, char datos[maxLineas][maxAlumnos], int claveAlumno[maxAlumnos], int salto[maxAlumnos]){
	int res, i, j, k;
	char index, auxiliar[maxAlumnos][6] = {NULL};
		for (i = 0; i < numeroAlumnos; i++){
			res = 14 * i;
			for (j = salto[i]; j < strlen(datos[res]); j++){
				index = datos[res][j];
				if (index == ';') break;
				auxiliar[i][j] = index;
			}salto[i] += strlen(auxiliar[i]) + 1;
			claveAlumno[i] = atoi(auxiliar[i]);

		}
}
void almacenaLineas(char nombreArchivo[a], char cadena[maxLineas][maxAlumnos]){
	/*Almacena Lineas de un  Archivo*/
	FILE *archivo;
		int contador = 0;
	archivo = fopen ( nombreArchivo, "r");
		while(fgets( cadena[contador], maxAlumnos, (FILE*) archivo)) contador++;	
	fclose(archivo);
}
int numeroLineas(char nombreArchivo[a]){
	/*Cuenta Lineas de un  Archivo*/
	FILE *archivo;
		int contador = 0; 
		char cadena[maxAlumnos];
	archivo = fopen ( nombreArchivo, "r");
		while(fgets( cadena, maxAlumnos, (FILE*) archivo)) contador++;
	fclose(archivo);
	return contador;
}
void validarArchivo(char nombreArchivo[a]){
	/*Valida un Archivo*/
	FILE *archivo;
		archivo = fopen(nombreArchivo,"r");
		if (archivo != NULL){
			if (fclose(archivo) != EOF) printf("ok!\n");
			else printf("Error al cerrar\n");
		}else printf("Error al abrir\n");
}
