def trans_data():
    with open("test.txt", 'r') as fin:
        with open("test1.txt", 'w') as fout:
            for line in fin:
                labels = line.split(" ")[0].split(",")
                for label in labels:
                    isA = float(label[0] == 'A')
                    fout.write(str(isA) + ' ' + line[line.find(" ") + 1:])


trans_data()


def test_data():
    a = 0
    all = 0
    with open("test1.txt", 'r') as fin:
        for line in fin:
            labels = line.split(" ")[0].split(",")
            for label in labels:
                isA = int(label[0])
                if isA > 0.5:
                    a += 1
                all += 1
    print a, all
test_data()


from liblinearutil import *


def train1():
    y, x = svm_read_problem('train1.txt')
    m = train(y, x)
    save_model("model1", m)

    train1()


def pre():
    m = load_model("model1")
    y, x = svm_read_problem("./test1.txt")
    predict(y, x, m)

pre()
