package test_test

import (
	"fmt"
	"testing"
)

func Test_ch(t *testing.T) {
	t.Log("test", "test")

	var kk int = 10000
	fmt.Println(kk)

	var (
		a int = 1
		b int = 2
	)

	aa := 100
	for i := 0; i < 100; i++ {
		fmt.Println("i is ", i)
	}

	fmt.Println(aa)

	t.Log(a, b)
}

func hel() {
	fmt.Println("hel")
}
