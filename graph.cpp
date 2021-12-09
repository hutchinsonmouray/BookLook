#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <map>
#include <numeric>


using namespace std;

struct Node {
    string author, genre, bookFormat, isbn, isbn13, desc, img, link;
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
    vector<int[100000]> adjMatrix;
	    // or vector<vector<int>>adjMatrix; ??? the 2D array was stated as "too large" for CLion

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

    //final recommendation lists
    vector<Node*> recBooksDFS;
    vector<Node*> recBooksBFS;
};

void Graph::constructMatrix() {
//for each book 0->9999999
    for (int i = 0; i < 100000; i++) {
        basic_string<char> genresB1 = books[i]->genre;
        adjMatrix[i][i] = 1; //book is a adj to itself

        for (int j = i+1; j < 100000; i++) { //check if any books after are adj to it
           string genresB2 = books[j]->genre; //genres of new book

                size_t pos = 0;
                 //while there are more genres to look into for book 1 pull a new one
                    while ((pos = genresB1.find(',')) != string::npos) {
                        string tempB1 = genresB1.substr(0, pos);
                        genresB1.erase(0, pos + 1);

                        //for each of those genres pulled for book 1 compare with all genres of book 2
                        while ((pos = genresB2.find(',')) != string::npos) {
                            string tempB2 = genresB2.substr(0, pos);
                            genresB2.erase(0, pos + 1);

                            //if book 1 & 2 share this genre
                            if (tempB1 == tempB2) {
                                adjMatrix[i][j] = 1;
                            }

                        }
                    }

                }
    }

};
void Graph::DFS(int v) { //DFS from a random src node
visited = new bool[100000];

visited[v] = true;
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

    if (recBook1DFS!=-1) {
        // Recur for all the vertices adjacent to this vertex
        for (int i=0; i<100000;i++) {
            //adjMatrix[v][i]==1 b/c the need to travel via edge
            if (!visited[adjMatrix[v][i]] && adjMatrix[v][i]==1)
                DFS(i);
         }
    }


  //  First take in two genres out of the parameters and pick an arbitrary node and use breadth first search or depth first search and stop once any of the genres are a match.

           // Take this node and put it and all nodes it has an edge with and both matching genres.
           // Return this as a vector.



}
void Graph::BFS(int v) { //BFS from a random src node
    std::list<int> toBeVisted;
    visited = new bool[100000];

    visited[v] = true;
    string genresB2 = books[v]->genre;

    size_t pos = 0;
    while ((pos = genresB2.find(',')) != string::npos) {
        string tempB2 = genresB2.substr(0, pos);
        genresB2.erase(0, pos + 1);

        //if book & target genre share this genre
        if (targGenre1 == tempB2 || targGenre2 == tempB2) {
            //could push any genre that's connected into graph??
            recBook1BFS = v;

        }
    }

    if (recBook1BFS!=-1) { //how is the recursion diff for DFS
        // Recur for all the vertices adjacent to this vertex
        for (int i=0; i<100000;i++) {
            if (!visited[adjMatrix[v][i]] && adjMatrix[v][i]==1)
                toBeVisted.push_back(i);
        }
    }

}

//the Graph Search function satisfied this part of the write up:

//  First (1) take in two genres out of the parameters and (2) pick an arbitrary node and (3) use breadth first search
//  or (4) depth first search and stop once any of the genres are a match.

// (5) Take this node and put it and all nodes it has an edge with and both matching genres.
// Return this as a vector.

void Graph::Search(string genre1, string genre2){
    //(1)
targGenre1 = genre1;
targGenre2 = genre2;
    //(2)
//random generated number from 1-100000
    int sum =1;
    int b = 0;

    while (sum<=1){
        //if we start with a node not connected to any others -> pick a new node?
        sum=0;
        int b = rand() % 99999 + 1;
        std::accumulate(adjMatrix[b],adjMatrix[b]+100000 , sum);
    }

    //(4)
    DFS(b); //does DFS & defines recBook1DFS (aka: index of first matching book)
    BFS(b); //does BFS & defines recBook1BFS (aka: index of first matching book)

    //(5)
    //complete the book lists using recBook1DFS & recBook1BFS
    for (int i=0; i<100000; i++){
       if  (adjMatrix[recBook1BFS][i]==1)
           recBooksBFS.push_back(books[i]);

        if  (adjMatrix[recBook1DFS][i]==1)
            recBooksDFS.push_back(books[i]);
    }

}



//Traverses through the CSV file and creates a node for each line

void Graph::readFile(){

    ifstream file("GoodReads_100k_books.csv");
    string input;
    getline(file, input);
    int i=0;

    while(getline(file, input)){

        stringstream myData(input);
        Node* temp = new Node();
        string token;

        getline(myData, token, ',');
        temp->author = token;

        getline(myData, token, ',');
        temp->bookFormat = token;

        getline(myData, token, ',');
        temp->genre = token;

        getline(myData, token, ',');
        temp->img = stoi(token);

        getline(myData, token, ',');
        temp->isbn= token;

        getline(myData, token, ',');
        temp->isbn13 = token;

        getline(myData, token, ',');
        temp->link= token;

        getline(myData, token, ',');
        temp->pageCount = stoi(token);

        getline(myData, token, ',');
        temp->rating = stod(token);

        getline(myData, token, ',');
        temp->review= token;

        getline(myData, token, ',');
        temp->title = token;

        getline(myData, token, ',');
        temp->totalRatings= token;


        books[i]=temp;  //Once the values in the node are attributed the node is added to a vector
        i++;
    }
};
