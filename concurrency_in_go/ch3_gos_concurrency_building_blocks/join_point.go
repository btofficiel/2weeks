package main

import (
	"fmt"
	"sync"
)

func main() {
	out := "Should not print"
	var wg sync.WaitGroup
	sayHello := func() {
		defer wg.Done()
		out = "Hello from the goroutine"
	}

	wg.Add(1)
	go sayHello()
	wg.Wait()
	fmt.Println(out)
}
