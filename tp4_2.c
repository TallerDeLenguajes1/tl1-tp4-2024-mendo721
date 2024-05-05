#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include <string.h>

typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;
typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

void mostrarTareas(Nodo *L);
Nodo *crearNodo(Tarea tarea);
Tarea crearTarea(int id);
void insertaNodo(Nodo **Lista, Nodo *Nnodo);
Nodo *crearListaVacia();
void pasarTareas(Nodo **origen, Nodo **destino, int id);
void buscarTarea(Nodo **L1, Nodo **L2, int id);
void liberarLista(Nodo *Lista);

int main(){

    int condicion = 1;
    int id = 1000;

    
    

    Nodo *tareasPendientes = crearListaVacia();
    Nodo *tareasRealizadas = crearListaVacia();

    do
    {
        Tarea nuevaTarea = crearTarea(id);
        Nodo *nuevoNodo = crearNodo(nuevaTarea);
        insertaNodo(&tareasPendientes, nuevoNodo); //siempre que haya un doble puntero va un adireccional
        

        printf("\nDesea ingresar otra tarea?\nSi:1  -  No:0  :");
        scanf("%d", &condicion);
        id++;
    } while (condicion == 1);
    
    printf("\n\n----Tareas pendientes----\n");
    mostrarTareas(tareasPendientes);

    do
    {
        printf("\nQue tarea desea marcar como tarea realizada?\nIngrese el ID: ");
        scanf("%d", &id);

        pasarTareas(&tareasPendientes, &tareasRealizadas, id);

        printf("\n\n----Tareas pendientes----\n");
        mostrarTareas(tareasPendientes);
        printf("\n\n----Tareas realizadas----\n");
        mostrarTareas(tareasRealizadas);

        printf("\nDesea ingresar otra tarea? \nSi:1  -  No:0  :");
        scanf("%d", &condicion);
    } while (condicion == 1);
    
    do
    {
        printf("\nIngrese el id de alguna tarea que desee buscar: ");
        scanf("%d", &id);
        buscarTarea(&tareasPendientes, &tareasRealizadas, id);
        printf("\nDesea ingresar otra tarea? \nSi:1  -  No:0  :");
        scanf("%d", &condicion);
    } while (condicion == 1);

    liberarLista(tareasPendientes);
    liberarLista(tareasRealizadas);

}

//-------------MOSTRAR LISTA-----------------

void mostrarTareas(Nodo *L){
    while (L != NULL)
    {
        printf("\nID: %d \nDescripcion: %s \nDuracion: %d\n\n",L->T.TareaID,L->T.Descripcion,L->T.Duracion);
        L = L->Siguiente;
    }
    
}

//----------CREAR UN NODO-----------

Nodo *crearNodo(Tarea tarea){
    Nodo *nodo = malloc(sizeof(Nodo));
    nodo->T.Descripcion = tarea.Descripcion;
    nodo->T.Duracion = tarea.Duracion;
    nodo->T.TareaID = tarea.TareaID;
    nodo->Siguiente = NULL;
    return nodo;
}

//------------CREAR UN VALOR PARA NODO------------

Tarea crearTarea(int id){
    Tarea nuevaTarea;
    char buff[50];
    printf("\nIngrese la descripcion de la tarea: ");
    fflush(stdin);
    gets(buff);
    nuevaTarea.TareaID = id;
    nuevaTarea.Descripcion = malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(nuevaTarea.Descripcion,buff);
    printf("\nIngrese la duracion de la tarea: ");
    int duracion;
    scanf("%d", &duracion);
    nuevaTarea.Duracion = duracion;

    return nuevaTarea;
}

//---------INSERTAR NODO EN UNA LISTA----------------

void insertaNodo(Nodo **Lista, Nodo *Nnodo){
    Nnodo->Siguiente = *Lista;
    *Lista = Nnodo;
}

//------------CREAR LISTA VACIA--------------

Nodo *crearListaVacia(){
    return NULL;
}

//---------PASAR NODO DE UNA LISTA A OTRA----------

void pasarTareas(Nodo **origen, Nodo **destino, int id){
    Nodo *actual = *origen;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id)
    {
        anterior = actual;
        actual = actual->Siguiente;
    }
    
    //Este caso la lista esta vacia y no se encontro resultados, directamente no entro en el while
    if (actual == NULL)
    {
        printf("\nNo se encontro resultados en la busqueda de la tarea");
    }
    
    if (anterior == NULL)//cuando el primer elemento de la lista es el buscado
    {
        *origen = actual->Siguiente;
    }
    else//saltea el nodo buscado del origen 
    {
        anterior->Siguiente = actual->Siguiente;
    }
    
    
    actual->Siguiente = *destino;
    *destino = actual;
}

//-------------BUSCAR NODO POR VALOR--------------

void buscarTarea(Nodo **L1, Nodo **L2, int id){ //Busqueda de nodo usando un valor y buscando en dos listas
    int bandera = 0;
    Nodo *aux1 = *L1;
    while (aux1 != NULL)
    {
        if (aux1->T.TareaID == id)
        {
            bandera = 1;
            printf("\nLa Tarea Buscada Pertenece a la lista de tareas pendientes");
            printf("\nID: %d \nDescripcion: %s \nDuracion: %d\n\n",aux1->T.TareaID,aux1->T.Descripcion,aux1->T.Duracion);
        }
        aux1 = aux1->Siguiente;
    }
    
    
    Nodo *aux2 = *L2;
    while (aux2 != NULL)
    {
        if (aux2->T.TareaID == id)
        {
            bandera = 1;
            printf("\nLa Tarea Buscada Pertenece a la lista de tareas realizada");
            printf("\nID: %d \nDescripcion: %s \nDuracion: %d\n\n",aux2->T.TareaID,aux2->T.Descripcion,aux2->T.Duracion);
        }
        aux2 = aux2->Siguiente;
    }
    
    if (bandera == 0)
    {
        printf("\nNo se encontro resultados en la busqueda de la tarea");
    }
}


//-----------LIBERAR LISTAS------------


void liberarLista(Nodo *Lista){
    Nodo *temp;
    while (Lista != NULL)
    {
        temp = Lista;
        Lista = Lista->Siguiente;
        free(temp->T.Descripcion);
        free(temp);
    }
}
