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
			RunTest(ChildrenOfChildren);
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

			Assert(childNode->GetParent() == &parentNode);
			Assert(childNode1->GetParent() == &parentNode);
			Assert(childNode2->GetParent() == &parentNode);
			Assert(childNode3->GetParent() == &parentNode);
		}

		static void ChildrenOfChildren()
		{
			Node parentNode;
			Node* childNode1 = Partition(Node);
			Node* childNode2 = Partition(Node);
			Node* childNode1Child1 = Partition(Node);
			Node* childNode1Child2 = Partition(Node);
			Node* childNode2Child1 = Partition(Node);
			Node* childNode2Child2 = Partition(Node);
			Node* childNode1Child1Child1 = Partition(Node);
			Node* childNode1Child1Child2 = Partition(Node);
			Node* childNode1Child2Child1 = Partition(Node);
			Node* childNode1Child2Child2 = Partition(Node);
			Node* childNode2Child1Child1 = Partition(Node);
			Node* childNode2Child1Child2 = Partition(Node);
			Node* childNode2Child2Child1 = Partition(Node);
			Node* childNode2Child2Child2 = Partition(Node);

			childNode1Child1->AddChild(childNode1Child1Child1);
			childNode1Child1->AddChild(childNode1Child1Child2);
			childNode1Child2->AddChild(childNode1Child2Child1);
			childNode1Child2->AddChild(childNode1Child2Child2);
			childNode2Child1->AddChild(childNode2Child1Child1);
			childNode2Child1->AddChild(childNode2Child1Child2);
			childNode2Child2->AddChild(childNode2Child2Child1);
			childNode2Child2->AddChild(childNode2Child2Child2);

			childNode1->AddChild(childNode1Child1);
			childNode1->AddChild(childNode1Child2);
			childNode2->AddChild(childNode2Child1);
			childNode2->AddChild(childNode2Child2);

			parentNode.AddChild(childNode1);
			parentNode.AddChild(childNode2);
		}
	};
}