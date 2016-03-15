# coding: utf-8
from svmutil import *


# In[ ]:

def read_problem(data_file_name, types):
    """
    svm_read_problem(data_file_name) -> [y, x]

    Read LIBSVM-format data from data_file_name and return labels y
    and data instances x.
    """
    prob = {}
    for item in types:
        prob[item] = []

    for line in open(data_file_name):
        line = line.split(None, 1)
        # In case an instance with all zero features
        if len(line) == 1: line += ['']
        label, features = line
        if int(label) not in types:
            continue
        xi = {}
        for e in features.split():
            ind, val = e.split(":")
            xi[int(ind)] = float(val)
#       prob_y += [float(label)]
#       prob_x += [xi]
        prob[int(label)] += [xi]
    return prob

train_filename = "../../train.txt"
problem = {}

import random

def random_data():
    random.seed(9727)
    print problem.keys()
    for i in xrange(12):
        random.shuffle(problem[i])

problem = read_problem(train_filename, range(12))
random_data()


# In[89]:

m = {}
def one_vs_one_train(kernel):
    '''
    kernel 0:linear 2:rbf
    '''
    for i in xrange(12):
        m[i] = {}
    for i in xrange(12):
        print i
        for j in xrange(i + 1, 12):
            y = [float(1) for k in xrange(len(problem[i]))]                +[float(0) for k in xrange(len(problem[j]))]
            x = problem[i] + problem[j]
            m[i][j] = svm_train(y, x, '-t %d -c 8 -g 0.25' % kernel)
            svm_save_model('./ovo_model/ovo_%02d_%02d_%d' % (i, j, kernel), m[i][j])
            p_label, p_acc, p_val = svm_predict(y, x, m[i][j])

one_vs_one_train(0)
one_vs_one_train(2)            


# In[96]:

def load_ovo_model(kernel):
    for i in xrange(12):
        for j in xrange(i + 1, 12):
            m[i][j] = svm_load_model('./ovo_model/ovo_%02d_%02d_%d' % (i, j, kernel))

class OVONet():
    def __init__(self):
        self.model = m
        for i in xrange(12):
            #self.model[i] = {}
            for j in xrange(i + 1, 12):
                pass
                #self.model[i][j] = svm_load_model('./ovo_model/ovo_%02d_%02d_%d' % (i, j, 2))

    def classify(self, data):
        vote = [0 for i in xrange(12)]
        for i in xrange(12):
            for j in xrange(i + 1, 12):
                pred_labels, ev, pred_values = svm_predict([0], [data], self.model[i][j], '-q')
                if pred_labels[0] > 0.5:
                    vote[i] += 1
                else:
                    vote[j] += 1

        return vote.index(max(vote))

ovonet = OVONet()
print m[0][1]
print ovonet.classify(problem[10][5])
print [len(problem[i]) for i in xrange(12)]


# In[97]:

allc = 0
rightc = 0

for i in xrange(12):
    print i
    allc = 0
    rightc = 0
    for j in xrange(len(problem[i])):
        allc += 1
        if ovonet.classify(problem[i][j]) == i:
            rightc += 1
    print 1.0 * rightc / allc


# In[151]:

m_all = {}

def one_vs_all_train(kernel):
    '''
    kernel 0:linear 2:rbf
    '''
    random.seed(9727)
    y = []
    x = []
    for i in xrange(12):
        y += [float(i) for j in xrange(len(problem[i]))]
    
    for i in xrange(12):
        x += problem[i]

    m_all = svm_train(y, x, '-t %d' % kernel)
    svm_save_model('./ova_model_%d' % (kernel), m_all)
    #p_label, p_acc, p_val = svm_predict(y, x, m[i][j])

one_vs_all_train(0)
one_vs_all_train(2)
print 'done'
   


# In[152]:

class OVANet():
    def __init__(self, kernel):
        self.model = svm_load_model('./ova_model_%d' % (kernel))

    def classify(self, data):
        pred_labels, ev, pred_values = svm_predict([0], [data], self.model, '-b 0 -q')
        return int(pred_labels[0])

ovanet = OVANet(2)


# In[ ]:

print m_all


# In[153]:

allc = 0
rightc = 0

for i in xrange(12):
    print i
    for j in xrange(len(problem[i])):
        allc += 1
        if ovanet.classify(problem[i][j]) == i:
           rightc += 1
    print 1.0 * rightc / allc

print 1.0 * rightc / allc



# In[155]:

import math
from svm import *
from svm import __all__ as svm_all
from svmutil import *

class PVPNet(object):
    def __init__(self):
        self.rho = 100
        self.gamma = 0.5
        self.Ni = [0 for i in xrange(12)]
        self.Li = [len(problem[i]) for i in xrange(12)]
        for i in xrange(12):
            if (((1.0 * self.Li[i] / self.rho) - int(self.Li[i] / self.rho) <= self.gamma) and                self.Li[i] > self.rho):
                self.Ni[i] = int(1.0 * self.Li[i] / self.rho)
            else:
                self.Ni[i] = int(math.ceil(1.0 * self.Li[i] / self.rho))
        self.m = {}
        for i in xrange(12):
            self.m[i] = {}
            for j in xrange(i + 1, 12):
                self.m[i][j] = {}
        print self.Ni

    def load_model(self, kernel):
        for i in xrange(12):
            for j in xrange(i + 1, 12):
                for idx in xrange(self.Ni[i] * self.Ni[j]):
                    self.m[i][j][idx] = svm_load_model('./pvp_model/pvp_%02d_%02d_%d_%d' % (i, j, idx, kernel))
        

    def train(self, kernel):
        for i in xrange(12):
            print i
            for j in xrange(i + 1, 12):
                Lii = self.Li[i] / self.Ni[i]
                Ljj = self.Li[j] / self.Ni[j]
                for k in xrange(self.Ni[i]):
                    for l in xrange(self.Ni[j]):
                        x1 = problem[i][Lii * k : min(Lii * (k + 1), self.Li[i])]
                        x2 = problem[j][Ljj * l : min(Ljj * (l + 1), self.Li[j])]
                        x = x1 + x2
                        y = [float(1) for kk in xrange(len(x1))] + [float(0) for kk in xrange(len(x2))]
                        idx = self.Ni[j] * k + l
                        self.m[i][j][idx] = svm_train(y, x, '-t %d -c 8' % kernel)
                        svm_save_model('./pvp_model/pvp_%02d_%02d_%d_%d' % (i, j, idx, kernel),                                        self.m[i][j][idx])

    def classify(self, data):
        vote = [0 for i in xrange(12)]
        mij = [[0 for i in xrange(12)] for j in xrange(12)]
        for i in xrange(12):
            for j in xrange(i + 1, 12):
                #maxx = []
                #for k in xrange(self.Ni[i]):
                #    minn = []
                #    for l in xrange(self.Ni[j]):
                #        pred_labels, ev, pred_values = svm_predict([0], [data], self.m[i][j][k * self.Ni[j] + l], '-b 0 -q')
                #        minn.append(pred_labels[0])
                #    maxx.append(min(minn))
                #rst = max(maxx)
                mij[i][j] = max([min([svm_predict([0], [data], self.m[i][j][self.Ni[j] * k + l], '-q')[2][0][0]                                 for l in xrange(self.Ni[j])])                            for k in xrange(self.Ni[i])])
        for i in xrange(12):
            for j in xrange(i):
                mij[i][j] = 1 -  mij[j][i]
                
        for i in xrange(12):
            vote[i] = min(mij[i][:i] + mij[i][i + 1:])
        return vote.index(max(vote))

pvpnet = PVPNet()
pvpnet.train(0)
#pvpnet.load_model(2)
                        
    
    


# In[156]:

pvpnet.classify(problem[5][0])


# In[157]:

allc = 0
rightc = 0
def read_test(data_file_name, types):
    """
    svm_read_problem(data_file_name) -> [y, x]

    Read LIBSVM-format data from data_file_name and return labels y
    and data instances x.
    """
    prob = {}
    for item in types:
        prob[item] = []
    for line in open(data_file_name):
        line = line.split(None, 1)
        # In case an instance with all zero features
        if len(line) == 1: line += ['']
        label, features = line
        if int(label) not in types:
            continue
        xi = {}
        for e in features.split():
            ind, val = e.split(":")
            xi[int(ind)] = float(val)
        prob[int(label)] += [xi]
    return prob

test_filename = "../../test.txt"
test = {}
def random_test():
    for i in xrange(12):
        random.shuffle(test[i])

test = read_test(test_filename, range(12))
random_test()

for i in xrange(12):
    print i
    allc = 0
    rightc = 0
    for j in xrange(len(test[i])):
        allc += 1
        if pvpnet.classify(test[i][j]) == i:
            rightc += 1
    print 1.0 * rightc / allc

