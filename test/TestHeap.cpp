#include "gtest/gtest.h"
#include "data-structures/Heap.h"

// Tworzenie kopca
TEST(CreateHeap, JustCreate){

    Heap heap(50);
    DynamicArray<VertexData> elements = heap.getElements();

    ASSERT_EQ(50, elements.getLength());

}

// Dodawanie do kopca
TEST(Add, JustAdd){

    Heap heap(5);
    heap.add(VertexData(0, 0, NULL_VERTEX));
    heap.add(VertexData(1, 10, 0));
    heap.add(VertexData(2, 4, 1));
    heap.add(VertexData(3, 5, 4));
    heap.add(VertexData(4, 7, 0));

    DynamicArray<VertexData> elements = heap.getElements();
    DynamicArray<VertexData> proper_elements = vector<VertexData>{
        VertexData(0, 0, NULL_VERTEX),
        VertexData(3, 5, 4),
        VertexData(2, 4, 1),
        VertexData(1, 10, 0),
        VertexData(4, 7, 0)
    };

    ASSERT_EQ(5, elements.getLength());
    for(int i = 0; i < elements.getLength(); i++){
        ASSERT_EQ(proper_elements[i]->vertex, elements[i]->vertex);
    }

}

// Usuwanie korzenia
TEST(PopRoot, JustPop){

    Heap heap(5);
    heap.add(VertexData(0, 0, NULL_VERTEX));
    heap.add(VertexData(1, 10, 0));
    heap.add(VertexData(2, 4, 1));
    heap.add(VertexData(3, 5, 4));
    heap.add(VertexData(4, 7, 0));

    // Usunięcie 1
    ASSERT_TRUE(heap.pop_root());
    DynamicArray<VertexData> pop_1 = vector<VertexData>{
        VertexData(2, 4, 1),
        VertexData(3, 5, 4),
        VertexData(4, 7, 0),
        VertexData(1, 10, 0)
    };
    for(int i = 0; i < pop_1.getLength(); i++){
        ASSERT_EQ(pop_1[i]->vertex, heap.getElements()[i]->vertex);
    }

    // Usunięcie 2
    ASSERT_TRUE(heap.pop_root());
    DynamicArray<VertexData> pop_2 = vector<VertexData>{
        VertexData(3, 5, 4),
        VertexData(1, 10, 0),
        VertexData(4, 7, 0)
    };
    for(int i = 0; i < pop_2.getLength(); i++){
        ASSERT_EQ(pop_2[i]->vertex, heap.getElements()[i]->vertex);
    }

    // Usunięcie 3
    ASSERT_TRUE(heap.pop_root());
    DynamicArray<VertexData> pop_3 = vector<VertexData>{
        VertexData(4, 7, 0),
        VertexData(1, 10, 0)
    };
    for(int i = 0; i < pop_3.getLength(); i++){
        ASSERT_EQ(pop_3[i]->vertex, heap.getElements()[i]->vertex);
    }

    // Usunięcie 4
    ASSERT_TRUE(heap.pop_root());
    DynamicArray<VertexData> pop_4 = vector<VertexData>{
        VertexData(1, 10, 0)
    };
    for(int i = 0; i < pop_4.getLength(); i++){
        ASSERT_EQ(pop_4[i]->vertex, heap.getElements()[i]->vertex);
    }

    // Usunięcie 5
    ASSERT_TRUE(heap.pop_root());
    ASSERT_EQ(heap.root(), nullptr);

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}