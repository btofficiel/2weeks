package main

import "fmt"

func main() {
	c1 := make(chan interface{})
	close(c1)
	c2 := make(chan interface{})
	close(c2)

	var c1Count, c2Count int

	for i := 0; i < 1000; i++ {
		//We keep reading default nil value from the closed channels
		// Selection happens at random
		select {
		case <-c1:
			c1Count++
		case <-c2:
			c2Count++
		}
	}

	fmt.Printf("C1 count: %d\n", c1Count)
	fmt.Printf("C2 count: %d\n", c2Count)

}
