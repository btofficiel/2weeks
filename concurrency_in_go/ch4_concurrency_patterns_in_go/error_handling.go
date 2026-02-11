package main

import (
	"fmt"
	"net/http"
)

func main() {
	type Result struct {
		Error    error
		Response *http.Response
	}

	checkStatus := func(done <-chan interface{}, urls ...string) <-chan Result {
		results := make(chan Result)
		go func() {
			defer close(results)
			for _, url := range urls {
				resp, err := http.Get(url)
				res := Result{Error: err, Response: resp}
				select {
				case <-done:
					return
				case results <- res:
				}
			}
		}()
		return results
	}
	done := make(chan interface{})
	defer close(done)

	urls := []string{"https://google.com", "https://cloudflare.com", "http://badhost"}
	for result := range checkStatus(done, urls...) {
		if result.Error != nil {
			fmt.Printf("Error: %v\n", result.Error)
			continue
		}

		fmt.Printf("Response: %v\n", result.Response)
	}

}
