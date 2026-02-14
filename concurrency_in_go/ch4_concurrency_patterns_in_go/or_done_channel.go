package main

import "fmt"

func orDone[T any](done <-chan interface{}, c <-chan T) <-chan T {
	valStream := make(chan T)
	go func() {
		defer close(valStream)
		for {
			select {
			case <-done:
				return
			case v, ok := <-c:
				if !ok {
					return
				}
				select {
				case <-done:
					return
				case valStream <- v:
				}

			}
		}
	}()

	return valStream
}

func main() {
	sampleStream := make(chan int, 10)

	for i := range 10 {
		sampleStream <- i
	}

	close(sampleStream)

	done := make(chan interface{})
	defer close(done)

	for i := range orDone(done, sampleStream) {
		fmt.Println(i)
	}
}
