#include <iostream>
#include "Graph.cpp"

void pageCount(int min, int max, vector<Node> &books) {
    vector<Node> newBooks;
    //deletes all old books and adds new books w/ correct page to vector
    for (int i=0; i<books.size();i++) {
        if (books.back().pageCount>=min && books.back().pageCount<=max)
            newBooks.push_back(books.back());

            books.pop_back();
    }

    books = newBooks; //now the new books will be filtered
}
void  ratingSort(vector<Node> &books) {
    //linear sort?
    //utilize ordered map
    //attempt a quicksort alg using a given pseudo code?
    //trying to decide which is faster
    
}



int main() {
    Graph LibraryofBooks;
    LibraryofBooks.readFile();
    return 0;
}
