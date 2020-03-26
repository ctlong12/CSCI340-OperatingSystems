#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Mar  3 22:45:06 2020

@author: swapnilsrivastava
"""

import random

def main(timeQuantum, totalMem , pageSize, ranSeed, noJobs, runTime, mem):
    print("Simulator parameters:\n Memory Size: " + str(totalMem) + "\n page size: " + str(pageSize) + "\n Random seed:" + str(ranSeed) + "\n Number of jobs: " + str(noJobs) + " \n Run time: " + str(runTime[0]) +  "-" + str(runTime[1]) + "\n Memory:"+ str(mem[0]) + "-" + str(mem[1]))
#jobs to be finished.
    jobQueue = createJobs(noJobs, runTime[0], runTime[1], mem[0], mem[1])
    printJobs(jobQueue)
#simulated computer memory
    pageFrames =["*"] * totalMem
#get the number of pages
    noPages = totalMem//pageSize
#list for output purpose
    finishedJobs = []
    
        
#set up the scheduled queue and page frames
    scheduledQueue = []
    count = 0
#set up physical page frames based on availibility
    while(count < len(jobQueue)):
        job = jobQueue[count]
        if(checkAvail(job, pageSize, pageFrames)):
            scheduledQueue.append(job)
            assignPage(job, pageSize, pageFrames)
            count = jobQueue.index(job)
            jobQueue.pop(count)
        else:
            count += 1

#run processes
    step = 0
    while((len(scheduledQueue)>0)):
#get the pending and scheduled jobs
        for i in range(len(jobQueue)):
            print(f"Pending JOB QUEUE: Job {jobQueue[i].processNum + 1}, ", end= " ")
        print("\nScheduled JOB QUEUE: ")
        for i in range(len(scheduledQueue)):
            print(f" Job{scheduledQueue[i].processNum + 1},", end= " ")
        print("\n")
        step += 1
        print("-----------------------------------")
#start the time steps
        print(f"Time step {step} \n")
        if(step==1):
            for i in range(len(scheduledQueue)):
                print(f"Job {scheduledQueue[i].processNum + 1} starting \n")
                scheduledQueue[i].startTime = step
#use RR scheduler to iterate through time steps
        scheduledQueue = roundRobinScheduler(scheduledQueue, timeQuantum)
#check if any jobs are finished
        for i in range(len(scheduledQueue)):
            if(scheduledQueue[i].burstTime<=0):
                
                print(f"Job {scheduledQueue[i].processNum + 1} finished at time step {step}")
                scheduledQueue[i].endTime = step
                pageFrames = emptyPage(scheduledQueue[i],pageSize,pageFrames)
                finishedJobs.append(scheduledQueue[i])
                scheduledQueue.pop(i)
                i -= 1
#get updated pending process list
        if(len(jobQueue)>0):
            print("\nPending JOB QUEUE: ")
            for i in range(len(jobQueue)):
                print(f"Job {jobQueue[i].processNum + 1}, ")
#check if any of the jobs can be fit into the physical page frame
        for j in range(len(jobQueue)):
            if(checkAvail(jobQueue[j], pageSize, pageFrames)):
                assignPage(jobQueue[j], pageSize, pageFrames)
                jobQueue[j].startTime = step
                scheduledQueue.append(jobQueue[j])
                print(f"Job {jobQueue[j].processNum + 1} starting \n")
                jobQueue.pop(j)
        pageTable(noPages, pageSize, pageFrames)
#get the process summary of the jobs
    print("\n Process summary: \n")
    print(f"Job #   Start   Finished \n")
    for i in range(len(finishedJobs)):
        print("{:5d} {:5d} {:5d}" .format((finishedJobs[i].processNum+1), finishedJobs[i].startTime, finishedJobs[i].endTime))
  
        
#method to print the physical page frame
def pageTable(noPages,pageSize,pageFrames):
    print("\n Page table \n")
    for i in range(noPages):
        print(f"Page{i} : ")
        for j in range(pageSize):
            print(f"{pageFrames[(i*pageSize)+j]}", end=" ")
        print("\n")

#method to assign pages to a job
def assignPage(job, pageSize, pageFrames):
    t = job.requiredMemory%pageSize
    if(t>0):
        reqPages = (job.requiredMemory//pageSize) + 1
    else:
        reqPages = job.requiredMemory//pageSize
    mem = job.requiredMemory
    count1 =0
    if(checkAvail(job,pageSize, pageFrames)):
        for i in range(1, reqPages+1):
            page = (freePage(pageFrames, pageSize)*pageSize)
            count = 0
            while(count<pageSize and count1<mem):
                pageFrames[page+count] = job.processNum+1
                count += 1
                count1 += 1
                
    else:
        print("no available pages")

#remove a job from the page frame
def emptyPage(job, pageSize, pageFrames):
    for i in range(0, len(pageFrames), pageSize):
        if(pageFrames[i] == (job.processNum+1)):
            t=0
            while(t<pageSize):
                pageFrames[i+t] = "*"
                t+=1
    return pageFrames

#check if there are available pages in the page frame
def checkAvail(job, pageSize, pageFrames):
    t = job.requiredMemory%pageSize
    if(t>0):
        reqPages = (job.requiredMemory//pageSize) + 1
    else:
        reqPages = job.requiredMemory//pageSize

    if(freePages(pageFrames, pageSize) >= reqPages):
        return True
    else:
        return False

#get the number of free pages         
def freePages(queue, pageSize):
    count = 0
    for i in range(0, len(queue), pageSize):
        if(queue[i] == "*"):
            count = count+1
    
    return count

#get the location of the first free page
def freePage(queue, pageSize):
    for i in range(0, len(queue), pageSize):
        if(queue[i] == "*"):
            return i//pageSize

#RR scheduler
def roundRobinScheduler(queue, timeQuantum):
    print(f"Job {queue[0].processNum + 1} Running \n")
    if(len(queue)==1):
                queue[0].burstTime = queue[0].burstTime-timeQuantum
    if(len(queue) != 0):
        temp = queue[len(queue)-1]
        for i in range(len(queue)-1):
            

            if(len(queue)==2):
                queue[0].burstTime = queue[0].burstTime-timeQuantum
                queue[len(queue)-1]= queue[0]
                queue[0]=temp
            elif(i==0):
                queue[0].burstTime = queue[0].burstTime-timeQuantum
                queue[len(queue)-1]= queue[0]
                queue[0]=queue[1]
            else:
                if(i == len(queue)-2):
                    queue[i] = temp
                else:
                    queue[i]=queue[i+1]
    else:
        print("job done")
    return queue

#create a list of jobs to be performed
def createJobs(numJobs, minJobTime, maxJobTime, minMem, maxMem):
    jobQueue = []
    for i in range(numJobs):
        burstTime = random.randrange(minJobTime, maxJobTime,1)
        requiredMemory = random.randrange(minMem, maxMem,1)
        job = Job(i, burstTime, requiredMemory)
        jobQueue.append(job)
    return jobQueue

#print job information
def printJobs(queue):
    print("\n Jobs in queue: \n")
    for job in queue:
        print("Job", (job.processNum + 1))
        print("Process Number:", job.processNum, "Burst Time:", job.burstTime)
        print("Memory Required:", job.requiredMemory)
        print("-------------------------------------")

#class that handles the job structure      
class Job:
    def __init__(self, processNum, burstTime, requiredMemory):
        self.finished = False
        self.processNum = processNum
        self.burstTime = burstTime
        self.requiredMemory = requiredMemory
        self.endTime = 0
        self.startTime = 0
    
    def calculateBurst(self):
        if self.burstTime <= 0:
            self.finished = True
        else:
            self.burstTime = self.burstTime - 1 # 1 is the Time Quantum
            
if __name__ == "__main__":
    timeQuantum = 1 
    totalMem = 20
    pageSize = 5
    ranSeed = 3
    noJobs = 3
    runTime = (3,7)
    mem = (3, 12)
    main(timeQuantum, totalMem , pageSize, ranSeed, noJobs, runTime, mem)