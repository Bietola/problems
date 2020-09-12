mod aln {
    use min_max_macros::*;

    /*************************/
    /* Matrix utility struct */
    /*************************/

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

    #[derive(Debug, PartialEq)]
    pub struct Allignment<'a> {
        strings: (&'a str, &'a str),
        contents: Vec<Pair>,
    }

    /*******************************/
    /* Global allignment functions */
    /*******************************/

    pub fn allign<'a>(
        str1: &'a str,
        str2: &'a str,
        same_score: i32,
        sub_score: i32,
        gap_score: i32,
    ) -> Allignment<'a> {
        assert!(str1.is_ascii());
        assert!(str2.is_ascii());
        let rowstr = str1.as_bytes();
        let colstr = str2.as_bytes();

        let colsn = rowstr.len();
        let rowsn = colstr.len();
        let mut dmat = Matrix::from_scalar(0, rowsn, colsn);

        // Init first cell.
        *dmat.at_mut(0, 0) = if rowstr[0] == colstr[0] {
            same_score
        } else {
            sub_score
        };

        // Init first row.
        for r in 1..rowsn {
            *dmat.at_mut(r, 0) = if rowstr[r] == colstr[0] {
                dmat.at(r - 1, 0) + same_score
            } else {
                dmat.at(r - 1, 0) + gap_score
            }
        }

        // Init first column.
        for c in 1..colsn {
            *dmat.at_mut(0, c) = if colstr[c] == rowstr[0] {
                dmat.at(0, c - 1) + same_score
            } else {
                dmat.at(0, c - 1) + gap_score
            }
        }

        // Complete allignment matrix.
        let mut max_allignment = (0, 0);
        for r in 1..rowsn {
            for c in 1..colsn {
                let diag = dmat.at(r - 1, c - 1);
                let up = dmat.at(r, c - 1);
                let left = dmat.at(r - 1, c);

                *dmat.at_mut(r, c) = max!(
                    if rowstr[r - 1] == colstr[c - 1] {
                        diag + same_score
                    } else {
                        diag + sub_score
                    },
                    up + gap_score,
                    left + gap_score
                );

                // Keep track of max allignment.
                if dmat.at(r, c) == dmat.at_tpl(max_allignment) {
                    max_allignment = (r, c);
                }
            }
        }

        // Backtrack from maximum allignment score to construct allignment.
        backtrack(&dmat, max_allignment)
    }

    fn backtrack<'a, T>(dmat: &Matrix<T>, (sr, sc): (usize, usize)) -> Allignment<'a> {
        backtrack(dmat,
            max!(
                using |(r, c)| dmat.at(r, c);

                (sr - 1, sc - 1),
                (sr - 1, sc),
                (sr, sc - 1),
            )
        )
    }

    #[cfg(test)]
    mod tests {
        use super::*;

        #[test]
        fn test_single_gap() {
            use Pair::*;

            assert_eq!(
                allign("hello", "heAllo", 1, -1, -2),
                Allignment {
                    strings: ("hello", "heAllo"),
                    contents: vec![Same, Same, Gap1('A'), Same, Same, Same,]
                }
            );
        }
    }
}

fn main() {
    println!("hello!");
}
