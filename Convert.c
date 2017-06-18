/*
 * Convert.c
 * 
 * Copyright 2016 Luis <luis@luis-VirtualBox>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

//Las librerias a usar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*////////////////////////////////////////////////////////////////////////ESTRUCTURA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
struct numba { //Estructura dela lista de numeros
	int num; //entero de la lista
	struct numba *siguiente;//apunta a el siguiente nodo de la lista
	struct numba *previo;//apunta a el previo
};

/*////////////////////////////////////////////////////////////////////////DEFINICION DE TIPOS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
typedef struct numba numLista; //definicion de estructura
typedef numLista *ptrNumLista; //Puntero a la estructura
/*////////////////////////////////////////////////////////////////////////FUNCIONES\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
ptrNumLista toB(numLista** numero); //Convierte el numero a binario
ptrNumLista toBUp(numLista** numero); //convierte la parte entra a binario
ptrNumLista toBDn(numLista** numero);//convierte la parte despues del punto a binario
ptrNumLista copiaD(numLista** lista);//hace una copia de un numero y se lo asigna a otro puntero, util en funciones que afectan al original como la resta
ptrNumLista toD(numLista** numero);//convierte el numero a decimal
ptrNumLista getLargestBit(numLista** numeroDec);//saca el bit mas grande, el priemro para convertir
void agregarNodo(int x,ptrNumLista *Cabeza);//agerga un nodo al final de la lista
void agregarNodoR(int x,ptrNumLista *Cabeza);//Misma funcionalidad de la funcion anterior, pero la R se refiere a reverso(al principio)
ptrNumLista crearNodo(int x);//crea un nodo y lo devuelve
void irPrincipio(numLista** comienzo);//va al prinicipio de la lista
void quitarceros(numLista** lista);//quitalos ceros de de la lista
void irFinal(numLista** final);//va al final de la lista
void ponerNumLista(char* n,numLista** numero);//Convierte el char a una lista
int getLenDpsPto(numLista** lista);//saca el largo antes del punto (decimales)
int getLenAtsPto(numLista** lista);//saca el largo despues del punto (enteros)
void ponerListaAtsPto(numLista** lista);//pone la lista entes del punto, en posicion
void agregarPto(int x,numLista** resultado);//agrega un punto al final de la lista
int tienePto(numLista** lista);//detecta si la lista tiene un punto o no
void printNum(numLista** lista);// iprime el numero(lista)
void printNumResp(numLista** resp,numLista** pres);//imprime la respuesta con la preciocion que requiere el usuario
ptrNumLista controlCtre(numLista** primerNum,numLista** segundoNum,int operacion);//encargado de decidir que se hace con los numeros
int cualEsMasGrande(numLista** primerNum,numLista** segundoNum);//devuelve cual numero es mas grande, con las entradas cuales se van acomparar
int isZero(numLista** numero);//revisa si el numero es igual a cero
ptrNumLista elevar(numLista** poder,numLista** numeroAEl);//eleva un numero al poder q se quiere, ej 2^2 = 4
ptrNumLista sumar(numLista** primerNum,numLista** segundoNum);//suma dos listas
void sumarAntsPto (numLista** numUno,numLista** numDos,numLista** suma,int carry);//se encarga de sumar antes del punto, los enteros
int sumarDspsPto (numLista** numUno,numLista** numDos,numLista** suma);//suma despues del punto los flotantes
int sumarAux(int numUno,int numDos,numLista** suma,int carry);//se encarga de sumar dos numeros, es la base de la suma
ptrNumLista restar(numLista** primerNum,numLista** segundoNum,int flag2);//resta dos numeros
void restarAux(numLista** numeroMasG,numLista** numeroPeq,numLista** resp);//basede la resta, toma todas las desiciones
ptrNumLista multiplicar(numLista** primerNum,numLista** segundoNum);//multiplica dos numeros
int multiplicarAux(int x,int y,int carry,numLista** resultado);//es la base de la multiplicacion
ptrNumLista dividir(numLista** primerNum,numLista** segundoNum);// se encarga de dividir dos numeros
/*////////////////////////////////////////////////////////////////////////GLOBALES\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
int bin = 0;//es una variablebooleana encargada de saber si el numero esta en binario o no
/*////////////////////////////////////////////////////////////////////////MAIN\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
int main(){ //int argc, char **argv
	char number[500];//arreglo de chares encargada de tener el numero en char
	char operacion[5];// char que decidela operaciones
	printf("El numero es de base 2? (s = si)");
	scanf("%s",number);//le asigna el valor a la variable numero
	if(number[0] == 115)//si es S (en ascii) se asigna uno a la condicion booleana de binario
		bin = 1;
	printf("Ingrese el primer numero");//Se pide el primer numero
	scanf("%s",number);//seleasigna esta a la variable
	ptrNumLista numUno = NULL;//Puntero a la primer lista
	ptrNumLista numDos = NULL;//puntero a la segunda lista
	ptrNumLista respuesta = NULL;//va a contener la lista de respuesta
	ptrNumLista precision = NULL;//va a tener una lista de precicoin,(en decimales) si es negativa se ignora la precicion
	ponerNumLista(number,&numUno);//llama a la funcion que pone al char en una lista
	//respuesta = toB(&numUno);
	//printNum(&respuesta);
	printf("Ingrese el segundo numero");//pide al segundo numero
	scanf("%s",number);//pone a este al char
	ponerNumLista(number,&numDos);//pone al segundo numero en la lista
	printNum(&numUno);irFinal(&numUno);//al quitar printNum, asegurarse de dejar el ir al final
	printNum(&numDos);irFinal(&numDos);// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	printf("Ingrese la operacion deseada (+,-,*,/)((o(r) n(ot) a(nd)) (el not ignora el segundo numero) a = and....");//pide la operacion
	scanf("%s",operacion);//pone la operacion al char de operacion
	respuesta = controlCtre(&numUno,&numDos,operacion[0]);//manda las listas y la operacion al "centro de control"
	printf("Ingrese la precisión(negativo para dar completo)");//pide la precicoin al usuario
	scanf("%s",number);// se la asigna a la variable
	ponerNumLista(number,&precision);//pone la presicion a la lista
	printf("resultado\n");//imprime para dar el resultado
	printNum(&respuesta);
	//quitarceros(&respuesta);//quita los ceros a la respuesta
	//printNumResp(&respuesta,&precision);//e imprime la respuesta
	return 0;//retorna cero, termino bien las funciones
}

/*////////////////////////////////////////////////////////////////////////FUNCIONES BINARIAS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
ptrNumLista toB(numLista** numero){//pone el numero decimal a binario
	ptrNumLista enB = NULL;
	ptrNumLista enBEnt = NULL;
	ptrNumLista enBPto = NULL;
	ptrNumLista numeroEnt = NULL;
	ptrNumLista numeroPto = NULL;
	numeroEnt = numeroPto = copiaD(numero);
	irPrincipio(&numeroEnt);
	irFinal(&numeroPto);
	if(tienePto(numero) == 1){//en caso de que tenga puntos se da esta funcion
		while(numeroEnt->num != 46){
			numeroEnt = numeroEnt->siguiente;
		}
		while(numeroPto->num != 46){
			numeroPto = numeroPto->previo;
		}
		numeroEnt = numeroEnt->previo;
		numeroEnt->siguiente = NULL;
		numeroPto->previo = NULL;
		agregarNodoR(0,&numeroPto);
		enBEnt = toBUp(&numeroEnt);
		enBPto = toBDn(&numeroPto);
		enB = sumar(&enBEnt,&enBPto);
	}
	else//en caso de que no se da esta, siempre se da a menos de que sea 0.xxxx
		enB = toBUp(&numeroEnt);
	return enB;
}
ptrNumLista toBUp(numLista** numero){//pone los bits para arriba del punto
	irPrincipio(numero);
	*numero = (*numero)->siguiente;//quita el punto o signal flag
	(*numero)->previo = NULL;
	ptrNumLista binEnt = NULL;//punteros a usar, uno y dos son para operar
	ptrNumLista bitAct = getLargestBit(numero);
	ptrNumLista pasar = copiaD(&bitAct);//copias son para realizar restas y demas
	ptrNumLista dos = crearNodo(2);
	ptrNumLista uno = crearNodo(1);
	ptrNumLista elevado = elevar(&pasar,&dos);//elevado para tener los bits actuales
	ptrNumLista copiaNum = NULL;
	while(isZero(&bitAct) != 1){//bucle que se da hasta que sea cer el resultado
		copiaNum = copiaD(numero);
		pasar = restar(&copiaNum,&elevado,43);
		irPrincipio(&pasar);
		if(pasar->num == 45)//pone un cer si la resta es negativa
			agregarNodo(0,&binEnt);
		else{//si esta no es mas grande pone un 1 significando que hay un bit ahi
			agregarNodo(1,&binEnt);
			if(isZero(&pasar) == 1){
				while(isZero(&bitAct) != 1){
					agregarNodo(0,&binEnt);
					pasar = restar(&bitAct,&uno,43);
					bitAct = pasar;
				}
				break;
			}
			*numero = pasar;
		}
		pasar = restar(&bitAct,&uno,43);
		bitAct = pasar;
		elevado = elevar(&bitAct,&dos);
		bitAct = pasar;
	}
	if((*numero)->num == 1)//si hay un carry entonces se pone
		agregarNodo(1,&binEnt);
	return binEnt;
}
ptrNumLista toBDn(numLista** numero){//pone los bits despues del punto
	ptrNumLista binFlt = NULL;//respuesta (este se va a retornar)
	ptrNumLista copNum = NULL;
	ptrNumLista dos = crearNodo(2);//dos para elevar
	agregarNodo(0,&binFlt);//se pone los puntos para nada mas sumar con los bits de la funcion anterior
	agregarNodo(46,&binFlt);
	for(int i = 0;isZero(numero) != 1;i++){//resta hasta que haya un cero, significa que no hay mas bits
		copNum = copiaD(numero);
		*numero = multiplicar(&copNum,&dos);
		irPrincipio(numero);
		if((*numero)->num == 1){
			agregarNodo(1,&binFlt);
			(*numero)->num = 0;
		}
		else
			agregarNodo(0,&binFlt);
		if(i / 45 == 0){//si se volvio una resta infinita se pide al usurio si quiere terminarla
			char yoN[5];
			printf("La respuesta va asi: ");
			printNum(&binFlt);
			printf("desea dejarla asi? (s = si)");
			scanf("%s",yoN);
			if(yoN[0] == 115)
				break;
		}
		if( i == 500)
			break;
	}
	return binFlt;
}
ptrNumLista getLargestBit(numLista** numeroDec){//saca el bit mas grande
	ptrNumLista pasar = copiaD(numeroDec);//punteros a usar, uno es nada mas uno, dos tambien
	ptrNumLista respu = crearNodo(0);//respuesta nicializada en 0 para poder suamr
	ptrNumLista chequeo = NULL;//un chqueo paraver si la respuestaes negativa (significa queya se alcanzo al bit mas grande)
	ptrNumLista elevado = crearNodo(1);
	ptrNumLista dos = crearNodo(2);
	ptrNumLista uno = crearNodo(1);
	while(1){// va restando los bits para poder alcanzar adonde se debe
		chequeo = restar(&pasar,&elevado,43);
		irPrincipio(&chequeo);
		if(chequeo->num == 45 || isZero(&chequeo) ==1)//verifica ceros y negativos la condicion de parada
			break;
		if(chequeo->siguiente != NULL){//si no hay adonde seguir significa que ya se debe parar
			if(chequeo->num == 0 && chequeo->siguiente->num == 46)
				break;
		}
		chequeo = sumar(&respu,&uno);//se pasa de chequeo a respuesta
		respu = chequeo;
		pasar = elevar(&respu,&dos);//seincrementa uno a respuesta
		respu = chequeo;
		elevado = pasar;
		pasar = copiaD(numeroDec);
	}
	return respu;//retorna una respuesta
}
void not(numLista** num){//cambia los valoresde 0 a uno y 1 a cero
	irPrincipio(num);
	while(1){
		if((*num)->num == 1)//1 a 0
			(*num)->num = 0;
		else//0 a 1
			(*num)->num = 1;
		if((*num)->siguiente == NULL)
			break;
		*num = (*num)->siguiente;
	}
}
ptrNumLista and(numLista** num1, numLista** num2){//
	ptrNumLista resp = NULL;
	ptrNumLista num1Pto = NULL;
	ptrNumLista num2Pto = NULL;
	if (tienePto(num1) == 1 || tienePto(num2) == 1 ){//verifica si hay puntos y como se deben de taratar
		if((*num1)->num == 46){
			num1Pto = *num1;
			*num1 = (*num1)->previo;
			(*num1)->siguiente = NULL;
			num1Pto = num1Pto->siguiente;
			num1Pto->previo = NULL;
		}
		if((*num2)->num == 46){
			num2Pto = *num2;
			*num2 = (*num2)->previo;
			(*num2)->siguiente = NULL;
			num2Pto = num2Pto->siguiente;
			num2Pto->previo = NULL;
		}
	}
	if( num1Pto!=NULL || num2Pto!=NULL){//se hace con los decimales
		while(1){//es diferene en la recorrida ya que esta va para adelante en contraste de para atras
			if(num1Pto->num == 1 && num2Pto->num == 1)
				agregarNodo(1,&resp);
			else
				agregarNodo(0,&resp);
			if(num1Pto->siguiente == NULL || num2Pto->siguiente == NULL)//si alguno es nulo se sige al siguiente bucle/s
				break;
			num1Pto = num1Pto->siguiente;
			num2Pto = num2Pto->siguiente;
		}
		while(num1Pto->siguiente != NULL){//se agregan ceros ya que se compara con solo ceros
			num1Pto = num1Pto->siguiente;
			agregarNodo(0,&resp);
		}
		while(num2Pto->siguiente != NULL){
			num2Pto = num2Pto->siguiente;//se agregan ceros hasta que se termie
			agregarNodo(0,&resp);
		}
		irPrincipio(&resp);
		agregarNodoR(46,&resp);
	}
	while(1){//mismo que lo anterior pero con enteros
		if((*num1)->num == 1 && (*num2)->num == 1)
			agregarNodoR(1,&resp);
		else
			agregarNodoR(0,&resp);
		if((*num1)->previo == NULL || (*num2)->previo == NULL)
			break;
		(*num1) = (*num1)->previo;
		(*num2) = (*num2)->previo;
		}
		while((*num1)->previo != NULL){
			(*num1) = (*num1)->previo;
			agregarNodoR(0,&resp);
		}
		while((*num2)->previo != NULL){
			(*num2) = (*num2)->previo;
			agregarNodoR(0,&resp);
		}
	return resp;
}
ptrNumLista or(numLista** num1, numLista** num2){//funcion de or, muy parecida a el and, solo cambian en lo comentado, para refencia ver and
	ptrNumLista resp = NULL;
	ptrNumLista num1Pto = NULL;
	ptrNumLista num2Pto = NULL;
	if (tienePto(num1) == 1 || tienePto(num2) == 1 ){
		if((*num1)->num == 46){
			num1Pto = *num1;
			*num1 = (*num1)->previo;
			(*num1)->siguiente = NULL;
			num1Pto = num1Pto->siguiente;
			num1Pto->previo = NULL;
		}
		if((*num2)->num == 46){
			num2Pto = *num2;
			*num2 = (*num2)->previo;
			(*num2)->siguiente = NULL;
			num2Pto = num2Pto->siguiente;
			num2Pto->previo = NULL;
		}
	}
	if( num1Pto!=NULL || num2Pto!=NULL){
		while(1){
			if(num1Pto->num == 1 || num2Pto->num == 1)//unica diferencia es si uno de los dos es 1 se agrega
				agregarNodo(1,&resp);
			else
				agregarNodo(0,&resp);
			if(num1Pto->siguiente == NULL || num2Pto->siguiente == NULL)
				break;
			num1Pto = num1Pto->siguiente;
			num2Pto = num2Pto->siguiente;
		}
		while(num1Pto->siguiente != NULL){//esto tambien en que se agregan si hay un nuo en vesz de solo ceros
			num1Pto = num1Pto->siguiente;
			agregarNodo(num1Pto->num,&resp);
		}
		while(num2Pto->siguiente != NULL){//ver ciclo anterios pero con segundo numero
			num2Pto = num2Pto->siguiente;
			agregarNodo(num2Pto->num,&resp);
		}
		irPrincipio(&resp);
		agregarNodoR(46,&resp);
	}
	while(1){//ahora con los enteros
		if((*num1)->num == 1 || (*num2)->num == 1)
			agregarNodoR(1,&resp);
		else
			agregarNodoR(0,&resp);
		if((*num1)->previo == NULL || (*num2)->previo == NULL)
			break;
		(*num1) = (*num1)->previo;
		(*num2) = (*num2)->previo;
		}
		while((*num1)->previo != NULL){
			(*num1) = (*num1)->previo;
			agregarNodoR((*num1)->num,&resp);
		}
		while((*num2)->previo != NULL){
			(*num2) = (*num2)->previo;
			agregarNodoR((*num2)->num,&resp);
		}
	return resp;
}
/*////////////////////////////////////////////////////////////////////////FUNCIONES DECIMALES\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
ptrNumLista toD(numLista** numero){//convierte a decimal
	ptrNumLista enBin = NULL;//los punteros a usar
	ptrNumLista pasar = NULL;//este es un paso intermedio entre funciones
	ptrNumLista pot = crearNodo(0);
	ptrNumLista uno = crearNodo(1);//punteros para usar como funciones ej. restar uno, multiplicar por dos
	ptrNumLista dos = crearNodo(2);
	ptrNumLista suma = crearNodo(0);//paso intermedio
	ptrNumLista copiaEnt = copiaD(numero);//para poder operarse
	ptrNumLista copiaPto = NULL;
	if(tienePto(&copiaEnt) == 1){//quita el punto para operarse por separado
		copiaPto = copiaEnt;
		copiaEnt = copiaEnt->previo;
		copiaEnt->siguiente = NULL;
		copiaPto->previo = NULL;
		//while(1){
			//pasar = copiaD(&pot);
			//pot = sumar(&pasar,&uno);
			//if(copiaPto->siguiente== NULL) break;
		//}
	}
	while(1){//este bucle va a transformar a decimal
		pasar = copiaD(&pot);
		pot = sumar(&pasar,&uno);
		pasar = elevar(&pot,&dos);
		suma = copiaD(&enBin);
		if(copiaEnt->num == 1)//se suma el poder del momento si hay uno, ej 01100 serian 2^3 y 2^4
			enBin = sumar(&pasar,&suma);
		if(copiaEnt->siguiente == NULL) break;//si no hay numero se termina el bucle
		copiaEnt = copiaEnt->previo;
	}
	return enBin;
}
/*////////////////////////////////////////////////////////////////////////FUNCIONES ARITMETICAS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
//Decision de funciones
ptrNumLista controlCtre(numLista** primerNum,numLista** segundoNum,int operacion){//controla tanto los signal flags como las funciones
	ptrNumLista copias = copiaD(primerNum);
	ptrNumLista resp = NULL;
	irPrincipio(primerNum);
	irPrincipio(segundoNum);
	int sigFl1 = (*primerNum)->num;//agarra y quita los signal flags al mismo tiempo esto para la poperacion de losmismos
	int sigFl2 = (*segundoNum)->num;
	(*primerNum) = (*primerNum)->siguiente;
	(*segundoNum) = (*segundoNum)->siguiente;
	(*primerNum)->previo = NULL;
	(*segundoNum)->previo = NULL;
	if(operacion == 43 || operacion ==42 || operacion ==45 ||operacion ==47){
		if(bin == 1){
			*primerNum = toD(&copias);
			copias = copiaD(segundoNum);
			*segundoNum = toD(&copias);
		}
	if (operacion == 43){ //SUMA
		if(sigFl1==sigFl2){
			resp = sumar(primerNum,segundoNum);
			if(sigFl1 == 45)
				agregarNodoR(45,&resp);
		}
		else{//segun los signal flags se llama a esta
			agregarNodoR(sigFl1,primerNum);
			agregarNodoR(sigFl1,segundoNum);
			resp = controlCtre(primerNum,segundoNum,45);
		}
	}
	else if (operacion == 42){//MULTIPLICAR
		resp = multiplicar(primerNum,segundoNum);
		irPrincipio(&resp);
		if(sigFl1!=sigFl2)
			agregarNodoR(45,&resp);
		}
	else if (operacion == 45){//RESTAR
		if(sigFl1!=sigFl2){
			agregarNodoR(sigFl1,primerNum);
			agregarNodoR(sigFl1,segundoNum);
			resp = controlCtre(primerNum,segundoNum,43);
		}
		else
			resp = restar(primerNum,segundoNum,sigFl2);
	}
	else if (operacion == 47){//DIVISION
		resp = dividir(primerNum,segundoNum);
		}
	}
	else{
		if(bin == 0){//transforma a binario para operar estas funciones
			*primerNum = toB(&copias);
			copias = copiaD(segundoNum);
			*segundoNum = toB(&copias);
		}
		if(operacion == 110){//NOT
			not(primerNum);
			resp = *primerNum;
		}
		else if(operacion == 111)//OR
			resp = or(primerNum,segundoNum);
		else if(operacion == 97)//And
			resp = and(primerNum,segundoNum);
		else{//si no se reconoce la funcion manda error y se recomienza
			printf("funcion no reconocida se retornara cero!!");
			printf("Respuesta\n0");
			main();
		}
		copias = copiaD(&resp);
	}
	return resp;
}
int cualEsMasGrande(numLista** primerNum,numLista** segundoNum){//fucnion que retorna si el segundo o promero es mas grande
	irPrincipio(primerNum);//para operar
	irPrincipio(segundoNum);
	if((*primerNum)->num == 0){//revisa que haya algun 0.xxxx
		if((*primerNum)->siguiente->num == 46 && tienePto(segundoNum) == 0)
			return 2;
	}
	if((*segundoNum)->num == 0){//revisa que hayan 0.0
		if((*segundoNum)->siguiente->num == 46 && tienePto(primerNum) == 0 )
			return 1;
	}
	irPrincipio(primerNum);//para operar
	irPrincipio(segundoNum);
	while(1){//el mas grande se va a revisar segun el tamanho de la lista si alguna es mas large y no tiene el punto primero se determina la mas grande
		if (((*primerNum)->siguiente == NULL && (*segundoNum)->siguiente == NULL) || ((*primerNum)->num == 46 && (*primerNum)->num == 46))
			break;
		else if(((*primerNum)->siguiente == NULL) || (*primerNum)->num == 46)
			return 2;
		else if((*segundoNum)->siguiente == NULL || (*segundoNum)->num == 46)
			return 1;
		*primerNum = (*primerNum)->siguiente;
		*segundoNum = (*segundoNum)->siguiente;
	}
	irPrincipio(primerNum);//para operar
	irPrincipio(segundoNum);
	while(1){//revisa si uno es mas grande que el otro si este es el caso se retorna 1 sifue el primero y dos si fuel el seguno
		if((*primerNum)->num > (*segundoNum)->num)
			return 1;
		else if((*primerNum)->num < (*segundoNum)->num)
			return 2;
		else if((*primerNum)->siguiente == NULL || (*segundoNum)->siguiente == NULL)//si se indefinin los dos se quiebra el ciclo
			break;
		*primerNum = (*primerNum)->siguiente;
		*segundoNum = (*segundoNum)->siguiente;
	}
	return 3;//si los dos son iguales se retorna 3
}
int isZero(numLista** numero){//Condicion Booleana que revisa que un numero no sea 0
	irPrincipio(numero);
	while((*numero)->num == 0 || (*numero)->num == 46){//bucle que se cumple siempre y cuando haya un cero, el momento que esto cambie se retorna un 0
		if((*numero)->siguiente == NULL)//si termino y no habian nada mas que ceros y puntos se retorna true
			return 1;
		(*numero) = (*numero)->siguiente;
	}
	return 0;//si no false
}
//sumar
ptrNumLista sumar(numLista** primerNum,numLista** segundoNum){//controla todas las funciones de sumar
	ptrNumLista suma = NULL;//se retornara este puntero
	int carry = 0;//carry "flag" indica si hay carry
	if(tienePto(primerNum) == 1 || tienePto(segundoNum) == 1){//si hay floats se llama a esta funcion
		carry = sumarDspsPto (primerNum,segundoNum,&suma);
		agregarNodoR(46,&suma);
		}
	sumarAntsPto(primerNum,segundoNum,&suma,carry);//se llama a la funcion de sumar normal
	return suma;
}
int sumarDspsPto (numLista** numUno,numLista** numDos,numLista** suma){//suma despes del punto los flotantes
	int len1 = getLenDpsPto(numUno);//saca los dos floats para ver cual es mas pquenho
	int len2 = getLenDpsPto(numDos);
	irFinal(numUno);//se ponen al principio para operar
	irFinal(numDos);
	int carry = 0;
	while(len1>len2){//si un flotante es mas peqienho se ponelos restantes al principio
		agregarNodoR((*numUno)->num,suma);
		*numUno = (*numUno)->previo;
		len1--;
	}
	while(len1<len2){//los mismo que el pasado pero con num 2
		agregarNodoR((*numDos)->num,suma);
		*numDos = (*numDos)->previo;
		len2--;
	}
	if(len1 + len2 >0){//revisa que hayan flotantes
		carry = sumarAux((*numUno)->num,(*numDos)->num,suma,carry);//hace una suma
		while((*numUno)->previo->num != 46 && (*numDos)->previo->num != 46){//revisa que no hayan puntosy los brinca
			*numUno = (*numUno)->previo;//sigue al siguiente si no se da
			*numDos = (*numDos)->previo;
			carry = sumarAux((*numUno)->num,(*numDos)->num,suma,carry);//se llama a la suma
		}
	}
	return carry;
}
void sumarAntsPto (numLista** numUno,numLista** numDos,numLista** suma,int carry){ //Suma de dos lista, los numeros de adentro antes (osea enteros, no decimales) del punto decimal
	if((*suma) != NULL){//revisa que no haya flotantes en respuesta
		irPrincipio(suma);
	}	
	ponerListaAtsPto(numUno);
	ponerListaAtsPto(numDos);
	while(1){//bucle que recorre el corazon de la lista
		carry = sumarAux((*numUno)->num,(*numDos)->num,suma,carry);//carry se define mientras este mismo se cambia dentro del mismo
		if((*numUno)->previo == NULL || (*numDos)->previo == NULL)//si uno se termina, se termina el bucle y el remainder se toma encuenta en los siguietnes bucles
			break;
		*numUno = (*numUno)->previo;//se recorre el ciclo
		*numDos = (*numDos)->previo;
	}
	while(1){//bucle somo el siguiente pero este lo hacer para el primer num a diferencia del siguietne que lo hace para el segundo
		if((*numUno)->previo == NULL)
			break;
		*numUno = (*numUno)->previo;
		carry = sumarAux((*numUno)->num,0,suma,carry);
	}	
	while(1){//bucle que pone el numero mas grande son los sobrantes ej 1111 + 2 el sobrante es 1111 y las suma es 3
		if((*numDos)->previo == NULL)
			break;
		*numDos = (*numDos)->previo;
		carry = sumarAux(0,(*numDos)->num,suma,carry);
	}
	if(carry !=0)
		agregarNodoR(carry,suma);//si no hay carry no se ocupa agregar al final
}
int sumarAux(int numUno,int numDos,numLista** suma,int carry){//
	if ((numUno + numDos + carry) >= 10){//si elcarry maslos dos numeros es menor a dies se pone normalmente
		agregarNodoR((numUno + numDos + carry - 10),suma);
		return 1;
	}
	else//si es mayor se pone un carry
		agregarNodoR((numUno + numDos + carry),suma);
		return 0;
}
//restar
ptrNumLista restar(numLista** primerNum,numLista** segundoNum,int flag2){//controla lafuncion de restar, ejemplo pone lo debido adonde debe de ir
	ptrNumLista respuesta = NULL;//puntero que se va a devolver
	quitarceros(primerNum);//quita los ceros a los dso
	quitarceros(segundoNum);
	irPrincipio(primerNum);//va a los principios de los dos para ser operados
	irPrincipio(segundoNum);
	if(isZero(primerNum) == 1){//verifica que no sea cero el primero
		respuesta = copiaD(segundoNum);
		irPrincipio(&respuesta);
		agregarNodoR(45,&respuesta);
	}
	if(isZero(segundoNum) == 1){//ve si el segundo no es cero
		respuesta = copiaD(primerNum);
		irPrincipio(&respuesta);
	}
	else if(cualEsMasGrande(primerNum,segundoNum) == 2){//revisa cual es mas grande para saber como se va a operar
		restarAux(segundoNum,primerNum,&respuesta);
		agregarNodoR(45,&respuesta);
	}
	else
		restarAux(primerNum,segundoNum,&respuesta);//si el segundo es mas pequeno se resta al primero
	return respuesta;
}
void restarAux(numLista** numeroMasG,numLista** numeroPeq,numLista** resp){//corazon de la resta, hacelas restar y decisiones directas
	int lenGra = getLenDpsPto(numeroMasG);//saca los dos length de los floats
	int lenPeq = getLenDpsPto(numeroPeq);
	ptrNumLista recorrida = NULL;
	irFinal(numeroMasG);//se poenen los doa a principio para poder operar bien
	irFinal(numeroPeq);
	while(lenGra>lenPeq ){//se agregan ceros para poder restar bien de grande a pequenho
		if(tienePto(numeroPeq) == 0)
			agregarNodo(46,numeroPeq);
		irFinal(numeroPeq);
		agregarNodo(0,numeroPeq);
		lenGra--;
	}
	while(lenGra<lenPeq){//se agregan ceros para poder restar bien de pequenho a grande
		if(tienePto(numeroMasG) == 0)
			agregarNodo(46,numeroMasG);
		irFinal(numeroMasG);
		agregarNodo(0,numeroMasG);
		lenPeq--;
	}
	irFinal(numeroMasG);
	irFinal(numeroPeq);
	while(1){
		if((*numeroMasG)->num == 46)//si hay un punto se ignora esta resta
			agregarNodoR(46,resp);
		else if((*numeroMasG)->num - (*numeroPeq)->num >= 0)//si se puede restar sin pedir prestado nada mas se resta los actuales
			agregarNodoR((*numeroMasG)->num - (*numeroPeq)->num,resp);
		else if ((*numeroMasG)->num - (*numeroPeq)->num < 0){//le pide prestado si el pequenho es mas grande que el grande(en las posiciones actuales)
			agregarNodoR(10 + (*numeroMasG)->num - (*numeroPeq)->num,resp);
			recorrida = (*numeroMasG)->previo;
			while(recorrida->num == 0 || recorrida->num == 46){//mientras hayan ceros no se piden prestados
				if(recorrida->num == 0)
					recorrida->num = 9;
				recorrida = recorrida->previo;
			}
			recorrida->num--;//le pide prestado al siguiente numer
		}
		if((*numeroPeq)->previo == NULL)//el momento que pequenho se termine se termina la recorrida
			break;
		*numeroMasG = (*numeroMasG)->previo;//va al precio de la dos listas
		*numeroPeq = (*numeroPeq)->previo;
	}
	irPrincipio(resp);
	while(1){//si el numero mas grande sigue se ponen cuantos sigan
		if((*numeroMasG)->previo == NULL)
			break;
		*numeroMasG = (*numeroMasG)->previo;
		agregarNodoR((*numeroMasG)->num,resp);
	}
}
//multiplicar
ptrNumLista multiplicar(numLista** primerNum,numLista** segundoNum){//multiplica las dos listas
	ptrNumLista primerM = NULL;//guarda al primer multiplo de la multiplicacion al cual se le va a agrega el segundo
	int carry = 0;//define al carry,
	irFinal(primerNum);//pone al final para operar
	for(int i = 0;;i++){//bucle, el i es para debuggear
		if((*primerNum)->num == 46)//se ignora el punto
			*primerNum =(*primerNum)->previo;
		ptrNumLista segundM = NULL;//segundo multiplo encargado de ser dumado al primero
		ptrNumLista sumaD2 = NULL;//lista que va a mantener la suma antes de pasarla al primer multiplo
		irFinal(segundoNum);
		for(int j = 0; j<i ;j++){//agrega los nodos o ceros para el segundo numero entre multiplicaciones
			agregarNodoR(0,&segundM);
		}
		while(1){
			if((*segundoNum)->num== 46)//se ignora el punto
				(*segundoNum) = (*segundoNum)->previo;
			if(i==0)//si es cero nada mas se ponene ceros
				carry = multiplicarAux((*primerNum)->num,(*segundoNum)->num,carry,&primerM);
			else//si no se da ninguno estonces este es la opcion default0
				carry = multiplicarAux((*primerNum)->num,(*segundoNum)->num,carry,&segundM); //multliplica los dos multiplos
			if((*segundoNum)->previo == NULL)//termina si no hay nada mas en la segunda lsita
				break;
			*segundoNum = (*segundoNum)->previo;
		}
		if(i==0){//se pone al carry al unltimo de la respuesta si hay carry por ejemplo 4 * 3 = 12 1 es carry
			if(carry > 0)
				agregarNodoR(carry,&primerM);
		}
		else{//si i no es cero significa que hay mas que agregar
			if(carry > 0)
				agregarNodoR(carry,&segundM);
			sumarAntsPto(&primerM,&segundM,&sumaD2,0);
			primerM = sumaD2;
		}
		carry = 0;//carry se pondria como 0
		if((*primerNum)->previo == NULL)//revida que el previo sea nulo
			break;
		*primerNum=(*primerNum)->previo;//si no lo pone como siguiente
	}
	agregarPto(getLenDpsPto(primerNum)+getLenDpsPto(segundoNum),&primerM);//pine al punto
	return primerM;//retorna la multiplicacion
}
int multiplicarAux(int x,int y,int carry,numLista** resultado){//corazon de la multiplicaicon
	if(x*y+carry >=10){//si la multiplicacion es mayor a dis se le smia al siguiente
		agregarNodoR((x*y+carry)%10,resultado);
		carry = (x*y+carry)/10;//pone a carry hacia el siguiente
		return carry;
	}
	agregarNodoR(x*y+carry,resultado);//agrega el resultado
	return 0;
}
void agregarPto(int x,numLista** resultado){//agrega un punto a la lista
	if(x==0)//condision de para si x es cerp
		return;
	irFinal(resultado);//se pone a final para poder trabajarlo
	for(int i=1;i<x;i++){//ciclo que decide adonde poner el punto
		*resultado = (*resultado)->previo;
	}
	ptrNumLista ptrPto = crearNodo(46);
	ptrNumLista nuevo = (*resultado)->previo;//puntero al cual va a ayudar a meter el punto
	nuevo->siguiente = ptrPto;
	ptrPto->siguiente = *resultado;//pone el punto entre los dos numeros
	ptrPto->previo = nuevo;
	(*resultado)->previo = ptrPto;
}
//Dividir
ptrNumLista dividir(numLista** primerNum,numLista** segundoNum){//divide las dos listas
	ptrNumLista agregar = crearNodo(1);
	ptrNumLista resp = crearNodo(0);
	ptrNumLista chequeo = crearNodo(1); //ptr que revise que la respuesta es mayor a cero
	ptrNumLista ceroPtoUno = NULL; //se usa para mover los numeros un digito a la derecha (9 = 0.9)
	ptrNumLista pasar = NULL; //Se usa para pasar de un dato a otro
	ponerNumLista("0.1",&ceroPtoUno);
	irPrincipio(&ceroPtoUno);
	pasar = ceroPtoUno;//variable de multiplicar 0.1
	ceroPtoUno = ceroPtoUno->siguiente;
	ceroPtoUno->previo = NULL;
	pasar->siguiente = NULL;
	if((*segundoNum)->num == 1){//division entre 1
		if((*segundoNum)->siguiente == NULL)//si es nada mas uno se retorna el primer numero
			return *primerNum;
		*segundoNum = (*segundoNum)->siguiente;
		if((*segundoNum)->num == 46){//chequea que es 1.0000000.....
			*segundoNum = (*segundoNum)->siguiente;
			while((*segundoNum)->num != 0){
				*segundoNum = (*segundoNum)->siguiente;
				if((*segundoNum)->siguiente == NULL) return *primerNum;//si se da retorna el primr numero
			}
		}
	}
	if(isZero(segundoNum)){//evalua division entre cero
			printf("error division entre cero, se retonera cero!!\n");//eror de division enttre cero
			return resp;
	}
	for(int i = 0;isZero(primerNum) != 1;i++){//bucle siempre que la division no de cero
		ptrNumLista copia = copiaD(primerNum);//copia porq resta afecta al original
		pasar = *primerNum;
		chequeo = restar(&copia,segundoNum,43);
		irPrincipio(&chequeo);
		if(chequeo->num == 45){//si la resta de negativa, se multiplica el divisro por 0.1 osea lo mueve uno al la derecha
			pasar = NULL;
			pasar = multiplicar(&agregar,&ceroPtoUno);
			agregar = pasar;
			pasar = NULL;
			pasar = multiplicar(segundoNum,&ceroPtoUno);
			(*segundoNum) = pasar;
		}
		else{//se le resta el divisor y se le pone uno a la respuesta
			(*primerNum) = chequeo;
			pasar = NULL;
			pasar = sumar(&resp,&agregar);
			resp = pasar;
		}
		if(i == 60 && tienePto(&resp) == 1){//da opsion al usuario de parar una division infinita
			i = 0;
			char si[3];
			printf("La respuesta va asi:");
			printNum(&resp);//pone la respuesta y cmo esta
			printf("\nDesea dejarla asi? (s = si)  ");
			scanf("%s",si);
			if(si[0] == 115)
				return resp;//si el usuario lo desea se retorna lo deseado
		}
		else if (i == 60)//recupera el puntero
			i=0;
	}
	return resp;//retorna respuesta
}
ptrNumLista elevar(numLista** poder,numLista** numeroAEl){//poder de la potencia, y numero a Elevar
	ptrNumLista uno = crearNodo(1);//lista que contiene un uno nada mas
	ptrNumLista resp = crearNodo(1);//va a ser la lista a responder
	ptrNumLista pasar = NULL;
	if(isZero(poder) == 1)//si el poder es cer se retorna un uno
		return uno;
	while(isZero(poder) != 1){//ciclo que se hace hasta que potencia sea cero
		pasar = copiaD(&resp);//hace una copia de respuesta para poder pasar el valor
		resp = multiplicar(numeroAEl,&pasar);//multiplica el numero por la potencia a ser agregaad
		pasar = copiaD(poder);//hace una copia de poder
		*poder = restar(&pasar,&uno,43);//le resta uno a poder para ver si ya termino
	}
	return resp;//retorna la respuesta
}
/*////////////////////////////////////////////////////////////////////////FUNCIONES DE LISTA/PUNTEROS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
void quitarceros(numLista** lista){//quita algun cer al final o inicio de la lista
	irPrincipio(lista);
	while((*lista)->num == 0){//recorre mientras hayan ceros en la lista, el momento que este sea dieferentese termina la recorrida
		if((*lista)->siguiente == NULL)
			break;
		if((*lista)->siguiente->num == 46)//si hay un ponto al siguiente se deja tal que quede 0.xxxxx
			break;
		(*lista) = (*lista)->siguiente;//quita los ceros
		(*lista)->previo = NULL;
	}
}
ptrNumLista copiaD(numLista** lista){//hace una copia de una lista
	ptrNumLista new = NULL;
	irPrincipio(lista);
	while(1){
		agregarNodo((*lista)->num,&new);//se recorre la lista y cada numero se pone en la que se retornara
		if((*lista)->siguiente == NULL)
			return new;
		*lista = (*lista)->siguiente;
	}
}
ptrNumLista crearNodo(int elemento) {//cea un nuevo nodo a ser retonrnado
 numLista *ptr;//crea un puntero basura que retornara
 
 ptr = (numLista*)malloc(sizeof(numLista));//guarda el espacio
 ptr->num = elemento;//pone al elemnto como num
 ptr->siguiente = ptr->previo = NULL;//retorna los dos lados como nulos
 return ptr;
}
void agregarNodo(int elemento, numLista** cabeza) {//pone al nodo en siguiente
 numLista* Nuevo;//crea el nuevo nodo
 Nuevo = crearNodo(elemento);
 Nuevo->previo = *cabeza;
 Nuevo->siguiente = NULL;
 if (*cabeza != NULL)
	 (*cabeza)->siguiente = Nuevo;//pone al nodo a siguiente
 *cabeza = Nuevo;
}
void agregarNodoR(int elemento, numLista** cabeza) {//se pone al principio de la lista en contra de la al final que es el otro
 numLista* Nuevo;
 Nuevo = crearNodo(elemento);//crea el nodo a agregar
 Nuevo->siguiente = *cabeza;
 Nuevo->previo = NULL;
 if (*cabeza != NULL)
	 (*cabeza)->previo = Nuevo;//se one al principio o al nodo pasado
 *cabeza = Nuevo;
}
void irPrincipio(numLista** comienzo){//opuesto de ir Final la pone al principio
	while((*comienzo)->previo !=NULL){
		*comienzo = (*comienzo)->previo;//se recorre hasta el primer numero
	}
}
void irFinal(numLista** final){//va al final de la lista
	while((*final)->siguiente !=NULL){
		*final = (*final)->siguiente;//recorre la lista y al momento que sea nulo se retorna
	}
}
void ponerNumLista(char* n,numLista** numero){//pone los cahres en lista
	int i = 0,pto = 0;//variables el i es parte de recorrer la lista y de si hay punto
	if(n[i] == 45){//revisa si el signal flag esta negativa y si esta es verdadera se la pone
		agregarNodo(45,numero);
		i++;
	}
	else
		agregarNodo(43,numero);//si no la pone positiva
	if(n[i] == 46){//si hay un punto de primero le pone un punto y queda asi: 0.xxxxx
		agregarNodo(0,numero);
		agregarNodo(46,numero);
		pto = 1;//pone que ya se puso el punto para que no repita
	}
	for(;n[i] != '\0';i++){//recorre la lista hasta que no haya un siguiente
		if((n[i]-48)<10 && (n[i]-48)>=0){
				agregarNodo(n[i]-48,numero);
		}//revisa que no se pase de 9 y si es binario quita alguno que no sea 0 o 1
		else if(n[i] == 46 && pto == 0 && n[i+1] != '\0'){//pone al punto
			agregarNodo(46,numero);
			pto = 1;
		}
	}
	if(((*numero)->num == 43 || (*numero)->num == 45) && (*numero)->siguiente == NULL){//si no se pone ningun numero se retorna error y se recomienza el main
		printf("Error No se ingreso un Numero!!\nSe reiniciara!\n");//hace un print de error
		getchar();
		getchar();
		system("clear");//hace un clear al shell
		main();// recomienza el main
	}
}
int getLenDpsPto(numLista** lista){//Da el elngth de la lista despues del punto (flotantes)
	int len = 0;//length
	irFinal(lista);//va al final de la lista
	for(;(*lista)->num != 46;len++){//si el punto solo existe de ultimo aqui lo manda con 0
		if((*lista)->previo == NULL)//condicion de parada si no hay siguiete
			return 0;//retorna cero si no hay punto
		*lista = (*lista)->previo;//se recorre al siguiente
	}
	return len;//retorna el length
}
int getLenAtsPto(numLista** lista){//retorna el tamanho de la lista antes del punto, enteros
	int len = 0;//lenght de la lista
	irPrincipio(lista);//va al principio de la lista
	for(;(*lista)->num != 46;len++){//si el punto solo existe de ultimo aqui lo manda con 0
		if((*lista)->siguiente == NULL)//condicion de parada si no hay punto
			return len;//retoorna el length
		*lista = (*lista)->siguiente;//recorre al siguiente
	}
	return len;//retorna el length
}
int tienePto(numLista** lista){//revisa si tiene un punto la lista
	irPrincipio(lista);//va al principio de la lista
	for(;(*lista)->siguiente != NULL;*lista = (*lista)->siguiente){//recorre la lista, hasta que no hala mas
		if((*lista)->num == 46)//si ve nu punto retorna un uno(condicion booleana
			return 1;//True
	}
	if((*lista)->num == 46)//si hay un punto al puro final retorne 2condicion de ultimo es punto
			return 2;
	return 0;//False
}
void ponerListaAtsPto(numLista** lista){//pone la lista antes del punto
	irPrincipio(lista);// va al principio de la lista
	while((*lista)->siguiente != NULL){//si se acaba la lista se sale
		if((*lista)->siguiente->num == 46)//si hay un punto termina aqui la funcion
			return;
		*lista = (*lista)->siguiente;//va al siguiente de la lista
	}
	return;
}
void printNum(numLista** lista){//Encargado de imprimir la lista entera sin precision hasta que esta se acabe
	if(lista == NULL)//si respuesta es nula se ignora la funcion
		return;
	irPrincipio(lista);//va a principio de lista para unificar cualquier lista y como llega
	if((*lista)->num == 45){//revisa el signal flag, si hay una se imprime esta, seria unicamente la negativa
		printf("-");//se imprime un meos
		(*lista) = (*lista)->siguiente;//va al siguiente para no imprmir la signal flag de nuevo
	}
	else if((*lista)->num ==43){//si llega con positivolo pone
		printf("+");
		(*lista) = (*lista)->siguiente;
	}
	while((*lista)->siguiente != NULL){//mientras halla algo que imprimir se imprime
		if((*lista)->num == 46)//si hay punto lo pone
			printf(".");
		else
			printf("%d",(*lista)->num);//pone el numero que tenga la lista
		(*lista) = (*lista)->siguiente;// va al siguiente nodo de la lista
	}
	if((*lista)->num == 46)//revisa si es un punto
			printf(".\n");//si el ultimo nodo fue un punto lo pone
	else
			printf("%d\n",(*lista)->num);//si no le da un espacio para que se sepa que es un numero aparte
}
void printNumResp(numLista** resp,numLista** pres){//Imprime la respuesta esta es diferente a print num a que ocupa precicion
	irPrincipio(pres);
	ptrNumLista uno = crearNodo(1);//crea un "uno"
	ptrNumLista cpiaPres = copiaD(pres);//copia a presicion
	irPrincipio(resp);
	if(isZero(pres) == 1 || (*pres)->num == 45){//revisa que la respuestano sea negativa, si esto se cumple imprime la lista entera
		printNum(resp);
		return;
	}
	irPrincipio(pres);
	*pres = (*pres)->siguiente;//le quita el signal flag que tenga precision
	(*pres)->previo = NULL;
	while((*resp)->num != 46){//un while que imprima mientras no halla un punto 
		printf("%d",(*resp)->num);
		if((*resp)->siguiente == NULL)
			break;
		(*resp) = (*resp)->siguiente;
		}//el momento que se tenga n numero se acaba la el ciclo pasado
		if(tienePto(resp) == 0)//si no tiene un punto se agrega este
			printf(".");
		while(isZero(pres) != 1){//la condicion es un contador que le quita a precision uno cada vez
			cpiaPres = copiaD(pres);//le saca un copa a preciosion para poder agregarle a este el valor de la resta
			if((*resp)->num == 46)
				printf(".");//imprime el punto
			if((*resp)->siguiente == NULL)
				printf("0");//si se acabo la lista pone un cero hasta que se acabe el contador
			else{
				*resp = (*resp)->siguiente;
				printf("%d",(*resp)->num);//se pone a la posioncion el siguiente para imprimir este
			}
			*pres = restar(&cpiaPres,&uno,43);//le resuta uno a la copia de presicion y el valor se pone a presicion
			irPrincipio(pres);//se pone al princiopio para ver si es cero
	}
}
