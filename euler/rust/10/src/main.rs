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
    PrimeItr { last: 0 }
}

struct PrimeItr {
    last: u64,
}

impl Iterator for PrimeItr {
    type Item = u64;

    fn next(&mut self) -> Option<Self::Item> {
        Some({
            if self.last < 2 {
                self.last = 2;
            } else if self.last == 2 {
                self.last = 3;
            } else {
                self.last += if self.last % 2 == 0 { 1 } else { 2 };

                while !is_prime(self.last) {
                    self.last += 2;
                }
            }

            self.last
        })
    }
}

fn main() {
    let result: u64 = primes().take_while(|n| n < &2000000).sum();
    println!("{:?}", result);
}
