#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <vector>
#include <string>
#include "Edge.h"

class Graph {
  private:
   int mySize;
   int myVerNum;
   int myEdgeNum;
   std::vector<Edge>* myAdj;

  public:
   Graph(int myVerNum = 0); //generate a empty graph containing certain # vertices
   Graph(int myVerNum, int density, double lower_bound, double upper_bound);
   Graph(const std::string &fileName);
   Graph(const Graph &that);
   const Graph & operator=(const Graph &that);
   ~Graph();
   void connect(int x, int y, double weight = 1.0);     //connect x & y point default edge weight is 1.0
   int V() const;   //return num of vertices in the graph
   int E() const;   //return num of edges in the graph
   bool adjacent(int x, int y) const;   //test whether there is a edge from x to y
   std::vector<Edge> neighbors(int x) const;  //put all edge from x to y into neighbor
   void add(const Edge &e);    //add edge e to the graph
   void set_edge_color(int x, int y, Color c);     //set color for the edge specified by x and y
   void remove(int x, int y);   //remove edge x to y from the graph, if it is there
   double get_edge_value(int x, int y) const;    //return the edge weight from x to y, if it is there; otherwise return -1
   void set_edge_value(int x, int y, double val);  //set the val as the edge weight from x to y
   void MST() const;    //Prim's MST Algorithm
   void print() const;

  private:
   void destory();
   void copyAll(const Graph &that);
   bool has_edge(int density) const;   //determin whether there is a edge randomly
   void random_graph_generator(int density, double lower_bound, double upper_bound);

};

#endif
