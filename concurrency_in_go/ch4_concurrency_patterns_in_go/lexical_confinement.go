package main

import "fmt"

func main() {
	// Restricitng ownership of the channel to this function and returning a read-only channel
	chanOwner := func() <-chan int {
		results := make(chan int, 4)
		go func() {
			defer close(results)
			for i := 0; i <= 5; i++ {
				results <- i
			}
		}()
		return results
	}

	// Consumer exposes a read-only channel within its scope
	consumer := func(results <-chan int) {
		for i := range results {
			fmt.Printf("Received: %d\n", i)
		}
		fmt.Println("Done receiving")
	}

	//Store read-only channel in results
	results := chanOwner()
	consumer(results)
}
