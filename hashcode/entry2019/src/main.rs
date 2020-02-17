/// Repeated Dijkstra
use petgraph::{
    dot::{Config, Dot},
    prelude::*,
};
use std::collections::HashSet;
use std::fs;

type Tags = HashSet<String>;

#[derive(Debug, Clone, Copy, PartialEq)]
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
    id: usize,
    ornt: Ornt,
    tags: HashSet<String>,
}

#[derive(Clone, Debug)]
enum Slide {
    O1(Pict),
    V2(Pict, Pict),
}
impl Default for Slide {
    fn default() -> Self {
        unimplemented!()
    }
}
impl Slide {
    fn tags(&self) -> Tags {
        // TODO: cache union and return &Tags
        match self {
            Slide::O1(p) => p.tags.clone(),
            Slide::V2(p1, p2) => p1.tags.union(&p2.tags).map(String::clone).collect(),
        }
    }
}

fn interest_rating(slide1: &Slide, slide2: &Slide) -> usize {
    use std::cmp::min;

    min(
        slide1.tags().difference(&slide2.tags()).count(),
        min(
            slide2.tags().difference(&slide1.tags()).count(),
            slide1.tags().intersection(&slide2.tags()).count(),
        ),
    )
}

fn add_node_and_complete<N, E, F>(graph: &mut UnGraph<N, E>, new_node: N, connect_fun: F)
where
    F: Fn(&N, &N) -> E,
    N: Default + Clone,
{
    let new_idx = graph.add_node(new_node.clone());

    let new_edges: Vec<_> = graph
        .node_weights_mut()
        .enumerate()
        .filter_map(|(old_i_idx, old_node)| {
            let old_idx = NodeIndex::new(old_i_idx);

            if old_idx == new_idx {
                None
            } else {
                Some((old_idx, new_idx, connect_fun(old_node, &new_node)))
            }
        })
        .collect();

    graph.extend_with_edges(new_edges);
}

fn parse_input(path: &'static str) -> UnGraph<Slide, usize> {
    let raw = fs::read_to_string(path).unwrap();

    let mut result = Graph::new_undirected();
    let mut vpicts = Vec::<Pict>::new();

    raw.lines()
        .skip(1)
        .enumerate()
        .for_each(|(curr_pict_id, line)| {
            let words: Vec<_> = line.split_whitespace().collect();

            let ornt = if words[0] == "H" { Ornt::H } else { Ornt::V };

            let new_node = Pict {
                id: curr_pict_id,
                ornt,
                tags: words.into_iter().skip(2).map(&str::to_owned).collect(),
            };

            if ornt == Ornt::V {
                // Create new node for every vertical picture already parsed (combined with the new
                // one).
                // NB. exclude new picture from pair up
                for vpict in vpicts.iter().filter(|vpict| vpict.id != new_node.id) {
                    // Every node created this way is still connected to every other node (the graph is
                    // kept complete).
                    add_node_and_complete(
                        &mut result,
                        Slide::V2(new_node.clone(), vpict.clone()),
                        interest_rating,
                    );
                }

                // Remember vertical picture parsed to repeat the process.
                vpicts.push(new_node);
            } else {
                add_node_and_complete(&mut result, Slide::O1(new_node), interest_rating);
            }
        });

    result
}

fn solve(input: UnGraph<Pict, usize>) {

}

fn main() {
    let picts = parse_input("res/input");

    println!("{:?}", Dot::with_config(&picts, &[Config::NodeIndexLabel]));
    println!(
        "graph:\n{:#?}",
        picts
            .node_indices()
            .map(|idx| picts.node_weight(idx))
            .collect::<Vec<_>>()
    );
}
