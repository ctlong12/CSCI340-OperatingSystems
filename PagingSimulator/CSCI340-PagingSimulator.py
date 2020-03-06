# CSCI 340
# Chandler Long
# Paging Simulator

import random



# Detemrine number of jobs

def main():
    timeQuantum = 1 
    jobQueue = createJobs(3, 0, 12, 100, 555)
    printJobs(jobQueue)
    scheduledJobQueue = roundRobinScheduler(jobQueue, timeQuantum)
    
    printJobs(scheduledJobQueue)


    





def roundRobinScheduler(queue, timeQuantum):
    scheduledQueue = []
    while(True):
        
        for job in queue:
            if job.finished == True:
                continue
            else:
                job.calculateBurst()
                scheduledQueue.append(job)
          
    return scheduledQueue



# Creates n number of jobs with a spesified min and max time
# Returns queue of Jobs
def createJobs(numJobs, minJobTime, maxJobTime, minMem, maxMem):
    jobQueue = []
    for i in range(numJobs):
        burstTime = random.randrange(minJobTime, maxJobTime,1)
        requiredMemory = random.randrange(minMem, maxMem,1)
        job = Job(i, burstTime, requiredMemory)
        jobQueue.append(job)
    return jobQueue


# Prints out the job prcesses and burst time in readable format
def printJobs(queue):
    for job in queue:
        print("Job", (job.processNum + 1))
        print("Process Number:", job.processNum, "Burst Time:", job.burstTime)
        print("Memory Required:", job.requiredMemory)
        print("-------------------------------------")


# Class Job that contains the process number and burst time
class Job:
    def __init__(self, processNum, burstTime, requiredMemory):
        self.finished = False
        self.processNum = processNum
        self.burstTime = burstTime
        self.requiredMemory = requiredMemory
    
    def calculateBurst(self):
        if self.burstTime <= 0:
            self.finished = True
        else:
            self.burstTime = self.burstTime - 1 # 1 is the Time Quantum
    

if __name__ == "__main__":
    main()
