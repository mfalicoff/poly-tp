import csv 
import numpy as np 
from sklearn.preprocessing import StandardScaler 
from sklearn.ensemble import RandomForestClassifier
 
 
with open('train.csv', 'r',newline='\n') as f: 
    wines = list(csv.reader(f, delimiter=',')) 
    DATA_training = np.array(wines) 
    Results= DATA_training[1:,-1] 
    DATA_training = DATA_training[1:,2:-1] 
 
 
l =Results.shape[0] 
for i in range(0,l): 
    if Results[i] == 'phishing': 
        Results[i] = 1 
    else: 
        Results[i] = 0 
Results = np.asarray(Results, dtype=float) 
 
 
 
with open('test.csv', 'r',newline='\n') as f: 
    wines = list(csv.reader(f, delimiter=',')) 
    DATA_test = np.array(wines) 
    DATA_test = DATA_test[1:,2:] 
 
 
 
scaler = StandardScaler() 
scaler.fit(DATA_training) 
DATA_training = scaler.transform(DATA_training) 
DATA_test = scaler.transform(DATA_test) 
 
clf = RandomForestClassifier()
 
clf.fit(DATA_training, Results) 
 
Test_Solution = clf.predict(DATA_test) 
 
 
Submission = np.empty((DATA_test.shape[0],2),dtype='object') 
Submission[:,0]=np.array(wines)[1:,1] 
lr =Test_Solution.shape[0] 
for i in range(0,lr): 
    if Test_Solution[i] == 1: 
        Submission[i,1] = 'phishing' 
    else: 
        Submission[i,1] = 'legitimate' 
Submission = np.insert(Submission, 0, ['url','status'], axis=0) 
 
with open('submission.csv', 'w', newline='') as file: 
     writer = csv.writer(file) 
     writer.writerows(Submission)