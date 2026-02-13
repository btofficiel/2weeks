package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

func main() {
	// Fake orders to be processed
	var orders [16]int
	for i := range 16 {
		orders[i] = i + 1
	}

	// Process orders
	fmt.Println("Adding orders")
	orderCh := make(chan int, 16)
	for _, order := range orders {
		orderCh <- order
	}

	close(orderCh)
	fmt.Println("Orders added")

	worker := func(
		done <-chan interface{},
		orderCounter <-chan int,
		workerId int,
	) <-chan int {
		plate := make(chan int)
		go func() {
			defer close(plate)
			for n := range orderCounter {
				fmt.Printf("Worked ID: %d working on order number: %d\n", workerId, n)
				select {
				case <-done:
					return
				case plate <- n:
					time.Sleep(1 * time.Second)
				}
			}
		}()
		return plate
	}

	servingStaff := func(done <-chan interface{}, workers ...<-chan int) <-chan int {
		orderCompletedStream := make(chan int)
		var wg sync.WaitGroup

		completeOrder := func(c <-chan int) {
			defer wg.Done()

			for i := range c {
				select {
				case <-done:
					return
				case orderCompletedStream <- i:
				}
			}
		}

		wg.Add(len(workers))

		for _, c := range workers {
			go completeOrder(c)
		}

		go func() {
			wg.Wait()
			close(orderCompletedStream)
		}()

		return orderCompletedStream
	}

	done := make(chan interface{})
	defer close(done)

	numWorkers := runtime.NumCPU()
	workerGroup := make([]<-chan int, numWorkers)

	fmt.Println("Workers have started processing orders")
	for wrkrId := range workerGroup {
		workerGroup[wrkrId] = worker(done, orderCh, wrkrId)
	}

	for completedOrder := range servingStaff(done, workerGroup...) {
		fmt.Printf("Order number: %d has been completed\n", completedOrder)
	}

}
