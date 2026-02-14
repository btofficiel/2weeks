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

func tee[T any](done <-chan interface{}, c <-chan T) (_, _ <-chan T) {
	out1 := make(chan T)
	out2 := make(chan T)
	go func() {
		defer close(out1)
		defer close(out2)
		for v := range orDone(done, c) {
			for i := 0; i < 2; i++ {
				var out1, out2 = out1, out2
				select {
				case <-done:
					return
				case out1 <- v:
					out1 = nil
				case out2 <- v:
					out2 = nil
				}
			}
		}
	}()
	return out1, out2
}

func main() {
	sampleStream := make(chan int, 10)

	for i := range 10 {
		sampleStream <- i
	}

	close(sampleStream)

	done := make(chan interface{})
	defer close(done)

	out1, out2 := tee(done, sampleStream)

	for v := range out1 {
		fmt.Printf("Writing to a fakeDB: %v, Logging: %v\n", v, <-out2)
	}

}
