# coding: utf-8
import math
from svm import *
from svm import __all__ as svm_all
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


class PVPNet(object):

    def __init__(self, problem, kernel):
        self.rho = 100
        self.gamma = 0.5
        self.Ni = [0 for i in xrange(12)]
        self.Li = [len(problem[i]) for i in xrange(12)]
        for i in xrange(12):
            if (((1.0 * self.Li[i] / self.rho) - int(self.Li[i] / self.rho) <= self.gamma) and self.Li[i] > self.rho):
                self.Ni[i] = int(1.0 * self.Li[i] / self.rho)
            else:
                self.Ni[i] = int(math.ceil(1.0 * self.Li[i] / self.rho))
        self.m = {}
        for i in xrange(12):
            self.m[i] = {}
            for j in xrange(i + 1, 12):
                self.m[i][j] = {}
        self.model = self.train(problem, kernel)

    # def load_model(self, kernel):
    #     for i in xrange(12):
    #         for j in xrange(i + 1, 12):
    #             for idx in xrange(self.Ni[i] * self.Ni[j]):
    #                 self.m[i][j][idx] = svm_load_model('./pvp_model/pvp_%02d_%02d_%d_%d' % (i, j, idx, kernel))

    def train(self, problem, kernel):
        for i in xrange(12):
            for j in xrange(i + 1, 12):
                Lii = self.Li[i] / self.Ni[i]
                Ljj = self.Li[j] / self.Ni[j]
                for k in xrange(self.Ni[i]):
                    for l in xrange(self.Ni[j]):
                        x1 = problem[i][
                            Lii * k: min(Lii * (k + 1), self.Li[i])]
                        x2 = problem[j][
                            Ljj * l: min(Ljj * (l + 1), self.Li[j])]
                        x = x1 + x2
                        y = [float(1) for kk in xrange(len(x1))] + \
                            [float(0) for kk in xrange(len(x2))]
                        idx = self.Ni[j] * k + l
                        self.m[i][j][idx] = svm_train(
                            y, x, '-t %d -c 8' % kernel)
                        # svm_save_model('./pvp_model/pvp_%02d_%02d_%d_%d' % (i, j, idx, kernel),self.m[i][j][idx])

    def classify(self, data):
        vote = [0 for i in xrange(12)]
        mij = [[0 for i in xrange(12)] for j in xrange(12)]
        for i in xrange(12):
            for j in xrange(i + 1, 12):
                mij[i][j] = max([min([svm_predict([0], [data], self.m[i][j][self.Ni[
                                j] * k + l], '-q')[2][0][0] for l in xrange(self.Ni[j])]) for k in xrange(self.Ni[i])])
        for i in xrange(12):
            for j in xrange(i):
                mij[i][j] = 1 - mij[j][i]

        for i in xrange(12):
            vote[i] = min(mij[i][:i] + mij[i][i + 1:])
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

    # OVANet1 = OVANet(problem,'linear')
    # OVANet2 = OVANet(problem,'rbf')
    pvpnet1 = PVPNet(problem, 0)
    pvpnet2 = PVPNet(problem, 2)

    print "---------------------"

    pvpnet1.cal_accuracy(problem, 'linear', 'train')
    pvpnet1.cal_accuracy(test_problem, 'linear', 'test')
    pvpnet2.cal_accuracy(problem, 'rbf', 'train')
    pvpnet2.cal_accuracy(test_problem, 'rbf', 'test')

if __name__ == '__main__':
    main()
