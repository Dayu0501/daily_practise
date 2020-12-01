package main

import "log"

func main() {
	defer func() {
		if err := recover(); err != nil {
			log.Printf("recover: %v", err)
		}
	}()

	/* 以并发的方式异步调用匿名函数 */
	go func() {
		log.Printf("test annoyname func")
	}()

	panic("panic learn!")
}
