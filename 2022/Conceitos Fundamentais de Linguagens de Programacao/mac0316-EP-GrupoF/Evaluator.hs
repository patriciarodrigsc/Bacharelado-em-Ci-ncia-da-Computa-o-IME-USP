module Evaluator where

import Types (Env, Binding (Binding), ExprC (..), Value (..))
import Env (extendEnv, lookupEnv)

-- Bibliotecas extras
----------------------------------------------------------------------------------------------
import Tokenizer (isValidId)
import Data.List
----------------------------------------------------------------------------------------------

-- | Avaliador.
--
-- Esta é a etapa do interpretador que executa o código desejado.
-- Uma vez que o código foi transformado em uma árvore com marcações
-- semânticas e os açúcares sintáticos foram removidos, podemos finalmente
-- realizar uma última travessia na árvore para interpretar o programa.
--
-- O resultado da avaliação será do tipo `Value`, que representa os
-- valores primitivos da linguagem. Veja a documentação de `Value`
-- no arquivos "Types.hs" para verificar quais são os valores primitivos.
--
-- A função `eval` também pede um _ambiente_ do tipo `Env`. O ambiente
-- é onde o interpretador irá buscar os valores utilizados no programa.
-- Por exemplo, caso o usuário de uma linguagem crie uma função através
-- do recurso `lambda`, a função `eval` irá buscar pelo valor do parâmetro
-- da função no ambiente. Para entender mais sobre o ambiente, veja o
-- módulo `Env.hs`.
--
-- >>> env = [Binding "x" (NumV 1)]
-- >>> code = (PlusC (IdC "x") (NumC 2)) 
-- >>> eval code env
-- NumV {numV = 3.0}
--
-- Para adicionar funcionalidade à linguagem, é necessário acrescentar
-- código a esta função (a não ser que a funcionalidade possa ser descrita
-- a partir de açúcares sintáticos).
eval :: ExprC -> Env -> Value
eval exp env = case exp of
  NumC  num   -> NumV num

-- Checagem de um identificador válido
----------------------------------------------------------------------------------------------
  IdC   sym   -> 
    case isValidId sym of
      True -> lookupEnv sym env
      False -> error "ERRO eval: identificador começa com número, é um número ou palavra reservada"
----------------------------------------------------------------------------------------------

  PlusC e1 e2 ->
    case (eval e1 env, eval e2 env) of 
      (NumV left, NumV right) -> NumV (left + right)
      (_, _)                  -> error "ERRO eval PlusC: um dos argumentos não é um número"
  MultC e1 e2 ->
    case (eval e1 env, eval e2 env) of
      (NumV left, NumV right) -> NumV (left * right)
      (_, _)                  -> error "ERRO eval MultC: um dos argumentos não é um número"

-- Checagem de um identificador válido no lambda
----------------------------------------------------------------------------------------------
  LamC argName body -> 
    case isValidId argName of
      True -> ClosV argName body env
      False -> error "ERRO eval: identificador começa com número, é um número ou palavra reservada"
----------------------------------------------------------------------------------------------

  AppC fun arg ->
    case closure of
      ClosV param body env ->
        eval body (extendEnv (Binding param argvalue) env)
      _ -> error ("ERRO eval AppC: AppC aplicado a algo que não é um fechamento: " ++ show closure)
    where
      closure  = eval fun env
      argvalue = eval arg env

-- Implementação do "case of"
----------------------------------------------------------------------------------------------
  CaseC num ofS intlist codelist ->
    case (eval num env, ofS) of
      (NumV res, "of") ->
        case (intlist, codelist) of
          (ConsC a1 a2, ConsC b1 b2) ->
            case eval a2 env of --tail tem 1 elemento
              NumV case_n2 ->
                case eval a1 env of
                  NumV case_n1 ->
                    if case_n1 == res
                      then eval b1 env
                      else 
                        if case_n2 == res
                          then eval b2 env
                          else error "ERRO eval CaseC: o número não está 'intlist'"
              _ -> --continua a recursao
                case eval a1 env of
                  NumV case_n1 ->
                    if case_n1 == res
                      then eval b1 env
                      else eval (CaseC num ofS a2 b2) env
          (_, _) -> error "ERRO eval CaseC: argumentos não são listas"
      _ -> error "ERRO eval CaseC: condicional não é um número ou 'of' inválido"
-----------------------------------------------------------------------------------------------

  IfC cond b1 b2 ->
    case eval cond env of
      NumV num ->
        if num /= 0
          then eval b1 env
          else eval b2 env
      _ -> error "ERRO eval IfC: condição não é um número"
  ConsC e1 e2    -> ConsV (eval e1 env) (eval e2 env)
  HeadC e        ->
    case eval e env of
      ConsV e1 e2 -> e1
      _ -> error "ERRO eval HeadC: head aplicado a algo que não é ConsV"
  TailC e        ->
    case eval e env of
      ConsV e1 e2 -> e2
      _ -> error "ERRO eval TailC: tail aplicado a algo que não é ConsV"
  LetrecC name val body ->

-- Checagem de um identificador válido no letrec
----------------------------------------------------------------------------------------------
    case (closure, isValidId name) of
      (ClosV param oldBody oldEnv, True) ->
----------------------------------------------------------------------------------------------

        -- estamos colocando o fechamento em seu próprio ambiente!
        -- note que estamos usando o `let` recursivo do próprio Haskell para
        -- fazer esta implementação...
        -- uma implementação mais baixo-nível seria mais trabalhosa em Haskell
        let newClos = ClosV param oldBody (extendEnv (Binding name newClos) oldEnv)
         in eval body (Types.env newClos)

----------------------------------------------------------------------------------------------
      (_ , True) -> error "ERRO eval LetrecC: valor declarado não é função"
      (_ , False) -> error "ERRO eval LetrecC: identificador começa com número, é um número ou palavra reservada"
----------------------------------------------------------------------------------------------

    where
      closure = eval val env
      
  QuoteC sym -> SymV sym
