#![feature(iter_next_chunk)]

use std::fs;
use std::collections::{HashSet, VecDeque};

cat assets/challenge_input.txt | nl | grep -E '^\s+\b118\b' -B 100 | grep -E '\b1\b'

fn main() {
    let inp = fs::read_to_string("assets/challenge_input.txt").unwrap();
    let inp = &inp[..inp.len()-1];

    let mut inp = inp
        .split("\n")
        .map(|line| {
            // println!("{}", line);
            let n: i32 = line.parse().unwrap();
            n
        });

    let mut win = VecDeque::from(inp.next_chunk::<100>().unwrap());
    let mut set: HashSet<_> = win.iter().map(|e| *e).collect();

    let ok = inp.find(|&sum| {
        let crash = win.iter()
            // .map(|&lh| { println!("lh: {}", lh); lh })
            .find(|&lh| set.contains(&(sum - lh)));

        if crash.is_some() {
            set.remove(
                &win.pop_front().unwrap()
            );
            win.push_back(sum);
            set.insert(sum);
            false
        } else {
            true
        }
    });

    println!("{:#?}", ok);
}
