#include "Label.h"
#include<stdio.h>
#include<windows.h>

Label LabellingAlg::labelling_SPPRC(Graph graph, int org, int des)
{
	vector<Label> Queue;

	Label label;
	label.path.push_back(org);
	Queue.push_back(label);

	map<int, Label> Paths;
	int cnt = 0;
	while (Queue.size() > 0)
	{
		db_print(DB_NORMAL, "Queue: %d\n", Queue.size());
		cnt += 1;

		Label curLabel = Queue[0];

		Queue.erase(Queue.begin());

		int lastNode = curLabel.path[curLabel.path.size() - 1];

		for (int child : graph.getSuccessors(lastNode))
		{
			Label extendedPath = curLabel;
			int arcFrom = lastNode;
			int arcTo = child;

			Edge* curEdge = graph.getEdge(arcFrom, arcTo);
			Node* curNode = graph.getNode(child);
			float_t arriveTime = curLabel.time + curEdge->travelTime;
			int readyTime = curNode->readyTime;
			int dueTime = curNode->dueTime;

			if (count(extendedPath.path.begin(), extendedPath.path.end(), child) == 0 &&
				arriveTime >= readyTime && arriveTime <= dueTime)
			{
				extendedPath.path.push_back(child);
				extendedPath.dis += curEdge->length;
				extendedPath.time += curEdge->travelTime;

				Queue.push_back(extendedPath);
			}
		}

		Paths[cnt] = curLabel;

		dominate(Queue, Paths);
	}

	map<int, Label> PathsCopy(Paths);
	for (auto ul: PathsCopy)
	{
		int key = ul.first;
		if (ul.second.path.back() != des)
		{
			Paths.erase(key);
		}
	}

	int minKey = -1;
	float_t minDis = 10000000;
	for (auto &ul: Paths)
	{
		int key = ul.first;
		if (ul.second.dis < minDis)
		{
			minDis = ul.second.dis;
			minKey = key;
		}
	}

	Label optPath = Paths[minKey];

	return optPath;
}

void LabellingAlg::dominate(vector<Label>& Queue, map<int, Label>& Paths)
{
	vector<Label> QueueCopy(Queue.begin(), Queue.end());
	map<int, Label> PathsCopy(Paths);

	vector<int> delIndexs;
	for (Label label : QueueCopy)
	{
		for (int i = 0; i < Queue.size(); ++i)
		{
			if (label.path[label.path.size() - 1] == Queue[i].path[Queue[i].path.size() - 1] && label.time < Queue[i].time && label.dis < Queue[i].dis)
			{
				delIndexs.push_back(i);
			}
		}
	}
	sort(delIndexs.rbegin(), delIndexs.rend());

	for (int index : delIndexs)
	{
		Queue.erase(Queue.begin() + index);
	}

	for (auto &ul1: PathsCopy)
	{
		int key1 = ul1.first;
		for (auto &ul2: PathsCopy)
		{
			int key2 = ul2.first;

			if (PathsCopy[key1].path.back() == PathsCopy[key2].path.back()
				&& PathsCopy[key1].time < PathsCopy[key2].time
				&& PathsCopy[key1].dis < PathsCopy[key2].dis
				&& Paths.count(key2) > 0)
			{
				Paths.erase(key2);
			}
		}
	}
}
