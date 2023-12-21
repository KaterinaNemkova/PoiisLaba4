#include "pch.h"
#include "CppUnitTest.h"
#include "..\лаба4поис\лаба4поис.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestAddVertex)
        {
            OrientedGraph<int> graph;
            Assert::IsTrue(graph.empty());

            graph.addVertex(1);
            Assert::IsFalse(graph.empty());
            Assert::IsTrue(graph.hasVertex(1));
        }

        TEST_METHOD(TestRemoveVertex)
        {
            OrientedGraph<int> graph;
            graph.addVertex(1);
            Assert::IsTrue(graph.hasVertex(1));

            graph.removeVertex(1);
            Assert::IsFalse(graph.hasVertex(1));
        }
        TEST_METHOD(TestAddEdge)
        {
            OrientedGraph<int> graph;
            graph.addVertex(1);
            graph.addVertex(2);
            Assert::IsFalse(graph.hasEdge(1, 2));

            graph.addEdge(1, 2);
            Assert::IsTrue(graph.hasEdge(1, 2));
        }
        TEST_METHOD(TestRemoveEdge)
        {
            OrientedGraph<int> graph;
            graph.addVertex(1);
            graph.addVertex(2);
            graph.addEdge(1, 2);
            Assert::IsTrue(graph.hasEdge(1, 2));

            graph.removeEdge(1, 2);
            Assert::IsFalse(graph.hasEdge(1, 2));
        }

        TEST_METHOD(TestVertexCount)
        {
            OrientedGraph<int> graph;
            Assert::AreEqual(size_t(0), graph.getVertexCount());

            graph.addVertex(1);
            Assert::AreEqual(size_t(1), graph.getVertexCount());
        }

        TEST_METHOD(TestEdgeCount)
        {
            OrientedGraph<int> graph;
            Assert::AreEqual(size_t(0), graph.getEdgeCount());

            graph.addVertex(1);
            graph.addVertex(2);
            graph.addEdge(1, 2);
            Assert::AreEqual(size_t(1), graph.getEdgeCount());
        }
        TEST_METHOD(TestHasEdge)
        {
            OrientedGraph<int> graph;
            graph.addVertex(1);
            graph.addVertex(2);
            graph.addEdge(1, 2);
            Assert::IsTrue(graph.hasEdge(1, 2));
        }

        TEST_METHOD(TestVertexDegree)
        {
            OrientedGraph<int> graph;
            graph.addVertex(1);
            graph.addVertex(2);
            graph.addEdge(1, 2);
            Assert::AreEqual(size_t(1), graph.getVertexDegree(1));
        }

        



	};
}
