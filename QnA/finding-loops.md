# Findling Loops in Control Flow Graph

The compiler maintains the program in a control flow graph which has basic blocks
with its predecessor and successor information. To perform loop optimizations,
the compiler will traverse the flow graph and find loops. After finding loops,
the compiler can do optimizations such as invariant or variant code motions where
possible.

Sample implementation to find loops in control flow graph:
```C++
// controlflowgraph.h
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
```
```C++
// findloops.cpp
#include "controlflowgraph.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

	ControlFlowGraph cfg;
	auto *bb1 = cfg.createBlock("bb1");
	auto *cond_block = cfg.createBlock("condition check");
	auto *loop_block1 = cfg.createBlock("loop block1");
	auto *loop_block2 = cfg.createBlock("loop block2");
	auto *end_block = cfg.createBlock("block3");
    cfg.addEdge(bb1, cond_block);
    cfg.addEdge(cond_block, loop_block1); // successor to true part (loop)
    cfg.addEdge(cond_block, end_block); // successor to false part
    cfg.addEdge(loop_block1, loop_block2);
    cfg.addEdge(loop_block2, cond_block); // back to loop condition
	cfg.printStats();

	CFGAnalyzer analyzer;
	auto loops = analyzer.findLoops(cfg);
	
	for (auto &loop : loops) {
		cout << "Loop {" << endl;
		for (auto *block : loop) {
			cout << "  " << block->statement << endl;
		}
		cout << "};\n";
	}
	return 0;
}
```
