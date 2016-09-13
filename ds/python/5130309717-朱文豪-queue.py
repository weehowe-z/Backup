class Node():
    def __init__(self,data):
        self.data = data
        self.next = None
class Queue():
    def __init__(self):
        self.head = None
        self.tail = None
    def inqueue(self,data):
        temp = Node(data)
        if  self.head != None:
            self.tail.next = temp
            self.tail = temp
        else:
            self.head = temp
            self.tail = temp
            self.head.next = self.tail
    def outqueue(self):
        if  self.head != None:
            print self.head.data
            self.head = self.head.next
        else:
            print "No data"
q = Queue()
inq = raw_input("Inqueue a data?Yes or No:")
while inq == "yes":
    inp = raw_input("Input a data :")
    q.inqueue(inp)
    inq = raw_input("More data?Yes or No:")
deq = raw_input("Dequeue a data?Yes or No:")
while deq == "yes":
    q.outqueue()
    deq = raw_input("More data?Yes or No:")
    
