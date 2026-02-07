package main

import (
	"fmt"
	"time"
)

func main() {
	work := make(chan int, 4)

	go func() {
		defer close(work)
		for {
			for i := range 4 {
				work <- i
			}
			time.Sleep(5 * time.Second)
		}
	}()

	for {
		select {
		case <-work:
			fmt.Println("Doing channel work")
		default:
			time.Sleep(2 * time.Second)
			fmt.Println("Continuing with non-preemptable work")
		}
	}

}
