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

    Nodo* My_New(int dato, int cant_bytes){
        Nodo* pos = colector.guardar_dato(cant_bytes);
        Nodo* nuevo = new Nodo(dato, NULL);
        pos = nuevo;
        return nuevo;
    }

    void My_Delete(Nodo* pos_memo, int pos){
      colector.borrar_dato(pos_memo, pos);
    }

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
    void cambiar_pos_memoria (int posicion, int pos_memo){
        if (Inicio == NULL) {
            return;
        }
        Nodo* temp = Inicio;
        for (int i = 0; i <= (posicion - 1); i++){
            temp = temp->siguiente;
        }
        temp->pos_memoria = pos_memo;
    }

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

