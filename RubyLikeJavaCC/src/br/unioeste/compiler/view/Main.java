package br.unioeste.compiler.view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.InputStream;

import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JTextArea;
import javax.swing.KeyStroke;

import br.unioeste.compiler.rubylike.RubyLikeGrammar;

public class Main extends JFrame{

	private static final long serialVersionUID = 1L;
	private JMenuBar menuBar;
	private JMenu menuBuild;
	private JMenuItem itemCompiler;
	private JMenuItem itemClose;
	
	private Editor editor;
	private Console console;
	
	private RubyLikeGrammar ruby;
	
	public Main(){
		super("Ruby Like");
		
		setSize(new Dimension(600, 580));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		
		initMenu();
		
		editor = new Editor(getSize());
		add(editor, BorderLayout.NORTH);
		
		console = new Console(getSize());
		add(console, BorderLayout.SOUTH);
	}
	
	public void initMenu(){
		menuBar = new JMenuBar();
		
		menuBuild = new JMenu("Build");
		menuBar.add(menuBuild);
		
		itemCompiler = new JMenuItem("Compilar");
		itemCompiler.setAccelerator(KeyStroke.getKeyStroke("control C"));
		itemCompiler.setMnemonic(KeyEvent.VK_C);
		itemCompiler.addActionListener(new Compiler());
		
		menuBuild.add(itemCompiler);
		menuBuild.addSeparator();
		
		itemClose = new JMenuItem("Close");
		itemClose.setAccelerator(KeyStroke.getKeyStroke("control X"));
		itemClose.setMnemonic(KeyEvent.VK_S);
		itemClose.addActionListener(new CloseRubyLike());
		
		menuBuild.add(itemClose);
		
		setJMenuBar(menuBar);
	}
	
	public static void main(String[] args) {
		Main main = new Main();
		main.setVisible(true);
	}

	private class CloseRubyLike implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			System.exit(0);
			
		}
		
	}
	
	private class Compiler implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
			ruby = new RubyLikeGrammar(text2imputStream(editor.getEditorTextArea()));
			console.getConsoleTextArea().setText("");
			ruby.compilar(true, true, console.getConsoleTextArea());
		}
		
	}
	public InputStream text2imputStream ( final JTextArea ta ) { 
		return new InputStream()
		{ 
			String s = ta.getText();  
			int inPtr=0;
			@Override
			public int read()  //minimum implementation of an InputStream
			{ 
				if( inPtr >= s.length() ) 
					return -1;
				else { 
					inPtr++; 
					return s.charAt(inPtr-1); 
				}
			}//read
		};//InputStream
	}//text2imputStream
}
