#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar  3 22:45:06 2020

@author: swapnilsrivastava
"""

import random

def main():
    timeQuantum = 1 
    jobQueue = createJobs(3, 0, 12, 100, 555)
    printJobs(jobQueue)
    scheduledJobQueue = roundRobinScheduler(jobQueue, timeQuantum)#0rder of jobs: 2,3,1
    printJobs(scheduledJobQueue)
    roundRobinScheduler(jobQueue, timeQuantum)#0rder of jobs: 3,1,2
    printJobs(scheduledJobQueue)l
    roundRobinScheduler(jobQueue, timeQuantum)#0rder of jobs: 1,2,3
    printJobs(scheduledJobQueue)

def roundRobinScheduler(queue, timeQuantum):
    if(len(queue) != 0):
        temp = queue[len(queue)-1]
        for i in range(len(queue)-1):
            if(i==0):
                temp = queue[len(queue)-1]
                queue[len(queue)-1]= queue[0]
                queue[0]=queue[1]
                queue[0].burstTime = queue[0].burstTime-timeQuantum
            else:
                if(i == len(queue)-2):
                    queue[i] = temp
                else:
                    queue[i]=queue[i+1]
    else:
        print("job done")

    return queue

def createJobs(numJobs, minJobTime, maxJobTime, minMem, maxMem):
    jobQueue = []
    for i in range(numJobs):
        burstTime = random.randrange(minJobTime, maxJobTime,1)
        requiredMemory = random.randrange(minMem, maxMem,1)
        job = Job(i, burstTime, requiredMemory)
        jobQueue.append(job)
    return jobQueue

def printJobs(queue):
    for job in queue:
        print("Job", (job.processNum + 1))
        print("Process Number:", job.processNum, "Burst Time:", job.burstTime)
        print("Memory Required:", job.requiredMemory)
        print("-------------------------------------")
        
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