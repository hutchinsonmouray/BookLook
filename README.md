# Project3

Team Name: Group 83

Team Members:
Mouray Hutchinson
Morgan Cobb
Colbi Hopkins

Project Title: BookLook 

Problem:
The problem that this project is solving is taking information about a user’s desired book and returning an appropriate recommendation to them. 

Motivation:
BookLook provides a platform for users to be able to find books according to specific search parameters. It is most effective in scenarios where users are researching a particular topic or are looking for material to read for fun. It helps with targeted book searches and alleviates the need to spend hours looking for a book.

Features: 
We know that we have solved the problem when we can return at least 5 books that match the most of the passed in parameters of the user. 

Data:

Description:
We will use a data set with 100,000 books of different lengths, genres, and authors.

Link: https://www.kaggle.com/mdhamani/goodreads-books-100k?select=GoodReads_100k_books.csv

Vertices: Page Length, Genres, Image of Book, and Author
Edges: Genres

Tools: Programming languages or any tools/frameworks we will be using [0.25 point]
C++ (most familiar development language)
Github (to work on development as a team)
QT.io for GUI Menu and Visuals (free open source GUI tool)

Strategy:
The strategy used for this project will include using a queue for all nodes that are connected via edge and then pop each one off the queue as the number of similarities is counted. Then a node pointer is placed in a map <int, Node*> with the int being how similar it is to the original node. This new list will then be separated by additional parameters several times until we narrow down a list of the top 10 books for the user. 

We will use a depth first search algorithm and compare it with a breadth first search algorithm; this will function as the two algorithms for achieving the same task. We will compare and critically analyze the performance by comparing their run times with one another. 

Graph Algorithms
A Depth-first search
A Breadth-first search
  
Distribution of Responsibility and Roles: Who is responsible for what? [0.25 points]  

Graphical User Interface and Video - Colbi Hopkins
Dataset CSV entry - Morgan Cobb
Search Algorithm Implementation - Mouray Hutchinson
Graph Construction - Mouray Hutchinson/Morgan Cobb

References 
Discussion 10 pptx - Graph definitions, implementations, and searching








Structure:
Main.cpp //taking in user input
graph.cpp / implementation of graph
  - node class





