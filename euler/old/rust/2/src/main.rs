use std::env;

#[derive(Debug)]
struct FibCounter {
    a: u64,
    b: u64,
}

impl FibCounter {
    fn new() -> Self {
        FibCounter { a: 0, b: 1 }
    }
}

impl Iterator for FibCounter {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        let tmp = self.a;
        self.a = self.b;
        self.b = self.a + tmp;

        Some(self.a)
    }
}

fn main() {
    let args: Vec<_> = env::args().collect();

    let limit: u64 = args[1].parse().unwrap();
    
    let result: u64 =  FibCounter::new()
             .take_while(|n| n <= &limit)
             .filter(|n| n % 2 == 0)
             .sum();

    println!("{}", result);
}
