#ifndef CONTROLFLOWGRAPH_
#define CONTROLFLOWGRAPH_

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class BasicBlock {
public:
	int id;
	string statement;
	vector<BasicBlock*> predecessors;
	vector<BasicBlock*> successors;
    BasicBlock(int _id, string _content) : id(_id), statement(_content) {}
};

class ControlFlowGraph {
public:
	BasicBlock *entry = nullptr;
	vector<BasicBlock*> blocks;
	ControlFlowGraph() {}
	~ControlFlowGraph() {
		for (auto &b : blocks) {
			delete b;
		}
	}
	BasicBlock *createBlock(const string &content) {
		int id = blocks.size();
		BasicBlock *bb = new BasicBlock(id, content);
		blocks.push_back(bb);
		return bb;
	}
	void addEdge(BasicBlock *from, BasicBlock *to) {
		from->successors.push_back(to);
		to->predecessors.push_back(from);
	}
	void printStats() {
		std::cout << "Num blocks: " << blocks.size() << std::endl;
	}
};

class CFGAnalyzer {
	set<BasicBlock*> visited;
	set<BasicBlock*> recursionStack;
	vector<vector<BasicBlock*>> loops;
	void findLoopsDFS(BasicBlock* block, vector<BasicBlock*> &currPath) {
		// mark the current block as visited and add it to recursion stack
		visited.insert(block);
		recursionStack.insert(block);

		currPath.push_back(block);

		// traverse all successors
		for (auto *succ : block->successors) {
			// found an ancestor in the recursion stack
			if (recursionStack.count(succ)) {
				vector<BasicBlock*> loop;
				bool inLoop = false;
				for (BasicBlock *pathBlock : currPath) {
					if (pathBlock == succ) {
						inLoop = true;
					}
					if (inLoop) {
						loop.push_back(pathBlock);
					}
				}
				loop.push_back(succ);
				loops.push_back(loop);
			} // else, continue DFS if successor is not visited
			else if (!visited.count(succ)) {
				findLoopsDFS(succ, currPath);
			}
		}

		// remove current block from recursion stack and curr path
		recursionStack.erase(block);
		currPath.pop_back();
	}

public:
	CFGAnalyzer() {}
	vector<vector<BasicBlock*>> findLoops(ControlFlowGraph &cfg) {
		visited.clear();
		loops.clear();
		for (auto *bb : cfg.blocks) {
			if (!visited.count(bb)) {
				vector<BasicBlock*> currentPath;
				findLoopsDFS(bb, currentPath);
			}
		}
		return loops;
	}
};

#endif  // CONTROLFLOWGRAPH_

