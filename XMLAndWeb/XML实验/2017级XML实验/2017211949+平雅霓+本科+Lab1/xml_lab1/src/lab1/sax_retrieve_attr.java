package lab1;

import java.io.*;
import org.xml.sax.*;
import javax.xml.parsers.*;
import org.xml.sax.helpers.DefaultHandler;

public class sax_retrieve_attr extends DefaultHandler {
	static int numberLines = 0;
	static String indentation = "";
	static String displayText[] = new String[1000];

	static boolean displayBoolean;

	public static void main(String args[]) {
		sax_retrieve_attr obj = new sax_retrieve_attr();
		
		obj.childLoop("src/lab1/ipo.xml");

		for (int index = 0; index < numberLines; index++) {
			System.out.println(displayText[index]);
		}
	}

	public void childLoop(String uri) {
		DefaultHandler saxHandler = this;
		SAXParserFactory saxFactory = SAXParserFactory.newInstance();
		try {
			SAXParser saxParser = saxFactory.newSAXParser();
			saxParser.parse(new File(uri), saxHandler);
		} catch (Throwable t) {
		}
	}

	public void startDocument() {
	}

	public void processingInstruction(String target, String data) {
	}

	public void startElement(String uri, String localName,
		String qualifiedName, Attributes attributes) {		
		displayBoolean = true;		
		if (displayBoolean) {			
			if (attributes.getLength() != 0) {
				displayText[numberLines] = "";
				displayText[numberLines] += '<';
				displayText[numberLines] += qualifiedName;
				int numberAttributes = attributes.getLength();
				for (int loopIndex = 0; loopIndex < numberAttributes; loopIndex++) {
					displayText[numberLines] += ' ';
					displayText[numberLines] += attributes.getQName(loopIndex);
					displayText[numberLines] += "=\"";
					displayText[numberLines] += attributes.getValue(loopIndex);
					displayText[numberLines] += '"';
				}
				displayText[numberLines] += '>';
				numberLines++;
			}			
		}
	}

	public void characters(char characters[], int start, int length) {
	}

	public void endElement(String uri, String localName, String qualifiedName) {
	}

	public void warning(SAXParseException exception) {
		System.err.println("Warning: " + exception.getMessage());
	}

	public void error(SAXParseException exception) {
		System.err.println("Error: " + exception.getMessage());
	}

	public void fatalError(SAXParseException exception) {
		System.err.println("Fatal error: " + exception.getMessage());
	}
}
