# endocoding:utf-8
import math
import random
import numpy
import matplotlib.pyplot as plt



# 生成区间[a, b)内的随机数
def rand(a, b):
    return (b - a) * random.random() + a


# 生成大小 I*J 的矩阵，默认零矩阵 (当然，亦可用 NumPy 提速)
def makeMatrix(I, J, fill=0.0):
    m = []
    for i in range(I):
        m.append([fill] * J)
    return m


def sigmoid(x):
    return 1/(1+numpy.exp(-x))

def dsigmoid(y):
    return y*(1-y)


class NN:
    ''' 三层反向传播神经网络 '''

    def __init__(self, ni, nh, no):
        # 输入层、隐藏层、输出层的节点（数）
        self.ni = ni + 1  # 增加一个偏差节点
        self.nh = nh
        self.no = no

        # 激活神经网络的所有节点（向量）
        self.ai = [1.0] * self.ni
        self.ah = [1.0] * self.nh
        self.ao = [1.0] * self.no

        # 建立权重（矩阵）
        self.wi = makeMatrix(self.ni, self.nh)
        self.wo = makeMatrix(self.nh, self.no)
        # 设为随机值
        for i in range(self.ni):
            for j in range(self.nh):
                self.wi[i][j] = rand(-0.1, 0.1)
        for j in range(self.nh):
            for k in range(self.no):
                self.wo[j][k] = rand(-0.1, 0.1)

        # 最后建立动量因子（矩阵）
        self.ci = makeMatrix(self.ni, self.nh)
        self.co = makeMatrix(self.nh, self.no)

    def update(self, inputs):
        if len(inputs) != self.ni - 1:
            raise ValueError('与输入层节点数不符！')

        # 激活输入层
        for i in range(self.ni - 1):
            # self.ai[i] = sigmoid(inputs[i])
            self.ai[i] = inputs[i]

        # 激活隐藏层
        for j in range(self.nh):
            sum = 0.0
            for i in range(self.ni):
                sum = sum + self.ai[i] * self.wi[i][j]
            self.ah[j] = sigmoid(sum)

        # 激活输出层
        for k in range(self.no):
            sum = 0.0
            for j in range(self.nh):
                sum = sum + self.ah[j] * self.wo[j][k]
            self.ao[k] = sigmoid(sum)

        return self.ao[:]

    def backPropagate(self, targets, N, M):
        ''' 反向传播 '''
        if len(targets) != self.no:
            raise ValueError('与输出层节点数不符！')

        # 计算输出层的误差
        output_deltas = [0.0] * self.no
        for k in range(self.no):
            error = targets[k] - self.ao[k]
            output_deltas[k] = dsigmoid(self.ao[k]) * error

        # 计算隐藏层的误差
        hidden_deltas = [0.0] * self.nh
        for j in range(self.nh):
            error = 0.0
            for k in range(self.no):
                error = error + output_deltas[k] * self.wo[j][k]
            hidden_deltas[j] = dsigmoid(self.ah[j]) * error

        # 更新输出层权重
        for j in range(self.nh):
            for k in range(self.no):
                change = output_deltas[k] * self.ah[j]
                self.wo[j][k] = self.wo[j][k] + N * change + M * self.co[j][k]
                self.co[j][k] = change
                # print(N*change, M*self.co[j][k])

            # 更新输入层权重
        for i in range(self.ni):
            for j in range(self.nh):
                change = hidden_deltas[j] * self.ai[i]
                self.wi[i][j] = self.wi[i][j] + N * change + M * self.ci[i][j]
                self.ci[i][j] = change

        # 计算误差
        error = 0.0
        for k in range(len(targets)):
            error = error + 0.5 * (targets[k] - self.ao[k]) ** 2
        return error

    def test(self, patterns):
        for p in patterns:
            result = self.update([p[0], p[1]])
            print "%f %f" % (result[0], p[2])

    def weights(self):
        print('输入层权重:')
        for i in range(self.ni):
            print(self.wi[i])
        print()
        print('输出层权重:')
        for j in range(self.nh):
            print(self.wo[j])

    def train(self, patterns, maxEpoch=10000, minError = 0.05, N=0.05, M=0.1):
        # N: 学习速率(learning rate)
        # M: 动量因子(momentum factor)
        for i in range(maxEpoch):
            error = 0.0
            for p in patterns:
                inputs = [p[0], p[1]]
                targets = [p[2]]
                self.update(inputs)
                error = error + self.backPropagate(targets, N, M)
           	# if (error <= 0.05):
           	# 	print "Convergence"
           	# 	break
            if  i%200 == 0:
                print 'Epoch' + str(i) + (' ErrorSum %-.5f' % error)

def divide(set):
	random.shuffle(set)
	result = [[],[],[],[]]
	for i in xrange(0,len(set)):
		result[i%4].append(set[i])
	return result

def combine(set1,set2):
    result = []
    for whiteSet in set1:
        for blackSet in set2:
            result.append( whiteSet + blackSet )
    return result

def arrange(set):
    whiteSet=[]
    blackSet=[]
    for data in set:
        if data[2]==1.0:
            whiteSet.append(data)
        else:
            blackSet.append(data)

    whiteSets = divide(whiteSet)
    blackSets = divide(blackSet)

    return combine(whiteSets,blackSets)

def MinMaxNN():

	rawSet = numpy.loadtxt("two_spiral_train.txt")
	resultSets = arrange(rawSet)


	networks = []
	for i in xrange(0,16):
		print "now deal with network " + str(i)
		network = NN(2,20,1)
		network.train(resultSets[i])
		networks.append(network)


	xset_black_semi =[[],[],[],[]]
	yset_black_semi = [[],[],[],[]]
	xset_black_final = []
	yset_black_final = []


#    Just for save the ram

	for p in xrange(0,16):
		yset_black = []
		xset_black = []
		for x in xrange(-100,101):
			line = []
			for y in xrange(-100,101):
				pos = [x / 200.0 * 8, y / 200.0 * 8]
				output = networks[p].update(pos)[0]
				if (output>=0.5):
					xset_black.append(x)
					yset_black.append(y)
		plt.scatter(xset_black,yset_black,color='0')
		plt.savefig('figure'+str(p)+'.jpg')
		plt.close('all')	


	for x in xrange(-100,101):
		line = []
		for y in xrange(-100,101):
			pos = [x / 200.0 * 8, y / 200.0 * 8]
			output_temp = []
			for network in networks:
				output = network.update(pos)[0]
				output_temp.append(output)
			out1 = min(output_temp[0:3])
			out2 = min(output_temp[4:7])
			out3 = min(output_temp[8:11])
			out4 = min(output_temp[12:15])
			# out = max(min(output_temp[0:3]),min(output_temp[4:7]),min(output_temp[8:11]),min(output_temp[12:15]))
			out = max (out1,out2,out3,out4)
			if (out>=0.5):
				xset_black_final.append(x)
				yset_black_final.append(y)
			if (out1>=0.5):
				xset_black_semi[0].append(x)
				yset_black_semi[0].append(y)
			if (out2>=0.5):
				xset_black_semi[1].append(x)
				yset_black_semi[1].append(y)
			if (out3>=0.5):
				xset_black_semi[2].append(x)
				yset_black_semi[2].append(y)
			if (out4>=0.5):
				xset_black_semi[3].append(x)
				yset_black_semi[3].append(y)

	for i in xrange(0,4):
		plt.scatter(xset_black_semi[i],yset_black_semi[i],color='0')
		plt.savefig('figure-semi'+ str(i) + '.jpg')
		plt.close('all')


	plt.scatter(xset_black_final,yset_black_final,color='0')
	plt.savefig('figure-final.jpg')
	plt.close('all')


if __name__ == '__main__':
    MinMaxNN()
