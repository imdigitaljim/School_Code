import numpy as np
import matplotlib.pyplot as plt
import math
from itertools import cycle
from sklearn import svm, datasets
from sklearn.metrics import roc_curve, auc
from scipy import interp
from scipy.stats import norm
from scipy.interpolate import interp1d
import sys

def graph(formula, min_x, max_x):  
	x = np.linspace(min_x, max_x, 100) 
	y = formula(x)
	plt.plot(x, y)  

#graph(lambda x: (1 / ( 2 * np.sqrt(2 * np.pi)))*(np.exp(-((x + 1)**2)/2)), -4, 4)
#graph(lambda x: (1 / ( 2 * np.sqrt(.5 * np.pi)))*(np.exp(-2 *((x - 1)**2))), -4, 4)
#plt.show()

p_false = []
p_hit = []
x_vals = []
x_val = -4
while(x_val < 4.0):
	p_hit.append([1 - norm.cdf(x_val,-1,1)])
	p_false.append([1 - norm.cdf(x_val, 1, .25)])
	x_vals.append([x_val])
	x_val+=.1

print(auc(p_hit, p_false))

plt.plot(p_hit, p_false);
plt.title('Receiver Operating Characteristic')
plt.legend(loc='lower right')
plt.xlim([0,1])
plt.ylim([0,1.1])
plt.ylabel('Hit')
plt.xlabel('False Alarm')
plt.show()
sys.exit()
