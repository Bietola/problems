#![feature(cmp_min_max_by)]

use educe::*;
use tuple::*;

/*************************/
/* Matrix utility struct */
/*************************/

#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
enum Dir {
    N,
    W,
    NW,
}

impl Dir {
    fn to_pair(&self) -> T2<i32, i32> {
        match self {
            N => T2(0, -1),
            W => T2(-1, 0),
            NW => T2(-1, -1),
        }
    }
}

struct Matrix<T> {
    contents: Vec<T>,
    width: usize,
    height: usize,
}

impl<T> Matrix<T> {
    fn from_scalar(scalar: T, width: usize, height: usize) -> Self
    where
        T: Clone,
    {
        Matrix {
            contents: vec![scalar; width * height],
            width,
            height,
        }
    }

    fn at(&self, x: usize, y: usize) -> &T {
        &self.contents[y * self.width + x]
    }

    fn at_mut(&mut self, x: usize, y: usize) -> &mut T {
        &mut self.contents[y * self.width + x]
    }

    fn at_tpl(&self, (x, y): (usize, usize)) -> &T {
        self.at(x, y)
    }
}

/**********************/
/* Allignment structs */
/**********************/

#[derive(Debug, PartialEq)]
pub enum Pair {
    Same,
    Gap1(char),
    Gap2(char),
    Sub(char, char),
}

#[derive(Clone, Educe)]
#[educe(PartialEq, Eq, PartialOrd, Ord)]
struct MatCell {
    score: i32,

    #[educe(Ord(ignore))]
    origin: Option<Dir>,
}

impl MatCell {
    fn branch(&self, branch_score: i32, origin: Dir) -> MatCell {
        MatCell {
            score: self.score + branch_score,
            origin: Some(origin),
        }
    }
}

impl From<i32> for MatCell {
    fn from(score: i32) -> Self {
        MatCell {
            score,
            origin: None,
        }
    }
}

#[derive(Debug, PartialEq)]
pub struct Allignment<'a> {
    pub info: AllignmentInfo<'a>,
    pub contents: Vec<Pair>,
}

/*******************************/
/* Global allignment functions */
/*******************************/

#[derive(Debug, PartialEq, Clone)]
pub struct AllignmentInfo<'a> {
    rowstr: &'a [u8],
    colstr: &'a [u8],
    same_score: i32,
    sub_score: i32,
    gap_score: i32,
}

pub fn allign<'a>(info: AllignmentInfo<'a>) -> Allignment<'a> {
    let rowstr = info.rowstr;
    let colstr = info.colstr;
    let same_score = info.same_score;
    let sub_score = info.sub_score;
    let gap_score = info.gap_score;

    let colsn = rowstr.len();
    let rowsn = colstr.len();
    let mut dmat = Matrix::from_scalar(MatCell::from(0), rowsn, colsn);

    // Init first cell.
    *dmat.at_mut(0, 0) = if rowstr[0] == colstr[0] {
        MatCell::from(same_score)
    } else {
        MatCell::from(sub_score)
    };

    // Init first row.
    for r in 1..rowsn {
        *dmat.at_mut(r, 0) = if rowstr[r] == colstr[0] {
            dmat.at(r - 1, 0).branch(same_score, Dir::W)
        } else {
            dmat.at(r - 1, 0).branch(gap_score, Dir::W)
        }
    }

    // Init first column.
    for c in 1..colsn {
        *dmat.at_mut(0, c) = if colstr[c] == rowstr[0] {
            dmat.at(0, c - 1).branch(same_score, Dir::N)
        } else {
            dmat.at(0, c - 1).branch(gap_score, Dir::N)
        }
    }

    // Complete allignment matrix.
    let mut max_allignment = (0, 0);
    for r in 1..rowsn {
        for c in 1..colsn {
            let diag = dmat.at(r - 1, c - 1);
            let north = dmat.at(r, c - 1);
            let west = dmat.at(r - 1, c);

            use std::cmp::max;
            *dmat.at_mut(r, c) = max(
                if rowstr[r - 1] == colstr[c - 1] {
                    diag.branch(same_score, Dir::NW)
                } else {
                    diag.branch(sub_score, Dir::NW)
                },
                max(
                    north.branch(gap_score, Dir::N),
                    west.branch(gap_score, Dir::W),
                ),
            );

            // Keep track of max allignment.
            // TODO: consider multiple candidates.
            if dmat.at(r, c) > dmat.at_tpl(max_allignment) {
                max_allignment = (r, c);
            }
        }
    }

    // Backtrack from maximum allignment score to construct allignment.
    backtrack(info, &dmat, max_allignment.into())
}

fn backtrack<'a>(
    info: AllignmentInfo<'a>,
    dmat: &Matrix<MatCell>,
    mut pos: T2<usize, usize>,
) -> Allignment<'a> {
    let mut aln_pairs = vec![];

    while let Some(origin) = dmat.at_tpl(pos.into()).origin {
        // Allignment pair is added in accordance to the backtrack movement.
        let rowchar = info.rowstr[pos.0].clone();
        let colchar = info.rowstr[pos.1].clone();
        aln_pairs.push(match origin {
            Dir::NW => {
                if rowchar == colchar {
                    Pair::Same
                } else {
                    Pair::Sub(rowchar as char, colchar as char)
                }
            }

            Dir::W => Pair::Gap1(rowchar as char),
            Dir::N => Pair::Gap2(colchar.into()),
        });

        // Backtrack pos.
        // TODO: Add Into traits to tuple library to simplify ridiculous type conversion.
        pos = (pos.map(|e| e as i32) + origin.to_pair()).map(|e| e as usize);
    }

    Allignment {
        info,
        contents: aln_pairs,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_single_gap() {
        use Pair::*;

        let info = AllignmentInfo {
            rowstr: b"hello",
            colstr: b"heAllo",
            same_score: 1,
            sub_score: -1,
            gap_score: -2,
        };
        assert_eq!(
            allign(info.clone()),
            Allignment {
                info,
                contents: vec![Same, Same, Gap1('A'), Same, Same, Same,]
            }
        );
    }
}
