#include <iostream>
#include <random>

class Nodo {
public: Nodo *siguiente;
public: int pos_memoria;
public: int Dato;
    Nodo (int dato, int pos_mem);
};

Nodo::Nodo(int dato, int pos_mem) {
    Dato = dato;
    pos_memoria = pos_mem;
    siguiente = NULL;

}

class NodoC {
public: NodoC *siguiente;
public: Nodo* nodo_memoria;
public: int Dato;
    NodoC (int dato, Nodo* nodo_mem);
};

NodoC::NodoC(int dato, Nodo* nodo_mem) {
    Dato = dato;
    nodo_memoria = nodo_mem;
    siguiente = NULL;
}

class Lista {
public: NodoC *Inicio;
public: Lista(){
        Inicio = NULL;
    }
    /// funcion que agrega un elemento al final de la lista
    /// \param dato elemento que se desea agregar a la lista
    /// \param Nodo_memoria posicion en memoria del dato
    void anadir_final (int dato, Nodo* Nodo_memoria){
        if(Inicio == NULL){
            Inicio = new NodoC(dato,Nodo_memoria);
        } else{
            NodoC *temp = Inicio;
            while(temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            temp->siguiente = new NodoC(dato,Nodo_memoria);
        }
    }
    /// funcion que muestra la canitad de datos
    /// \return int con la canitdad de datos de la lista
    int tamano(){
        NodoC* temp = Inicio;
        int i = 1;
        if (Inicio == NULL) {
            return 0;
        }
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
            i++;
        }
        return i;
    }
    /// funcion que permite borrar los datos de una lista
    /// \param posicion posicion que se desea borrar en la lista
    void borrar_Dato(int posicion){
        if (Inicio == NULL) {
            return;
        }
        if(tamano() < posicion){
            return;
        }
        NodoC* temp = Inicio;
        for (int i = 0; i <= (posicion - 2); i++){
            temp = temp->siguiente;
        }
        if (temp->siguiente != NULL){
            NodoC* temp2 = temp->siguiente;
            if(temp2->siguiente != NULL){
                temp->siguiente = temp2->siguiente;
            }else if(temp2->siguiente == NULL){
                temp->siguiente = NULL;
            }
        }
        return;
    }
    /// funcion que cambia el dato en la posicion indicada por uno nuevo
    /// \param posicion posicion que se desesa cambiar
    /// \param dato dato que se va a sustituir
    void cambiar_Dato (int posicion, int dato){
        if (Inicio == NULL) {
            return;
        }
        NodoC* temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++){
            temp = temp->siguiente;
        }
        temp->Dato = dato;
    }
    /// funcion que cambia la posicion en memoria por otra indicada
    /// \param posicion posicion que se desea cambiar
    /// \param pos_memo nueva posicion
    void cambiar_pos_memoria (int posicion, Nodo* pos_memo){
        if (Inicio == NULL) {
            return;
        }
        NodoC* temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++){
            temp = temp->siguiente;
        }
        temp->nodo_memoria = pos_memo;
    }
    /// funcion que muestra la posicion de memoria del dato indicado
    /// \param posicion posicion a la que se le desea conocer la direccion
    /// \return retorna la direccion de memoria de la posicion indica
    Nodo* obtener_pos_memoria(int posicion){
        if (Inicio == NULL) {
            return NULL;
        }
        NodoC* temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++){
            temp = temp->siguiente;
        }
        return temp->nodo_memoria;
    }

};


// True = 1  -> Lleno
// False = 0 -> Vacìo

class Colector{
public:Lista* lista_Datos;

public: Colector(){
        lista_Datos = new Lista();
    }

public: Nodo* guardar_dato (int cant_bytes){
        NodoC* temp = lista_Datos->Inicio;
        for(int i = 0; i < lista_Datos->tamano();i++){
            if (temp->Dato == 0){
                lista_Datos->cambiar_Dato(i,1);
                return lista_Datos->obtener_pos_memoria(i);
            }
            temp = temp->siguiente;
        }
        Nodo *puntero;
        puntero = (Nodo *)malloc(sizeof(cant_bytes));
        lista_Datos->anadir_final(1, puntero);
        return puntero;

    }

public: void borrar_dato (Nodo* pos_memo, int pos){
        NodoC* temp = lista_Datos->Inicio;
        int i = 0;
        while (temp->siguiente != NULL){
            if (&temp->nodo_memoria == &pos_memo){
                lista_Datos->cambiar_Dato(i,0);
                return;
            }
            temp = temp->siguiente;
            i++;
        }
        lista_Datos->cambiar_Dato(pos,0);
    }

public: void print_lista(){
        NodoC* temp = lista_Datos->Inicio;
        for(int i = 0; i < lista_Datos->tamano();i++){
            std::cout << temp->Dato << " / " << &temp->nodo_memoria << std::endl;
            temp = temp->siguiente;
        }
        return ;
    }

};

class PLista{
public: Nodo *Inicio = NULL;
public: Colector colector;

    PLista(Colector colecto){
        colector = colecto;
    }
    ///
    /// \param dato dato que se desea agragar a la lista
    /// \param cant_bytes cantidad de bytes que se le asignan
    /// \return
    Nodo* My_New(int dato, int cant_bytes){
        Nodo* pos = colector.guardar_dato(cant_bytes);
        Nodo* nuevo = new Nodo(dato, NULL);
        pos = nuevo;
        return nuevo;
    }
    /// funcion que libera la memoria del collector
    /// \param pos_memo posicion de memoria que se libera
    /// \param accion si es 1 libera la memoria parcialmete y 0 completamente
    void My_Delete(Nodo* pos_memo, int accion){
        colector.borrar_dato(pos_memo, accion);
    }
    /// funcion que agrega al final de la lista un elemento
    /// \param dato dato que se desea agregar
    void anadir_final (int dato){
        if(Inicio == NULL){
            Nodo* nuevo = My_New(dato, 4);
            Inicio = nuevo;
            // Inicio = new Nodo(dato,NULL);
        } else{
            Nodo *temp = this->Inicio;
            while(temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            Nodo* nuevo = My_New(dato, 4);
            temp->siguiente = nuevo;
            //temp->siguiente = new Nodo(dato,NULL);
        }
    }
    /// funcion que agrega al inicio un elemento
    /// \param dato elemento que se agrega
    void anadir_Inicio(int dato){
        if (Inicio == NULL){
            Nodo* nuevo = My_New(dato, 4);
            Inicio = nuevo;
        }else{
            Nodo* nuevo = My_New(dato, 4);
            Nodo* temp = Inicio;
            Inicio = nuevo;
            nuevo->siguiente = temp;
        }
        return;
    }
    /// funcion que muestra el dato de la posicion indicada
    /// \param posicion posicion en la lista del dato que se desea consultar
    /// \return int con el dato que esta en esa posicion
    int obtener_dato(int posicion){
        if (Inicio == NULL) {
            return NULL;
        }
        Nodo* temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++){
            temp = temp->siguiente;
        }
        return temp->Dato;
    }
    /// funcion que retorna la posicion de memoria de un dato indicado
    /// \param posicion posicion del dato en la lista
    /// \return posicion de memoria del dato consultado
    int obtener_pos_memoria(int posicion){
        if (Inicio == NULL) {
            return NULL;
        }
        Nodo* temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++){
            temp = temp->siguiente;
        }
        return temp->pos_memoria;
    }
    /// funcion que muestra la cantidad de datos de una lista
    /// \return int con la cantidad de datos
    int tamano(){
        Nodo* temp = Inicio;
        int i = 1;
        if (Inicio == NULL) {
            return 0;
        }
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
            i++;
        }
        return i;
    }
    /// funcion que borra el nodo en la posicion indicada
    /// \param posicion posicion que se desea eliminar
    void borrar_Dato(int posicion){
        if (Inicio == NULL) {
            return;
        }
        if(tamano() < posicion){
            return;
        }
        Nodo* temp = Inicio;
        for (int i = 0; i <= (posicion - 2); i++){
            temp = temp->siguiente;
        }
        My_Delete(temp, posicion);
        if (temp->siguiente != NULL){
            Nodo* temp2 = temp->siguiente;
            if(temp2->siguiente != NULL){
                temp->siguiente = temp2->siguiente;
            }else if(temp2->siguiente == NULL){
                temp->siguiente = NULL;
            }
        }
        return;
    }
    /// funcion que cambia el dato en la posicion indicada por uno nuevo
    /// \param posicion posicion que se desesa cambiar
    /// \param dato dato que se va a sustituir
    void cambiar_Dato (int posicion, int dato){
        if (Inicio == NULL) {
            return;
        }
        Nodo* temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++){
            temp = temp->siguiente;
        }
        temp->Dato = dato;
    }
    /// funcion que cambia la posicion en memoria por otra indicada
    /// \param posicion posicion que se desea cambiar
    /// \param pos_memo nueva posicion
    void cambiar_pos_memoria (int posicion, int pos_memo) {
        if (Inicio == NULL) {
            return;
        }
        Nodo *temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++) {
            temp = temp->siguiente;
        }
        temp->pos_memoria = pos_memo;
    }
    ///funcion imprime la lista
    void print_lista(){
        Nodo* temp = Inicio;

        while(temp->siguiente!= NULL){
            //for (int i = 0; i < ; i++){
            if (Inicio == NULL) {
                return ;
            }
            std::cout << temp->Dato << std::endl;
            temp = temp->siguiente;
        }
        return ;
    }

};

class insertionSort{
public :PLista* ordenar(PLista* list){
        int n = list->tamano();
        for (int i = 0; i < (n-1); i++) {
            int mIndex = i;
            for(int j = i+1; j < (n); j++){
                if (list->obtener_dato(j) < list->obtener_dato(mIndex)){
                    mIndex = j;
                }
            }
            int temp = list->obtener_dato(mIndex);
            list->cambiar_Dato(mIndex, list->obtener_dato(i));
            list->cambiar_Dato(i, temp);
        }
        return list;
    }
};







int main() {

    std::cout << "---------Se inicializa el colector---------" << std::endl;
    // Crear Colector
    Colector colector;


    // Crear Lista
    std::cout << "---------Creamos la lista con n elementos---------" << std::endl;
    PLista* lista = new PLista(colector);
    for (int i = 0; i < 10; i++){
        int num = rand() % 100 + 1;
        lista->anadir_final( num );
    }
    std::cout << "---------Le aplicamos insetion sort a la lista; Lista ordenada: ---------" << std::endl;
    insertionSort sort;
    lista = sort.ordenar(lista);
    lista->print_lista();

    std::cout << "-------Print de la lista en el colector-----------" << std::endl;
    std::cout << "-----Como el colector no tenia ningun espacio disponible se crearon n espacios nuevos------" << std::endl;
    std::cout << "-----entonces todos los los datos de la lista del colector son = 1------" << std::endl;


    colector.print_lista();

    std::cout << "--------Borramos en la lista la aposicion 1: Luego se imprimer la lista del colector----------" << std::endl;
    std::cout << "-------El colector deberia de libera un espacio en memoria-----------" << std::endl;
    std::cout << "-------uno de los datos del colector ahora es = 0 (espacio libre)-----------" << std::endl;


    lista->borrar_Dato(1);
    colector.print_lista();

    std::cout << "--------ahora se agrega un elemento nuevo a la lista (Al INICIO); se imprime la lista del colector----------" << std::endl;
    std::cout << "--------Como un espacio del colector estaba libre, este se resicla, ahora el espacio----------" << std::endl;
    std::cout << "-------------que tenia un 0, es igual a 1; un nuevo dato ocupa ese espacio--------------" << std::endl;
    lista->anadir_Inicio(1000);
    colector.print_lista();

    std::cout << "--------Ahora se imprime la lista con los cambios generales----------" << std::endl;
    lista->print_lista();
    std::cout << "---------------------------------------------------------------------" << std::endl;
    return 0;
}

