package br.unioeste.compiler.recovery;

import br.unioeste.compiler.rubylike.RubyLikeGrammarConstants;;

public class First {
	
	static public final RecoverySet calc     = new RecoverySet();
	static public final RecoverySet vars     = new RecoverySet();	
	static public final RecoverySet sum      = new RecoverySet();
	static public final RecoverySet term     = new RecoverySet();	
	static public final RecoverySet unary    = new RecoverySet();	
	static public final RecoverySet element  = new RecoverySet();
	static public final RecoverySet ifStmt = new RecoverySet();
	static public final RecoverySet elseStmt = new RecoverySet();
	static public final RecoverySet lista = new RecoverySet();
	static public final RecoverySet eachStmt = new RecoverySet();
	
    static {
    	calc.add ( new Integer ( RubyLikeGrammarConstants.END_CMD )  );
    	calc.add ( new Integer ( RubyLikeGrammarConstants.INT_CONSTANT )  );
    	calc.add ( new Integer ( RubyLikeGrammarConstants.FLOAT )  );
    	calc.add( new Integer(RubyLikeGrammarConstants.STRING));
    	calc.add( new Integer(RubyLikeGrammarConstants.VAR));
    	calc.add( new Integer(RubyLikeGrammarConstants.IF));
    	calc.add( new Integer(RubyLikeGrammarConstants.EACH));

    	lista.add(new Integer(RubyLikeGrammarConstants.INT_CONSTANT));
    	lista.add(new Integer(RubyLikeGrammarConstants.STRING));
    	lista.add(new Integer(RubyLikeGrammarConstants.FLOAT));
    	lista.add(new Integer(RubyLikeGrammarConstants.LIST));
    	
    	vars.add(new Integer(RubyLikeGrammarConstants.INT_CONSTANT));
    	vars.add(new Integer(RubyLikeGrammarConstants.STRING));
    	vars.add(new Integer(RubyLikeGrammarConstants.FLOAT));
    	vars.add(new Integer(RubyLikeGrammarConstants.LIST));
    	vars.addAll(lista);
    	calc.addAll(vars);
    	
    	
    	ifStmt.add(new Integer(RubyLikeGrammarConstants.IF));
    	ifStmt.add(new Integer(RubyLikeGrammarConstants.EACH));
    	ifStmt.add(new Integer(RubyLikeGrammarConstants.PRINT));
    	ifStmt.add(new Integer(RubyLikeGrammarConstants.VAR));
    	ifStmt.addAll(vars);
    	
    	elseStmt.add(new Integer(RubyLikeGrammarConstants.IF));
    	elseStmt.add(new Integer(RubyLikeGrammarConstants.EACH));
    	elseStmt.add(new Integer(RubyLikeGrammarConstants.PRINT));
    	elseStmt.add(new Integer(RubyLikeGrammarConstants.VAR));
    	elseStmt.addAll(vars);
    	
    	eachStmt.add(new Integer(RubyLikeGrammarConstants.IF));
    	eachStmt.add(new Integer(RubyLikeGrammarConstants.EACH));
    	eachStmt.add(new Integer(RubyLikeGrammarConstants.PRINT));
    	eachStmt.add(new Integer(RubyLikeGrammarConstants.VAR));
    	eachStmt.addAll(vars);
	}
}
