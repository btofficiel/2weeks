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

	or := func(channels ...<-chan interface{}) <-chan interface{} {
		var orFunc func(chs ...<-chan interface{}) <-chan interface{}
		orFunc = func(chs ...<-chan interface{}) <-chan interface{} {
			switch len(chs) {
			case 0:
				return nil
			case 1:
				return chs[0]
			}

			orDone := make(chan interface{})
			go func() {
				defer close(orDone)
				switch len(chs) {
				case 2:
					select {
					case <-chs[0]:
					case <-chs[1]:
					}
				default:
					select {
					case <-chs[0]:
					case <-chs[1]:
					case <-chs[2]:
					case <-orFunc(append(chs[3:], orDone)...):
					}
				}
			}()

			return orDone

		}

		return orFunc(channels...)
	}
	// Stream to be used as work done signal
	doneA := make(chan interface{})
	doneB := make(chan interface{})
	doneC := make(chan interface{})

	combinedOr := or(doneA, doneB, doneC)

	randStream := newRandStream(combinedOr)
	for i := 0; i < 3; i++ {
		randInt, _ := <-randStream
		fmt.Printf("Random Int: %d\n", randInt)
	}
	close(doneC)
	// Simulating background work
	time.Sleep(1 * time.Second)
}
