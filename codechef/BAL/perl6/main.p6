# N -> number of problem instances
# x -> potato weight
# y -> tomato weight
# n -> potato number available
# m -> tomato number available
# required: x*n == y*m

sub MAIN() {
    constant N = get();
    for 1..N {
        my ($x, $y, $n, $m) = get().split(" ").map(*.Int);
        say solve($x, $y, $n, $m) ??  "YES" !! "NO";
    }
}

sub solve($x, $y, $n, $m) {
    my $F = $x gcd $y;

    $m >= $x div $F and $n >= $y div $F;
}
