class Node():
    def __init__(self,data):
        self.data = data
        self.Next = None
class Stack():
    def __init__(self):
        self.top = None
    def push(self,data):
        temp = Node(data)
        temp.Next = self.top
        self.top = temp
    def pop(self):
        if self.top != None:
            print self.top.data
            self.top = self.top.Next
        else:
            print "No data!"
s = Stack()
pus = raw_input("Push a data?yes or no:")
while pus == "yes":
    pu = input("Push a data:")
    s.push(pu)
    pus = raw_input("More data?Yes or No:")
tak = raw_input("Take a data?Yes or No:")
while tak == "yes":
    s.pop()
    tak = raw_input("More data?Yes or No:")

       
