use criterion::{criterion_group, criterion_main, black_box, Criterion};

use all::*;

fn bench(c: &mut Criterion) {
    let mut group = c.benchmark_group("All");

    group.bench_function("no_idx",  |b| b.iter(|| black_box(no_idx::solve())));
    group.bench_function("no_dups", |b| b.iter(|| black_box(no_dups::solve())));
    group.bench_function("cyclic", |b| b.iter(|| black_box(cyclic::solve())));

    group.finish();
}

criterion_group!(benches, bench);
criterion_main!(benches);
