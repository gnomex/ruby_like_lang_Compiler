package br.unioeste.compiler.recovery;

import br.unioeste.compiler.rubylike.RubyLikeGrammarConstants;;

public class First {
	
	static public final RecoverySet calc     = new RecoverySet();
	static public final RecoverySet vars     = new RecoverySet();	
	static public final RecoverySet sum      = new RecoverySet();
	static public final RecoverySet term     = new RecoverySet();	
	static public final RecoverySet unary    = new RecoverySet();	
	static public final RecoverySet element  = new RecoverySet();
	
    static {
    	calc.add ( new Integer ( RubyLikeGrammarConstants.END_CMD )  );
    	//calc.add ( new Integer ( CalculatorConstants.VAR )  );
    	//calc.add ( new Integer ( CalculatorConstants.NUMBER )  );
    	//calc.add ( new Integer ( CalculatorConstants.INTEGER )  );

	}
}
