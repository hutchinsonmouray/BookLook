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
	Node* books[100000];
	int adjMatrix[100000][100000];	
	void constructMatrix();
};

Graph::constructMatrix() {
};

//Traverses through the CSV file and creates a node for each line
void readFile(){ 		
	ifstream file("GoodReads_100k_books.csv");
	string input;
	getline(file, input);
	int i=0;
	while(getline(file, input)){
        stringstream myData(input);
        Node temp = new Node();
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
	books[i]=temp;  //Once the vaues in the node are attributed the node is added to a vector
	i++;
    }
};

