import numpy as np
import math
import copy
from numpy import linalg as LA

def main():
	dataset = get_dataset("./data.txt")
	totalpredictions = len(dataset) * len(dataset[0])
	correctprediction = 0
	corrpred2 = 0
	class_means = get_n_dimension_mean(dataset)
	np_means = [np.array(x) for x in class_means] 
	
	print("--------------------------------------------")
	for i in range(totalpredictions):
		dataset_loo = copy.deepcopy(dataset)
		currentclass = int(i / len(dataset[0]))
		currentsample = i % len(dataset[0])
		test_set = dataset_loo[currentclass].pop(currentsample)
		mod_class_means = get_n_dimension_mean(dataset_loo)
		mod_np_means = [np.array(x) for x in mod_class_means]
		output = "testing..." + str(test_set) + " ?= class " + str(currentclass)
		prediction = predict_class(test_set, mod_np_means)
		prediction2 = predict_class(test_set,np_means)
		if (currentclass is prediction2):
			corrpred2 += 1
		if (currentclass is prediction):
			correctprediction += 1
			print(output,"...true")
		else:
			print(output,"...false")
		print("=-=-=-=-=-=-=-=-=-=-=-=-=-")
	print("correctly predicted..", correctprediction)
	print("loo accuracy is", 100 * (correctprediction / totalpredictions))
	print("included accuracy is", 100 * (corrpred2 / totalpredictions))
	
	#prompt = "Enter a " + str(len(class_means[0])) + "d instance to be classified as single line csv: "
	#while True:
	#	user_query = input(prompt)
	#	user_query = [float(x) for x in user_query.split(',')]
	#	print_closest_mean(user_query, np_means)
	#	break
	
#query = n-d array
#np_means = numpy mean n-d array 
def predict_class(query, np_means):
	query = np.array(query)
	min_dist = math.inf
	closest = -1
	for i in range(0, len(np_means)):
		dist = LA.norm(np_means[i] - query)
		if (dist < min_dist):
			min_dist = dist
			closest = i
	return closest 

def get_dataset(name):
	dataset = []
	f = open(name, "r")
	while True:
		data_class = []
		label = f.readline()
		if (label == ''): break
		while True:
			line = f.readline()
			if (line == '\n' or line == ''): break  
			data_class += [[float(j) for j in line[:-2].split(' ')]]
		dataset += [data_class]
	return dataset

#expecting [[[ax1,ay1,az1,...][ax2,ay2,az2,...]],[[bx1,by1,bz1,...],...],...]
#[class[sample[feature]]]
def get_n_dimension_mean(dataset):
	mean = []
	if dataset is None: return []
	for dataclass in dataset:
		if dataclass[0] is None: return []
		sum = [0] * len(dataclass[0])
		for sample in dataclass: # 1 - 10
			for j in range(len(sample)): # 1 - 3
				sum[j] += sample[j]
		mean += [[x/len(dataclass) for x in sum]]
	return mean
	
if __name__ == "__main__":
    main()
