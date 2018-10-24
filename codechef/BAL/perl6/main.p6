# N -> number of problem instances
# x -> potato weight
# y -> tomato weight
# n -> potato number available
# m -> tomato number available
# required: x*n == y*m

sub MAIN() {
    constant N = get();
    for 1..N {
        my ($x, $y, $n, $m) = get().split(" ");
        solve($x, $y, $n, $m);
    }
}

sub solve($x, $y, $n, $m) {
    for 1..$n {
        for 1..$m {
            if $x * $n == $y * $m {
                say "YES";
                return;
            }
        }
    }
    say "NO";
    return 0;
}
