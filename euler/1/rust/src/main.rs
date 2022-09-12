fn mults(n: u32, lim: u32) -> u32 {
    (n..).filter(|x| x % &n == 0).take_while(|x| x < &lim).sum()
}

fn main() {
    println!("{}", mults(5, 1000) + mults(3, 1000) - mults(15, 1000));
}