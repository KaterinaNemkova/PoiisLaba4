#include <vector>
#include <algorithm>

template <typename T>
class Node {
public:
	T value;
	std::vector<Node<T>*> neighbors;

	Node(T value) : value(value) {}
};
template <typename T>
class OrientedGraph {
public:
	std::vector<Node<T>*> nodes;

	OrientedGraph() {}

	OrientedGraph(const OrientedGraph& other) {
		for (auto node : other.nodes) {
			nodes.push_back(new Node<T>(*node));
		}
	}
	~OrientedGraph() {
		for (auto node : nodes) {
			delete node;
		}
	}
	bool empty() const {
		return nodes.empty();
	}
	void clear() {
		for (auto node : nodes) {
			delete node;
		}
		nodes.clear();
	}
	OrientedGraph& operator=(const OrientedGraph& other) {
		if (this != &other) {
			clear();
			for (auto node : other.nodes) {
				nodes.push_back(new Node<T>(*node));
			}
		}
		return *this;
	}
	bool operator==(const OrientedGraph& other) const {
		if (nodes.size() != other.nodes.size()) {
			return false;
		}
		for (size_t i = 0; i < nodes.size(); ++i) {
			if (nodes[i]->neighbors.size() != other.nodes[i]->neighbors.size()) {
				return false;
			}
			for (size_t j = 0; j < nodes[i]->neighbors.size(); ++j) {
				if (nodes[i]->neighbors[j] != other.nodes[i]->neighbors[j]) {
					return false;
				}
			}
		}
		return true;
	}
	bool operator!=(const OrientedGraph& other) const {
		return !(*this == other);
	}
	bool operator<(const OrientedGraph& other) const {
		if (nodes.size() < other.nodes.size()) {
			return true;
		}
		if (nodes.size() > other.nodes.size()) {
			return false;
		}
		for (size_t i = 0; i < nodes.size(); ++i) {
			if (nodes[i]->neighbors.size() < other.nodes[i]->neighbors.size()) {
				return true;
			}
			if (nodes[i]->neighbors.size() > other.nodes[i]->neighbors.size()) {
				return false;
			}
		}
		return false;
	}

	bool operator>(const OrientedGraph& other) const {
		return other < *this;
	}

	bool operator<=(const OrientedGraph& other) const {
		return !(other < *this);
	}

	bool operator>=(const OrientedGraph& other) const {
		return !(*this < other);
	}
	bool hasVertex(T value) const {
		for (auto node : nodes) {
			if (node->value == value) {
				return true;
			}
		}
		return false;
	}
	bool hasEdge(T from, T to) const {
		Node<T>* fromNode = nullptr;
		Node<T>* toNode = nullptr;

		for (auto node : nodes) {
			if (node->value == from) {
				fromNode = node;
			}
			if (node->value == to) {
				toNode = node;
			}
		}

		if (fromNode && toNode) {
			for (auto neighbor : fromNode->neighbors) {
				if (neighbor->value == to) {
					return true;
				}
			}
		}
		return false;
	}
	size_t getVertexCount() const {
		return nodes.size();
	}
	size_t getEdgeCount() const {
   	size_t count = 0;
   	for (auto node : nodes) {
       count += node->neighbors.size();
   	}
   	return count; // Учитываем, что каждое ребро учитывается дважды
	}
	size_t getVertexDegree(T value) const {
		Node<T>* node = nullptr;

		for (auto n : nodes) {
			if (n->value == value) {
				node = n;
				break;
			}
		}

		if (node) {
			return node->neighbors.size();
		}
		return 0;
	}
	size_t getEdgeDegree(T from, T to) const {
		return hasEdge(from, to) ? 2 : 0;
	}
	void addVertex(T value) {
		nodes.push_back(new Node<T>(value));
	}

	void addEdge(T from, T to) {
		Node<T>* fromNode = nullptr;
		Node<T>* toNode = nullptr;

		for (auto node : nodes) {
			if (node->value == from) {
				fromNode = node;
			}
			if (node->value == to) {
				toNode = node;
			}
		}

		if (fromNode && toNode) {
			fromNode->neighbors.push_back(toNode);
		}
	}
	void removeVertex(T value) {
		Node<T>* node = nullptr;

		for (auto n : nodes) {
			if (n->value == value) {
				node = n;
				break;
			}
		}

		if (node) {
			for (auto n : nodes) {
				n->neighbors.erase(std::remove(n->neighbors.begin(), n->neighbors.end(), node), n->neighbors.end());
			}
			nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
			delete node;
		}
	}
	void removeEdge(T from, T to) {
		Node<T>* fromNode = nullptr;
		Node<T>* toNode = nullptr;

		for (auto node : nodes) {
			if (node->value == from) {
				fromNode = node;
			}
			if (node->value == to) {
				toNode = node;
			}
		}

		if (fromNode && toNode) {
			fromNode->neighbors.erase(std::remove(fromNode->neighbors.begin(), fromNode->neighbors.end(), toNode), fromNode->neighbors.end());
		}
	}
	std::pair<typename std::vector<Node<T>*>::iterator, typename std::vector<Node<T>*>::iterator> getVertices() {
		return std::make_pair(nodes.begin(), nodes.end());
	}
	std::pair<typename std::vector<Node<T>*>::iterator, typename std::vector<Node<T>*>::iterator> getEdges() {
		std::vector<Node<T>*> allEdges;
		for (auto node : nodes) {
			allEdges.insert(allEdges.end(), node->neighbors.begin(), node->neighbors.end());
		}
		return std::make_pair(allEdges.begin(), allEdges.end());
	}

	std::pair<typename std::vector<Node<T>*>::iterator, typename std::vector<Node<T>*>::iterator> getEdges(T value) {
		Node<T>* node = nullptr;

		for (auto n : nodes) {
			if (n->value == value) {
				node = n;
				break;
			}
		}

		if (node) {
			return std::make_pair(node->neighbors.begin(), node->neighbors.end());
		}
		return std::make_pair(nodes.end(), nodes.end());
	}
	std::pair<typename std::vector<Node<T>*>::iterator, typename std::vector<Node<T>*>::iterator> getNeighbors(T value) {
		Node<T>* node = nullptr;

		for (auto n : nodes) {
			if (n->value == value) {
				node = n;
				break;
			}
		}

		if (node) {
			std::vector<Node<T>*> neighbors;
			for (auto neighbor : node->neighbors) {
				neighbors.push_back(neighbor);
			}
			return std::make_pair(neighbors.begin(), neighbors.end());
		}
		return std::make_pair(nodes.end(), nodes.end());
	}
	void removeVertex(typename std::vector<Node<T>*>::iterator it) {
		for (auto n : nodes) {
			n->neighbors.erase(std::remove(n->neighbors.begin(), n->neighbors.end(), *it), n->neighbors.end());
		}
		nodes.erase(it);
		delete* it;
	}
	void removeEdge(typename std::vector<Node<T>*>::iterator itFrom, typename std::vector<Node<T>*>::iterator itTo) {
		itFrom->neighbors.erase(std::remove(itFrom->neighbors.begin(), itFrom->neighbors.end(), *itTo), itFrom->neighbors.end());
	}
	std::pair<typename std::reverse_iterator<typename std::vector<Node<T>*>::iterator>, typename std::reverse_iterator<typename std::vector<Node<T>*>::iterator>> getVerticesReverse() {
		return std::make_pair(nodes.rbegin(), nodes.rend());
	}

	std::pair<typename std::reverse_iterator<typename std::vector<Node<T>*>::iterator>, typename std::reverse_iterator<typename std::vector<Node<T>*>::iterator>> getEdgesReverse(T value) {
		Node<T>* node = nullptr;

		for (auto n : nodes) {
			if (n->value == value) {
				node = n;
				break;
			}
		}

		if (node) {
			return std::make_pair(node->neighbors.rbegin(), node->neighbors.rend());
		}
		return std::make_pair(nodes.rend(), nodes.rend());
	}
	std::pair<typename std::vector<Node<T>*>::const_iterator, typename std::vector<Node<T>*>::const_iterator> getVerticesConst() const {
		return std::make_pair(nodes.begin(), nodes.end());
	}

	std::pair<typename std::vector<Node<T>*>::const_iterator, typename std::vector<Node<T>*>::const_iterator> getEdgesConst(T value) const {
		Node<T>* node = nullptr;

		for (auto n : nodes) {
			if (n->value == value) {
				node = n;
				break;
			}
		}

		if (node) {
			return std::make_pair(node->neighbors.begin(), node->neighbors.end());
		}
		return std::make_pair(nodes.end(), nodes.end());
	}

};
