package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

func main() {
	var numCalcsCreated atomic.Int64
	pool := &sync.Pool{
		New: func() interface{} {
			numCalcsCreated.Add(1)
			mem := make([]byte, 1024)
			return &mem
		},
	}

	pool.Put(pool.New())
	pool.Put(pool.New())
	pool.Put(pool.New())
	pool.Put(pool.New())

	const numWorkers = 1024 * 1024
	var wg sync.WaitGroup
	wg.Add(numWorkers)

	for i := numWorkers; i > 0; i-- {
		go func() {
			defer wg.Done()

			mem := pool.Get().(*[]byte)
			defer pool.Put(mem)
		}()
	}

	wg.Wait()
	fmt.Printf("%d calculators were created", numCalcsCreated.Load())
}
