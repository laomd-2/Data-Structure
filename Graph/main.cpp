#include <iostream>
#include <stack>
#include <cfloat>
#include "LGraph.h"
#include "UndirectedLGraph.h"
#include "MGraph.h"
using namespace std;

struct WeightType
{
	double distance;
	double cost;
	WeightType(double dist = 0, double c = 0) 
					: distance(dist), cost(c) {

	}

	bool operator< (const WeightType& other) const {
		return distance < other.distance 
			|| distance == other.distance && cost < other.cost;
	}
	
	bool operator== (const WeightType& other) const {
		return distance == other.distance && cost == other.cost;
	}

	WeightType operator+ (const WeightType& other) const {
		return WeightType(distance + other.distance, cost + other.cost);
	}
};
void testLGraph() {
	UnDirectedLGraph<int, WeightType> g;
	g.setUnconnectedWeight(WeightType(DBL_MAX, DBL_MAX));
	g.initialize();

	g.insertEdge(0, 1, WeightType(1, 15));
	g.insertEdge(0, 2, WeightType(2, 20));
	g.insertEdge(0, 3, WeightType(4, 10));
	g.insertEdge(1, 4, WeightType(5, 10));
	g.insertEdge(2, 3, WeightType(4, 12));

	map<int, WeightType> distance;
	map<int,int> pre;
	auto rule = [](WeightType w) {
		return w.distance;
	};
	int src = 1, des = 3;
	g.findShortestPath(src, des, rule, pre, distance);
	cout << "shortest distance from " << src << " to " << des << ": ";
	cout << rule(distance[des]) << endl;
	
	/*cout << "top sort:" << endl;
	for(auto i : g.topSort()) cout << i << ' ';
	cout << endl;*/

	cout << "Minimal spanning tree:" << endl;
	UnDirectedLGraph<int, WeightType> k;
	WeightType w;
	tie(k, w) = g.MST(rule);
	cout << "total weight: "<< rule(w) << endl;
	k.BFS(0, [](int v) {
		cout << v << ' ';
	});
	cout << endl;
	
	
}      
void testMGraph() {
	MGraph<WeightType> g;
	g.setUnconnectedWeight(WeightType(DBL_MAX, DBL_MAX));
	g.initialize();

	g.insertEdge(0, 1, WeightType(1, 15));
	g.insertEdge(0, 2, WeightType(2, 20));
	g.insertEdge(0, 3, WeightType(4, 10));
	g.insertEdge(1, 3, WeightType(2, 25));
	g.insertEdge(2, 3, WeightType(1, 15));
	g.insertEdge(3, 4, WeightType(2, 26));

	stack<unsigned> path;
	g.findShortestPath(0, 4, path);

	while(!path.empty()) {
	    cout << path.top();
	    path.pop();
	    if (path.empty())
	    {
	    	cout << endl;
	    }
	    else
	    {
	    	cout << "->";
	    }
	}

	MGraph<WeightType> k;
	unsigned root = g.MST(k);
	k.BFS(root, [](unsigned v) {
		cout << v << ' ';
	});
	cout << endl;
 
}
int main(int argc, char const *argv[])
{
	testLGraph();
//	testMGraph();
	return 0;
}
