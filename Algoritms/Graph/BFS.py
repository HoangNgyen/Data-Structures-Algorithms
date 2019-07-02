from sys import stdin, stdout
from array import *
from queue import Queue

class Graph:

    def __init__(self):
        self.__Vertices = list()
        self.__Edges = dict()

    def input(self):
        inputs = int(input())
        for i in range(inputs):
            _input = stdin.readline()
            _input =  list(map(int, _input.split()))
            if _input[0] not in self.__Vertices:
                self.__Vertices.append(_input[0])
                if _input[0] not in self.__Edges:
                    self.__Edges[_input[0]] = list()
                
            if _input[1] not in self.__Vertices:
                self.__Edges[_input[1]] = list()
            if _input[1] not in self.__Edges[_input[0]]:
                self.__Edges[_input[0]].append(_input[1])

    def Traversal_BFS(self):
        traversal = Queue()
        newVertex = self.__Vertices.pop(0)
        traversal.put(newVertex)
        visited = set()
        visited.add(newVertex)    
        while traversal:
            s = traversal.get()
            visited.add(s)
            stdout.write("{0}\n".format(s))
            for Vertex in self.__Edges[s]:
                if Vertex not in visited:
                    traversal.put(Vertex)
                    visited.add(Vertex)

def main():
    myGraph = Graph()
    myGraph.input()
    myGraph.Traversal_BFS()

main()


