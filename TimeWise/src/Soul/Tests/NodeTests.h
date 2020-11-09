#pragma once

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Nodes/Node.h>
#include <Utility/Macros.h>

namespace Soul
{
	class NodeTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(AddChildrenMemoryLeakTest);
		}

	private:
		static void AddChildrenMemoryLeakTest()
		{
			Node parentNode;
			Node* childNode = Partition(Node);
			Node* childNode1 = Partition(Node);
			Node* childNode2 = Partition(Node);
			Node* childNode3 = Partition(Node);
			parentNode.AddChild(childNode);
			parentNode.AddChild(childNode1);
			parentNode.AddChild(childNode2);
			parentNode.AddChild(childNode3);
		}
	};
}