package main

import (
	"fmt"
	"time"
)

func main() {
	doWork := func(
		done <-chan interface{},
		pulseInterval time.Duration,
	) (<-chan interface{}, <-chan time.Time) {
		heartbeats := make(chan interface{})
		results := make(chan time.Time)
		go func() {
			pulse := time.Tick(pulseInterval)
			work := time.Tick(2 * pulseInterval)

			sendPulse := func() {
				select {
				case heartbeats <- struct{}{}:
				default:
				}
			}

			sendWork := func(t time.Time) {
				for {
					select {
					case <-pulse:
						sendPulse()
					case results <- t:
						return
					}
				}
			}

			for i := 0; i < 2; i++ {
				select {
				case <-done:
					return
				case <-pulse:
					sendPulse()
				case t := <-work:
					sendWork(t)
				}
			}
		}()

		return heartbeats, results
	}

	done := make(chan interface{})
	time.AfterFunc(10*time.Second, func() { close(done) })

	interval := 1 * time.Second
	timeout := 2 * interval

	heartbeats, results := doWork(done, interval)

	for {
		select {
		case _, ok := <-heartbeats:
			if !ok {
				return
			}

			fmt.Println("pulse")
		case t, ok := <-results:
			if !ok {
				return
			}

			fmt.Printf("Work: %v\n", t)
		case <-time.After(timeout):
			fmt.Println("Worker goroutine is not healthy")
			return
		}
	}

}
