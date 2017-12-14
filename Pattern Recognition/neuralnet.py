import numpy as np
import random as r
np.set_printoptions(precision=3, threshold=np.nan, suppress=True)

def fnet_derivative(x):
    return 1.0 - x**2

def activate_transfer(weights, inputs):
    return np.tanh(np.dot(weights, inputs))

class NeuralNet:
    #+1 are for bias
    def __init__(self, layout=[3+1,3+1,1]):
        self.weights = [np.array([[r.uniform(-.25, .25) for i in range(layout[0])] for j in range(layout[1])]),
                        np.array([[r.uniform(-.25, .25)] for i in range(layout[1])])]

    def train(self, feature_space, solution, error_target=.0001, epoch_max=50000, learn_rate=.5):
        #append 1's to the feature space for the constant bias
        bias_constant = [np.ones(len(feature_space))]
        feature_space = np.insert(feature_space, 0, bias_constant, axis=1)
        #prevent infinite loop
        for epoch in range(epoch_max):
            seed = r.randint(0, len(feature_space) - 1)
            layers = self.feedforward(feature_space[seed])
            #conditional stop condition
            if self.compute_error(feature_space, solution) <= error_target:
                print("completed on epoch:", epoch)
                break
            delta = (solution[seed] - layers[-1]) * fnet_derivative(layers[-1])
            sensitivity = self.compute_sensitivity(delta, reversed(layers[1:-1]))
            self.backpropagate(layers, sensitivity, learn_rate)

    def compute_sensitivity(self, error, layers):
        result = [error]
        #starting from the end towards the beginning
        for w, layer in zip(reversed(self.weights), layers):
            result += [np.dot(result[-1], w.T) * fnet_derivative(layer)]
        return result[::-1]

    def compute_error(self, feature_space, solution):
        error = 0
        for X, T in zip(feature_space, solution):
            Z = self.feedforward(X)[-1][0]
            error += .5 * (T - Z)**2
        return error

    def backpropagate(self, layers, sensitivity, learn_rate):
        for i, (inputs, delta) in enumerate(zip(layers,sensitivity)):
            inputs = np.array([inputs]).T
            delta = np.array([delta])
            self.weights[i] += learn_rate * np.dot(inputs, delta)

    def feedforward(self, pattern):
        results = [pattern]
        for inputs, weight in zip(results, self.weights):
            results += [activate_transfer(inputs, weight)]
        return results

    def classify(self, x):
        result = np.insert(x, 0, 1)
        for w in self.weights:
            result = activate_transfer(result, w)
        return result

def main():
    network331_wbias = NeuralNet()
    feature_space = np.array([[-1,-1,-1], [-1,-1,1], [-1,1,-1], [-1,1,1],
    [1,-1,-1], [1,-1,1], [1,1,-1], [1,1,1]])
    solution = np.array([ 1, -1, -1, 1, -1, 1, 1, -1])
    network331_wbias.train(feature_space, solution)
    print(network331_wbias.weights)
    for features, parity in zip(feature_space,solution):
        result = network331_wbias.classify(features)[0]
        result2 = 1 if result >= 0 else -1
        print("for:", np.array(features))
        summary = "CORRECT!" if parity == result2 else "\nMISSED CLASSIFICATION"
        print("solution=", parity, " ?= guess=", result, summary)
        print("----------------------------------------")

main()
