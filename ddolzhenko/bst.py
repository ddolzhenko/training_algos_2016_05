import networkx as nx
import math
from random import shuffle
import matplotlib.pyplot as plt
    

class Tree:
    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right
        self.parent = None

        if self.left:
            self.left.parent = self
        if self.right:
            self.right.parent = self

    def __lt__(self, other):
        return self.data < other.data

    def __str__(self):
        return str(self.data)
    
    def str(self):
        return str(self.data)


    def to_graph(self):
        g = nx.Graph()
        for node in dfs_nodes(self):
            if node.left:
                g.add_edge(node.data, node.left.data)
            if node.right:
                g.add_edge(node.data, node.right.data)
        return g

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
        g = self.to_graph()

        plt.axis('on')
        nx.draw_networkx(g, positions, node_size=1500, font_size=24, node_color='g')
        plt.show()



def height(tree):
    if not tree:
        return 0
    return 1 + max(height(tree.left), height(tree.right))


def dfs_nodes(tree):
    if tree:
        yield from dfs_nodes(tree.left)
        yield tree
        yield from dfs_nodes(tree.right)

def bfs_nodes(tree):
    queue = []
    queue.append(tree)
    while queue:
        node = queue.pop(0)
        if node:
            yield node
            queue.append(node.left)
            queue.append(node.right)


def is_bst(tree):
    if not tree:
        return True

    return \
        (not tree.left or (max_node(tree.left) < tree)) and  \
        (not tree.right or (tree < min_node(tree.right))) and \
        is_bst(tree.left) and \
        is_bst(tree.right)
   

def min_node(bst):
    # assert is_bst(bst) and bst is not None

    while bst.left:
        bst = bst.left

    return bst

def max_node(bst):
    # assert is_bst(bst) and bst is not None

    while bst.right:
        bst = bst.right

    return bst

def next_node(bst):
    assert bst

    if bst.right:
        return min_node(bst.right)

    if bst.parent:
        if bst.parent.left == bst:
            return bst.parent
            
        while bst.parent and bst.parent.right == bst:
            bst = bst.parent

    return bst.parent


def prev_node(bst):
    if bst.left:
        return max_node(bst.left)

    if bst.parent:
        if bst.parent.right == bst:
            return bst.parent

        while bst.parent and bst.parent.left == bst:
            bst = bst.parent
    
    return bst.parent

begin = min_node

def end(bst):
    return None

def iterate(bst):
    it = begin(bst)
    while it != end(bst):
        yield it
        it = next_node(it)

def lower_bound(bst, x):
    assert is_bst(bst)

    if bst:
        if x < bst.data:
            res = lower_bound(bst.left, x)
            if res:
                bst = res

        elif bst.data < x:
            return lower_bound(bst.right, x) 

    return bst


def insert_to(ref, x):
    if ref[0]:
        return insert2(ref[0], x)
    ref[0] = Tree(x)
    return ref[0]

def insert2(tree, x):
    assert is_bst(tree) and tree is not None

    if x < tree.data:
        return insert_to([tree.left], x)
    elif tree.data < x:
        return insert_to([tree.right], x)
        
    return tree



def insert(tree, x):
    assert is_bst(tree) and tree is not None

    if x < tree.data:
        if tree.left:
            return insert(tree.left, x)
        else:
            tree.left = Tree(x)
            tree.left.parent = tree
            return tree.left

    elif tree.data < x:
        if tree.right:
            return insert(tree.right, x)
        else:
            tree.right = Tree(x)
            tree.right.parent = tree
            return tree.right

    return tree


def create_tree_1():
    return Tree(10,
            Tree(4,
                Tree(3),
                Tree(5,
                    right=Tree(6))),
            Tree(20,
                Tree(15,
                    right=Tree(17,
                            Tree(16),
                            Tree(18, right=Tree(19))))))

def create_tree_2():
    return Tree(8,
            Tree(3,
                Tree(1),
                Tree(6,
                    Tree(4),
                    Tree(7))),
            Tree(10, 
                right=Tree(14,
                    Tree(13))))

def create_tree_3():
    return Tree(3,
                Tree(2),
                Tree(5,
                    Tree(1),
                    Tree(7)))

def main():
    
    t = create_tree_2()    
    
    insert(t, 5)
    # insert(t, 9)

    print(", ".join(map(str, dfs_nodes(t))))
    

    # for x in iterate(t):
    #     print (x)

    print(", ".join(map(str, iterate(t))))

    print(is_bst(create_tree_1()))
    print(is_bst(create_tree_2()))
    print(is_bst(create_tree_3()))

    # create_tree_1().draw()    
    
    



if __name__ == '__main__':
    main()