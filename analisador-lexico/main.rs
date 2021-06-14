mod operator;
mod punctuation;

enum Token {
  Number { val: String },
  Operator { val: operator::Operator },
  Punctuation { val: punctuation::Punctuation },
}

fn match_args(character: &str) -> Token {
  match character {
    "1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9"|"0" => Token::Number { val: character.to_string() },
    "+"|"-"|"*"|"/" => Token::Operator { val: operator::Operator::match_operator(character)  },
    "("|")" => Token::Punctuation { val: punctuation::Punctuation::match_operator(character) },
    _ => panic!("Caractere não reconhecido. Digite a expressão separada por espaços"),
  }
}

// Exemplo de invocação: cargo run 5 + 3 \* \( 2 - 5 \) / 4 + 3
fn main() {
  for arg in std::env::args().skip(1) {
    match match_args(&arg) {
      Token::Number { val } => println!("Número({})", val),
      Token::Operator { val } => println!("Operador({})", val.to_string()),
      Token::Punctuation { val } => println!("Punctuation({})", val.to_string()),
    };
  }
}
