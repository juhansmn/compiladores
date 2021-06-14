use std::fmt::Display;
use std::fmt::Formatter;
use std::fmt::Result;

pub enum Operator {
  Sum,
  Sub,
  Div,
  Mult,
}

impl Display for Operator {
  fn fmt(&self, f: &mut Formatter) -> Result {
    match self {
      Operator::Sum  => write!(f, "Soma"),
      Operator::Sub  => write!(f, "Subtração"),
      Operator::Div  => write!(f, "Divisão"),
      Operator::Mult => write!(f, "Multiplicação"),
    }
  }
}

impl Operator {
  pub fn match_operator(character: &str) -> Operator {
    match character {
      "+" => Operator::Sum,
      "-" => Operator::Sub,
      "/" => Operator::Div,
      "*" => Operator::Mult,
      _ => panic!("operador inválido!"),
    }
  }
}
