const helloWorld = `
func main() {
    print("Hello, World!");
}
`;

const fibRecursive = `
func main() {
    int n = 5;

    int result = fib(n);
    print(result);
}

func fib(int n) -> int {

    if(n is 0 or n is 1) {
        return n;
    }

    return fib(n - 1) + fib(n - 2);
}
`;

const fibSequential = `
func main() {
    int n = 5;

    int result = fib(n);
    print(result);
}

func fib(int n) -> int {
    int first = 0;
    int second = 1;
    
    int i = 0;
    while(i < n) {
        int sum = first + second;
        first = second;
        second = sum;
        
        i = i + 1;
    }

    return first;
}
`;

export const getProgText = (progName) => {
  return (
    {
      'Hello, World!': helloWorld,
      'Fibonacci (Iterative)': fibSequential,
      'Fibonacci (Recursive)': fibRecursive,
    }[progName] ?? helloWorld
  );
};
