#include <iostream>
#include "Graph.cpp"


vector<Node*>  pageCount(int min, int max, vector<Node*> &books) {
    vector<Node*> newBooks;

    //deletes all old books and adds new books w/ correct page to vector
    for (int i=0; i<books.size();i++) {
        if (books.back()->pageCount>=min && books.back()->pageCount<=max)
            newBooks.push_back(books.back());

        books.pop_back();
    }

    books = newBooks; //now the new books will be filtered
    return newBooks;
}
vector<Node*>  ratingSort(vector<Node*> &books) {
    //utilize ordered map

    map<double,vector<Node*>>rankedList;
    for (int i=0;i<books.size();i++) {
        rankedList[books[i]->rating].push_back(books[i]);
    }

    vector<Node*> recList;
    for (auto i=rankedList.begin();i!=rankedList.end();i++){
        copy(i->second.begin(),i->second.end(),back_inserter(recList));
        // recList now contains all books sorted in order
    }
    return recList;
}


int main() {
    Graph obj;
    //this should probably be moved into the graph function itself
    obj.readFile();
    obj.constructMatrix();

    //sort by value later if wanted
    cout<<"Genre List"<<endl;
    int counter=1;
    for (auto i=obj.genreList.begin();i!=obj.genreList.end();i++){
        // recList now contains all books sorted in order
        cout<<i->first<<". ";
        i++;
        counter++;
        if (counter==100) {
            cout << endl;
            break;
        }

    }
    bool repeat = true;
    while (repeat) {
        repeat = false;
        string userinput;
        string genre1;
        string genre2;
        int min;
        int max;
        cout<<endl;
        cout << "BookLook: The Fastest Book Recommendation Database." << endl;
        cout << "Type your favorite genre from the ones listed above!" << endl;
        cin >> genre1;
        cout << "Type your second favorite genre!" << endl;
        cin >> genre2;
        obj.Search(genre1, genre2);

        cout << "Thank you! We used two search algorithms to create two recommendation lists with the top rated books based on your liking.....Enjoy!" << endl;
        cout<<"BFS took "<< obj.bfstime<<" nanoseconds"<<endl;
        cout<<"DFS took "<< obj.dfstime<<" nanoseconds"<<endl;

        //int pageNum;
        //cin >> pageNum;

        auto y = obj.recBooksDFS;
        auto x = obj.recBooksBFS;
        x = ratingSort(x);
        y = ratingSort(y);
        cout << endl;
        cout << "We have found " << y.size() << " books for specifically for you!" << endl;
        cout << endl;

        cout << "Would you like to add a page count parameter? (Y/N)" << endl;
        cin >> userinput;
        if (userinput == "Y" || userinput == "y" ) {
            cout << "What is the minimum page count you would like?" << endl;
            cin >> min;
            cout << "What is the maximum page count you would like?" << endl;
            cin >> max;
            x = pageCount(min,max,x);
            y = pageCount(min,max,y);
        }




        for (int i = y.size() - 1; i > y.size() - 6; i--) {
            cout << "Title = " << y[i]->title << endl;
            cout << "Author = " << y[i]->author << endl;
            cout << "Rating = " << y[i]->rating << endl;
            cout << "Page Count = " << y[i]->pageCount << endl;
            cout << endl;

            if (y[i]->title!=x[i]->title) {
                cout << "Title = " << x[i]->title << endl;
                cout << "Author = " << x[i]->author << endl;
                cout << "Rating = " << x[i]->rating << endl;
                cout << "Page Count = " << x[i]->pageCount << endl;
                cout << endl;
            }

        }

        cout << "Would you like to find another tailored book? (Y/N)" << endl;
        cin >> userinput;
        if (userinput == "Y") {
            obj.dfsvisited.clear();
            repeat = true;
        }
    }

    return 0;
}

