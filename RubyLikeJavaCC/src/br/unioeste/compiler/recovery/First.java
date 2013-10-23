package br.unioeste.compiler.recovery;

import br.unioeste.compiler.rubylike.RubyLikeGrammarConstants;;

public class First {
	
	static public final RecoverySet calc     = new RecoverySet();
	static public final RecoverySet vars     = new RecoverySet();	
	static public final RecoverySet sum      = new RecoverySet();
	static public final RecoverySet term     = new RecoverySet();	
	static public final RecoverySet unary    = new RecoverySet();	
	static public final RecoverySet element  = new RecoverySet();
	static public final RecoverySet statlist = new RecoverySet();
	static public final RecoverySet lista = new RecoverySet();
	
    static {
    	calc.add ( new Integer ( RubyLikeGrammarConstants.END_CMD )  );
    	calc.add ( new Integer ( RubyLikeGrammarConstants.INT_CONSTANT )  );
    	calc.add ( new Integer ( RubyLikeGrammarConstants.FLOAT )  );
    	calc.add( new Integer(RubyLikeGrammarConstants.STRING));

    	vars.add(new Integer(RubyLikeGrammarConstants.INT_CONSTANT));
    	vars.add(new Integer(RubyLikeGrammarConstants.STRING));
    	vars.add(new Integer(RubyLikeGrammarConstants.FLOAT));
    	vars.add(new Integer(RubyLikeGrammarConstants.LIST));
    	calc.addAll(vars);
    	
    	lista.addAll(vars);
    	lista.add(new Integer(RubyLikeGrammarConstants.INT_CONSTANT));
    	lista.add(new Integer(RubyLikeGrammarConstants.STRING));
    	lista.add(new Integer(RubyLikeGrammarConstants.FLOAT));
    	lista.add(new Integer(RubyLikeGrammarConstants.LIST));
    	
    	statlist.addAll(calc);
    	statlist.add(new Integer(RubyLikeGrammarConstants.EACH));
    	statlist.add(new Integer(RubyLikeGrammarConstants.IF));
    	statlist.add(new Integer(RubyLikeGrammarConstants.LIST));
    	statlist.add(new Integer(RubyLikeGrammarConstants.PRINT));
    	statlist.add(new Integer(RubyLikeGrammarConstants.ELSE));
    	
	}
}
