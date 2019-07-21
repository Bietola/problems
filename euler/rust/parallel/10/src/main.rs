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
    for i in (3..s).step_by(2) {
        if n % i == 0 {
            return false;
        }
    }

    true
}

fn prime_itr() -> PrimeItr{
    PrimeItr { current: 0 }
}

struct PrimeItr {
    current: usize,
}

fn main() {
    println!(
        "{:?}",
        is_prime(14)
    );
}
