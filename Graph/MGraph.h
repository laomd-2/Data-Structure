#ifndef M_GRAPH_H
#define M_GRAPH_H

#include <vector>
#include <stdexcept>
#include "source.h"
#include "Graph.h"

template<typename WeightType = double>
class MGraph : public Graph<unsigned, WeightType>
{
	using VertexType = unsigned;
	using Graph<VertexType, WeightType>::numOfEdges;
	using Graph<VertexType, WeightType>::INF;
	using Precursor = typename Graph<VertexType, WeightType>::Neighbor;
public:
	virtual unsigned numberOfVertices() const;
	virtual WeightType getWeight(const VertexType& src, const VertexType& des);

   	virtual void initialize();
   
	virtual void insertEdge(const VertexType&, const VertexType&, WeightType);

	virtual void removeEdge(const VertexType&, const VertexType&);

	virtual unsigned inDegree(const VertexType&);
    virtual unsigned outDegree(const VertexType&);

    virtual vector<VertexType> topSort();

	virtual WeightType findShortestPath(const VertexType&, 
										const VertexType&, 
										stack<VertexType>&);

	virtual VertexType MST(MGraph&);

	template<typename Visit>
	void BFS(const VertexType& begin, Visit&&);

	template<typename Visit>
	void DFS(const VertexType& begin, Visit&&);

private:
	virtual bool is_visited(const VertexType&);
	template<typename Visit>
	void visit(const VertexType&, Visit&&);
	virtual void reset();
	template<typename Visit>
	void DFS(const VertexType& begin, int, Visit&& doSomething);
private:
	std::vector<std::vector<WeightType>> neighborMatrix;
	map<VertexType, bool> visited;	
};

template<typename WeightType>
inline bool MGraph<WeightType>::is_visited(const VertexType& vertex) {
	return visited[vertex];
}

template<typename WeightType>
template<typename Visit>
inline void MGraph<WeightType>::visit(const VertexType& vertex, 
										Visit&& doSomething) {
	doSomething(vertex);
	visited[vertex] = true;
}

template<typename WeightType>
inline void MGraph<WeightType>::reset() {
	visited = map<VertexType, bool>();
}

template<typename WeightType>
inline unsigned MGraph<WeightType>::numberOfVertices() const {
	return neighborMatrix.size();
}

template<typename WeightType>
WeightType MGraph<WeightType>::getWeight(const VertexType& src, 
										const VertexType& des) {
	unsigned num = numberOfVertices();
	if (src < num && des < num)
	{
		return neighborMatrix[src][des];
	}
	else 
	{
		throw std::logic_error("vertex code out of range.");
	}
}

template<typename WeightType>
void MGraph<WeightType>::initialize() {
	for(auto& i : neighborMatrix) {
		for(auto& j : i) {
			j = INF;
		}
	}
}

template<typename WeightType> 
void MGraph<WeightType>::insertEdge(const VertexType& src, 
									const VertexType& des, 
									WeightType w)  {

	unsigned num = numberOfVertices();
	if (src <= num + 1 && des <= num + 1)
	{
		if (src >= num || des >= num)
		{
			unsigned newsize = (src > des ? src : des) + (src == des ? 0 : 1);

			neighborMatrix.resize(newsize);
			for(auto& i : neighborMatrix) {
				i.resize(newsize, INF);
			}
		}
		neighborMatrix[src][des] = w;
		if (!(w == INF))
		{
			numOfEdges++;
		}
	}
	else
	{
		throw std::logic_error("vertex code out of range.");
	}
}

template<typename WeightType>
void MGraph<WeightType>::removeEdge(const VertexType& src, 
									const VertexType& des) {

	unsigned num = numberOfVertices();
	if (src < num && des < num)
	{
		if (!(neighborMatrix[src][des] == INF))
		{
			neighborMatrix[src][des] = INF;
			numOfEdges--;
		}
		
	}
	else 
	{
		throw std::logic_error("vertex code out of range.");
	}
}

template<typename WeightType>
unsigned MGraph<WeightType>::inDegree(const VertexType& vertex) {
	unsigned num = numberOfVertices();
	if (vertex < num)
	{
		unsigned cnt = 0;
		for(const auto& i : neighborMatrix) {
			if (!(i[vertex] == INF))
			{
				cnt++;
			}
		}
		return cnt;
	}
	else 
	{
		throw std::logic_error("vertex code out of range.");
	}
}

template<typename WeightType>
unsigned MGraph<WeightType>::outDegree(const VertexType& vertex) {
	unsigned num = numberOfVertices();
	if (vertex < num)
	{
		unsigned cnt = 0;
		for(const WeightType& i : neighborMatrix[vertex]) {
			if (!(i == INF))
			{
				cnt++;
			}
		}
		return cnt;
	}
	else 
	{
		throw std::logic_error("vertex code out of range.");
	}
}
template<typename WeightType>
vector<typename MGraph<WeightType>::VertexType> 
					MGraph<WeightType>::topSort() {

	vector<VertexType> result;

	std::queue<VertexType> zeroDegVertexes;
	unsigned num = numberOfVertices();

	std::map<VertexType, unsigned> inDegreeOfVertex;

	for(VertexType vertex = 0; vertex < num; ++vertex) {
		inDegreeOfVertex[vertex] = inDegree(vertex);
	 	if (inDegreeOfVertex[vertex] == 0)
	 	{
	 		zeroDegVertexes.push(vertex);
	 	}
	} 

	VertexType curPrecursor;

	while(!zeroDegVertexes.empty()) {
		curPrecursor = zeroDegVertexes.front();
	    result.push_back(curPrecursor);
	    zeroDegVertexes.pop();

	    for(VertexType neighbor = 0; neighbor < num; ++neighbor) {
	    	if (!(neighborMatrix[curPrecursor][neighbor] == INF))
	    	{
	    		if (--inDegreeOfVertex[neighbor] == 0)
	    		{
	    			zeroDegVertexes.push(neighbor);
	    		}
	    	}
	    }
	}
	if (result.size() != num)
	{
		throw std::logic_error("The graph isn't a DAG!");
	}
	return result;
}

template<typename WeightType>
WeightType MGraph<WeightType>::findShortestPath(const VertexType& src, 
												const VertexType& des, 
												stack<VertexType>& result) {
	VertexType num = numberOfVertices();
	if(src < num && des < num) {
		
		map<VertexType, Precursor> shortestPath;
		map<VertexType, bool> isOk;

		using Pre = typename Graph<VertexType, WeightType>::Edge;
		std::priority_queue<Pre, std::vector<Pre>, std::greater<Pre> > minPre; 

		VertexType impossible = -1;

		for(VertexType vertex = 0; vertex < num; vertex++) {
			shortestPath[vertex].vertex = impossible;
			shortestPath[vertex].weight = vertex == src ? WeightType() : INF;
		}
		
		VertexType curPrecursor = src;

		while(curPrecursor != des) {
			isOk[curPrecursor] = true;
			
			const auto& arr = neighborMatrix[curPrecursor];
		    for(VertexType vertex = 0; vertex < num; vertex++) {
		    	WeightType weight = arr[vertex];
		    	if (!isOk[vertex])
		    	{
		    		if (weight < shortestPath[vertex].weight)
					{
						shortestPath[vertex].vertex = curPrecursor;
						shortestPath[vertex].weight = weight;
						minPre.push(Pre(vertex, vertex, weight));
					}
		    	}			
			}
			if (minPre.empty())
			{
				return INF;
			}
			else
			{
				curPrecursor = minPre.top().src;
				minPre.pop();
			}

		}
		
		WeightType total = WeightType();
		do
		{
			result.push(curPrecursor);
			total = total + shortestPath[curPrecursor].weight;
			curPrecursor = shortestPath[curPrecursor].vertex;
		} while (curPrecursor != src && curPrecursor != impossible);
		result.push(src);
		
		return total;
	}
	else {
		return INF;
	}
}

template<typename WeightType>
typename MGraph<WeightType>::VertexType 
					MGraph<WeightType>::MST(MGraph<WeightType>& result) {

	MGraph<WeightType> tree(*this);
	tree.initialize();
	
	using Edge = typename Graph<VertexType, WeightType>::Edge;
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > allEdges;

	unsigned num = numberOfVertices();

	for(VertexType i = 0; i < num; ++i) {
		for(VertexType j = 0; j < num; ++j) {
			if (i != j && !(neighborMatrix[i][j] == INF))
			{
				allEdges.push(Edge(i, j, neighborMatrix[i][j]));
			}
		}
	}

	VertexType impossible = -1;
	VertexType root = impossible;

	unionFindSet myset(num);

	unsigned cnt = 0;
	while(cnt < num - 1 && !allEdges.empty()) {
	    Edge e = allEdges.top();
	    allEdges.pop();
	    
	    if (myset.find(e.src) != myset.find(e.des))
	    {
	    	tree.insertEdge(e.src, e.des, e.weight);
	    	tree.insertEdge(e.des, e.src, e.weight);
	    	cnt++;
	    	myset.unite(e.src, e.des);
	    	if (root == impossible)
	    	{
	    		root = e.src;
	    	}
	    }
	}
	if (cnt != num - 1)
	{
		root = impossible;
	}
	else
	{
		result = tree;
	}
	
	return root;
}

template<typename WeightType>
template<typename Visit>
void MGraph<WeightType>::BFS(const VertexType& begin, 

							Visit&& doSomething) {
	int num = numberOfVertices();
	if(begin < num) {
		std::queue<VertexType> help;
		help.push(begin);
		while(!help.empty()) {
		    VertexType v = help.front();
		    help.pop();
		    if (!is_visited(v))
		    {
		    	visit(v, doSomething);
		    }
		    const auto& arr = neighborMatrix[v];
		    for (VertexType vertex = 0; vertex < num; vertex++) {
		    	if (!(arr[vertex] == INF)) 
		    	{
		    		if (!is_visited(vertex))
			    	{
			    		help.push(vertex);
			    	}
		    	}
		    }
		}
		reset();
	}
	else {
		throw std::logic_error("vertex code out of range.");
	}
}

template<typename WeightType>
template<typename Visit>
void MGraph<WeightType>::DFS(const VertexType& begin, 
							int, 
							Visit&& doSomething) {

	visit(begin, doSomething);

	const auto& arr = neighborMatrix[begin];
	unsigned num = numberOfVertices();
	for(VertexType vertex = 0; vertex < num; vertex++) {
		if (arr[vertex] != INF)
		{
			if (!is_visited(vertex))
			{
				DFS(vertex, 0, doSomething);
			}
		}
	}
}	

template<typename WeightType>
template<typename Visit>
void MGraph<WeightType>::DFS(const VertexType& begin, 
							Visit&& doSomething) {

	unsigned num = numberOfVertices();
	if (begin < num)
	{
		DFS(begin, 0, doSomething);
		reset();
	}
	else {
		throw std::logic_error("vertex code out of range.");
	}
}
#endif // M_GRAPH_H
