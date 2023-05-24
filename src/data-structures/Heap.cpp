#include "data-structures/Heap.h"

Heap::Heap(unsigned max_size){

    current_size = 0;
    elements = new DynamicArray<VertexData>(max_size, VertexData());

}

Heap::~Heap(){
    delete elements;
    elements = nullptr;
}

bool Heap::pop_root(){

    // Z pustego nie można usunąć
    if(current_size == 0) return false;

    // Kopiuje wartośc ostatniego elementu na pierwszą pozycję, zmniejszam rozmiar kopca, 
    // aby zasymulować usunięcie ostatniego elementu
    // Następnie naprawiam kopiec w dół
    *root() = *elements->operator[](current_size-1);
    current_size--;
    repairDownwards(0);
    return true;

}

VertexData* Heap::root(){
    if(current_size == 0) return nullptr;
    return elements->operator[](0);
}

VertexData* Heap::find(int vertex){

    if(root() == nullptr) return nullptr;
    return elements->find(VertexData(vertex, NULL_VERTEX, INFINITY_W));

}

void Heap::add(VertexData new_element){

    // Dodaję wirtualnie element do kopca poprzez dodawnie go na indeks wskazywany przez
    // wartość current_size. Następnie naprawiam kopiec w górę.
    *elements->operator[](current_size) = new_element;
    current_size++;
    repairUpwards(current_size-1);

}

VertexData* Heap::getRightChild(unsigned index){
    // Jeżeli potomek wierzchołka znajduje się w obszarze tablicy, którego nie obejmuje obecny 
    // rozmiar kopca, to de facto ten wierzchołek jest liściem.
    if(RIGHT_CHILD_INDEX(index) >= current_size) 
        return nullptr;

    // W przeciwnym wypadku można sprawdzić istnienie potomka w sposób standardowy
    return elements->operator[](RIGHT_CHILD_INDEX(index));
}

VertexData* Heap::getLeftChild(unsigned index){
    // Jeżeli potomek wierzchołka znajduje się w obszarze tablicy, którego nie obejmuje obecny 
    // rozmiar kopca, to de facto ten wierzchołek jest liściem.
    if(LEFT_CHILD_INDEX(index) >= current_size) 
        return nullptr;

    // W przeciwnym wypadku można sprawdzić istnienie potomka w sposób standardowy
    return elements->operator[](LEFT_CHILD_INDEX(index));
}

int Heap::getMinChildIndex(unsigned node_index){
    
    VertexData* left_child = getLeftChild(node_index);
    VertexData* right_child = getRightChild(node_index);

    // Jeżeli jest liściem to brak maksymalnego potomka
    if(left_child == nullptr && right_child == nullptr) 
        return IS_LEAF;

    // Jeżeli ma jednego potomka to właśnie on jest minimum
    if(left_child == nullptr) 
        return RIGHT_CHILD_INDEX(node_index);
    if(right_child == nullptr) 
        return LEFT_CHILD_INDEX(node_index);

    // W przeciwnym wypadku szukamy minimum w sposób tradycyjny
    if(left_child->weight > right_child->weight) 
        return RIGHT_CHILD_INDEX(node_index);
    return LEFT_CHILD_INDEX(node_index);

}

void Heap::repairUpwards(unsigned node_index){

    // Sprawdzam, czy wierzchołek nie jest korzeniem, wówczas kończe naprawę
    if( node_index == 0 ) 
        return;

    // Sprawdzam, czy wierchołek jest maksymalnym potomkiem swojego rodzica
    // Jeżeli tak, to zamieniam go miejscami z rodzicem i kontynuuję naprawę
    // Jeżeli nie, to naprawę można zakończyć, gdyż warunek kopca jest na pewno spełniony
    if( node_index != getMinChildIndex(PARENT_INDEX(node_index)) ) 
        return;

    VertexData* current_node = elements->operator[](node_index);
    VertexData* parent = elements->operator[](PARENT_INDEX(node_index));
    if(parent->weight <= current_node->weight) 
        return;

    elements->swap(node_index, PARENT_INDEX(node_index));
    repairUpwards(PARENT_INDEX(node_index));

}

void Heap::repairDownwards(unsigned current_index){

    // Znajduję minimalnego potomka
    // Jeżeli wierzchołek okaże się liściem (nie ma potomków) kończę naprawę
    int min_index = getMinChildIndex(current_index);
    if(min_index == IS_LEAF) return;
    VertexData* min = elements->operator[](min_index);
    VertexData* current_node = elements->operator[](current_index);
    
    // Zamieniam miejscami rodzica z minimalnym potomkiem, jeżeli zaburzony jest warunek kopca 
    // Kontynuuje naprawe kopca
    if( min->weight >= current_node->weight) return;
    elements->swap(min_index, current_index);
    repairDownwards(min_index);

}

void Heap::buildHeapFloyd(){

    // Pustego nie naprawiam
    if(elements->getLength() == 0) return;

    // Wybieram kolejnych rodziców i zamieniam miejscami z dziećmi, jeżeli nie jest spełniony warunek kopca
    int left_child;
    int right_child;
    for(int i = (current_size-1)/2; i >= 0; i--) {
        repairDownwards(i);
    }

}