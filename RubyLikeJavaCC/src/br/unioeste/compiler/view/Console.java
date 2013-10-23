package br.unioeste.compiler.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class Console extends JPanel{

	private static final long serialVersionUID = 1L;
	private JTextArea area;
	private JScrollPane scroll;
	
	public Console(Dimension dimension){
		setSize(dimension.width - 100, dimension.height - 200);
		setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.BLACK), "Console:"));
		
		initTextArea();
	}
	
	public void initTextArea(){
		area = new JTextArea(15, 52);
		area.setEditable(false);
		scroll = new JScrollPane(area);
		
		add(scroll, BorderLayout.CENTER);
	}
	
	public JTextArea getConsoleTextArea(){
		return area;
	}
}
