import networkx as nx
import math
from random import shuffle
# import pygraphviz as PG
import matplotlib.pyplot as plt


def draw(G, pos=None):
    plt.axis('on')
    nx.draw_networkx(G, pos, node_size=1500, font_size=24, node_color='g')
    # nx.draw_spectral(G, node_size=1500, font_size=24, node_color='g')
    plt.show()


class GraphVertex:
    def __init__(self):
        self.neighbours = []
        self.visited = False
        self.prev = -1

class Graph:

    
    class GraphError(Exception):
        def __init__(self, arg):
                super(GraphError, self).__init__(arg)
           

    def __init__(self):
        self.adjList = {}

    def add_single_vertex(self, x):
        if x not in self.adjList:
            # raise GraphError('already there')
            self.adjList[x] = GraphVertex()

    def add_vertices(self, *arr):
        for x in arr:
            self.add_single_vertex(x)

    def get_vertex(self, i):
        return self.adjList[i]

    def verticies(self):
        yield from self.adjList.values()
           
    def add_single_edge(self, e):
        self.add_single_vertex(e[0])
        self.add_single_vertex(e[1])
                
        self.get_vertex(e[0]).neighbours.append(e[1])
        # self.adjList[e[1]].append(e[0])

    def add_edges(self, *arr):
        for e in arr:
            self.add_single_edge(e)


    def draw(self, pos=None):
        G = nx.Graph()
        for i, v in self.adjList.items():
            for j in v.neighbours:
                G.add_edge(i, j)
        
        draw(G, pos)
        

    def draw_circ(self):
        G = nx.DiGraph()
        for i, v in self.adjList.items():
            for j in v.neighbours:
                G.add_edge(i, j)

        labels = {k:k  for k in self.adjList.keys() }
        nx.draw_shell(G, node_size=1000, node_color='g', labels=labels)
        plt.show()



class Tree:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    # def height(tree):
    #     if tree == null_tree:
    #         return 0
    #     return 1 + max(height(tree.left), height(tree.right))


    def __str__(self):
        return str(self.data)

    def nodes(self):
        yield from dfs_1(self)

    def to_graph(self):
        G = Graph()
        def visitor(node):
            if node.data not in G.adjList:
                G.add_single_vertex(node.data)
            if node.left:
                G.add_edges((node.data, node.left.data))
            if node.right:
                G.add_edges((node.data, node.right.data))
            # if node.neighbour:
            #     G.add_edges((node.data, node.neighbour.data))

        traverse_pre_order(self, visitor)
        return G

    def get_positions(node, positions, x, y):
        if node:
            node_size = 0.5
            
            my_x = (x[1] + x[0]) / 2
            my_y = y[0] + (node_size / 2)

            positions[node.data] = (my_x, -my_y)
            Tree.get_positions(node.left, positions, (x[0], my_x), (my_y, y[1]))
            Tree.get_positions(node.right, positions, (my_x, x[1]), (my_y, y[1]))



    def draw(self):
        positions = {}
        Tree.get_positions(self, positions, x=(0, 10), y=(0, 10))

        print(positions)

        self.to_graph().draw(positions)

null_tree = Tree(None)

def height(tree):
    if not tree:
        return 0
    return 1 + max(height(tree.left), height(tree.right))


def dfs_1(tree):
    if tree:
        yield tree
        yield from dfs_1(tree.left)
        yield from dfs_1(tree.right)


def traverse_pre_order(tree, visitor):
    if tree:
        visitor(tree)
        traverse_pre_order(tree.left, visitor)
        traverse_pre_order(tree.right, visitor)

def traverse_in_order(tree, visitor):
    if tree:
        traverse_in_order(tree.left, visitor)
        visitor(tree)
        traverse_in_order(tree.right, visitor)

def traverse_post_order(tree, visitor):
    if tree:
        traverse_post_order(tree.left, visitor)
        traverse_post_order(tree.right, visitor)
        visitor(tree)


class Queue:
    def __init__(self):
        self._data = []

    def push(self, x):
        self._data.append(x)

    def pop(self):
        return self._data.pop(0)

    def empty(self):
        return len(self._data) == 0
       

def bfs(tree, visitor):
    queue = Queue()
    queue.push(tree);
    while not queue.empty():
        node = queue.pop()

        if node.left:
            queue.push(node.left)
        if node.right:
            queue.push(node.right)
        visitor(node)



def co_numbers(max, pred):
    for i in range(max):
        if pred(i):
            yield i

def natural_numbers():
    i = 1;
    while True:
        yield i
        i += 1

def divided_by_3():
    yield from co_numbers(10, lambda x: x%3==0)

def test_generators():
    for i in divided_by_3():
        print (i)

    N = natural_numbers()
    N = co_numbers(100000000, lambda x: x%4 == 0)
    for i in range(100):
        print(N.__next__())

def main():

    t = Tree(1,
            Tree(2,
                Tree(4),
                Tree(5,
                    Tree(8))),
            Tree(3,
                Tree(6),
                Tree(7,
                    Tree(9,
                        Tree(10)))))

    
    traverse_pre_order(t, print)

    for node in t.nodes():
        print(node)

    t.draw()


    print("BFS:")
    bfs(t, print)

    # print(t.left.right.data)



if __name__ == '__main__':
    main()