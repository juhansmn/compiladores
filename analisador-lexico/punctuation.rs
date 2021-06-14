use std::fmt::Display;
use std::fmt::Formatter;
use std::fmt::Result;

pub enum Punctuation {
  OpPar,
  ClPar,
}

impl Display for Punctuation {
  fn fmt(&self, f: &mut Formatter) -> Result {
    match self {
      Punctuation::OpPar  => write!(f, "Abre parênteses"),
      Punctuation::ClPar  => write!(f, "Fecha parênteses"),
    }
  }
}

impl Punctuation {
  pub fn match_operator(character: &str) -> Punctuation {
    match character {
      "(" => Punctuation::OpPar,
      ")" => Punctuation::ClPar,
      _ => panic!("operador inválido!"),
    }
  }
}
