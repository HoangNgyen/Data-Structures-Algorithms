from sys import stdin, stdout
from queue import Queue

visited = set()

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

        for Vertex in self.__Vertices:
            self.Traversal_DFS(Vertex)

    def Traversal_DFS(self, Vertex):
        if Vertex not in visited:
            stdout.write("%d\n" %Vertex)
        for Edge in self.__Edges[Vertex]:
            if Edge not in visited:
                visited.add(Edge)
                stdout.write("%d\n" %Edge)
                self.Traversal_DFS(Edge)
            
    

if __name__ == "__main__":
    myGraph = Graph()
    myGraph.input()

