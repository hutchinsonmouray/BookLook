#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
 
struct Node {
    string author, genre, bookFormat, isbn, isbn13, desc, img, link;
	int pageCount;
	double rating;
};

struct Edge {
    int src, dest;
};


class Graph
{
public:

	vector<Node*> books;
	int numNodes=0; //number of nodes in the graph
	int x;
	int y;
	
    //adjacency matrix
    vector<vector<int>> adjMatrix;
 
    //Constructor
    Graph(vector<Edge> const &edges, int n)
    {
        
    }
};

void readFile(){
	ifstream file("GoodReads_100k_books.csv");
    string input;
    getline(file, input);
    while(getline(file, input)){
        stringstream myData(input);
        Node temp;
        string token;
        getline(myData, token, ',');
        temp.author = token;
        getline(myData, token, ',');
        temp.bookFormat = token;
        getline(myData, token, ',');
        temp.desc= token;
        getline(myData, token, ',');
        temp.genre = token;
        getline(myData, token, ',');
        temp.img = stoi(token);
		getline(myData, token, ',');
        temp.isbn= token;
        getline(myData, token, ',');
        temp.isbn13 = token;
        getline(myData, token, ',');
        temp.link= token;
        getline(myData, token, ',');
        temp.pageCount = stoi(token);
		getline(myData, token, ',');
        temp.rating = stod(token);
		books.push_back(temp);
    }
};

/*
- creating 100,000
- inserting values to nodes
- store in vector/arr
*/