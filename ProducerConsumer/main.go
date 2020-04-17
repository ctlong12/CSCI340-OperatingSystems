package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
	"sync"
)

// Define the number of consumers
const consumerCount int = 3 //consumerCount := os.Args[1]

// Define global variables
var messages []string
var wordCount int
var wg sync.WaitGroup

func producer(jobs chan<- string) {

	// Produce items to the buffer/channel
	for _, line := range messages {
		fmt.Printf("\nProduced ->: %v\n", line)
		jobs <- line
	}
	close(jobs)
}

func consumer(worker int, jobs <-chan string, done chan<- bool) {
	// Indicate when goroutine is finished
	defer wg.Done()
	for line := range jobs {
		fmt.Printf("\n%v -> Consumed by Worker %v.\n", line, worker)
		line := strings.Fields(line)
		// Get the number of words
		for _, word := range line {
			wordCount = wordCount + 1
			println(word)
		}
	}

	done <- true

}

func main() {

	// Read in text file
	readFile, err := os.Open("text.txt")

	if err != nil {
		log.Fatalf("failed to open file: %s", err)
	}

	fileScanner := bufio.NewScanner(readFile)
	fileScanner.Split(bufio.ScanLines)
	for fileScanner.Scan() {
		messages = append(messages, fileScanner.Text())
	}
	readFile.Close()

	// Start up channels
	jobs := make(chan string)
	done := make(chan bool)

	// Start up producer go routine
	go producer(jobs)
	// Start up n number of consumer routines
	for i := 1; i <= consumerCount; i++ {
		// Add wait for consumer
		wg.Add(1)
		go consumer(i, jobs, done)
	}
	// Wait for processes to finsh and print word count
	wg.Wait()
	println("Wordccount: ", wordCount)
	<-done

}
