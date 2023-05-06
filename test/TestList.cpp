#include "gtest/gtest.h"
#include "data-structures/List.h"

// Stworzenie pustej listy
TEST(Create, EmptyList){

    List list;
    ASSERT_EQ(list.front(), nullptr);
    ASSERT_EQ(list.back(), nullptr);

}

// Stworzenie niepustej listy
TEST(Create, NonEmptyList){

    int ends[] = {
        0, 1, 2, 3
    };
    int weigths[] = {
        12, 38, -46, 81
    };

    List list;  
    list.push_back(ends[0], weigths[0]);
    list.push_back(ends[1], weigths[1]);
    list.push_back(ends[2], weigths[2]);
    list.push_back(ends[3], weigths[3]);

    // Sprawdzenie
    for(int i = 0; list[i] != nullptr; i++){
        ASSERT_EQ(list[i]->isEqual(ends[i], weigths[i]), true);
    }

}

// Wyszukiwanie elementu w liście
TEST(Find, ExistingElement){

    int ends[] = {
        0, 1, 2, 3
    };
    int weigths[] = {
        41, -73, -76, 13
    };

    List list;  
    list.push_back(ends[0], weigths[0]);
    list.push_back(ends[1], weigths[1]);
    list.push_back(ends[2], weigths[2]);
    list.push_back(ends[3], weigths[3]);

    // Sprawdzenie
    for(int i = 0; i < 4; i++){
        ASSERT_NE(list.find(ends[i], weigths[i]), nullptr);
        ASSERT_EQ(list.find(ends[i], weigths[i])->isEqual(ends[i], weigths[i]), true);
    }

}

// Wyszukiwanie nieistniejącego elementu w liście
TEST(Find, NonExistingElement){

    int ends[] = {
        0, 1, 2, 3
    };
    int weigths[] = {
        41, -73, -76, 13
    };


    int non_existing_ends[] = {
        52, 60
    };
    int non_existing_weigths[] = {
        20, -41
    };


    List list;  
    list.push_back(ends[0], weigths[0]);
    list.push_back(ends[1], weigths[1]);
    list.push_back(ends[2], weigths[2]);
    list.push_back(ends[3], weigths[3]);

    // Sprawdzenie
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++) 
            ASSERT_EQ(list.find(non_existing_ends[j], weigths[i]), nullptr);
        for(int j = 0; j < 2; j++) 
            ASSERT_EQ(list.find(ends[i], non_existing_weigths[j]), nullptr);
    }

    for(int j = 0; j < 2; j++) 
        ASSERT_EQ(list.find(non_existing_ends[j], non_existing_weigths[j]), nullptr);

}

// Wyszukiwanie w pustej liście
TEST(Find, EmptyList){

    List list;
    ASSERT_EQ(list.find(0, 12), nullptr);

}

// Pobranie głowy z niepustej listy
TEST(Front, NonEmptyList){

    List list;
    list.push_back(0, -100);
    list.push_back(1, 0);
    list.push_back(2, 14);

    // Sprawdzenie
    ASSERT_NE(list.front(), nullptr);
    ASSERT_EQ(list.front()->isEqual(0, -100), true);

}

// Pobranie głowy z pustej listy
TEST(Front, EmptyList){

    List list;
    
    // Sprawdzenie
    ASSERT_EQ(list.front(), nullptr);

}

// Pobranie głowy z listy 1-elementowej
TEST(Front, OneElementList){

    List list;
    list.push_back(0, -100);

    // Sprawdzenie
    ASSERT_NE(list.front(), nullptr);
    ASSERT_EQ(list.front()->isEqual(0, -100), true);
    ASSERT_NE(list.back(), nullptr);
    ASSERT_EQ(list.front()->isEqual(list.back()->end, list.back()->weigth), true);

}

// Pobranie ogona z niepustej listy
TEST(Back, NonEmptyList){

    List list;
    list.push_back(0, -100);
    list.push_back(1, 0);
    list.push_back(2, 14);

    // Sprawdzenie
    ASSERT_NE(list.back(), nullptr);
    ASSERT_EQ(list.back()->isEqual(2, 14), true);

}

// Pobranie głowy z pustej listy
TEST(Back, EmptyList){

    List list;
    
    // Sprawdzenie
    ASSERT_EQ(list.back(), nullptr);

}

// Pobranie głowy z listy 1-elementowej
TEST(Back, OneElementList){

    List list;
    list.push_back(0, -100);

    // Sprawdzenie
    ASSERT_NE(list.back(), nullptr);
    ASSERT_EQ(list.back()->isEqual(0, -100), true);
    ASSERT_NE(list.front(), nullptr);
    ASSERT_EQ(list.back()->isEqual(list.front()->end, list.front()->weigth), true);

}

// Dodanie elementu na początek pustej listy
TEST(PushFront, EmptyList){

    List list;
    list.push_front(0, -44);

    // Sprawdzenie
    ASSERT_NE(list.front(), nullptr);
    ASSERT_EQ(list.front()->isEqual(0, -44), true);

    ASSERT_NE(list.back(), nullptr);
    ASSERT_EQ(list.back()->isEqual(0, -44), true);

}

// Dodanie elementu na początek niepustej listy
TEST(PushFront, NonEmptyList){

    List list;
    list.push_front(2, 31);
    list.push_front(1, -44);
    list.push_front(0, -23);

    // Sprawdzenie
    ASSERT_NE(list.front(), nullptr);
    ASSERT_EQ(list.front()->isEqual(0, -23), true);

}

// Dodanie elementu na koniec pustej listy
TEST(PushBack, EmptyList){

    List list;
    list.push_back(0, -44);

    // Sprawdzenie
    ASSERT_NE(list.back(), nullptr);
    ASSERT_EQ(list.back()->isEqual(0, -44), true);

    ASSERT_NE(list.front(), nullptr);
    ASSERT_EQ(list.front()->isEqual(0, -44), true);

}

// Dodanie elementu na początek niepustej listy
TEST(PushBack, NonEmptyList){

    List list;
    list.push_back(0, 31);
    list.push_back(1, -44);
    list.push_back(2, -23);

    // Sprawdzenie
    ASSERT_NE(list.back(), nullptr);
    ASSERT_EQ(list.back()->isEqual(2, -23), true);

}

// Usunięcie elementu z początku pustej listy
TEST(PopFront, EmptyList){

    List list;
    list.pop_front();

    // Sprawdzenie
    ASSERT_EQ(list.front(), nullptr);
    ASSERT_EQ(list.back(), nullptr);

}

// Usunięcie elementu z początku 1-elementowej listy
TEST(PopFront, OneElementList){

    List list;
    list.push_back(0, -27);

    list.pop_front();

    // Sprawdzenie
    ASSERT_EQ(list.front(), nullptr);
    ASSERT_EQ(list.back(), nullptr);

}

// Usunięcie elementu z początku niepustej listy
TEST(PopFront, NonEmpty){

    List list;
    list.push_back(0, -27);
    list.push_back(1, 18);
    list.push_back(2, 50);

    list.pop_front();

    // Sprawdzenie
    ASSERT_EQ(list.front()->isEqual(1, 18), true);
    ASSERT_EQ(list.find(0, -27), nullptr);

}

// Usunięcie elementu z końca pustej listy
TEST(PopBack, EmptyList){

    List list;
    list.pop_back();

    // Sprawdzenie
    ASSERT_EQ(list.front(), nullptr);
    ASSERT_EQ(list.back(), nullptr);

}

// Usunięcie elementu z końca 1-elementowej listy
TEST(PopBack, OneElementList){

    List list;
    list.push_back(0, -27);

    list.pop_back();

    // Sprawdzenie
    ASSERT_EQ(list.front(), nullptr);
    ASSERT_EQ(list.back(), nullptr);

}

// Usunięcie elementu z początku niepustej listy
TEST(PopBack, NonEmpty){

    List list;
    list.push_back(0, -27);
    list.push_back(1, 18);
    list.push_back(2, 50);

    list.pop_back();

    // Sprawdzenie
    ASSERT_EQ(list.back()->isEqual(1, 18), true);
    ASSERT_EQ(list.find(2, 50), nullptr);

}

// Dodanie elementu w dowole miejsce pustej listy
TEST(Add, EmptyList){

    List list;
    list.add(0, 57, 312);

    // Sprawdzenie
    ASSERT_NE(list.front(), nullptr);
    ASSERT_TRUE(list.front()->isEqual(0, 57));

    ASSERT_NE(list.back(), nullptr);
    ASSERT_TRUE(list.back()->isEqual(0, 57));

}

// Dodanie elementu w dowole miejsce niepustej listy
TEST(Add, NonEmptyList){

    List list;
    list.push_back(0, 44);
    list.push_back(1, 45);
    list.push_back(2, 78);

    list.add(15, 66, 1);

    // Sprawdzenie
    ASSERT_NE(list[1], nullptr);
    ASSERT_TRUE(list[1]->isEqual(15, 66));

}


// Usunięcie elementu z dowolnego miejsca pustej listy
TEST(Remove, EmptyListy){

    List list;
    list.remove(34);

    // Sprawdzenie
    ASSERT_EQ(list.front(), nullptr);
    ASSERT_EQ(list.back(), nullptr);

}

// Usunięcie elementu z dowolnego miejsca niepustej listy
TEST(Remove, NonEmptyListy){

    List list;
    list.push_back(0, 44);
    list.push_back(1, 45);
    list.push_back(2, 78);

    list.remove(1);

    // Sprawdzenie
    ASSERT_EQ(list.find(1, 45), nullptr);
    ASSERT_NE(list[1], nullptr);
    ASSERT_TRUE(list[1]->isEqual(2, 78));

}

// Usunięcie elementu z dowolnego miejsca 1-elementowej listy
TEST(Remove, OneElementList){

    List list;
    list.push_back(0, 44);

    list.remove(0);

    // Sprawdzenie
    ASSERT_EQ(list.front(), nullptr);
    ASSERT_EQ(list.back(), nullptr);

}

// Usunięcie nieistniejącego elementu z dowolnego miejsca listy
TEST(Remove, NonExistingElement){

    List list;
    int ends[] = {
        0, 1, 2
    };
    int weigths[] = {
        44, 45, 78
    };

    list.push_back(ends[0], weigths[0]);
    list.push_back(ends[1], weigths[1]);
    list.push_back(ends[2], weigths[2]);

    list.remove(45);

    // Sprawdzenie
    for(int i = 0; list[i] != nullptr; i++){
        ASSERT_TRUE(list[i]->isEqual(ends[i], weigths[i]));
    }

}


// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}