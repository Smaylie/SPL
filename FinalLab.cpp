// FinalLab.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>

int arbolSPL[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
FILE* fichero = NULL;

void insertar(int valor);
void recorrer(int indice, int valor);
int rotaciones(int indice);
void graph();
void vector();
void graph2(int indice);
void Zig(int hijo, int padre);
void Zag(int hijo, int padre);
void reEnlazarHijos(int viejoIndice, int nuevoIndice);
void buscar(int valor);
void buscarR(int indice, int valor);
int mayorMenor();
void eliminar(int valor);

int main()
{
    //std::cout << "Hello World!\n"; 
	//La raiz es el indice 1, el indice 0 no se toca.
	insertar(5);
	insertar(10);
	insertar(96);
	insertar(30);
	//insertar(2);


	//buscar(5);
	eliminar(10);
	graph();
	vector();
}

void insertar(int valor)
{
	//Creo que puede ir solo recorrer(1,valor), probar después.
	if (arbolSPL[1] != 0) {
		recorrer(1, valor);
	}
	else {
		arbolSPL[1] = valor;
	}
}

void recorrer(int indice,int valor) {
	if (arbolSPL[indice] != 0) {
		if (arbolSPL[indice] != valor) {
			if (valor < arbolSPL[indice]) {//Si es menor camina a la izquierda
				recorrer(indice * 2,valor);
			}
			else {//Sino por la derecha
				int aux = (indice * 2) + 1;
				recorrer(aux,valor);
			}
		}
		//Sino no hace nada porque el número esta repetido
	}
	else {
		arbolSPL[indice] = valor;
		int auxI = indice;
		while (auxI != 1 && auxI != 0) {
			auxI = rotaciones(auxI);
		}	
	}		
}

int rotaciones(int indice) {
	int indicePadre=0;
	int indiceAbuelo=0;
	if (indice % 2 == 0) {//Si es cero  es hijo izquierdo del Padre
		indicePadre = indice / 2;
		if (arbolSPL[indicePadre] != 0) {
			//Zig(indice, indicePadre);
			if (indicePadre % 2 == 0) {//Si es cero el padre es hijo por la izquierda del Abuelo
				indiceAbuelo = indicePadre / 2;
				if (arbolSPL[indiceAbuelo] != 0) {
					Zig(indicePadre, indiceAbuelo);				
					Zig(indice, indicePadre);
					arbolSPL[indice+1] = 0;
					return indiceAbuelo;
				}
				//Si el valor es cero el hijo no tiene Abuelo;
				Zig(indice, indicePadre);
				return indicePadre;
			}
			else {//Sino es cero el padre es hijo por la derecha del Abuelo
				Zig(indice, indicePadre);
				indiceAbuelo = (indicePadre - 1) / 2;
				if (arbolSPL[indiceAbuelo] != 0) {
					Zag(indicePadre, indiceAbuelo);
					return indiceAbuelo;
				}
				//Si el indice es cero el hijo no tiene Abuelo;
				return indicePadre;
			}
		}
		//Si el indice es cero el hijo no tiene Padre
		return 0;
	}
	else {//Sino es hijo derecho del Padre
		indicePadre = (indice - 1) / 2;
		if (arbolSPL[indicePadre] != 0) {
			//Zag(indice, indicePadre);
			if (indicePadre % 2 == 0) {//Si es cero el padre es hijo por la izquierda del Abuelo
				Zag(indice, indicePadre);
				indiceAbuelo = indicePadre / 2;
				if (arbolSPL[indiceAbuelo] != 0) {
					Zig(indicePadre, indiceAbuelo);
					return indiceAbuelo;
				}
				//Si el indice es cero el hijo no tiene Abuelo;
				return indicePadre;
			}
			else {//Sino es cero el padre es hijo por la derecha del Abuelo
				indiceAbuelo = (indicePadre - 1) / 2;
				if (arbolSPL[indiceAbuelo] != 0) {
					Zag(indicePadre, indiceAbuelo);
					Zag(indice, indicePadre);
					arbolSPL[indice+1] = 0;//No probado
					return indiceAbuelo;
				}
				//Si el indice es cero el hijo no tiene Abuelo;
				Zag(indice, indicePadre);
				return indicePadre;
			}
		}
		//Si el valor es cero el hijo no tiene Padre
		return 0;
	}
}

void buscar(int valor) {
	buscarR(1, valor);
}

void buscarR(int indice,int valor) {
	if (arbolSPL[indice] != 0) {
		if (arbolSPL[indice] != valor) {
			if (valor < arbolSPL[indice]) {//Si es menor camina a la izquierda
				buscarR(indice * 2, valor);
			}
			else {//Sino por la derecha
				int aux = (indice * 2) + 1;
				buscarR(aux, valor);
			}
		}
		int auxI = indice;
		while (auxI != 1 && auxI != 0) {
			auxI = rotaciones(auxI);
		}
	}
}

void eliminar(int valor) {
	buscar(valor);
	int aux = mayorMenor();
	arbolSPL[1] = arbolSPL[aux];
	arbolSPL[aux] = 0;
	if (aux % 2 == 0) {
		reEnlazarHijos(aux, 1);
	}
	else {
		if (arbolSPL[aux * 2] != 0) {
			arbolSPL[aux] = arbolSPL[aux * 2];
		}
	}
}

int mayorMenor() {
	int aux = 1 * 2;
	if (arbolSPL[aux] != 0) {
		aux = (aux * 2) + 1;
		while (arbolSPL[aux] != 0) {
			aux = (aux * 2) + 1;
		}
		return (aux - 1) / 2;
	}
	return aux/2;
}

void Zig(int hijo, int padre) {//hijo y padre son indices, no son los valores¡
	int valPadre = arbolSPL[padre];
	int indiceHijoDer = (padre * 2) + 1; //Indice del hijo derecho del padre
	int valHijoDer = arbolSPL[indiceHijoDer];

	reEnlazarHijos(indiceHijoDer,(indiceHijoDer*2)+1);
	reEnlazarHijos((hijo * 2) + 1, indiceHijoDer*2);	

	arbolSPL[padre] = arbolSPL[hijo];
	arbolSPL[padre * 2] = arbolSPL[hijo * 2];
	arbolSPL[indiceHijoDer] = valPadre;

	reEnlazarHijos(hijo * 2, padre * 2);

	arbolSPL[indiceHijoDer * 2] = arbolSPL[(hijo * 2) + 1];
	arbolSPL[(indiceHijoDer * 2) + 1] = valHijoDer;
	
	

	//arbolSPL[hijo * 2] = 0;
	//arbolSPL[(hijo * 2)+1] = 0;
}

void Zag(int hijo, int padre) {
	int valPadre = arbolSPL[padre];
	int indiceHijoIzq = (padre * 2); //Indice del hijo izquierdo del padre
	int valHijoIzq = arbolSPL[indiceHijoIzq];

	reEnlazarHijos(indiceHijoIzq, indiceHijoIzq * 2);
	reEnlazarHijos(hijo * 2, (indiceHijoIzq * 2)+1);	

	arbolSPL[padre] = arbolSPL[hijo];
	arbolSPL[indiceHijoIzq] = valPadre;
	arbolSPL[(padre*2)+1] = arbolSPL[(hijo*2)+1];

	reEnlazarHijos((hijo * 2) + 1, (padre * 2) + 1);

	arbolSPL[indiceHijoIzq * 2] = valHijoIzq;
	arbolSPL[(indiceHijoIzq * 2) + 1] = arbolSPL[hijo*2];


	//arbolSPL[hijo * 2] = 0;
	//arbolSPL[(hijo * 2) + 1] = 0;
}

void reEnlazarHijos(int viejoIndice, int nuevoIndice) {
	int hijoIzq = viejoIndice * 2;
	int hijoDer = (viejoIndice * 2) + 1;
	if (arbolSPL[hijoIzq] != 0) {
		arbolSPL[nuevoIndice * 2] = arbolSPL[viejoIndice * 2];
		arbolSPL[viejoIndice * 2] = 0;
		reEnlazarHijos((viejoIndice * 2) * 2, (nuevoIndice * 2) * 2);
		reEnlazarHijos((((viejoIndice * 2)+1) * 2)+1, (((nuevoIndice * 2)+1) * 2)+1);
	}
	if (arbolSPL[hijoDer] != 0) {
		arbolSPL[(nuevoIndice * 2)+1] = arbolSPL[(viejoIndice * 2)+1];
		arbolSPL[(viejoIndice * 2) + 1] = 0;
		reEnlazarHijos((viejoIndice * 2) * 2, (nuevoIndice * 2) * 2);
		reEnlazarHijos((((viejoIndice * 2) + 1) * 2) + 1, (((nuevoIndice * 2) + 1) * 2) + 1);
	}
}
/*
void buscar(int indice, int valor) {
	if (arbolSPL[indice] != 0) {
		if (arbolSPL[indice] == valor) {

		}
	}
	//Si es 0 el valor no existe
}
*/ 
void graph() {
	if (arbolSPL[1] != 0) {
		fichero = fopen("arbolSPL.dot", "wt");
		fputs("digraph Arbolito { \n graph [ rankdir=\"TB\" , rank = \"same\" ]; \n ", fichero);
		
		graph2(1);

		fputs("}", fichero);
		fclose(fichero);
		system("dot -Tpng arbolSPL.dot -o arbolSPL.png");
		//system("nohup display arbolSPL.png &");
	}
}

void graph2(int indice) {
	if (indice != 0) {
		int izquierdo = indice * 2;
		int derecho = (indice * 2) + 1;
		if (arbolSPL[izquierdo] != 0 && arbolSPL[derecho] != 0) {
			fprintf(fichero, "%d[ label = \"%d\" ]; \n", arbolSPL[indice], arbolSPL[indice]);

			fprintf(fichero, "%d -> %d; \n", arbolSPL[indice], arbolSPL[izquierdo]);
			fprintf(fichero, "%d -> %d; \n", arbolSPL[indice], arbolSPL[derecho]);
			graph2(izquierdo);
			graph2(derecho);
		}
		else if (arbolSPL[izquierdo] != 0) {
			fprintf(fichero, "%d[ label = \"%d\" ]; \n", arbolSPL[indice], arbolSPL[indice]);

			fprintf(fichero, "%d -> %d; \n", arbolSPL[indice], arbolSPL[izquierdo]);
			graph2(izquierdo);
		}
		else if (arbolSPL[derecho] != 0) {
			fprintf(fichero, "%d[ label = \"%d\" ]; \n", arbolSPL[indice], arbolSPL[indice]);

			fprintf(fichero, "%d -> %d; \n", arbolSPL[indice], arbolSPL[derecho]);
			graph2(derecho);
		}
		else {
			fprintf(fichero, "%d[ label = \"%d\" ]; \n", arbolSPL[indice], arbolSPL[indice]);
		}
	}
}

void vector() {
	if (arbolSPL[1] != 0) {
		fichero = fopen("vectorSPL.dot", "wt");
		fputs("digraph Vectorcito { \n graph [ rankdir=\"TB\" , rank = \"same\" ]; \n ", fichero);

		fputs(" struct1 [label=<<TABLE>",fichero);
		int indice;
		for (indice = 1; indice < 15; indice++) {
			fputs("  <TR>",fichero);
			fprintf(fichero, "		<TD> (%d) </TD>",arbolSPL[indice]);
			fputs("   </TR>",fichero);
		}
		fputs("</TABLE>>];",fichero);

		fputs("}", fichero);
		fclose(fichero);
		system("dot -Tpng vectorSPL.dot -o vectorSPL.png");
		//system("nohup display arbolSPL.png &");
	}

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
