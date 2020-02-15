/// Repeated Dijkstra
use petgraph::{
    dot::{Config, Dot},
    prelude::*,
};
use std::collections::HashSet;
use std::fs;

#[derive(Debug, Clone, Copy)]
enum Ornt {
    V,
    H,
}

impl Default for Ornt {
    fn default() -> Self {
        unimplemented!()
    }
}

#[derive(Debug, Default, Clone)]
struct Pict {
    ornt: Ornt,
    tags: HashSet<String>,
}

fn interest_rating(pict1: &Pict, pict2: &Pict) -> usize {
    use std::cmp::min;

    min(
        pict1.tags.difference(&pict2.tags).count(),
        min(
            pict2.tags.difference(&pict1.tags).count(),
            pict1.tags.intersection(&pict2.tags).count(),
        ),
    )
}

fn parse_input(path: &'static str) -> UnGraph<Pict, usize> {
    let raw = fs::read_to_string(path).unwrap();

    let mut result = Graph::new_undirected();

    raw.lines().skip(1).for_each(|line| {
        let words: Vec<_> = line.split_whitespace().collect();

        let new_node = Pict {
            ornt: if words[0] == "H" { Ornt::H } else { Ornt::V },
            tags: words.into_iter().skip(2).map(&str::to_owned).collect(),
        };
        let new_idx = result.add_node(new_node.clone());

        let new_edges: Vec<_> = result
            .node_weights_mut()
            .enumerate()
            .filter_map(|(old_i_idx, old_node)| {
                let old_idx = NodeIndex::new(old_i_idx);

                if old_idx == new_idx {
                    None
                } else {
                    Some((old_idx, new_idx, interest_rating(old_node, &new_node)))
                }
            })
            .collect();

        result.extend_with_edges(new_edges);
    });

    result
}

solve(input: UnGraph<Pict, usize>) {

}

fn main() {
    let picts = parse_input("res/input");

    println!("{:?}", Dot::with_config(&picts, &[]));
}
