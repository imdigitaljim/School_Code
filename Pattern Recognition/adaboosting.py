import numpy as np
import random as r
import re
from sklearn import preprocessing as pp
import operator
import datetime

np.set_printoptions(precision=3, threshold=np.inf, suppress=True)

def train_fixed_increment(data_set, _class, epoch_max=100000):
    (n, feature_count) = data_set.shape
    weights = np.zeros((feature_count - 1,))
    best = np.inf
    best_weights = weights
    for epoch in range(epoch_max):
        old_weights = weights.copy()
        error_count = 0
        for sample in data_set:
            if classify_sample(sample, weights) <= 0:
                weights += sample[1:]
                error_count += 1
        if error_count == 0:
            print("no errors on epoch", epoch)
            return old_weights
        if error_count < best:
            best = error_count
            best_weights = old_weights
        if epoch % 10000 == 0:
            print("best error count:", best, " on epoch ", epoch)
            print("accuracy:", ((n - best) * 100) / n)
    return np.array(best_weights)

def train_batch_relax(data_set, _class, rate = .5, margin = .5, epoch_max=100000, is_print=True):
    (n, feature_count) = data_set.shape
    weights = np.zeros((feature_count - 1,))
    best = np.inf
    best_weights = weights
    for epoch in range(epoch_max):
        y_set = []
        old_weights = weights.copy()
        for sample in data_set:
            if classify_sample(sample, weights) <= 0:
                y_set += [sample[1:]]
        if len(y_set) == 0:
            if is_print:
                print("no errors on epoch ", epoch)
            return old_weights
        if len(y_set) < best:
            best = len(y_set)
            best_weights = old_weights
        sum_value = []
        for error in y_set:
            sum_value = error * ((margin - np.dot(weights, error)) / (np.linalg.norm(error) ** 2))
        #print("printing", rate * sum_value)
        weights += rate * sum_value
        if epoch % 10000 == 0 and is_print:
            print("best error count:", best, " on epoch ", epoch)
            print("accuracy:", ((n - best) * 100) / n)
    return np.array(weights)



def parse_raw_data(text):
    result = []
    for sample in text:
        sample = re.sub("[ ]+", ' ', sample)
        result += [[float(x) for x in sample.split(' ')]]
    return np.array(result)

def build_class_table(samples):
    data_set = {}
    keys = set()
    for sample in samples:
        key = int(sample[0])
        keys.add(key)
        if key in data_set:
            data_set[key] += [sample]
        else:
            data_set[key] = [sample]
    return data_set, keys

def sample_from(data, weights, min_size=2, cap=100000):
    min_size = max(min_size, 1)
    vals = []
    attempt = 0
    while len(vals) < min_size:
        val = r.random()
        print(val)
        exit()
    return np.array(vals)



def classify_sample(sample, weights):
    ssample = sample[1:]
    net = np.sum(weights * ssample)
    return -1 if net <= 0 else 1

def classify_test_set(test_set, weights, _class):
    count = 0
    for sample in test_set:
        pred = classify_sample(sample, weights)
        if pred > 0:
            count += 1
    print((count * 100) / len(test_set), " correct")

def normalize_2category(data_set, _class):
    (n, features) = data_set.shape
    result = []
    for i in range(len(data_set)):
        sample = [data_set[i][0]]
        for j in range(1, len(data_set[i])):
            if int(sample[0]) == _class:
                sample += [data_set[i][j]]
            else:
                sample += [data_set[i][j] * -1]
        result += [sample];
    return np.array(result)

def vote_2category(test_sample, weight_class, _classes):
    vote = [0] * (len(_classes) + 1)
    for _class in _classes:
        if classify_sample(test_sample, weight_class[_class]) > 0:
            vote[_class] += 1
    index, value = max(enumerate(vote), key=operator.itemgetter(1))
    return index
def vote_2category_ovoboost(test_sample, weights, _classes):
    for k,v in weights.items():
        pred = classify_sample(test_sample, v)
        return k[0] if pred > 0 else k[1]

def vote_multicategory(sample, weights, _classes):
    vote = [0] * (len(_classes) + 1)
    for k,v in weights.items():
        pred = classify_sample(sample, v)
        vote[k[0] if pred > 0 else k[1]] += 1
    index, value = max(enumerate(vote), key=operator.itemgetter(1))
    return index

def one_vs_one(data_set, test_set, _classes):
    print("ONE vs ONE - classification")
    z = datetime.datetime.now()
    weights_fixed_inc = {}
    weights_batch_relax = {}
    for _class in _classes:
        for _anotherclass in _classes:
            if _class != _anotherclass:
                print("*#*#*#*#*#*#*#*#*#*#*#*##*#*#*#*##*#*#*#*#*#*#*#*#*#*##")
                print("training ", _class, " against ", _anotherclass)
                full_set = np.concatenate((data_set[_class], data_set[_anotherclass]))
                norm_data_set = normalize_2category(full_set, _class)
                print("=======Training Fixed Increment Single Sample =========")
                a = datetime.datetime.now()
                weights_fixed_inc[(_class,_anotherclass)] = train_fixed_increment(norm_data_set, _class)
                print("took: ", (datetime.datetime.now() - a).total_seconds(), "seconds\n")
                print("=======Training Batch Relaxation With Margin =========")
                a = datetime.datetime.now()
                weights_batch_relax[(_class,_anotherclass)] = train_batch_relax(norm_data_set, _class)
                print("took: ", (datetime.datetime.now() - a).total_seconds(), "seconds\n")
                print("*#*#*#*#*#*#*#*#*#*#*#*##*#*#*#*##*#*#*#*#*#*#*#*#*#*##")

    print("=======Multiclass Classification =========")
    correct_fi = correct_br = 0
    for sample in test_set:
        if vote_multicategory(sample, weights_fixed_inc, _classes) == sample[0]:
             correct_fi += 1
        if vote_multicategory(sample, weights_batch_relax, _classes) == sample[0]:
             correct_br += 1

    print((correct_fi * 100) / len(test_set), " single increment correct")
    print((correct_br * 100) / len(test_set), " batch correct")
    print("Total time took: ", (datetime.datetime.now() - z).total_seconds(), "seconds\n")

def one_vs_rest(data_set, test_set, _classes):
    print("ONE vs REST - classification")
    z = datetime.datetime.now()
    weights_fixed_inc = {}
    weights_batch_relax = {}
    for _class in _classes:
        print("=======Training Fixed Increment Single Sample =========")
        print("training [", _class , "] against the rest")
        norm_test_set = normalize_2category(test_set, _class)
        norm_data_set = normalize_2category(data_set, _class)
        a = datetime.datetime.now()
        weights_fixed_inc[_class] = train_fixed_increment(norm_data_set, _class)
        print("took: ", (datetime.datetime.now() - a).total_seconds(), "seconds\n")
        print("performing 2cat classifications")
        classify_test_set(norm_test_set, weights_fixed_inc[_class], _class)
        print("=======Training Batch Relaxation With Margin =========")
        a = datetime.datetime.now()
        weights_batch_relax[_class] = train_batch_relax(norm_data_set, _class)
        print("took: ", (datetime.datetime.now() - a).total_seconds(), "seconds\n")
        print("performing 2cat classifications")
        classify_test_set(norm_test_set, weights_batch_relax[_class], _class)

    print("=======Multiclass Classification =========")
    correct_fi = correct_br = 0
    for sample in test_set:
        if vote_2category(sample, weights_fixed_inc, _classes) == sample[0]:
            correct_fi += 1
        if vote_2category(sample, weights_batch_relax, _classes) == sample[0]:
            correct_br += 1

    print((correct_fi * 100) / len(test_set), " single increment correct")
    print((correct_br * 100) / len(test_set), " batch correct")
    print("Total time took: ", (datetime.datetime.now() - z).total_seconds(), "seconds\n")

def adaboost(data_set, _class, _anotherclass, epoch_max=100000):
    (n, feature_count) = data_set.shape
    weights = np.ones((n,)) *  (1 / n)
    print(weights)
    for epoch in range(epoch_max):
        training_samples = sample_from(data_set, weights)
        weak = train_batch_relax(training_samples, _class, is_print=True)
        error = 0
        for sample in data_set:
            pred = _class if classify_sample(sample, weak) > 0 else _anotherclass
            if int(sample[0]) != pred:
                error += 1
        error /= n
        print("error is ", error)
        alpha_t = .5 * np.log((1 - error) / error) if error > 0 else 1
        Z = 2 * np.sqrt(error*(1 - error))
        for (i, w), sample in zip(enumerate(weights), data_set):
            if int(sample[0]) == (_class if w > 0 else _anotherclass):
                weights[i] = (weights[i] / Z) * np.exp(alpha_t)
            else:
                weights[i] = (weights[i] / Z) * np.exp(-alpha_t)

        if epoch % 5000 == 0:
            print(epoch, " is epoch")
            print(weights)







def adaboosting(data_set, test_set, _classes):
    print("Adaboosting ONE vs ONE - classification")
    for _class in _classes:
        for _anotherclass in _classes:
            if _class != _anotherclass:
                weights_batch_relax = {}
                print("*#*#*#*#*#*#*#*#*#*#*#*##*#*#*#*##*#*#*#*#*#*#*#*#*#*##")
                full_set = np.concatenate((data_set[_class], data_set[_anotherclass]));
                print("=======Training Batch Relaxation With Margin Adaboosting =========")
                norm_data_set = normalize_2category(full_set, _class)
                weights_batch_relax[(_class,_anotherclass)] = train_batch_relax(norm_data_set, _class, is_print=False)
                print("*#*#*#*#*#*#*#*#*#*#*#*##*#*#*#*##*#*#*#*#*#*#*#*#*#*##")
                print("=======Testing ",  _class, " against ", _anotherclass, " Classification =========")
                correct_br = 0
                count = 0
                for sample in test_set:
                    _2classes = [_class, _anotherclass]
                    if int(sample[0]) not in _2classes:
                        continue
                    count += 1
                    pred = vote_2category_ovoboost(sample, weights_batch_relax, _2classes)
                    if pred == int(sample[0]):
                         correct_br += 1
                print((correct_br * 100) / count, " batch correct (boosted)")



def main():
    training_keys = ["wine_uci_train.txt", "zip_train_0_2.txt"]
    test_keys = ["wine_uci_test.txt", "zip_test_0_2.txt"]
    for train_key, test_key in zip(training_keys, test_keys):
        print("^^^^^^^^^^^", train_key, " ", test_key, "^^^^^^^^^^^^")
        train_samples = parse_raw_data(x.strip() for x in open(train_key).read().strip().split('\n'))
        test_samples= parse_raw_data(x.strip() for x in open(test_key).read().strip().split('\n'))
        joined_set = np.concatenate((train_samples, test_samples))
        joined_set = np.concatenate((joined_set[:, :1], pp.normalize(joined_set[:, 1:], norm="max", axis=0)), axis=1)
        train_samples = joined_set[:len(train_samples)]
        test_samples = joined_set[len(train_samples):]
        train_samples_table, _classes = build_class_table(train_samples)
        #one_vs_rest(train_samples, test_samples, _classes)
        #one_vs_one(train_samples_table, test_samples, _classes)
        adaboosting(train_samples_table, test_samples, _classes)

main()
