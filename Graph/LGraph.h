#ifndef DIRECTEDL_GRAPH_H
#define DIRECTEDL_GRAPH_H
#include <stdexcept>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <list>
#include "Graph.h"
#include "source.h"

using std::map;
using std::set;	

template<typename VertexType, typename WeightType>
class DirectedLGraph : public Graph<VertexType, WeightType>
{
protected:
	using Graph<VertexType, WeightType>::INF;
	map<VertexType, set<std::pair<VertexType, WeightType>>> neighborsList;
public:
	
	virtual unsigned numberOfVertices() const;
	virtual WeightType getWeight(const VertexType& src, const VertexType& des);

   	virtual void initialize();
   
	virtual void insertEdge(const VertexType&, const VertexType&, WeightType);

	virtual void removeEdge(const VertexType&, const VertexType&);

	virtual unsigned inDegree(const VertexType&);
    virtual unsigned outDegree(const VertexType&);

    virtual vector<VertexType> topSort();

	template<typename Rule>
	void findShortestPath(const VertexType&,const VertexType&,Rule,
		std::map<VertexType, VertexType>&,
        std::map<VertexType, WeightType>&);

	template<typename Visit>
	void BFS(const VertexType& begin, Visit&&);

	template<typename Visit>
	void DFS(const VertexType& begin, Visit&&);

private:
	void checkVertex(const VertexType&) const;
	template<typename Visit>
	void DFS(const VertexType&,std::map<VertexType, bool>,Visit&&);
};

template<typename VertexType, typename WeightType>
unsigned DirectedLGraph<VertexType, WeightType>::numberOfVertices() const {
	return neighborsList.size();
}

template<typename VertexType, typename WeightType>
void DirectedLGraph<VertexType, WeightType>::initialize() {
	for(auto& i : neighborsList) i.second.clear();
} 

template<typename VertexType, typename WeightType>
void DirectedLGraph<VertexType, WeightType>::checkVertex(const VertexType& v) const {
    if(neighborsList.find(v) == neighborsList.end()) {
        throw std::logic_error("The vertex is not in the graph");
    }
}

template<typename VertexType, typename WeightType>
WeightType DirectedLGraph<VertexType, WeightType>::getWeight(const VertexType& src,
													 const VertexType& des) {
	checkVertex(src);
    checkVertex(des);
    for(const auto& neighbor : neighborsList[src]) {
        if(neighbor.first == des) {
            return neighbor.second;
        }
    }
    return INF; 
}	

template<typename VertexType, typename WeightType>
inline void DirectedLGraph<VertexType, WeightType>::insertEdge(const VertexType& src, 
														const VertexType& des,
														WeightType w) {
	if (!(w == INF))
    {
    	neighborsList[src].insert(std::make_pair(des, w));
        neighborsList[des];
    }
	
}

template<typename VertexType, typename WeightType>
inline void DirectedLGraph<VertexType, WeightType>::removeEdge(const VertexType& src, 
														const VertexType& des) {
	checkVertex(src);
	checkVertex(des);
	set<std::pair<VertexType, WeightType>>& neighbors = neighborsList[src];
	for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
		if(it->first == des) {
			neighbors.erase(it);
			break;
		}	
	}
}

template<typename VertexType, typename WeightType>
unsigned DirectedLGraph<VertexType, WeightType>::inDegree(const VertexType& vertex) {
	checkVertex(vertex);
	unsigned cnt = 0;
	for(const auto& v : neighborsList) {
		for(const auto& p : v.second) {
			if(p.first == vertex)
				cnt++;
		}
	}
	return cnt;
}

template<typename VertexType, typename WeightType>
unsigned DirectedLGraph<VertexType, WeightType>::outDegree(const VertexType& vertex) {
	checkVertex(vertex);
	return neighborsList[vertex].size();
}

template<typename VertexType, typename WeightType>
vector<VertexType> DirectedLGraph<VertexType, WeightType>::topSort() {
	vector<VertexType> result;

	std::queue<VertexType> zeroDegVertexes;
	unsigned num = numberOfVertices();

	std::map<VertexType, unsigned> inDegreeOfVertex;

	VertexType vertex;

	for(const auto& i : neighborsList) {
		vertex = i.first;
		inDegreeOfVertex[vertex] = inDegree(vertex);
	 	if (inDegreeOfVertex[vertex] == 0)
	 	{
	 		zeroDegVertexes.push(vertex);
	 	}
	}

	while(!zeroDegVertexes.empty()) {
		VertexType curPrecursor = zeroDegVertexes.front();
		zeroDegVertexes.pop();
	    result.push_back(curPrecursor);
	    
	    for(const auto& v : neighborsList[curPrecursor]) {
	    	if (--inDegreeOfVertex[v.first] == 0)
    		{
    			zeroDegVertexes.push(v.first);
    		}
	    }
	}
	if (result.size() != num)
	{
		throw std::logic_error("The graph isn't a DAG!");
	}
	return result;
}

template<typename VertexType, typename WeightType>
template<typename Rule>
void DirectedLGraph<VertexType, WeightType>::findShortestPath(const VertexType& src,
                                                            const VertexType& des,
                                                            Rule rule,
                                                            std::map<VertexType, VertexType>& precursor,
                                                            std::map<VertexType, WeightType>& distances) {
    checkVertex(src);
    checkVertex(des);
    std::map<VertexType, bool> isOK;
    
    auto pred = [&](const VertexType& a, const VertexType& b) {
        return rule(distances[a]) > rule(distances[b]);
    };
    std::priority_queue<VertexType, std::vector<VertexType>, decltype(pred)> bests(pred);

    for(const auto& v : neighborsList) {
        precursor[v.first] = v.first;
        distances[v.first] = INF;
    }
    distances[src] = WeightType();
    bests.push(src);

    while(!bests.empty()) {
    	VertexType best = bests.top();
        bests.pop();
        isOK[best] = true;
        for(const auto& neighbor: neighborsList[best]) {
            VertexType n = neighbor.first;
            if (!isOK[n])
            {
                WeightType new_weight = distances[best] + neighbor.second;
                if (rule(new_weight) < rule(distances[n]))
                {
                    precursor[n] = best;
                    distances[n] = new_weight;
                    bests.push(n);
                }
            }
        }
    }
}

template<typename VertexType, typename WeightType>
template<typename Visit>
void DirectedLGraph<VertexType, WeightType>::BFS(const VertexType& begin, 
										Visit&& doSomething) {
	checkVertex(begin);
	std::queue<VertexType> help;
	std::map<VertexType, bool> visited;
	help.push(begin);
	while(!help.empty()) {
	    VertexType v = help.front();
	    help.pop();
	    if (!visited[v])
	    {
	    	doSomething(v);
	    	visited[v] = true;
	    	for (const auto& n : neighborsList[v]) {
		    	if (!visited[n.first])
		    	{
		    		help.push(n.first);
		    	}
		    }
	    }
	}
}

template<typename VertexType, typename WeightType>
template<typename Visit>
void DirectedLGraph<VertexType, WeightType>::DFS(const VertexType& begin,
										 std::map<VertexType, bool> visited,
										 Visit&& doSomething) {

	doSomething(begin);
	visited[begin] = true;
	for(const auto& v : neighborsList[begin]) {
		if (!visited[v.first])
		{
			DFS(v.first, visited, doSomething);
		}
	}
}	

template<typename VertexType, typename WeightType>
template<typename Visit>
inline void DirectedLGraph<VertexType, WeightType>::DFS(const VertexType& begin,
												Visit&& doSomething) {
	checkVertex(begin);
	std::map<VertexType, bool> visited;
	DFS(begin, visited, doSomething);
}	

#endif // DIRECTEDL_GRAPH_H
