package main

import "fmt"

func main() {
	// Returning channel implicitly converted into a read-only channel
	chanOwner := func() <-chan int {
		// Channel owner instantiating channel
		resultStream := make(chan int, 5)
		go func() {
			// Channel owner closing channel at last
			defer close(resultStream)
			for i := 0; i <= 5; i++ {
				resultStream <- i
			}
		}()
		return resultStream
	}

	resultStream := chanOwner()
	for i := range resultStream {
		fmt.Printf("Received: %d\n", i)
	}

	fmt.Println("Done receiving")

}
