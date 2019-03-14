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



class Lista {
public: Nodo *Inicio = NULL;

    void anadir_final (int dato, int pos_memoria){
        if(Inicio == NULL){
            Inicio = new Nodo(dato,pos_memoria);
        } else{
            Nodo *temp = this->Inicio;
            while(temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            temp->siguiente = new Nodo(dato,pos_memoria);
        }
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

};


// True = 1  -> Lleno
// False = 0 -> Vacìo

class Colector{
    Lista lista_Datos;


    void guardar_dato (int pos_mem){
        Nodo* temp = lista_Datos.Inicio;
        int i = 0;
        while (temp->siguiente != NULL){
            if (temp->Dato == 0){
                lista_Datos.cambiar_Dato(i,1);
                return;
            }
            temp = temp->siguiente;
            i++;
        }
        lista_Datos.anadir_final(1, pos_mem);
    }
    void borrar_dato (int pos_memo){
        Nodo* temp = lista_Datos.Inicio;
        int i = 0;
        while (temp->siguiente != NULL){
            if (temp->pos_memoria == pos_memo){
                lista_Datos.cambiar_Dato(i,0);
                return;
            }
            temp = temp->siguiente;
            i++;
        }
    }

};

class PLista{
public: Nodo *Inicio = NULL;
public: Colector colector;

    PLista(Colector colecto){
        colector = colecto;
    }

    Nodo* My_New(int dato){

        Nodo* nuevo = new Nodo(dato, NULL);
        return nuevo;
    }

    void anadir_final (int dato){
        if(Inicio == NULL){
            Nodo* niu = My_New(dato);
            Inicio = niu;
            // Inicio = new Nodo(dato,NULL);
        } else{
            Nodo *temp = this->Inicio;
            while(temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            Nodo* niu = My_New(dato);
            temp->siguiente = niu;
            //temp->siguiente = new Nodo(dato,NULL);
        }
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


    // Crear Colector
    Colector colector;


    // Crear Lista
    PLista* lista = new PLista(colector);
    for (int i = 0; i < 100; i++){
        int num = rand() % 100 + 1;
        lista->anadir_final( num );
    }
    insertionSort sort;
    lista = sort.ordenar(lista);
    std::cout << lista->obtener_dato(10) << std::endl;
    std::cout << lista->obtener_dato(20) << std::endl;
    std::cout << lista->obtener_dato(30) << std::endl;
    std::cout << lista->obtener_dato(40) << std::endl;
    std::cout << lista->obtener_dato(50) << std::endl;
    std::cout << lista->obtener_dato(60) << std::endl;
    return 0;
}

