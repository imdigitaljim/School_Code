import math
import requests
import re
import datetime
import numpy as np
from sklearn import preprocessing as pp
np.set_printoptions(threshold=np.inf)
#np.seterr(all='raise')

separation = "." * 60
title_separation = "#" * 60


def get_cov(samples):
    mean = np.mean(samples, axis=0)
    cov_matrix = []
    for i in range(len(samples[0])):
        cov_row = []
        for j in range(len(samples[0])):
            sum = 0
            for k in range(len(samples)):
                sum += (samples[k][i] - mean[i]) * (samples[k][j] - mean[j])
            cov_row += [1 / len(samples) * sum]
        cov_matrix += [cov_row]
    return np.array(cov_matrix)


def get_BMLE_class_conditional(test_sample, mean, invcov_matrix, sqrt_det, const):
    diff = np.array(test_sample) - mean
    exp_power = -.5 * np.dot(np.dot(diff.T, invcov_matrix), diff)     
    return math.exp(exp_power)/(const * sqrt_det)  


def get_BPW_class_conditional(test_sample, train_set, h):
    sum = 0
    n = len(train_set)
    d = len(test_sample)
    constant = (2 * np.pi)**(d / 2) * h**d * n
    for sample in train_set:
        diff = (sample - test_sample) / h
        exp_power = np.dot(diff, diff.T) * -0.5
        sum += np.exp(exp_power) / constant
    return sum    
    
def get_parzen_window_classification(trained, test_sample):   
    max_probability = float('-inf')
    best_match = None
    h = trained.data["parzen"]["hwindow"]
    for key, val in trained.data["parzen"]["train"].items():
        bpw = get_BPW_class_conditional(test_sample, val, h)

        class_conditional = np.log(bpw) * np.log(len(val) / trained.n)
        
        if best_match is None or class_conditional > max_probability:
            max_probability = class_conditional
            best_match = key
    return best_match


def get_max_likelihood_classification(trained, test_sample):
    max_probability = float('-inf')
    best_match = None    
    for key, val in trained.data["mle"]["train"].items():
        const = (2 * np.pi) ** (len(val)/2)
        mean = trained.data["mle"]["statistics"][key]["mean"]
        invcov_matrix = trained.data["mle"]["statistics"][key]["inv_cov_matrix"]
        sqrt_det = trained.data["mle"]["statistics"][key]["sqrt_det"]
        
        blme = get_BMLE_class_conditional(test_sample, mean, invcov_matrix, sqrt_det, const)
        class_conditional = np.log(blme) * np.log(len(val) / trained.n)
        if best_match is None or class_conditional > max_probability:
            max_probability = class_conditional
            best_match = key
    return best_match


def get_neighbors(data_set, k, test_sample):
    distances = []
    for sample in data_set:
        distances += [[np.linalg.norm(test_sample - sample[1:]), sample]]
    distances.sort(key=lambda x: x[0])
    return distances[:k]


def get_knn_classification(data_set, k, test_sample, neighbors=None):
    if neighbors is None:
        neighbors = get_neighbors(data_set, k, test_sample)
    classification = {}
    for i in range(len(neighbors)):
        key = neighbors[i][1][0]
        if key in classification:
            classification[key] += 1
        else: 
            classification[key] = 1
    max_value = max(classification.values())  # maximum value
    max_keys = [k for k, v in classification.items() if v == max_value]
    if (len(max_keys) is 1):
        return max_keys[0]
    else:
        return get_knn_classification(data_set, k, test_sample, neighbors[:-1])


def parse_raw_data(text):
    result = []
    class_table = {}
    for sample in text:    
        sample = re.sub("[ ]+", ' ', sample)
        result += [[float(x) for x in sample.split(' ')]]
        key = result[-1][0]
        if key in class_table:
            class_table[key] += 1
        else:
            class_table[key] = 1
    return np.array(result), class_table

def run_classifier(test_data, header, classification_func, args):
    print("\n" + separation)
    print(header)
    print(separation)
    a = datetime.datetime.now()
    correctly_classified = 0
    for i, sample in enumerate(test_data):
        classification = classification_func(*args, sample[1:])
        if int(sample[0]) is int(classification):
            correctly_classified += 1
    b = datetime.datetime.now()
    print("took: ",(b - a).total_seconds(), " seconds")
    print("accuracy: ",(correctly_classified * 100) / len(test_data))


def build_class_table(training):
    sample_table = {}
    for sample in training:
        key = sample[0]
        if key in sample_table:
            sample_table[key] += [sample[1:]]
        else:
            sample_table[key] = [sample[1:]]
    return sample_table
    
class ClassifierSet:
    
    def __init__(self, n, d, test_set=[]):
        self.n = n
        self.d = d
        self.class_frequency = {}
        self.data = { "knn" : {
                                "accuracy" : 0, "train" : {}, "test" : test_set, "k" : 1
                              }, 
                      "parzen" : {
                                  "accuracy" : 0, "statistics" : {}, "train" : {}, "test" : test_set, "hwindow" : 1
                                 },       
                      "mle" : {    
                                "accuracy" : 0, "statistics" : {}, "train" : {}, "test" : test_set
                              } 
                    }               
    def set_statistics(self, key, training):
        self.data[key]["train"] = build_class_table(training)
        stat_set = {}
        for dkey, dval in self.data[key]["train"].items():   
            stats = { 
                    "mean" : [],
                    "inv_cov_matrix" : [],
                    "sqrt_det" : []
                    }
            
            cov_matrix = get_cov(dval) 
            determinant = np.linalg.det(cov_matrix)
            stats["mean"] = np.mean(dval, axis=0)    
            if determinant == 0: 
                beta_value = 0.4 #TODO: better handle this?   
                cov_matrix = (1 - beta_value) * cov_matrix + beta_value * np.identity(len(cov_matrix))
                determinant = np.linalg.det(cov_matrix)
            stats["inv_cov_matrix"] = np.linalg.inv(cov_matrix)
            stats["sqrt_det"] = determinant**(1/2)
            stat_set[dkey] = stats
        self.data[key]["statistics"] = stat_set
        
def get_parzen_leave_one_out(train_samples):
    d = len(train_samples[0] - 1)
    n = len(train_samples) - 1 #leaving -1 out
    h = (4 / (2 * d + 1))**(1/(d + 4)) * n **(-1/(d + 4)) 
    accuracy = correctly_classified = 0
    for i, sample in enumerate(train_samples):
        new_samples = np.delete(train_samples, (i), axis=0)
        classifier_set = ClassifierSet(len(new_samples), len(sample[1:]), test_set=sample)
        classifier_set.set_statistics("parzen", new_samples)
        classifier_set.data["parzen"]["hwindow"] = h
        classification = get_parzen_window_classification(classifier_set, sample[1:])     
        if int(sample[0]) is int(classification):
            correctly_classified += 1  
    return correctly_classified / len(new_samples)
        
def get_mle_leave_one_out(train_samples):
    accuracy = correctly_classified = 0
    for i, sample in enumerate(train_samples):
        new_samples = np.delete(train_samples, (i), axis=0)
        classifier_set = ClassifierSet(len(new_samples), len(sample[1:]), test_set=sample)
        classifier_set.set_statistics("mle", new_samples)
        classification = get_max_likelihood_classification(classifier_set, sample[1:])     
        if int(sample[0]) is int(classification):
            correctly_classified += 1  
    return correctly_classified / len(new_samples)

def get_k_leave_one_out(train_samples):
    k = best_k = 1
    best_accuracy = 0

    min_type = len(train_samples)
    for key, value in build_class_table(train_samples).items():
        min_type = min(min_type, len(value))
    while(k < min_type): 
        correctly_classified = 0    
        for i, sample in enumerate(train_samples):
            new_samples = np.delete(train_samples, (i), axis=0)
            classification = get_knn_classification(new_samples, k, sample[1:])
            if int(sample[0]) is int(classification):
                correctly_classified += 1  
        accuracy = correctly_classified / len(new_samples)
        if accuracy > best_accuracy: 
            best_k = k
            best_accuracy = accuracy
        k += 1
    return best_accuracy, best_k
   
def train(training_key, test_key, norm_assignments):
        
        train_samples, frequency = parse_raw_data(x.strip() for x in open(training_key).read().strip().split('\n'))
        test_samples, _ = parse_raw_data(x.strip() for x in open(test_key).read().strip().split('\n'))
        trained = ClassifierSet(len(train_samples), len(test_samples[0]) - 1) 
        trained.class_frequency = frequency
           
        if len(norm_assignments) == 3:
            #0 parzen
            ptrain = mtrain = ktrain = []
            
            if norm_assignments[0] is not None:
                joined_set = np.concatenate((train_samples, test_samples))
                joined_set = np.concatenate((joined_set[:, :1], pp.normalize(joined_set[:, 1:], norm=norm_assignments[0], axis=0)), axis=1)
                ptrain = joined_set[:len(train_samples)]
                trained.data["parzen"]["test"] = joined_set[len(train_samples):]
            else:
                ptrain = train_samples
                trained.data["parzen"]["test"] = test_samples
            if norm_assignments[1] is not None:
                joined_set = np.concatenate((train_samples, test_samples))
                joined_set = np.concatenate((joined_set[:, :1], pp.normalize(joined_set[:, 1:], norm=norm_assignments[1], axis=0)), axis=1)
                mtrain = joined_set[:len(train_samples)]
                trained.data["mle"]["test"] = joined_set[len(train_samples):]
            else:
                mtrain = train_samples
                trained.data["mle"]["test"] = test_samples
            if norm_assignments[2] is not None:
                joined_set = np.concatenate((train_samples, test_samples))
                joined_set = np.concatenate((joined_set[:, :1], pp.normalize(joined_set[:, 1:], norm=norm_assignments[2], axis=0)), axis=1)
                trained.data["knn"]["train"] = joined_set[:len(train_samples)]
                trained.data["knn"]["test"] = joined_set[len(train_samples):]
            else:
                trained.data["knn"]["train"] = train_samples
                trained.data["knn"]["test"] = test_samples 
            
                 
            n = trained.n
            d = trained.d
            trained.data["parzen"]["hwindow"] = (4 / (2 * d + 1))**(1/(d + 4)) * n **(-1/(d + 4)) 
            trained.set_statistics("parzen", ptrain)
            #1 mle
            trained.set_statistics("mle", mtrain)
            _ , trained.data["knn"]["k"] = get_k_leave_one_out(trained.data["knn"]["train"])
            return trained

                
        #try each normalization   
        for i, norm_factor in enumerate([None, 'l1','l2', 'max']):
        
            
            if norm_factor is not None:
                joined_set = np.concatenate((train_samples, test_samples))
                joined_set = np.concatenate((joined_set[:, :1], 
                                             pp.normalize(joined_set[:, 1:], 
                                                         norm=norm_factor, axis=0)), 
                                             axis=1)
                train_samples = joined_set[:len(train_samples)]
                test_samples = joined_set[len(train_samples):]

            
            print("getting leave-one-out training values...")
            
            #parzen leave-one-out accuracy
            accuracy = get_parzen_leave_one_out(train_samples)
            if accuracy > trained.data["parzen"]["accuracy"]: 
               trained.data["parzen"]["accuracy"] = accuracy
               trained.data["parzen"]["test"] = test_samples
               n = trained.n
               d = trained.d
               h = (4 / (2 * d + 1))**(1/(d + 4)) * n **(-1/(d + 4)) 
               trained.data["parzen"]["hwindow"] = h
               trained.set_statistics("parzen", train_samples)
              

               
            #mle leave-one-out accuracy
            accuracy = get_mle_leave_one_out(train_samples)
            if accuracy > trained.data["mle"]["accuracy"]: 
               trained.data["mle"]["accuracy"] = accuracy
               trained.data["mle"]["test"] = test_samples
               trained.set_statistics("mle", train_samples)
               
   

            #knn leave-one-out accuracy
            accuracy, k = get_k_leave_one_out(train_samples)
            if accuracy > trained.data["knn"]["accuracy"]:
                trained.data["knn"]["k"] = k
                trained.data["knn"]["accuracy"] = accuracy   
                trained.data["knn"]["test"] = test_samples
                trained.data["knn"]["train"] = train_samples
             
            
            
       
        return trained
        
        
def classify(training_key, test_key, assignments=[]):
    print("\n", title_separation)
    print("processing raw data for:")
    print("[ test_key = ", test_key, "]")
    print("[ training_key = ", training_key, "]")
    print(title_separation, "\n")

    a = datetime.datetime.now()
    trained = train(training_key, test_key, assignments)
    b = datetime.datetime.now()
    print('training complete\n')
    print("took: ", (b - a).total_seconds(), " for ", trained.n, " ", trained.d, "d-vectors")
    print("class frequency table:\n", trained.class_frequency)
    print(title_separation)
    print("classifying ", len(trained.data["mle"]["test"]), " samples")
    print(title_separation)
    k = trained.data["knn"]["k"]
    run_classifier(trained.data["knn"]["test"], "K-Nearest Neighbor Classification [ k=" + str(k) + " ]",
                   get_knn_classification, (trained.data["knn"]["train"], k))
   
    #Silvermans optimal h
    
    
    h = trained.data["parzen"]["hwindow"]
    run_classifier(trained.data["parzen"]["test"], "Bayes Classification with Parzen Window Estimation [ h=" + str(h) + " ]",
                  get_parzen_window_classification, (trained,))
    
    run_classifier(trained.data["mle"]["test"], "Bayesian Classification with Maximum Likelihood Estimation",
                   get_max_likelihood_classification, (trained,))
    
    print("\n" + separation)
    print("classification complete.")
    print(separation + "\n")


def main():
    classify('iris_training.txt', 'iris_test.txt', [None,None,None])
    classify('wine_uci_train.txt', 'wine_uci_test.txt', ["l1","max","l2"])
    classify('zip_train_small.txt', 'zip_test_small.txt', ["max","max","l2"])
    
main()
