#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cfloat>
#include "Graph.h"
#include "PriorityQueue.h"

void Graph::destory() {
    delete [] myAdj;
    myAdj = 0;
    myVerNum = 0;
    myEdgeNum = 0;
}

void Graph::copyAll(const Graph &that) {
    myVerNum = that.V();
    myEdgeNum = that.E();
    myAdj = new std::vector<Edge> [myVerNum];
    for (int i = 0; i < myVerNum; ++i) {
        myAdj[i] = that.myAdj[i];
    }
}


//if random num fails in 0 - 19, it denotes there is a edge(return true); otherwise
//there is no edge(return false).
bool Graph::has_edge(int density) const {
    int random_num = rand() % 100;
    if (random_num < density) {
        return true;
    }
    return false;
}

void Graph::random_graph_generator(int density, double lower_bound, double upper_bound) {
    double range = upper_bound - lower_bound;
    for (int i = 0; i < myVerNum; ++i) {
        for (int j = i + 1; j < myVerNum; ++j) {
            if (has_edge(density) == true) {
                double random_num = (static_cast<double>(rand())) / (static_cast<double>(RAND_MAX));
                double random_offset = random_num * range;
                double weight = lower_bound + random_offset;
                Edge e(i, j, weight);
                add(e);
            }
        }
    }
}

Graph::Graph(int myVerNum) : myVerNum(myVerNum), myEdgeNum(0), myAdj(0) {
    myAdj = new std::vector<Edge> [myVerNum];
}

Graph::Graph(int myVerNum, int density, double lower_bound, double upper_bound) : myVerNum(myVerNum), myEdgeNum(0), myAdj(0) {
    myAdj = new std::vector<Edge> [myVerNum];
    random_graph_generator(density, lower_bound, upper_bound);
}

Graph::Graph(const std::string &fileName) : myVerNum(0), myEdgeNum(0), myAdj(0) {
    const char* file_name = fileName.c_str();
    std::ifstream infile;
    infile.open(file_name);
    if (infile.is_open() == false) {
        std::cout << "The input file cannot be open." << std::endl;
        assert(false);
    }
    infile >> myVerNum;
    myAdj = new std::vector<Edge> [myVerNum];
    while (true) {
        int x = 0, y = 0;
        double weight = 0;
        infile >> x;
        if (infile.good() == false) {
            break;
        }
        infile >> y >> weight;
        Edge e(x, y, weight);
        add(e);
    }

    infile.close();
}

Graph::Graph(const Graph &that) : myVerNum(0), myEdgeNum(0), myAdj(0) {
    copyAll(that);
}

const Graph & Graph::operator=(const Graph &that) {
    if (this != &that) {
        destory();
        copyAll(that);
    }
    return *this;
}

Graph::~Graph() {
    destory();
}

void Graph::connect(int x, int y, double weight) {
    assert(x >= 0 && x < myVerNum && y >= 0 && y < myVerNum);
    Edge e(x, y, weight);
    add(e);
}

int Graph::V() const {
    return myVerNum;
}

int Graph::E() const {
    return myEdgeNum;
}

bool Graph::adjacent(int x, int y) const {
    assert(x >= 0 && x < myVerNum && y >= 0 && y < myVerNum);
    for (int i = 0; i < static_cast<int>(myAdj[x].size()); ++i) {
        Edge e = myAdj[x][i];
        if (e.to() == y) {
            return true;
        }
    }
    return false;
}

std::vector<Edge> Graph::neighbors(int x) const {
    assert(x >= 0 && x < myVerNum);
    return myAdj[x];
}

void Graph::set_edge_color(int x, int y, Color c) {
    assert(x >= 0 && x < myVerNum && y >= 0 && y < myVerNum);
    for (std::vector<Edge>::iterator it = myAdj[x].begin(); it != myAdj[x].end(); ++it) {
        if (it->to() == y) {
            it->setColor(c);
            break;
        }
    }

    for (std::vector<Edge>::iterator it = myAdj[y].begin(); it != myAdj[y].end(); ++it) {
        if (it->to() == x) {
            it->setColor(c);
            break;
        }
    }
}

void Graph::add(const Edge &e) {
    int x = e.from(), y = e.to();
    assert(x >= 0 && x < myVerNum && y >= 0 && y < myVerNum);
    if (adjacent(x, y) == true) {
        return;
    }
    myAdj[x].push_back(e);
    Edge tmp(y, x, e.weight());
    myAdj[y].push_back(tmp);
    myEdgeNum += 2;
}

void Graph::remove(int x, int y) {
    assert(x >= 0 && x < myVerNum && y >= 0 && y < myVerNum);
    for (std::vector<Edge>::iterator it = myAdj[x].begin(); it != myAdj[x].end(); ) {
        Edge e = *it;
        if (e.to() == y) {
            it = myAdj[x].erase(it);
        } else {
            ++it;
        }
    }

    for (std::vector<Edge>::iterator it = myAdj[y].begin(); it != myAdj[y].end(); ) {
        Edge e = *it;
        if (e.to() == x) {
            it = myAdj[y].erase(it);
        } else {
            ++it;
        }
    }
}

double Graph::get_edge_value(int x, int y) const {
    assert(x >= 0 && x < myVerNum && y >= 0 && y < myVerNum);
    for (int i = 0; i < static_cast<int>(myAdj[x].size()); ++i) {
        Edge e = myAdj[x][i];
        if (e.to() == y) {
            return e.weight();
        }
    }
    return -1;
}

void Graph::set_edge_value(int x, int y, double val) {
    assert(x >= 0 && x < myVerNum && y >= 0 && y < myVerNum);
    for (int i = 0; i < static_cast<int>(myAdj[x].size()); ++i) {
        Edge e = myAdj[x][i];
        if (e.to() == y) {
            myAdj[x][i].setWeight(val);
        }
    }

    for (int i = 0; i < static_cast<int>(myAdj[y].size()); ++i) {
        Edge e = myAdj[y][i];
        if (e.to() == x) {
            myAdj[y][i].setWeight(val);
        }
    }
}

void Graph::print() const {
    for (int i = 0; i < myVerNum; ++i) {
        std::cout << "Ver#" << i << ": " << std::endl;
        for (int j = 0; j < static_cast<int>(myAdj[i].size()); ++j) {
            myAdj[i][j].print();
        }
    }
}


void Graph::MST() const {

    double* distance = new double [myVerNum];
    int* pred = new int [myVerNum];
    bool* mark = new bool [myVerNum];
    for (int i = 0; i < myVerNum; ++i) {
        distance[i] = DBL_MAX;
        pred[i] = -1;
        mark[i] = false;
    }
    PriorityQueue pq;
    Distance source(0, 0.0);
    pq.insert(source);
    distance[0] = 0.0;
    while (pq.empty() == false) {
        Distance cur_dis = pq.delMin();
        int cur_verNum = cur_dis.getVerNum();
        if (mark[cur_verNum] == true) {     //already passed this vertice
            continue;
        }
        mark[cur_verNum] = true;
        const std::vector<Edge> adj_edge_vec = neighbors(cur_verNum);
        for (unsigned i = 0; i < adj_edge_vec.size(); ++i) {
            Edge cur_edge = adj_edge_vec[i];
            int next_verNum = cur_edge.to();
            double weight = cur_edge.weight();
            if (mark[next_verNum] == false && distance[next_verNum] > weight) {
                pred[next_verNum] = cur_verNum;
                distance[next_verNum] = weight;
                Distance tmp(next_verNum, distance[next_verNum]);
                pq.insert(tmp);
            }
        }
    }
    double cost = 0.0;
    std::vector<Edge> mst;
    for (int i = 1; i < myVerNum; ++i) {
        double weight = get_edge_value(pred[i], i);
        Edge e(pred[i], i, weight);
        mst.push_back(e);
        cost += weight;
    }
    std::cout << "The cost of MST is " << cost << ". And tree edges are as following: " << std::endl;
    for (unsigned i = 0; i < mst.size(); ++i) {
        mst[i].print();
    }
    delete [] distance;
    delete [] pred;
    delete [] mark;
}
