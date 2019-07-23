extern crate itertools;

use itertools::Itertools;

fn is_prime(n: u64) -> bool {
    if n < 3 {
        return true;
    }

    if n % 2 == 0 {
        return false;
    }

    let s = (n as f64).sqrt() as u64;
    for i in (3..=s).step_by(2) {
        if n % i == 0 {
            return false;
        }
    }

    true
}

fn primes() -> PrimeItr {
    PrimeItr::new()
}

struct PrimeItr {
    last: u64,
    cur_delta: u64,
    next_delta: u64,
}

impl PrimeItr {
    fn new() -> Self {
        Self { last: 0, cur_delta: 2, next_delta: 4}
    }

    fn incr(&mut self) {
        use std::mem::swap;

        self.last += self.cur_delta;
        swap(&mut self.cur_delta, &mut self.next_delta);
    }
}

impl Iterator for PrimeItr {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        Some({
            if self.last < 2 {
                self.last = 2;
            } else if self.last == 2 {
                self.last = 3;
            } else if self.last == 3 {
                self.last = 5;
            } else {
                loop {
                    self.incr();
                    if is_prime(self.last) { break; }
                }
            }

            self.last
        })
    }
}

fn main() {
    let result: u64 = primes().take_while(|n| n < &2_000_000).sum();
    println!("{:?}", result);
}
