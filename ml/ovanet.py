# coding: utf-8
from svmutil import *


def read_data(data_file_name, types):
    problem = {}
    for item in types:
        problem[item] = []

    for line in open(data_file_name):
        line = line.split(None, 1)
        if len(line) == 1:
            line += ['']
        label, features = line
        if int(label) not in types:
            continue
        xi = {}
        for e in features.split():
            ind, val = e.split(":")
            xi[int(ind)] = float(val)
        problem[int(label)] += [xi]
    return problem


class OVANet(object):

    def __init__(self, problem, kernel):
        if kernel == 'linear':
            self.model = self.one_vs_all_train(problem, 0)
        elif kernel == 'rbf':
            self.model = self.one_vs_all_train(problem, 2)
        else:
            raise ValueError("Only support kernel function linear and rbf!")

    def one_vs_all_train(self, problem, kernel):
        '''
        kernel 0:linear 2:rbf
        '''
        y = []
        x = []
        for i in xrange(12):
            y += [float(i) for j in xrange(len(problem[i]))]

        for i in xrange(12):
            x += problem[i]

        m_all = svm_train(y, x, '-t %d' % kernel)
        # svm_save_model('./ova_model_%d' % (kernel), m_all)
        return m_all

    def classify(self, data):
        pred_labels, ev, pred_values = svm_predict(
            [0], [data], self.model, '-b 0 -q')
        return int(pred_labels[0])

    def cal_accuracy(self, problem, kernel, dataset):
        print "kernel: " + kernel
        print "dataset: " + dataset
        allcount = [0] * 12
        rightcount = [0] * 12

        for i in xrange(0, 12):
            for j in xrange(0, len(problem[i])):
                allcount[i] += 1
                if self.classify(problem[i][j]) == i:
                    rightcount[i] += 1
            print "Accuracy of label%d:\t%.1f%%" % (i, (rightcount[i] * 1.0 / allcount[i]) * 100)

        print "Accuracy of total problem:\t%.1f%%" % (sum(rightcount) * 1.0 / sum(allcount) * 100)
        print "---------------------"


def main():
    train_filename = "train.txt"
    test_filename = "test.txt"

    problem = {}
    test_problem = {}

    problem = read_data(train_filename, range(12))
    test_problem = read_data(test_filename, range(12))

    OVANet1 = OVANet(problem, 'linear')
    OVANet2 = OVANet(problem, 'rbf')

    print "---------------------"

    OVANet1.cal_accuracy(problem, 'linear', 'train')
    OVANet1.cal_accuracy(test_problem, 'linear', 'test')
    OVANet2.cal_accuracy(problem, 'rbf', 'train')
    OVANet2.cal_accuracy(test_problem, 'rbf', 'test')

if __name__ == '__main__':
    main()
