// **************************************************************************
// File       [ test_cmd.cpp ]
// Author     [ littleshamoo ]
// Synopsis   [ ]
// Date       [ 2012/04/10 created ]
// **************************************************************************

#include "user_cmd.h"
#include "graph.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <stack>
#include <sstream>
#include "../lib/tm_usage.h"
using namespace std;
using namespace CommonNs;

TestCmd::TestCmd(const char * const name) : Cmd(name) {
	optMgr_.setShortDes("test");
	optMgr_.setDes("test");

	Opt *opt = new Opt(Opt::BOOL, "print usage", "");
	opt->addFlag("h");
	opt->addFlag("help");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "print the string of -s", "[string]");
	opt->addFlag("s");
	optMgr_.regOpt(opt);
}

TestCmd::~TestCmd() {}

bool TestCmd::exec(int argc, char **argv) {
	optMgr_.parse(argc, argv);

	if (optMgr_.getParsedOpt("h")) {
		optMgr_.usage();
		return true;
	}

	if (optMgr_.getParsedOpt("s")) {
		printf("%s\n", optMgr_.getParsedValue("s"));
	}
	else
		printf("hello world !!\n");


	return true;
}

Graph *graph = new Graph("nil");

Read_GraphCmd::Read_GraphCmd(const char * const name) : Cmd(name) {
	optMgr_.setShortDes("read graph");
	optMgr_.setDes("read a graph in dot language");

	optMgr_.regArg(new Arg(Arg::REQ, "input dot file", "INPUT"));

	Opt *opt = new Opt(Opt::BOOL, "print usage", "");
	opt->addFlag("h");
	opt->addFlag("help");
	optMgr_.regOpt(opt);
}

Read_GraphCmd::~Read_GraphCmd() {}

bool Read_GraphCmd::exec(int argc, char **argv) {
	optMgr_.parse(argc, argv);
	if (optMgr_.getParsedOpt("h")) 
	{
		optMgr_.usage();
		return true;
	}
	else if (argc < 2) 
	{
		fprintf(stderr, "**ERROR Read_GraphCmd::exec(): please specify input file\n");
		return false;
	}
	else if (optMgr_.getNParsedArg() < 1) 
	{
		fprintf(stderr, "**ERROR Read_GraphCmd::exec(): need input file\n");
		return false;
	}
	fstream fin;
	fin.open(argv[1], ios::in);
	if(!fin) 
	{
		cout<<"**ERROR Read_GraphCmd::exec(): can not open input file\n";
		return false;
	}
	char line[100];
	string str;
	while(fin.getline(line, sizeof(line), ' ')){
		if(line[5] == 't'){
			fin.getline(line, sizeof(line), ' ');
			str = line;
			break;
		}
	}
	if(graph[0].name != "nil")
		delete graph;
	graph = new Graph(str);
	while(fin.getline(line, sizeof(line), '\n')){
		fin.getline(line, sizeof(line), ' ');
		if(line[0] == '}')
			break;
		if(line[0] == 'v')
		{
			int len1 = strlen(line);
			str = line;
			str.assign(str, 1, len1-1);
			len1 = atoi(str.c_str());
			if((graph->nodes).find(len1) == (graph->nodes).end())
			{
				Node *v1 = new Node(len1);
				(graph->nodes).insert(pair<int, Node *>(len1, v1));
			}
			fin.getline(line, sizeof(line), ' ');
			fin.getline(line, sizeof(line), ' ');
			int len2 = strlen(line);
			str = line;
			str.assign(str, 1, len2-1);
			len2 = atoi(str.c_str()); 
			if((graph->nodes).find(len2) == (graph->nodes).end())
			{
				Node *v2 = new Node(len2);
				(graph->nodes).insert(pair<int, Node *>(len2, v2));
			}
			fin.getline(line, sizeof(line), '\"');
			fin.getline(line, sizeof(line), '\"');
			int w = strlen(line);
			str = line;
			w = atoi(str.c_str());
			Edge *e = new Edge(((graph->nodes).find(len1))->second, ((graph->nodes).find(len2))->second, w);
			(graph->edges).push_back(e);
			(graph->getNodeById(len1))->addEdge(e);
			(graph->getNodeById(len2))->addEdge(e);
		}
	}
	graph->sortEdgesOfNode();
	return true;
}

Write_Tree_DFSCmd::Write_Tree_DFSCmd(const char * const name) : Cmd(name) {
	optMgr_.setShortDes("write tree dfs");
	optMgr_.setDes("perform depth first search starting from source node");

	Opt *opt = new Opt(Opt::BOOL, "print usage", "");
	opt->addFlag("h");
	opt->addFlag("help");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "sourcenode", "[node]");
	opt->addFlag("s");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "output dot file", "OUTPUT");
	opt->addFlag("o");
	optMgr_.regOpt(opt);
}

Write_Tree_DFSCmd::~Write_Tree_DFSCmd() {}

void DFS_Visit(int id, int& vertices, int& edges, fstream& fin) {
	Node *node = new Node(0);
	node = graph->getNodeById(id);
	node->color = 1;
	++ vertices;
	Node *next = new Node(0);
	for(int i = 0; i < (node->edge).size(); ++i)
	{
		next = ((node->edge).at(i))->getNeighbor(node);
		if(next->color == 0)
		{
			fin<<"v"<<id<<" -- v"<<next->id<<"  [label = \""<<(node->edge).at(i)->weight<<"\"];"<<endl;
			++ edges;
			DFS_Visit(next->id, vertices, edges, fin);
		}
	}
}

void DFS(int id, int& vertices, int& edges,  fstream& fin) {
	for(int i = 0; i < (graph->nodes).size(); ++i)
		graph->getNodeById(i)->color = 0;
	DFS_Visit(id, vertices, edges, fin);
}

bool Write_Tree_DFSCmd::exec(int argc, char **argv) {
	CommonNs::TmUsage tmusg;
	CommonNs::TmStat stat;
	tmusg.periodStart();
	optMgr_.parse(argc, argv);

	if (optMgr_.getParsedOpt("h")) {
		optMgr_.usage();
		return true;
	}

	if (argc < 2) {
		fprintf(stderr, "**ERROR Write_Tree_DFSCmd::exec(): please specify sourcenode\n");
		return false;
	}


	string name = argv[4];
	fstream fin;
	fin.open(name.c_str(), ios::out);
	fin<<"// DFS tree produced by graphlab\ngraph ";
	int namelen = name.size();
	name.assign(name, 8, namelen-12);
	fin<<name<<" {\n";

	name = optMgr_.getParsedValue("s");
	namelen = name.size();
	name.assign(name, 1, namelen-1);
	namelen = atoi(name.c_str());

	int vertices = 0, edges = 0;
	DFS(namelen, vertices, edges, fin);
	tmusg.getPeriodUsage(stat);
	fin<<"}\n// vertices = "<<vertices<<"\n// edges = "<<edges<<endl;
	fin<<"// source = v"<<namelen<<endl;
	fin<<"// runtime = "<<(stat.uTime + stat.sTime) / 1000000.0<<" sec"<<endl;
	fin<<"// memory = "<<stat.vmPeak / 1024.0<<" MB"<<endl;
	fin.close();
	graph->init();
	return true;
}

Write_Tree_BFSCmd::Write_Tree_BFSCmd(const char * const name) : Cmd(name) {
	optMgr_.setShortDes("write tree bfs");
	optMgr_.setDes("perform breadth first search starting from source node");

	Opt *opt = new Opt(Opt::BOOL, "print usage", "");
	opt->addFlag("h");
	opt->addFlag("help");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "sourcenode", "[node]");
	opt->addFlag("s");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "output dot file", "OUTPUT");
	opt->addFlag("o");
	optMgr_.regOpt(opt);
}

Write_Tree_BFSCmd::~Write_Tree_BFSCmd() {}

void BFS(int id, int& vertices, int& edges, fstream& fin) {
	for(int i = 0; i < (graph->nodes).size(); ++i)
		graph->getNodeById(i)->color = 0;
	queue<Node*> q;
	graph->getNodeById(id)->color = 1;
	q.push(graph->getNodeById(id));
	while(q.empty() == false)
	{
		Node *u = new Node(0);
		u = q.front();
		q.pop();
		++ vertices;
		for(int i = 0; i < (u->edge).size(); ++i)
		{
			Node *v = new Node(0);
			v = ((u->edge).at(i))->getNeighbor(u);
			if(v->color == 0)
			{
				v->color = 1;
				fin<<"v"<<u->id<<" -- v"<<v->id<<"  [label = \""<<(u->edge).at(i)->weight<<"\"];"<<endl;
				++ edges;
				q.push(v);
			}
		}
	}
}

bool Write_Tree_BFSCmd::exec(int argc, char **argv) {
	CommonNs::TmUsage tmusg;
	CommonNs::TmStat stat;
	tmusg.periodStart();

	optMgr_.parse(argc, argv);

	if (optMgr_.getParsedOpt("h")) {
		optMgr_.usage();
		return true;
	}

	if (argc < 2) {
		fprintf(stderr, "**ERROR Write_Tree_BFSCmd::exec(): please specify sourcenode\n");
		return false;
	}

	tmusg.getPeriodUsage(stat);

	string name = argv[4];
	fstream fin;
	fin.open(name.c_str(), ios::out);
	fin<<"// BFS tree produced by graphlab\ngraph ";
	int namelen = name.size();
	name.assign(name, 8, namelen-12);
	fin<<name<<" {\n";

	name = optMgr_.getParsedValue("s");
	namelen = name.size();
	name.assign(name, 1, namelen-1);
	namelen = atoi(name.c_str());

	int vertices = 0, edges = 0;
	BFS(namelen, vertices, edges, fin);
	tmusg.getPeriodUsage(stat);
	fin<<"}\n// vertices = "<<vertices<<"\n// edges = "<<edges<<endl;
	fin<<"// source = v"<<namelen<<endl;
	fin<<"// runtime = "<<(stat.uTime + stat.sTime) / 1000000.0<<" sec"<<endl;
	fin<<"// memory = "<<stat.vmPeak / 1024.0<<" MB"<<endl;
	fin.close();
	graph->init();
	return true;
}

Write_DijkstraCmd::Write_DijkstraCmd(const char * const name) : Cmd(name) {
	optMgr_.setShortDes("write dijkstra");
	optMgr_.setDes("perform Dijkstra's algorithm to find the shortest path from sourcenode to endnode");

	Opt *opt = new Opt(Opt::BOOL, "print usage", "");
	opt->addFlag("h");
	opt->addFlag("help");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "sourcenode", "[node]");
	opt->addFlag("from");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "endnode", "[node]");
	opt->addFlag("to");
	optMgr_.regOpt(opt);

	opt = new Opt(Opt::STR_REQ, "output dot file", "OUTPUT");
	opt->addFlag("o");
	optMgr_.regOpt(opt);
}

Write_DijkstraCmd::~Write_DijkstraCmd() {}

Node * Extract_Min(vector<Node*>& q){
	int id = 0;
	for(int i = 0; i < q.size(); ++i)
		if((q.at(id))->d > (q.at(i))->d)
			id = i;
	Node *result = new Node(0);
	result = q.at(id);
	q.erase(q.begin()+id);
	return result;
}

void Dijkstra(int source, int end, int& edges, fstream& fin) {
	graph->getNodeById(source)->d = 0;
	vector<Node*> q;
	for(int i = 0; i < (graph->nodes).size(); ++i)
		q.push_back(graph->getNodeById(i));
	while(q.empty() == false)
	{
		Node *u = new Node(0);
		u = Extract_Min(q);
		for(int i = 0; i < (u->edge).size(); ++i)
		{
			Node *v = new Node(0);
			v = ((u->edge).at(i))->getNeighbor(u);
			if(v->d > u->d + ((u->edge).at(i))->weight)
			{
				v->d = u->d + ((u->edge).at(i))->weight;
				v->prev = u;
			}
		}
	}
	stack<string> s;
	string str;
	while(end != source)
	{
		stringstream ss;
		string convert;
		ss<<graph->getNodeById(end)->prev->id;
		ss>>convert;
		str+="v";
		str+=convert;
		ss.str("");
		ss.clear();
		convert.clear();
		ss<<end;
		ss>>convert;
		str+=" -- v";
		str+=convert;
		ss.str("");
		ss.clear();
		convert.clear();
		for(int i = 0; i < (graph->getNodeById(end)->edge).size(); ++i)
		{
			if(((graph->getNodeById(end)->edge).at(i))->getNeighbor(graph->getNodeById(end))->id == graph->getNodeById(end)->prev->id)
			{
				ss<<((graph->getNodeById(end)->edge).at(i))->weight;
				ss>>convert;
				str+="  [label = \"";
				str+=convert;
				str+="\"];\n";
				++ edges;
				break;
			}
		}
		s.push(str);
		str.clear();
		end = graph->getNodeById(end)->prev->id;
	}
	while(s.empty() == false)
	{
		fin<<s.top();
		s.pop();
	}
}

bool Write_DijkstraCmd::exec(int argc, char **argv) {
	CommonNs::TmUsage tmusg;
	CommonNs::TmStat stat;
	tmusg.periodStart();

	optMgr_.parse(argc, argv);

	if (optMgr_.getParsedOpt("h")) {
		optMgr_.usage();
		return true;
	}

	if (argc < 2) {
		fprintf(stderr, "**ERROR Write_DijkstraCmd::exec(): please specify sourcenode and endnode\n");
		return false;
	}

	tmusg.getPeriodUsage(stat);

	string name = optMgr_.getParsedValue("o");
	fstream fin;
	fin.open(name.c_str(), ios::out);
	fin<<"// Dijkstra produced by graphlab\ngraph ";
	int namelen = name.size();
	name.assign(name, 8, namelen-12);
	fin<<name<<" {\n";
	name.clear();

	name = argv[4];
	namelen = name.size();
	name.assign(name, 1, namelen-1);
	namelen = atoi(name.c_str());
	name.clear();

	name = argv[6];
	int end = name.size();
	name.assign(name, 1, end-1);
	end = atoi(name.c_str());

	int edges = 0;
	Dijkstra(namelen, end, edges, fin);
	int vertices = edges + 1;
	int total_weight = graph->getNodeById(end)->d;
	tmusg.getPeriodUsage(stat);
	fin<<"}\n// vertices = "<<vertices<<"\n// edges = "<<edges<<endl;
	fin<<"// source = v"<<namelen<<endl;
	fin<<"// end = v"<<end<<endl;
	fin<<"// total_weight = "<<total_weight<<endl;
	fin<<"// runtime = "<<(stat.uTime + stat.sTime) / 1000000.0<<" sec"<<endl;
	fin<<"// memory = "<<stat.vmPeak / 1024.0<<" MB"<<endl;
	fin.close();
	graph->init();
	return true;
}

