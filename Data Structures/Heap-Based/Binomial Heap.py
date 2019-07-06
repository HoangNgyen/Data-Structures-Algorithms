from math import pow
from sys import stdin, stdout

class Node:
    
    def __init__(self, key = None, parent = None, leftNode = None, rightNode = None):
        self.__key = key
        self.__leftNode = leftNode
        self.__rightNode = rightNode
        self.__parent = parent
        self.__childList = []
        self.__degree = 0
        self.__amountOfNodes = 1

    def __modify(self):
        if len(self.__childList):
            self.__rightNode._Node__leftNode = self.__childList[-1]
            self.__childList[-1]._Node__rightNode = self.__rightNode;
        else:
            self.__rightNode._Node__leftNode = None
        self.__degree += 1
        self.__amountOfNodes *= 2
        self.__rightNode.__parent = self
        self.__childList.append(self.__rightNode)
        self.__rightNode = None


    def insert_Node(self, newKey):

        if self.__key == None:
            self.__key = newKey
            return

        if newKey < self.__key:
            self.__key, newKey = newKey, self.__key

        if self.__rightNode == None:
            self.__rightNode = Node(newKey, None, self)
        else:
            self.__rightNode.insert_Node(newKey)
        
        if self.__rightNode.__amountOfNodes == self.__amountOfNodes:
            self.__modify()

    def __Link(self, fur):
        self.__childList.append(fur)
        fur.__parent = self
        self.__amountOfNodes += fur.__amountOfNodes
        self.__degree += 1
        if (len(self.__childList) > 1):
            fur.__leftNode = self.__childList[-2]

    def __Traversal(self):
        stdout.write("%d " % self.__key)
        if self.__childList:
            for child in self.__childList:
                child.__Traversal()


    def extractMin(self):
        min = self.__childList[0].__key
        minPos = 0
        for pos in range(len(self.__childList)):
            if self.__childList[pos].__key < min:
                min = self.__childList[pos].__key
                minPos = pos
        self.__key = min
        if self.__childList[minPos].__childList == []:
            self.__childList.pop(minPos)
        else:
            self.__childList[minPos].extractMin()

class BinomialHeap:
    
    def __init__(self):
        self.__heap = []

    def __heapify(self):
        if len(self.__heap) == 1:
            return
        index = 0
        pre, cur, fur = None, self.__heap[index], self.__heap[index + 1]
        while 1:
            if cur._Node__degree != fur._Node__degree:
                index += 1
                if index == len(self.__heap) - 1:
                    return
                pre, cur, fur = cur, fur, self.__heap[index + 1]
            else:
                if cur._Node__key <= fur._Node__key:
                    cur._Node__Link(fur)
                    self.__heap.pop(index + 1)
                else:
                    fur._Node__Link(cur)
                    self.__heap.pop(index)

                index -= 1
                if index < 0:
                    return
                fur, cur = cur, self.__heap[index]
                if index > 0:
                    pre = self.__heap[index - 1]


    def __Union(self):
        if (len(self.__heap)) == 1:
            return
        newHeap = []        
        for pos in range(len(self.__heap)):
            if self.__heap[pos]._Node__key < self.__heap[-1]._Node__key:
                newHeap.append(self.__heap[pos])
            else: 
                newHeap.append(self.__heap[-1])
                while pos < len(self.__heap) - 1:
                    newHeap.append(self.__heap[pos])
                    pos += 1
                break
        self.__heap = newHeap
        self.__heapify()


    def Insert(self, value):
        newNode = Node(value)
        self.__heap.append(newNode) 
        self.__Union()

    def printHeap(self):
        for node in self.__heap:
            node._Node__Traversal()
            stdout.write("\n")

    def getMin(self):
        return self.__heap[0]._Node__key

    def ExtractMin(self):
        answer = self.getMin()  
        if self.__heap[0]._Node__childList == []:
            self.__heap.pop(0)
        else:
            self.__heap[0].extractMin()
        if len(self.__heap) > 1:
            if self.__heap[0]._Node__key > self.__heap[1]._Node__key:
                self.__heap[0], self.__heap[1] = self.__heap[1], self.__heap[0]
        return answer


if __name__ == "__main__":  
    binomialHeap = BinomialHeap()
    _input = stdin.readline()
    _input = list(map(int, _input.split())) 

    for key in _input:
        binomialHeap.Insert(key)

    binomialHeap.printHeap()

    while binomialHeap._BinomialHeap__heap:
        stdout.write("\n")
        binomialHeap.ExtractMin()
        binomialHeap.printHeap()
