package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	//Channel owner func
	newRandStream := func(done <-chan interface{}) <-chan int {
		randStream := make(chan int)
		go func() {
			defer fmt.Println("newRandStream has exited.")
			defer close(randStream)
			for {
				select {
				case randStream <- rand.Int():
				case <-done:
					return
				}
			}
		}()

		return randStream
	}

	// Stream to be used as work done signal
	done := make(chan interface{})

	randStream := newRandStream(done)
	for i := 0; i < 3; i++ {
		randInt, _ := <-randStream
		fmt.Printf("Random Int: %d\n", randInt)
	}
	close(done)
	// Simulating background work
	time.Sleep(1 * time.Second)

}
