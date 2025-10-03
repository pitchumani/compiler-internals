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
