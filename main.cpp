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


    void anadir_final (int dato){
        if(Inicio == NULL){
            Inicio = new Nodo(dato, NULL);
        } else{
            Nodo *temp = this->Inicio;
            while(temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            temp->siguiente = new Nodo(dato, NULL);
        }
    }
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
};

class insertionSort{

public :Lista ordenar(Lista list){
        int n = list.tamano();
        for (int i = 0; i < (n-1); i++) {
            int mIndex = i;
            for(int j = i+1; j < (n); j++){
                if (list.obtener_dato(j) < list.obtener_dato(mIndex)){
                    mIndex = j;
                }
            }
            int temp = list.obtener_dato(mIndex);
            list.cambiar_Dato(mIndex, list.obtener_dato(i));
            list.cambiar_Dato(i, temp);
        }
        return list;
    }
};

class Colector{
    Lista lista_Datos;

    void guardar_dato (int pos_mem){
        lista_Datos.anadir_final(1, pos_mem);
    }
    void borrar_dato (int posicion){

        lista_Datos.cambiar_Dato(posicion, 0);
    }

};







int main() {
    std::cout << "------ Pruebas Lista enlazada -----" << std::endl;
    Lista a;
    a.anadir_final(10);
    a.anadir_final(9);
    a.anadir_final(10);

    std::cout << a.Inicio->Dato << std::endl;
    std::cout << a.obtener_dato(1) << std::endl;
    std::cout <<  "cambio dato en pos 1 a 55" << std::endl;
    a.cambiar_Dato(1,55);
    std::cout <<  a.obtener_dato(1) << std::endl;
    std::cout << "-----Fin Pruebas Lista enlazada----" << std::endl;


    // Crear Colector


    // Crear Lista
    Lista lista;
    for (int i = 0; i < 100; i++){
        int num = rand() % 100 + 1;
        lista.anadir_final( num );
    }
    insertionSort sort;
    lista = sort.ordenar(lista);
    std::cout << lista.obtener_dato(10) << std::endl;
    std::cout << lista.obtener_dato(20) << std::endl;
    std::cout << lista.obtener_dato(30) << std::endl;
    std::cout << lista.obtener_dato(40) << std::endl;
    std::cout << lista.obtener_dato(50) << std::endl;
    std::cout << lista.obtener_dato(60) << std::endl;
    return 0;
}

