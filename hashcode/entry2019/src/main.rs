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
    unimplemented!()
}

fn parse_input(path: &'static str) -> UnGraph<Pict, usize> {
    let raw = fs::read_to_string(path).unwrap();

    let mut result = Graph::new_undirected();

    raw.lines().skip(1).for_each(|line| {
        let words: Vec<_> = line.split_whitespace().collect();

        let new_index = result.add_node(Pict {
            ornt: if words[0] == "H" { Ornt::H } else { Ornt::V },
            tags: words.into_iter().skip(2).map(&str::to_owned).collect(),
        });

        result.extend_with_edges(result.node_indices().filter_map(|old_index| {
            if old_index == new_index {
                None
            } else {
                Some((
                    old_index,
                    new_index,
                    interest_rating(
                        result.node_weight(old_index).unwrap(),
                        result.node_weight(new_index).unwrap(),
                    )
                ))
            }
        }));
    });

    result
}

fn main() {
    let picts = parse_input("res/input");

    println!("{:?}", Dot::with_config(&picts, &[]));
}
