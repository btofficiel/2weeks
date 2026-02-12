package main

import "fmt"

func main() {
	generator := func(done <-chan interface{}, numbers ...int) <-chan int {
		intStream := make(chan int)
		go func() {
			defer close(intStream)
			for _, n := range numbers {
				select {
				case <-done:
					return
				case intStream <- n:
				}
			}
		}()
		return intStream
	}

	multiply := func(done <-chan interface{}, intStream <-chan int, multiplier int) <-chan int {
		multiplierStream := make(chan int)
		go func() {
			defer close(multiplierStream)
			for n := range intStream {
				select {
				case <-done:
					return
				case multiplierStream <- (n * multiplier):
				}
			}
		}()
		return multiplierStream
	}

	add := func(done <-chan interface{}, intStream <-chan int, additive int) <-chan int {
		adderStream := make(chan int)
		go func() {
			defer close(adderStream)
			for n := range intStream {
				select {
				case <-done:
					return
				case adderStream <- (n + additive):
				}
			}
		}()
		return adderStream
	}

	done := make(chan interface{})
	defer close(done)

	intStream := generator(done, 1, 2, 3, 4)
	pipeline := multiply(done, add(done, multiply(done, intStream, 2), 1), 2)

	for n := range pipeline {
		fmt.Println(n)
	}
}
