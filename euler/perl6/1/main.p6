use v6;

# sum of all natural numbers that are multiples of 3 or 5 below limit
sub MAIN($limit) {
    my $sum = 0;
    for 0..$limit-1 {
        if $_ %% 3 or $_ %% 5 {
            $sum += $_;
        }
    }
    say $sum;
}
