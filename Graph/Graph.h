#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <stack>
#include <map>
using std::stack;
using std::vector;
using std::map;

template<typename VertexType, typename WeightType>
class Graph
{
public:
	struct Edge
	{
		VertexType src;
		VertexType des;
		WeightType weight;
		Edge(VertexType s, VertexType d, WeightType w) : src(s), des(d), weight(w) {

		}
		friend bool operator< (const Edge& a, const Edge& b) {
			return a.weight < b.weight;
		}
		friend bool operator> (const Edge& a, const Edge& b) {
			return b < a;
		}
	};
	struct Neighbor
	{
		VertexType vertex;
		WeightType weight;
		Neighbor(VertexType n = VertexType(), WeightType w = WeightType()) : vertex(n), weight(w) {

		}
		friend bool operator< (const Neighbor& a, const Neighbor& b) {
			return a.vertex < b.vertex;
		}
	};
public:
	Graph() : numOfEdges(0) {}
	virtual unsigned numberOfVertices() const = 0;
	virtual WeightType getWeight(const VertexType& src, const VertexType& des) = 0;
    unsigned numberOfEdges() const {
    	return numOfEdges;
    }
    virtual unsigned inDegree(const VertexType&) = 0;
    virtual unsigned outDegree(const VertexType&) = 0;

    virtual vector<VertexType> topSort() = 0;

    void setUnconnectedWeight(WeightType w) {INF = w;};

	virtual void insertEdge(const VertexType&, const VertexType&, WeightType) = 0;
	virtual void removeEdge(const VertexType&, const VertexType&) = 0;

protected:
	unsigned numOfEdges;
	WeightType INF;
};

#endif // GRAPH_H
