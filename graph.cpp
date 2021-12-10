#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <map>
#include <numeric>
#include <algorithm>
#include <queue>
#include<chrono>

using namespace std::chrono;
using namespace std;
typedef high_resolution_clock Clock;


struct Node {
    string author, genre, bookFormat, isbn, isbn13, desc, img, link, title, review, totalRatings;
    int pageCount;
    double rating;
};

struct Edge { //did not use; not sure if that was an issue
    int src, dest;
};

class Graph
{
public:

    //Graph Implementation Functions & Variables
    Node* books[100000];
 // vector<bool[100000]> adjMatrix;
    list<int>* adjList= new list<int> [100000];
    //vector<vector<bool>> adjList;
    map<int, bool> dfsvisited;

    //Graph Data initialization
    void constructMatrix();
    void readFile();


    //Graph Traversal Functions & Variables
    bool* visited;

    void Search(string genre1, string genre2); //umbrella function that implements DFS and BFS
    void DFS(int v); //v is the random src node
    void BFS(int v); //v is the random src node

    //tracks index of 1st found recommended book for DFS and BFS
    int recBook1DFS = -1;
    int recBook1BFS = -1;

    string targGenre1; //to be changed to be a target genre
    string targGenre2; //to be changed to be a target genre

    long long dfstime;
    long long bfstime;

    //final recommendation lists
    vector<Node*> recBooksDFS;
    vector<Node*> recBooksBFS;
    map<string,int>genreList;
    //list all the unique genres; <genre, pair<has it been added yet, total books w/ that genre>>
};

void Graph::constructMatrix() {
    int matSize = 100000;
    //for each book 0->9999999//
    string currentgenre;
    string allgenres;
    //adjList.size()
    for (int i = 0; i < 100000; i++) {
        cout << i << endl;
        allgenres = books[i]->genre;
        while (!allgenres.empty()) {
            currentgenre = allgenres.substr(0, allgenres.find(','));
            if (allgenres.find(',') != std::string::npos)
            {
                allgenres.erase(0, allgenres.find(',') + 1);
            } else {
                currentgenre = allgenres;
                allgenres = "";
            }
            for (int j = i + 1; j < 50000; j++) {
                if (books[j]->genre.find(currentgenre) != std::string::npos) {
                    //IF BOOK HAS THE SAME GENRE

                    adjList[i].push_back(j);
                    adjList[j].push_back(i);

                    //adds this genre to the list of genres
                    if (genreList.find(currentgenre) == genreList.end()) {
                        genreList[currentgenre] = 1;
                    } else
                        genreList[currentgenre]++;
                }
            }
        }

    }
};
void Graph::DFS(int v) {
    dfsvisited[v] = true;
    string genresB2 = books[v]->genre;

    size_t pos = 0;
    while ((pos = genresB2.find(',')) != string::npos) {
        string tempB2 = genresB2.substr(0, pos);
        genresB2.erase(0, pos + 1);

        //if book & target genre share this genre
        if (targGenre1 == tempB2 || targGenre2 == tempB2) {
            //could push any genre that's connected into graph??
            recBook1DFS = v;

        }
    }

    // Recur for all the vertices adjacent
    // to this vertex
    if (recBook1DFS==-1) {
        list<int>::iterator i;
        for (i = adjList[v].begin(); i != adjList[v].end(); ++i)
            if ( dfsvisited.find(*i) == dfsvisited.end() ) {
                DFS(*i);
            }
    }
}
    //  First take in two genres out of the parameters and pick an arbitrary node and use breadth first search or depth first search and stop once any of the genres are a match.

    // Take this node and put it and all nodes it has an edge with and both matching genres.
    // Return this as a vector.

void Graph::BFS(int v) { //BFS from a random src node
    visited = new bool [100000];
    for (int i = 0; i < 100000; i++) {
        visited[i] = false;
    }
    visited[v] = true;
    queue<int> toBeVisited;
    toBeVisited.push(v);

    while (!toBeVisited.empty()) {
        int current = toBeVisited.front();
        toBeVisited.pop();

        string genresB2 = books[current]->genre;

        size_t pos = 0;
        while ((pos = genresB2.find(',')) != string::npos) {
            string tempB2 = genresB2.substr(0, pos);
            genresB2.erase(0, pos + 1);

            //if book & target genre share this genre
            if (targGenre1 == tempB2 || targGenre2 == tempB2) {
                //could push any genre that's connected into graph??
                recBook1BFS = current;

            }
        }
        if (recBook1BFS == -1) { //how is the recursion diff for DFS
            // Recur for all the vertices adjacent to this vertex
            for (int i = 0; i < 50000; i++) {
                if (!visited[i] && find(adjList[current].begin(), adjList[current].end(), i) != adjList[current].end()) {
                    toBeVisited.push(i);
                    visited[current] = true;
                }


            }
        }
    }
}

//the Graph Search function satisfied this part of the write up:

//  First (1) take in two genres out of the parameters and (2) pick an arbitrary node and (3) use breadth first search
//  or (4) depth first search and stop once any of the genres are a match.

// (5) Take this node and put it and all nodes it has an edge with and both matching genres.
// defines two vectors based on DFS and BFS.

void Graph::Search(string genre1, string genre2){
    //(1)
    targGenre1 = genre1;
    targGenre2 = genre2;
    //(2)
//random generated number from 1-100000
    bool find =0;
    int b = 0;

    while (recBook1BFS==-1 && recBook1DFS==-1) {
        //if we start with a node not connected to any others -> pick a new node?
        int b = rand() % 99999 + 1;
        find = 1;


        auto t1 = Clock::now();

//Insert function u are timing


        //(4)
        //insert timer here - using chrono


        DFS(b); //does DFS & defines recBook1DFS (aka: index of first matching book)
        //stop timer
        //cout << "DFS Time: " << endl;


        auto t2 = Clock::now();

         dfstime = duration_cast<nanoseconds>(t2-t1).count();

        //insert timer here - using chrono
         t1 = Clock::now();
        BFS(b); //does BFS & defines recBook1BFS (aka: index of first matching book)
         t2 = Clock::now();

        //stop timer
        bfstime = duration_cast<nanoseconds>(t2-t1).count();


    }

    //(5)
    //complete the book lists using recBook1DFS & recBook1BFS
    if (recBook1BFS!=-1 && recBook1DFS!=-1) {
        for (int i = 0; i < 100000; i++) {
            auto it  = std::find(adjList[recBook1BFS].begin(), adjList[recBook1BFS].end(), i);

            if (it != adjList[recBook1BFS].end()){
                if (books[*it]->genre.find(genre1) != std::string::npos ||books[*it]->genre.find(genre2) != std::string::npos  ) {
                    recBooksBFS.push_back(books[i]);
                    recBooksDFS.push_back(books[i]);
                }

            }
        }
    }
    else
        cout<<"error: no first book found -->> DfS:"<<recBook1DFS<<" BFS: "<<recBook1DFS<<endl;

}

void Graph::readFile(){
    ifstream file("GoodReads_100k_books.csv");
    string input;
    string token;
    getline(file, input);
    int i=0;

    while(getline(file, input) && i < 100000){
        bool skip = false;
        stringstream myData(input);
        Node* temp = new Node();

        getline(myData, token, '~');
        temp->author = token;

        getline(myData, token, '~');
        //temp->bookFormat = token;

        getline(myData, token, '~');
        //temp->desc = token;

        getline(myData, token, '~');
        temp->genre  = token;

        getline(myData, token, '~');
        //Skips any entry with no .jpg link attached
        if (token.find(".jpg") != std::string::npos) {
            skip = false;
            temp->img = token;
        } else {
            skip = true;
        }

        getline(myData, token, '~');
        //temp->isbn = token;

        getline(myData, token, '~');
        //temp->isbn13 = token;

        getline(myData, token, '~');
        //temp->link = token;

        getline(myData, token, '~');
        try {
            (temp->pageCount = stoi(token));
        } catch (invalid_argument){
            //Skips if no Valid Page Number
            skip = true;
        } catch (out_of_range){
            //Skips if no Valid Page Number
            skip = true;
        }

        getline(myData, token, '~');
        try {
            (temp->rating = stod(token));
        } catch (invalid_argument){
            //Skips if no Valid Rating
            skip = true;
        }

        getline(myData, token, '~');
        temp->review= token;

        getline(myData, token, '~');
        temp->title= token;

        getline(myData, token, '~');
        //temp->totalRatings= token;

        if (skip == false) {
            books[i]=temp;  //Once the values in the node are attributed the node is added to a vector
            i++;

            //vector<bool>tempVec;
            //adjList.push_back(tempVec);

            /*for (int i=0; i<100000;i++){
                adjList.at(i).push_back(false);
            }*/

        } else {
            //Frees from Memory if Node was not Added
            free(temp);
        }
    }
};
