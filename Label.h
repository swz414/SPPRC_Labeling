#pragma once
#include "comm.h"
#include "Graph.h"

class Label {

public:
	vector<int> path;
	float_t time;
	float_t dis;

	Label() { time = 0; dis = 0; };
	Label(const Label& label) {
		path.assign(label.path.begin(), label.path.end()); time = label.time; dis = label.dis;
	};
};

class LabellingAlg {
public:
	Label labelling_SPPRC(Graph graph, int org, int des);
	void dominate(vector<Label>& Queue, map<int, Label>& Paths);
};