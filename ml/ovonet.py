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


class OVONet(object):

    def __init__(self, problem, kernel):
        if kernel == 'linear':
            self.model = self.one_vs_one_train(problem, 0)
        elif kernel == 'rbf':
            self.model = self.one_vs_one_train(problem, 2)
        else:
            raise ValueError("Only support kernel function linear and rbf!")

    def one_vs_one_train(self, problem, kernel):
        '''
        kernel 0:linear 2:rbf
        '''
        m = {}
        for i in xrange(12):
            m[i] = {}
        for i in xrange(12):
            print i
            for j in xrange(i + 1, 12):
                y = [float(1) for k in xrange(len(problem[i]))] + \
                    [float(0) for k in xrange(len(problem[j]))]
                x = problem[i] + problem[j]
                m[i][j] = svm_train(y, x, '-t %d -c 8 -g 0.25' % kernel)
                svm_save_model('./ovo_model/ovo_%02d_%02d_%d' %
                               (i, j, kernel), m[i][j])
                p_label, p_acc, p_val = svm_predict(y, x, m[i][j])
        return m

    def classify(self, data):
        vote = [0] * 12  # or  vote = [0 for i in xrange(12)]
        for i in xrange(0, 12):
            for j in xrange(i + 1, 12):
                pred_labels, ev, pred_values = svm_predict(
                    [0], [data], self.model[i][j], '-q')
                if pred_labels[0] > 0.5:
                    vote[i] += 1
                else:
                    vote[j] += 1
        return vote.index(max(vote))

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

    ovonet1 = OVONet(problem, 'linear')
    ovonet2 = OVONet(problem, 'rbf')

    print "---------------------"

    ovonet1.cal_accuracy(problem, 'linear', 'train')
    ovonet1.cal_accuracy(test_problem, 'linear', 'test')
    ovonet2.cal_accuracy(problem, 'rbf', 'train')
    ovonet2.cal_accuracy(test_problem, 'rbf', 'test')

if __name__ == '__main__':
    main()
