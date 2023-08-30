#include "Label.h"
#include<stdio.h>
#include<windows.h>

void LabellingAlg::labelling_SPPRC(Graph graph, int org, int des)
{
	vector<Label> Queue;

	Label label;
	label.path.push_back(org);
	Queue.push_back(label);

	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);

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

			Edge curEdge = graph.getEdge(arcFrom, arcTo);
			float_t arriveTime = curLabel.time + curEdge.travelTime;
			int readyTime = graph.getNode(child).readyTime;
			int dueTime = graph.getNode(child).dueTime;

			if (count(extendedPath.path.begin(), extendedPath.path.end(), child) == 0 &&
				arriveTime >= readyTime && arriveTime <= dueTime)
			{
				extendedPath.path.push_back(child);
				extendedPath.dis += curEdge.length;
				extendedPath.time += curEdge.travelTime;

				Queue.push_back(extendedPath);
			}
		}

		Paths[cnt] = curLabel;

		dominate(Queue, Paths);
	}

	QueryPerformanceCounter(&t2);
	dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	cout << "Running time1:" << dt * 1000 << "ms" << endl;

	map<int, Label> PathsCopy(Paths);
	for (auto ul = PathsCopy.begin(); ul != PathsCopy.end(); ++ul)
	{
		int key = (*ul).first;
		if (Paths[key].path[Paths[key].path.size() - 1] != des)
		{
			Paths.erase(key);
		}
	}

	int minKey = -1;
	float_t minDis = 10000000;
	for (auto ul = Paths.begin(); ul != Paths.end(); ++ul)
	{
		int key = (*ul).first;
		if (Paths[key].dis < minDis)
		{
			minDis = Paths[key].dis;
			minKey = key;
		}
	}

	Label optPath = Paths[minKey];

	db_print(DB_NORMAL, "minDis: %f, minTime: %f\n", optPath.dis, optPath.time);
	for (int index : optPath.path)
	{
		cout << index << " ";
	}
	cout << endl;
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

	for (auto ul1 = PathsCopy.begin(); ul1 != PathsCopy.end(); ++ul1)
	{
		int key1 = (*ul1).first;
		for (auto ul2 = PathsCopy.begin(); ul2 != PathsCopy.end(); ++ul2)
		{
			int key2 = (*ul2).first;

			if (PathsCopy[key1].path[PathsCopy[key1].path.size() - 1] == PathsCopy[key2].path[PathsCopy[key2].path.size() - 1]
				&& PathsCopy[key1].time < PathsCopy[key2].time
				&& PathsCopy[key1].dis < PathsCopy[key2].dis
				&& Paths.count(key2) > 0)
			{
				Paths.erase(key2);
			}
		}
	}
}
