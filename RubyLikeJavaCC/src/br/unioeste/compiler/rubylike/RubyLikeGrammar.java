/* Generated By:JavaCC: Do not edit this line. RubyLikeGrammar.java */
package br.unioeste.compiler.rubylike;

import java.io.*;
import java.util.*;
import br.unioeste.compiler.recovery.*;

public class RubyLikeGrammar implements RubyLikeGrammarConstants {
    int contParseError; // Contador de erros sintáticos
    boolean debug_recovery; // Controla a verbose de recuperação de erros

    Hashtable tbl = new Hashtable ();

  public static void main(String args []) throws ParseException
  {
    boolean debug_as = false;
    boolean debug_recovery = false;

    RubyLikeGrammar parser = new RubyLikeGrammar(System.in);

    parser.debug_recovery = debug_recovery;

    if (!debug_as) parser.disable_tracing();

    int b=1;
    while (b==1) {
      System.out.println("Lendo da entrada padr\u00e3o...");
      System.out.print("Express\u00e3o \u005c"1+(2+3)*4;\u005c" ou atribui\u00e7\u00e3o :");
      try {
        b = parser.one_line();
        switch (b) {
          case 0 :  System.out.println("Goodbye.");
                    break;
          case 1 :  System.out.println("OK.");
                    break;
          default : break;
        }
      }
      catch (ParseException e) {
        System.out.println("NOK.");
        System.out.println(e.getMessage());
        parser.ReInit(System.in);
      }
      catch (Exception e) {
        System.out.println("NOK.");
        System.out.println(e.getMessage());
        parser.ReInit(System.in);
      }
      catch (Error e) {
        System.out.println("Oops.");
        System.out.println(e.getMessage());
        break;
      }
    }
  }

  void mostrarResult ( double a )
  {
        //this.erros.append ( Double.toString ( a ) );
  }

  // Relaciona o indice de um token com seu nome
  static public String im ( int x ) {
    int k;
    String s;
    s = tokenImage[x];
    k = s.lastIndexOf ( "\u005c"");
    try {
      s = s.substring ( 1, k );
    } catch ( StringIndexOutOfBoundsException e ) { }
    return s;
  }

  boolean eof; // Variável que indica se EOF foi alcançado
  // O método abaixo consome os tokens até alcançar um que pertença
  // ao conjunto de resincronização
  void consumeUntil ( RecoverySet g,
                      ParseException e,
                      String met ) throws ParseEOFException, ParseException  {
     Token tok;
     eof=false; // FIXME
     if (debug_recovery) { // Informação sobre a recuperação
       //erros.append("");
       //erros.append( "*** " + met + " *** ");
       //erros.append( " Syncronizing Set: "+ g );
     }
     if (g==null) throw e; // se o conjunto de recuperação é null, propaga a exceção

     tok = getToken ( 1 ); // pega o token atual
     while (!eof) {
       if ( g.contains ( tok.kind ) ) {
         if ( debug_recovery )
           //erros.append( " Found syncronizing token: " + im (tok.kind));
         break;
       }
       if (debug_recovery)
         //erros.append( " Ignorando token "+ im ( tok.kind));
       getNextToken();
       tok = getToken(1);
       if (tok.kind==EOF && !g.contains(EOF) )
         eof = true;
     }
     System.out.println ( e.getMessage());
     contParseError++;
     if ( eof ) throw new ParseException ( "EOF found prematurely.");
   }

  final public void program() throws ParseException {
    try {
      if (jj_2_1(2)) {
        vars();
        jj_consume_token(END_CMD);
      } else if (jj_2_2(2)) {
        list();
        jj_consume_token(END_CMD);
      } else if (jj_2_3(2)) {
        IfElse();
      } else if (jj_2_4(2)) {
        each();
      } else {
        jj_consume_token(-1);
        throw new ParseException();
      }
    } catch (ParseException e) {
                consumeUntil ( g, e, "calc" );
                getNextToken();
    }
  }

  final public void list() throws ParseException {
    if (jj_2_8(2)) {
      jj_consume_token(LIST);
      jj_consume_token(LBRACE);
      label_1:
      while (true) {
        vars();
        jj_consume_token(SEMICOLON);
        if (jj_2_5(2)) {
          ;
        } else {
          break label_1;
        }
      }
    } else if (jj_2_9(2)) {
      label_2:
      while (true) {
        jj_consume_token(INT_CONSTANT);
        jj_consume_token(SEMICOLON);
        if (jj_2_6(2)) {
          ;
        } else {
          break label_2;
        }
      }
    } else if (jj_2_10(2)) {
      label_3:
      while (true) {
        jj_consume_token(STRING);
        jj_consume_token(SEMICOLON);
        if (jj_2_7(2)) {
          ;
        } else {
          break label_3;
        }
      }
      jj_consume_token(RBRACE);
    } else {
      jj_consume_token(-1);
      throw new ParseException();
    }
  }

  final public void IfElse() throws ParseException {
    jj_consume_token(IF);
    expression();
    ifBlock();
    jj_consume_token(ELSE);
    elseBlock();
  }

  final public void expression() throws ParseException {
    jj_consume_token(LBRACE);
    label_4:
    while (true) {
      if (jj_2_14(2)) {
        jj_consume_token(INT_CONSTANT);
      } else if (jj_2_15(2)) {
        jj_consume_token(STRING);
      } else if (jj_2_16(2)) {
        vars();
        label_5:
        while (true) {
          if (jj_2_11(2)) {
            jj_consume_token(AND);
          } else if (jj_2_12(2)) {
            jj_consume_token(OR);
          } else {
            jj_consume_token(-1);
            throw new ParseException();
          }
          if (jj_2_13(2)) {
            ;
          } else {
            break label_5;
          }
        }
        jj_consume_token(INT_CONSTANT);
      } else if (jj_2_17(2)) {
        jj_consume_token(STRING);
      } else if (jj_2_18(2)) {
        vars();
      } else {
        jj_consume_token(-1);
        throw new ParseException();
      }
      if (jj_2_19(2)) {
        ;
      } else {
        break label_4;
      }
    }
    jj_consume_token(RBRACE);
  }

  final public void ifBlock() throws ParseException {
    jj_consume_token(LBRACKET);
    label_6:
    while (true) {
      vars();
      if (jj_2_20(2)) {
        ;
      } else {
        break label_6;
      }
    }
    jj_consume_token(END_CMD);
    jj_consume_token(RBRACKET);
  }

  final public void elseBlock() throws ParseException {
    jj_consume_token(LBRACKET);
    label_7:
    while (true) {
      vars();
      if (jj_2_21(2)) {
        ;
      } else {
        break label_7;
      }
    }
    jj_consume_token(END_CMD);
    jj_consume_token(RBRACKET);
  }

  final public void each() throws ParseException {
    jj_consume_token(EACH);
    expression();
    eachBlock();
  }

  final public void eachBlock() throws ParseException {
    if (jj_2_24(2)) {
      jj_consume_token(LBRACKET);
      label_8:
      while (true) {
        if (jj_2_22(2)) {
          ;
        } else {
          break label_8;
        }
        vars();
      }
    } else if (jj_2_25(2)) {
      label_9:
      while (true) {
        if (jj_2_23(2)) {
          ;
        } else {
          break label_9;
        }
        IfElse();
      }
      jj_consume_token(RBRACKET);
    } else {
      jj_consume_token(-1);
      throw new ParseException();
    }
  }

  final public int one_line() throws ParseException, Exception {
  RecoverySet g = new RecoverySet ( EOF );
    try {
      if (jj_2_27(2)) {
        label_10:
        while (true) {
          calc(g);
          if (jj_2_26(2)) {
            ;
          } else {
            break label_10;
          }
        }
                     {if (true) return 1;}
      } else if (jj_2_28(2)) {
        jj_consume_token(END_CMD);
                         {if (true) return 0;}
      } else {
        jj_consume_token(-1);
        throw new ParseException();
      }
    } catch (ParseException e) {
        consumeUntil ( g, e, "one_line" );
    }
    throw new Error("Missing return statement in function");
  }

  final public void calc(RecoverySet f) throws ParseException, Exception {
  double a = 0;
  RecoverySet g = First.calc.union ( f );
    try {
      if (jj_2_29(2)) {
        vars();
        jj_consume_token(END_CMD);
      } else if (jj_2_30(2)) {
        a = sum();
        jj_consume_token(END_CMD);
                             mostrarResult( a );
      } else {
        jj_consume_token(-1);
        throw new ParseException();
      }
    } catch (ParseException e) {
        consumeUntil ( g, e, "calc" );
        getNextToken();
    }
  }

// Declarar ou alterar o valor de variáveis
  final public void vars() throws ParseException, Exception {
                                 Token var; double a=0;
    var = jj_consume_token(VAR);
    jj_consume_token(ATTRIB);
    a = sum();
    tbl.put ( var.image, new Float(a) );
    System.out.println ( "Vari\u00e1vel ["+var.image+"] criada/modificada!" );
    {if (true) return;}
  }

  final public float sum() throws ParseException, Exception {
                                  float a=0, b=0; Token tk;
    a = term();
    label_11:
    while (true) {
      if (jj_2_31(2)) {
        ;
      } else {
        break label_11;
      }
      if (jj_2_32(2)) {
        tk = jj_consume_token(PLUS);
      } else if (jj_2_33(2)) {
        tk = jj_consume_token(MINUS);
      } else {
        jj_consume_token(-1);
        throw new ParseException();
      }
      b = term();
      if (tk.image=="+")
        a+=b;
      else
        a-=b;
    }
    {if (true) return a;}
    throw new Error("Missing return statement in function");
  }

  final public float term() throws ParseException, Exception {
                                   float a=0, b=0; Token tk;
    a = unary();
    label_12:
    while (true) {
      if (jj_2_34(2)) {
        ;
      } else {
        break label_12;
      }
      if (jj_2_35(2)) {
        tk = jj_consume_token(MULTIPLY);
      } else if (jj_2_36(2)) {
        tk = jj_consume_token(DIVIDE);
      } else {
        jj_consume_token(-1);
        throw new ParseException();
      }
      b = unary();
       if (tk.image=="*")
        a*=b;
      else
        a/=b;
    }
    {if (true) return a;}
    throw new Error("Missing return statement in function");
  }

  final public float unary() throws ParseException, Exception {
 float a=0;
    if (jj_2_37(2)) {
      jj_consume_token(MINUS);
      a = element();
                          {if (true) return -a;}
    } else if (jj_2_38(2)) {
      a = element();
                {if (true) return a;}
    } else {
      jj_consume_token(-1);
      throw new ParseException();
    }
    throw new Error("Missing return statement in function");
  }

  final public float element() throws ParseException, Exception {
  Token tk; float a=0;
    if (jj_2_39(2)) {
      tk = jj_consume_token(INT_CONSTANT);
                             {if (true) return Integer.parseInt ( tk.image );}
    } else if (jj_2_40(2)) {
      tk = jj_consume_token(FLOAT);
                       {if (true) return Float.parseFloat ( tk.image );}
    } else if (jj_2_41(2)) {
      tk = jj_consume_token(VAR);
      if (tbl.containsKey(tk.image))
        {if (true) return ((Float)tbl.get(tk.image)).floatValue();}
      {if (true) throw new ParseException (
        "Vari\u00e1vel ["+ tk.image + "] n\u00e3o localizada!"
      + " Linha: " + tk.beginLine + ", Coluna: "+ tk.beginColumn );}
    } else if (jj_2_42(2)) {
      jj_consume_token(LPAREN);
      a = sum();
      jj_consume_token(RPAREN);
                         {if (true) return a;}
    } else {
      jj_consume_token(-1);
      throw new ParseException();
    }
    throw new Error("Missing return statement in function");
  }

  private boolean jj_2_1(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_1(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(0, xla); }
  }

  private boolean jj_2_2(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_2(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(1, xla); }
  }

  private boolean jj_2_3(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_3(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(2, xla); }
  }

  private boolean jj_2_4(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_4(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(3, xla); }
  }

  private boolean jj_2_5(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_5(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(4, xla); }
  }

  private boolean jj_2_6(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_6(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(5, xla); }
  }

  private boolean jj_2_7(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_7(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(6, xla); }
  }

  private boolean jj_2_8(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_8(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(7, xla); }
  }

  private boolean jj_2_9(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_9(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(8, xla); }
  }

  private boolean jj_2_10(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_10(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(9, xla); }
  }

  private boolean jj_2_11(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_11(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(10, xla); }
  }

  private boolean jj_2_12(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_12(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(11, xla); }
  }

  private boolean jj_2_13(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_13(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(12, xla); }
  }

  private boolean jj_2_14(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_14(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(13, xla); }
  }

  private boolean jj_2_15(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_15(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(14, xla); }
  }

  private boolean jj_2_16(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_16(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(15, xla); }
  }

  private boolean jj_2_17(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_17(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(16, xla); }
  }

  private boolean jj_2_18(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_18(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(17, xla); }
  }

  private boolean jj_2_19(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_19(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(18, xla); }
  }

  private boolean jj_2_20(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_20(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(19, xla); }
  }

  private boolean jj_2_21(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_21(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(20, xla); }
  }

  private boolean jj_2_22(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_22(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(21, xla); }
  }

  private boolean jj_2_23(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_23(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(22, xla); }
  }

  private boolean jj_2_24(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_24(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(23, xla); }
  }

  private boolean jj_2_25(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_25(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(24, xla); }
  }

  private boolean jj_2_26(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_26(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(25, xla); }
  }

  private boolean jj_2_27(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_27(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(26, xla); }
  }

  private boolean jj_2_28(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_28(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(27, xla); }
  }

  private boolean jj_2_29(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_29(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(28, xla); }
  }

  private boolean jj_2_30(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_30(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(29, xla); }
  }

  private boolean jj_2_31(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_31(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(30, xla); }
  }

  private boolean jj_2_32(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_32(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(31, xla); }
  }

  private boolean jj_2_33(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_33(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(32, xla); }
  }

  private boolean jj_2_34(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_34(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(33, xla); }
  }

  private boolean jj_2_35(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_35(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(34, xla); }
  }

  private boolean jj_2_36(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_36(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(35, xla); }
  }

  private boolean jj_2_37(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_37(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(36, xla); }
  }

  private boolean jj_2_38(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_38(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(37, xla); }
  }

  private boolean jj_2_39(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_39(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(38, xla); }
  }

  private boolean jj_2_40(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_40(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(39, xla); }
  }

  private boolean jj_2_41(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_41(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(40, xla); }
  }

  private boolean jj_2_42(int xla) {
    jj_la = xla; jj_lastpos = jj_scanpos = token;
    try { return !jj_3_42(); }
    catch(LookaheadSuccess ls) { return true; }
    finally { jj_save(41, xla); }
  }

  private boolean jj_3_41() {
    if (jj_scan_token(VAR)) return true;
    return false;
  }

  private boolean jj_3_40() {
    if (jj_scan_token(FLOAT)) return true;
    return false;
  }

  private boolean jj_3_24() {
    if (jj_scan_token(LBRACKET)) return true;
    Token xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_22()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

  private boolean jj_3R_21() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_39()) {
    jj_scanpos = xsp;
    if (jj_3_40()) {
    jj_scanpos = xsp;
    if (jj_3_41()) {
    jj_scanpos = xsp;
    if (jj_3_42()) return true;
    }
    }
    }
    return false;
  }

  private boolean jj_3_39() {
    if (jj_scan_token(INT_CONSTANT)) return true;
    return false;
  }

  private boolean jj_3_15() {
    if (jj_scan_token(STRING)) return true;
    return false;
  }

  private boolean jj_3_21() {
    if (jj_3R_13()) return true;
    return false;
  }

  private boolean jj_3R_16() {
    if (jj_scan_token(EACH)) return true;
    if (jj_3R_22()) return true;
    return false;
  }

  private boolean jj_3_38() {
    if (jj_3R_21()) return true;
    return false;
  }

  private boolean jj_3R_20() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_37()) {
    jj_scanpos = xsp;
    if (jj_3_38()) return true;
    }
    return false;
  }

  private boolean jj_3_37() {
    if (jj_scan_token(MINUS)) return true;
    if (jj_3R_21()) return true;
    return false;
  }

  private boolean jj_3_20() {
    if (jj_3R_13()) return true;
    return false;
  }

  private boolean jj_3_14() {
    if (jj_scan_token(INT_CONSTANT)) return true;
    return false;
  }

  private boolean jj_3_19() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_14()) {
    jj_scanpos = xsp;
    if (jj_3_15()) {
    jj_scanpos = xsp;
    if (jj_3_16()) {
    jj_scanpos = xsp;
    if (jj_3_17()) {
    jj_scanpos = xsp;
    if (jj_3_18()) return true;
    }
    }
    }
    }
    return false;
  }

  private boolean jj_3_36() {
    if (jj_scan_token(DIVIDE)) return true;
    return false;
  }

  private boolean jj_3_35() {
    if (jj_scan_token(MULTIPLY)) return true;
    return false;
  }

  private boolean jj_3_18() {
    if (jj_3R_13()) return true;
    return false;
  }

  private boolean jj_3_34() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_35()) {
    jj_scanpos = xsp;
    if (jj_3_36()) return true;
    }
    if (jj_3R_20()) return true;
    return false;
  }

  private boolean jj_3R_19() {
    if (jj_3R_20()) return true;
    Token xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_34()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

  private boolean jj_3R_22() {
    if (jj_scan_token(LBRACE)) return true;
    return false;
  }

  private boolean jj_3_17() {
    if (jj_scan_token(STRING)) return true;
    return false;
  }

  private boolean jj_3_7() {
    if (jj_scan_token(STRING)) return true;
    if (jj_scan_token(SEMICOLON)) return true;
    return false;
  }

  private boolean jj_3_10() {
    Token xsp;
    if (jj_3_7()) return true;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_7()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

  private boolean jj_3_6() {
    if (jj_scan_token(INT_CONSTANT)) return true;
    if (jj_scan_token(SEMICOLON)) return true;
    return false;
  }

  private boolean jj_3_9() {
    Token xsp;
    if (jj_3_6()) return true;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_6()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

  private boolean jj_3_5() {
    if (jj_3R_13()) return true;
    return false;
  }

  private boolean jj_3_33() {
    if (jj_scan_token(MINUS)) return true;
    return false;
  }

  private boolean jj_3_32() {
    if (jj_scan_token(PLUS)) return true;
    return false;
  }

  private boolean jj_3_31() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_32()) {
    jj_scanpos = xsp;
    if (jj_3_33()) return true;
    }
    if (jj_3R_19()) return true;
    return false;
  }

  private boolean jj_3R_15() {
    if (jj_scan_token(IF)) return true;
    if (jj_3R_22()) return true;
    return false;
  }

  private boolean jj_3R_18() {
    if (jj_3R_19()) return true;
    Token xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_31()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

  private boolean jj_3_4() {
    if (jj_3R_16()) return true;
    return false;
  }

  private boolean jj_3_3() {
    if (jj_3R_15()) return true;
    return false;
  }

  private boolean jj_3_2() {
    if (jj_3R_14()) return true;
    return false;
  }

  private boolean jj_3_1() {
    if (jj_3R_13()) return true;
    return false;
  }

  private boolean jj_3R_14() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_8()) {
    jj_scanpos = xsp;
    if (jj_3_9()) {
    jj_scanpos = xsp;
    if (jj_3_10()) return true;
    }
    }
    return false;
  }

  private boolean jj_3_8() {
    if (jj_scan_token(LIST)) return true;
    if (jj_scan_token(LBRACE)) return true;
    return false;
  }

  private boolean jj_3R_13() {
    if (jj_scan_token(VAR)) return true;
    if (jj_scan_token(ATTRIB)) return true;
    return false;
  }

  private boolean jj_3_12() {
    if (jj_scan_token(OR)) return true;
    return false;
  }

  private boolean jj_3_30() {
    if (jj_3R_18()) return true;
    if (jj_scan_token(END_CMD)) return true;
    return false;
  }

  private boolean jj_3_29() {
    if (jj_3R_13()) return true;
    return false;
  }

  private boolean jj_3R_17() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_29()) {
    jj_scanpos = xsp;
    if (jj_3_30()) return true;
    }
    return false;
  }

  private boolean jj_3_13() {
    Token xsp;
    xsp = jj_scanpos;
    if (jj_3_11()) {
    jj_scanpos = xsp;
    if (jj_3_12()) return true;
    }
    return false;
  }

  private boolean jj_3_11() {
    if (jj_scan_token(AND)) return true;
    return false;
  }

  private boolean jj_3_23() {
    if (jj_3R_15()) return true;
    return false;
  }

  private boolean jj_3_26() {
    if (jj_3R_17()) return true;
    return false;
  }

  private boolean jj_3_28() {
    if (jj_scan_token(END_CMD)) return true;
    return false;
  }

  private boolean jj_3_22() {
    if (jj_3R_13()) return true;
    return false;
  }

  private boolean jj_3_25() {
    Token xsp;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_23()) { jj_scanpos = xsp; break; }
    }
    if (jj_scan_token(RBRACKET)) return true;
    return false;
  }

  private boolean jj_3_42() {
    if (jj_scan_token(LPAREN)) return true;
    if (jj_3R_18()) return true;
    return false;
  }

  private boolean jj_3_27() {
    Token xsp;
    if (jj_3_26()) return true;
    while (true) {
      xsp = jj_scanpos;
      if (jj_3_26()) { jj_scanpos = xsp; break; }
    }
    return false;
  }

  private boolean jj_3_16() {
    if (jj_3R_13()) return true;
    return false;
  }

  /** Generated Token Manager. */
  public RubyLikeGrammarTokenManager token_source;
  SimpleCharStream jj_input_stream;
  /** Current token. */
  public Token token;
  /** Next token. */
  public Token jj_nt;
  private int jj_ntk;
  private Token jj_scanpos, jj_lastpos;
  private int jj_la;
  private int jj_gen;
  final private int[] jj_la1 = new int[0];
  static private int[] jj_la1_0;
  static private int[] jj_la1_1;
  static {
      jj_la1_init_0();
      jj_la1_init_1();
   }
   private static void jj_la1_init_0() {
      jj_la1_0 = new int[] {};
   }
   private static void jj_la1_init_1() {
      jj_la1_1 = new int[] {};
   }
  final private JJCalls[] jj_2_rtns = new JJCalls[42];
  private boolean jj_rescan = false;
  private int jj_gc = 0;

  /** Constructor with InputStream. */
  public RubyLikeGrammar(java.io.InputStream stream) {
     this(stream, null);
  }
  /** Constructor with InputStream and supplied encoding */
  public RubyLikeGrammar(java.io.InputStream stream, String encoding) {
    try { jj_input_stream = new SimpleCharStream(stream, encoding, 1, 1); } catch(java.io.UnsupportedEncodingException e) { throw new RuntimeException(e); }
    token_source = new RubyLikeGrammarTokenManager(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 0; i++) jj_la1[i] = -1;
    for (int i = 0; i < jj_2_rtns.length; i++) jj_2_rtns[i] = new JJCalls();
  }

  /** Reinitialise. */
  public void ReInit(java.io.InputStream stream) {
     ReInit(stream, null);
  }
  /** Reinitialise. */
  public void ReInit(java.io.InputStream stream, String encoding) {
    try { jj_input_stream.ReInit(stream, encoding, 1, 1); } catch(java.io.UnsupportedEncodingException e) { throw new RuntimeException(e); }
    token_source.ReInit(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 0; i++) jj_la1[i] = -1;
    for (int i = 0; i < jj_2_rtns.length; i++) jj_2_rtns[i] = new JJCalls();
  }

  /** Constructor. */
  public RubyLikeGrammar(java.io.Reader stream) {
    jj_input_stream = new SimpleCharStream(stream, 1, 1);
    token_source = new RubyLikeGrammarTokenManager(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 0; i++) jj_la1[i] = -1;
    for (int i = 0; i < jj_2_rtns.length; i++) jj_2_rtns[i] = new JJCalls();
  }

  /** Reinitialise. */
  public void ReInit(java.io.Reader stream) {
    jj_input_stream.ReInit(stream, 1, 1);
    token_source.ReInit(jj_input_stream);
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 0; i++) jj_la1[i] = -1;
    for (int i = 0; i < jj_2_rtns.length; i++) jj_2_rtns[i] = new JJCalls();
  }

  /** Constructor with generated Token Manager. */
  public RubyLikeGrammar(RubyLikeGrammarTokenManager tm) {
    token_source = tm;
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 0; i++) jj_la1[i] = -1;
    for (int i = 0; i < jj_2_rtns.length; i++) jj_2_rtns[i] = new JJCalls();
  }

  /** Reinitialise. */
  public void ReInit(RubyLikeGrammarTokenManager tm) {
    token_source = tm;
    token = new Token();
    jj_ntk = -1;
    jj_gen = 0;
    for (int i = 0; i < 0; i++) jj_la1[i] = -1;
    for (int i = 0; i < jj_2_rtns.length; i++) jj_2_rtns[i] = new JJCalls();
  }

  private Token jj_consume_token(int kind) throws ParseException {
    Token oldToken;
    if ((oldToken = token).next != null) token = token.next;
    else token = token.next = token_source.getNextToken();
    jj_ntk = -1;
    if (token.kind == kind) {
      jj_gen++;
      if (++jj_gc > 100) {
        jj_gc = 0;
        for (int i = 0; i < jj_2_rtns.length; i++) {
          JJCalls c = jj_2_rtns[i];
          while (c != null) {
            if (c.gen < jj_gen) c.first = null;
            c = c.next;
          }
        }
      }
      return token;
    }
    token = oldToken;
    jj_kind = kind;
    throw generateParseException();
  }

  static private final class LookaheadSuccess extends java.lang.Error { }
  final private LookaheadSuccess jj_ls = new LookaheadSuccess();
  private boolean jj_scan_token(int kind) {
    if (jj_scanpos == jj_lastpos) {
      jj_la--;
      if (jj_scanpos.next == null) {
        jj_lastpos = jj_scanpos = jj_scanpos.next = token_source.getNextToken();
      } else {
        jj_lastpos = jj_scanpos = jj_scanpos.next;
      }
    } else {
      jj_scanpos = jj_scanpos.next;
    }
    if (jj_rescan) {
      int i = 0; Token tok = token;
      while (tok != null && tok != jj_scanpos) { i++; tok = tok.next; }
      if (tok != null) jj_add_error_token(kind, i);
    }
    if (jj_scanpos.kind != kind) return true;
    if (jj_la == 0 && jj_scanpos == jj_lastpos) throw jj_ls;
    return false;
  }


/** Get the next Token. */
  final public Token getNextToken() {
    if (token.next != null) token = token.next;
    else token = token.next = token_source.getNextToken();
    jj_ntk = -1;
    jj_gen++;
    return token;
  }

/** Get the specific Token. */
  final public Token getToken(int index) {
    Token t = token;
    for (int i = 0; i < index; i++) {
      if (t.next != null) t = t.next;
      else t = t.next = token_source.getNextToken();
    }
    return t;
  }

  private int jj_ntk() {
    if ((jj_nt=token.next) == null)
      return (jj_ntk = (token.next=token_source.getNextToken()).kind);
    else
      return (jj_ntk = jj_nt.kind);
  }

  private java.util.List<int[]> jj_expentries = new java.util.ArrayList<int[]>();
  private int[] jj_expentry;
  private int jj_kind = -1;
  private int[] jj_lasttokens = new int[100];
  private int jj_endpos;

  private void jj_add_error_token(int kind, int pos) {
    if (pos >= 100) return;
    if (pos == jj_endpos + 1) {
      jj_lasttokens[jj_endpos++] = kind;
    } else if (jj_endpos != 0) {
      jj_expentry = new int[jj_endpos];
      for (int i = 0; i < jj_endpos; i++) {
        jj_expentry[i] = jj_lasttokens[i];
      }
      jj_entries_loop: for (java.util.Iterator<?> it = jj_expentries.iterator(); it.hasNext();) {
        int[] oldentry = (int[])(it.next());
        if (oldentry.length == jj_expentry.length) {
          for (int i = 0; i < jj_expentry.length; i++) {
            if (oldentry[i] != jj_expentry[i]) {
              continue jj_entries_loop;
            }
          }
          jj_expentries.add(jj_expentry);
          break jj_entries_loop;
        }
      }
      if (pos != 0) jj_lasttokens[(jj_endpos = pos) - 1] = kind;
    }
  }

  /** Generate ParseException. */
  public ParseException generateParseException() {
    jj_expentries.clear();
    boolean[] la1tokens = new boolean[45];
    if (jj_kind >= 0) {
      la1tokens[jj_kind] = true;
      jj_kind = -1;
    }
    for (int i = 0; i < 0; i++) {
      if (jj_la1[i] == jj_gen) {
        for (int j = 0; j < 32; j++) {
          if ((jj_la1_0[i] & (1<<j)) != 0) {
            la1tokens[j] = true;
          }
          if ((jj_la1_1[i] & (1<<j)) != 0) {
            la1tokens[32+j] = true;
          }
        }
      }
    }
    for (int i = 0; i < 45; i++) {
      if (la1tokens[i]) {
        jj_expentry = new int[1];
        jj_expentry[0] = i;
        jj_expentries.add(jj_expentry);
      }
    }
    jj_endpos = 0;
    jj_rescan_token();
    jj_add_error_token(0, 0);
    int[][] exptokseq = new int[jj_expentries.size()][];
    for (int i = 0; i < jj_expentries.size(); i++) {
      exptokseq[i] = jj_expentries.get(i);
    }
    return new ParseException(token, exptokseq, tokenImage);
  }

  /** Enable tracing. */
  final public void enable_tracing() {
  }

  /** Disable tracing. */
  final public void disable_tracing() {
  }

  private void jj_rescan_token() {
    jj_rescan = true;
    for (int i = 0; i < 42; i++) {
    try {
      JJCalls p = jj_2_rtns[i];
      do {
        if (p.gen > jj_gen) {
          jj_la = p.arg; jj_lastpos = jj_scanpos = p.first;
          switch (i) {
            case 0: jj_3_1(); break;
            case 1: jj_3_2(); break;
            case 2: jj_3_3(); break;
            case 3: jj_3_4(); break;
            case 4: jj_3_5(); break;
            case 5: jj_3_6(); break;
            case 6: jj_3_7(); break;
            case 7: jj_3_8(); break;
            case 8: jj_3_9(); break;
            case 9: jj_3_10(); break;
            case 10: jj_3_11(); break;
            case 11: jj_3_12(); break;
            case 12: jj_3_13(); break;
            case 13: jj_3_14(); break;
            case 14: jj_3_15(); break;
            case 15: jj_3_16(); break;
            case 16: jj_3_17(); break;
            case 17: jj_3_18(); break;
            case 18: jj_3_19(); break;
            case 19: jj_3_20(); break;
            case 20: jj_3_21(); break;
            case 21: jj_3_22(); break;
            case 22: jj_3_23(); break;
            case 23: jj_3_24(); break;
            case 24: jj_3_25(); break;
            case 25: jj_3_26(); break;
            case 26: jj_3_27(); break;
            case 27: jj_3_28(); break;
            case 28: jj_3_29(); break;
            case 29: jj_3_30(); break;
            case 30: jj_3_31(); break;
            case 31: jj_3_32(); break;
            case 32: jj_3_33(); break;
            case 33: jj_3_34(); break;
            case 34: jj_3_35(); break;
            case 35: jj_3_36(); break;
            case 36: jj_3_37(); break;
            case 37: jj_3_38(); break;
            case 38: jj_3_39(); break;
            case 39: jj_3_40(); break;
            case 40: jj_3_41(); break;
            case 41: jj_3_42(); break;
          }
        }
        p = p.next;
      } while (p != null);
      } catch(LookaheadSuccess ls) { }
    }
    jj_rescan = false;
  }

  private void jj_save(int index, int xla) {
    JJCalls p = jj_2_rtns[index];
    while (p.gen > jj_gen) {
      if (p.next == null) { p = p.next = new JJCalls(); break; }
      p = p.next;
    }
    p.gen = jj_gen + xla - jj_la; p.first = token; p.arg = xla;
  }

  static final class JJCalls {
    int gen;
    Token first;
    int arg;
    JJCalls next;
  }

}
