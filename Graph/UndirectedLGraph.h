#ifndef UNDIRECTEDL_GRAPH_H
#define UNDIRECTEDL_GRAPH_H

#include "LGraph.h"
template<typename VertexType, typename WeightType>
class UnDirectedLGraph : public DirectedLGraph<VertexType, WeightType> 
{
	using Base = DirectedLGraph<VertexType, WeightType>;
	using Base::numberOfVertices;
	using Base::neighborsList;
	using Base::getWeight;
	using Base::INF;
public:
	template<typename Rule>
	std::pair<UnDirectedLGraph, WeightType> MST(Rule);
	virtual void insertEdge(const VertexType&, const VertexType&, WeightType);
	virtual void removeEdge(const VertexType&, const VertexType&);
private:
	template<typename Rule>
	std::pair<UnDirectedLGraph, WeightType> PrimMST(Rule);
};

template<typename VertexType, typename WeightType>
inline void UnDirectedLGraph<VertexType, WeightType>::insertEdge(const VertexType& src, 
														const VertexType& des,
														WeightType w) {
	Base::insertEdge(src, des, w);
	Base::insertEdge(des, src, w);	
}

template<typename VertexType, typename WeightType>
inline void UnDirectedLGraph<VertexType, WeightType>::removeEdge(const VertexType& src, 
														const VertexType& des) {
	Base::removeEdge(src, des);
	Base::removeEdge(des, src);
}

template<typename VertexType, typename WeightType>
template<typename Rule>
std::pair<UnDirectedLGraph<VertexType, WeightType>, WeightType> UnDirectedLGraph<VertexType, WeightType>::MST(Rule rule) {
	return PrimMST(rule);
}

template<typename VertexType, typename WeightType>
template<typename Rule>
std::pair<UnDirectedLGraph<VertexType, WeightType>, WeightType> UnDirectedLGraph<VertexType, WeightType>::PrimMST(Rule rule) {
	UnDirectedLGraph<VertexType, WeightType> result(*this);
	result.initialize();
	WeightType w;

	if(numberOfVertices()) {
		map<VertexType, WeightType> distances;
		map<VertexType, VertexType> neighbor;
		map<VertexType, bool> isOK;
		
		auto pred = [&](const VertexType& a, const VertexType& b) {
			WeightType da = distances[a], db = distances[b];
			return rule(da) > rule(db) || (rule(da) == rule(db) && a >= b);
		};
		std::priority_queue<VertexType, std::vector<VertexType>, decltype(pred)> bests(pred);
		
		auto it = neighborsList.begin();
		VertexType root = it->first;
		distances[root] = WeightType();
		neighbor[root] = root;
		++it;
		while(it != neighborsList.end()) {
			distances[it->first] = INF;
			neighbor[it->first] = root;
			++it;
		}
		bests.push(root);
		while(!bests.empty()) {
			VertexType best = bests.top();
			bests.pop();
			if(!isOK[best]) {
				isOK[best] = true;
				w = w + distances[best];
				VertexType n = neighbor[best];
				if(!(n == best)) {
					result.insertEdge(best, n, distances[best]);
				}
				for(const auto& p : neighborsList[best]) {
					if(!isOK[p.first]) {
						if(rule(p.second) < rule(distances[p.first])) {
							distances[p.first] = p.second;
							neighbor[p.first] = best;
							bests.push(p.first);
						}
					}
				}
			}
		}
	}
	return std::make_pair(result, w);
}
#endif 
