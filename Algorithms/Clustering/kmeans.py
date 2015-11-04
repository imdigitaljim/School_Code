import random
import math
import time

class cluster:      
    def __init__(self, point, clusterId, pointId=None):
        self.clusterId = clusterId
        self.center = point
        self.points = []
        self.points.append(pointId)

class clusterPoint:
    def __init__(self, point, clusterId, distance):
        self.point = point
        self.clusterId = clusterId
        self.distance = distance
        self.disAry = []
        
def lloyd(count, k, data):
    #get lloyd method start clusterings by index
    startClusters = getUniqueStarts(k, count)
    
    dimensions = len(data[0]) #get dimensions for clusterings
    kmean = None  #init k mean  
    lowKdata = []  #init to save the lowest set of clusterPoints
    for startPoint in startClusters:   #go through 100 or nCr < 100
        startList = [data[s] for s in startPoint]#get initial points           
        #this will be an array of k cluster objects and n clusterpoint objects
        clusterSet = []
        clusterData = []  
        cid = 0 #initial id of cluster [0, k-1]
        #initialize cluster sets and clusterdata arrays
        for point in data:
            #if it is an initial point from the unique start list,
            #init data having cluster and data, and init cluster center and id 
            if (point in startList):
                startList.remove(point)
                clusterSet.append(cluster(point, cid))
                clusterData.append(clusterPoint(point, cid, 0))
                cid += 1
            else:  #otherwise init the clusterpoint with the input data
                clusterData.append(clusterPoint(point, None, None))
        while (True):  #waiting on convergence
            changeMade = False #not converged
            for i in range(len(clusterData)): #iterate through data
                for clusterNode in clusterSet: #check against each cluster set
                    d = getDistance(clusterNode.center, clusterData[i].point) #get the distance to that cluster
                    if (clusterData[i].distance is None or clusterData[i].distance > d): #if its uninit or min
                        clusterData[i].distance = d #set new dist to center
                        clusterData[i].clusterId = clusterNode.clusterId #set new cluster id
                        changeMade = True # not converged
            if (not changeMade):
                break #convergence met
            else: #the state of the clusters have changed
                for i in range(len(clusterSet)): #iterate through all clusters
                    newCenter = [0] * dimensions #get empty centroid
                    count = 0 # count how many in that cluster for average
                    for elem in clusterData: #loop through all data
                        if elem.clusterId == clusterSet[i].clusterId: #that matches this cluster
                            count += 1 #add for local count
                            newCenter = [a+b for a,b in zip(newCenter, elem.point)] #add each dimension to the centroid
                    clusterSet[i].center = [x / count for x in newCenter] #average the centroid for the correct new center
        newK = computeKmean(clusterData) #calculate new Kmean
        if (kmean is None or newK < kmean): #if its smaller, set it
            kmean = newK  #save the value
            lowKdata = clusterData #save the clusterdata state for output
    print("A = [%s]" % ','.join(str(dat.clusterId) for dat in lowKdata))
    return lowKdata
    
def linkage(count, k, data):
    clusterSet = []
    clusterData = []
    for i in range(count):
        clusterSet.append(cluster(None, None, i)) #building n clusters
        clusterData.append(clusterPoint(data[i], i, 0)) #setting clusterPoint data
    for i in range(count): #calc the distance to each cluster
        for j in range(count):
                clusterData[i].disAry.append(getDistance(clusterData[i].point, clusterData[j].point)) #find the distance to every other point
    currentK = count #current k
    while (currentK > k): #while != k
        minClust = None
        minAB = None
        for i in range(len(clusterSet)):
            for j in range(len(clusterSet)):
                if (i != j):
                    for iPointId in clusterSet[i].points:
                        maxDist = None
                        for jPointId in clusterSet[j].points:
                            d = clusterData[iPointId].disAry[jPointId]
                            #d = getDistance(clusterData[iPointId].point, clusterData[jPointId].point)
                            if (maxDist is None or d > maxDist):
                                maxDist = d
                        if (minClust is None or maxDist < minClust):
                            minClust = maxDist
                            minAB = (i,j)
        clusterSet[minAB[0]].points += clusterSet[minAB[1]].points
        del clusterSet[minAB[1]]
        currentK -= 1
    for i in range(k):
        for pointId in clusterSet[i].points:
            clusterData[pointId].clusterId = i
    print("A = [%s]" % ','.join(str(dat.clusterId) for dat in clusterData))
    return clusterData

def getHamDistance(A, B, count):
    hamming = sum(c1.clusterId != c2.clusterId for c1, c2 in zip(A, B))
    print("The hamming distance is :" + str(hamming))


def computeKmean(points): 
    return sum([x.distance for x in points])

def getDistance(a, b):
    return sum([(x-y)**2 for x,y in zip(a,b)])

def getUniqueStarts(k, count):
    result = []
    runs = nChooseR(count, k)
    if (runs > 100):
        runs = 100      
    while(len(result) < runs):
        x = tuple(sorted(random.sample(range(count),k)))
        if(x not in result):
            result.append(x)
    return result
        
def nChooseR(n, r):
    f = math.factorial
    return f(n) / (f(r) * f(n-r))

while (True):
    name = input("What is the file name? [exit to stop]:")
    if (name.lower() == "exit"):
        exit()
    try: 
        lines = open(name).read().splitlines()
        count = int(lines[0])
        k = int(lines[1])
        data = []
        for line in lines[2:]:
            try:
                data.append([int(x.strip()) for x in line.strip("()").split(',')])
            except ValueError:
                data.append([float(x.strip()) for x in line.strip("()").split(',')])
        
        print("Lloyds Method")
        start = time.time() * 1000
        A = lloyd(count, k, data)
        end = time.time() * 1000
        print("Took: " + str(end - start))
        
        print("Complete Linkage")
        start = time.time() * 1000
        B = linkage(count, k, data)
        end = time.time() * 1000
        print("Took: " + str(end - start))
        getHamDistance(A,B, count)
    except OSError:
        print(name + ": cannot open/file does not exist.")
