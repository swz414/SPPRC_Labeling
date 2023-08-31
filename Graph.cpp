#include "Graph.h"

void Graph::addNode(int index, float_t corX, float_t corY, int demand, float_t readyTime, float_t dueTime, float_t serviceTime)
{
	nodes.emplace(index, Node{ index, corX, corY, demand, readyTime, dueTime, serviceTime});
}

void Graph::addEdge(int from, int to, float_t length, float_t travelTime)
{
	edges[from][to] = Edge{ from, to, length, travelTime };

	previous[to].insert(from);
	successors[from].insert(to);
}

Node* Graph::getNode(int index)
{
	return &nodes[index];
}

vector<Node*> Graph::getNodes()
{
	vector<Node*> rstVec;
	transform(
		nodes.begin(),
		nodes.end(),
		std::back_inserter(rstVec), // 需要使用back_inserter，它会自动为vector分配空间
		[](auto& kv) { return &(kv.second); }
	);
	return rstVec;
}

Edge* Graph::getEdge(int from, int to)
{
	return &edges[from][to];
}

vector<Edge*> Graph::getEdges(int from)
{
	vector<Edge*> rstVec;
	transform(
		edges[from].begin(),
		edges[from].end(),
		std::back_inserter(rstVec), // 需要使用back_inserter，它会自动为vector分配空间
		[](auto& kv) { return &(kv.second); }
	);

	return rstVec;
}

vector<Edge*> Graph::getAllEdges()
{
	vector<Edge*> retVec, tmpVec;
	for (const auto &kv : edges)
	{
		tmpVec = getEdges(kv.first);
		retVec.assign(tmpVec.begin(), tmpVec.end());
	}
	return retVec;
}

vector<int> Graph::getSuccessors(int from)
{
	return vector<int>(successors[from].begin(), successors[from].end());
}

vector<int> Graph::getPrevious(int to)
{
	return vector<int>(previous[to].begin(), previous[to].end());
}


