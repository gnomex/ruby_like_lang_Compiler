package br.unioeste.compiler.recovery;

import java.util.*;
import br.unioeste.compiler.rubylike.*;

public class RecoverySet extends HashSet<Integer> {
	private static final long serialVersionUID = 1L;

	/// Cria um conjunto vazio
	public RecoverySet () {
		super();
	}
	
	/// Cria o conjunto com um tipo de token
	public RecoverySet ( int t ) {
		this.add( new Integer( t ) );
	}
	
	/// Verifica se o token pertence ao conjunto
	public boolean contains ( int t ) {
		return super.contains( new Integer ( t ));		
	}
	
	/// Faz a uni�o de dois conjuntos
	public RecoverySet union ( RecoverySet s) {
		RecoverySet t=null;
		if (s!=null) { // Se s==null retorna null
			t = (RecoverySet)this.clone();
			t.addAll( s );			
		}
		return t;	/// Retorna um terceiro conjunto sem destruir nenhum
	}
	
	/// Retira um elemento do conjunto
	public RecoverySet remove ( int n ) {
		RecoverySet t = (RecoverySet)this.clone();
		t.remove( new Integer(n ) );
		return t; // retorna um novo conjunto sem um dos elementos
	}
	
	/// Cria uma string descrevendo os tokens que pertecem ao conjunto
	public String toString () {
		Iterator<Integer> it = this.iterator();
		String s = "";
		int k;
		while ( it.hasNext() ) {
			k = ((Integer)it.next()).intValue();
			s += RubyLikeGrammar.im(k) + " ";
		}
		return s;
	}
	
}
