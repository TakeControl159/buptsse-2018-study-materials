package dom;

import java.io.File;
import javax.xml.parsers.*;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import com.sun.org.apache.xerces.internal.dom.*;

import org.w3c.dom.*;



public class domSample {
	private static Document doc;
	private static Document doc_ABC;
	private static Document doc_IBM;
	private static File file;
	private static File fileABC;
	private static File fileIBM;
	private static Element abcNode;
	private static Element ibmNode;
	
	public static void split(Node node){
		if(node == null){
			return;
		}
		int type = node.getNodeType();
		
		switch(type){
		    case Node.DOCUMENT_NODE:{
			    split(((Document)node).getDocumentElement());
			    break;
		    }
		    
		    case Node.ELEMENT_NODE:{
		    	NodeList childNodes = node.getChildNodes();
		    	int length = node.getAttributes().getLength();
		    	if(length != 0){
		    		//有属性
		    		Attr attributes[] = new Attr[length];
		    		for(int loopIndex = 0; loopIndex < length; loopIndex++){
		    			attributes[loopIndex] =(Attr)node.getAttributes().item(loopIndex);
		    			//属性有comp_name="ABC"
		    			if(attributes[loopIndex].getName().compareTo("comp_name") ==0
		    					&& attributes[loopIndex].getValue().compareTo("ABC") == 0){
		    				abcNode.appendChild(doc_ABC.importNode((Element)node, true));
		    				}
		    			
		    			//属性有comp_name="IBM"
		    			else if(attributes[loopIndex].getName().compareTo("comp_name")==0 
		    					&& attributes[loopIndex].getValue().compareTo("IBM")==0){
		    				ibmNode.appendChild(doc_IBM.importNode((Element)node, true));
		    			}
		    			else 
							continue;
		    		}
		    	}
						
		    	if (childNodes != null) {
		    	    for (int loopIndex = 0; loopIndex < childNodes.getLength(); loopIndex++ ) {
		    	       split(childNodes.item(loopIndex));
		    	    }
		    	}
		    	break;
		    }
		    case Node.COMMENT_NODE:
		    	break;
		}	
	}
	
	public static void split_ABC(Node node,Element middle){
		//Element middle=null;
    	Element newNode = null;
    	Element slibingNode = null;
    	
		if(node == null){
			return;
		}
		int type = node.getNodeType();
		switch(type){
		    
		    case Node.ELEMENT_NODE:{
		    	NodeList childNodes = node.getChildNodes();
		    	int length = node.getAttributes().getLength();
		    	if(length != 0){
		    		Attr attributes[] = new Attr[length];
		    		
		    		for(int loopIndex = 0; loopIndex < length; loopIndex++){
		    			attributes[loopIndex] = 
		    					(Attr)node.getAttributes().item(loopIndex);
		    		}
		    		
		    		for(int loopIndex = 0; loopIndex < length; loopIndex++){
		    			//属性有comp_name="ABC"
		    			if(attributes[loopIndex].getName().compareTo("comp_name") ==0
		    					&& attributes[loopIndex].getValue().compareTo("ABC") == 0){
		    				//ABC_COMP.xml中没有ABC_COMP结点
		    				if(doc_ABC.getElementsByTagName("ABC_COMP").getLength() == 0){
		    					newNode = doc_ABC.createElement("ABC_COMP");
		    					((Element)node).removeAttributeNode(attributes[loopIndex]);
		    					slibingNode = (Element)node.getNextSibling();
		    					middle.insertBefore(newNode, node);
		    					middle = newNode;
		    					middle.appendChild(node);
		    					middle.appendChild(slibingNode);
		    					childNodes = middle.getChildNodes();
		    				}
		    				//ABC_COMP.xml中有ABC_COMP结点
		    				else{
		    					((Element)node).removeAttributeNode(attributes[loopIndex]);
		    					middle =(Element) node;	
		    				}
		    			}
		    			else{
		    				newNode = doc_ABC.createElement(attributes[loopIndex].getName());
		    				((Element)node).removeAttributeNode(attributes[loopIndex]);
		    				newNode.appendChild(doc_ABC.createTextNode(attributes[loopIndex].getValue()));
		    				middle = (Element)node;
		    				middle.appendChild(newNode);
		    			}
		    		} 
		    	}
		    	else 
					middle = (Element)node;
					
		    	
		    	if (childNodes != null) {
		    	    for (int loopIndex = 0; loopIndex < childNodes.getLength(); loopIndex++ ) {
		    	       split_ABC(childNodes.item(loopIndex),middle);
		    	    }
		    	}
		    	break;
		    }
		    
		    case Node.TEXT_NODE:{
		    	break;
		    }
		}
		    
	}
	
	public static void split_IBM(Node node,Element middle){
		Element newNode = null;
		//Element middle=null;
    
		if(node == null){
			return;
		}
		int type = node.getNodeType();
		switch(type){
		    
		    case Node.ELEMENT_NODE:{
		    	NodeList childNodes = node.getChildNodes();
		    	int length = node.getAttributes().getLength();
		    	if(length != 0){
		    		Attr attributes[] = new Attr[length];
		    		
		    		for(int loopIndex = 0; loopIndex < length; loopIndex++){
		    			attributes[loopIndex] = 
		    					(Attr)node.getAttributes().item(loopIndex);
		    		}
		    		
		    		for(int loopIndex = 0; loopIndex < length; loopIndex++){
		    			//属性有comp_name="IBM"
		    			if(attributes[loopIndex].getName().compareTo("comp_name") ==0
		    					&& attributes[loopIndex].getValue().compareTo("IBM") == 0){
		    					newNode = doc_IBM.createElement("IBM_COMP");
		    					((Element)node).removeAttributeNode(attributes[loopIndex]);
		    					middle.insertBefore(newNode, node);
		    					middle = newNode;
		    					middle.appendChild(node);
		    					childNodes = middle.getChildNodes();
		    				}
		    			else{
		    				newNode = doc_IBM.createElement(attributes[loopIndex].getName());
		    				((Element)node).removeAttributeNode(attributes[loopIndex]);
		    				newNode.appendChild(doc_IBM.createTextNode(attributes[loopIndex].getValue()));
		    				middle = (Element)node;
		    				middle.appendChild(newNode);
		    			}
		    		} 
		    	}
		    	else 
					middle = (Element)node;
					
		    	if (childNodes != null) {
		    	    for (int loopIndex = 0; loopIndex < childNodes.getLength(); loopIndex++ ) {
		    	       split_IBM(childNodes.item(loopIndex),middle);
		    	    }
		    	}
		    	break;
		    }
		    
		    case Node.TEXT_NODE:{
		    	break;
		    }
		}
	}
	
	@SuppressWarnings("restriction")
	public static void main(String args[]){
		try{
			try{
				file = new File("src/ipo.xml");
				fileABC = new File("src/ABC_COMP.xml");
				fileIBM = new File("src/IBM_COMP.xml");
				
				//获取解析器工厂
				DocumentBuilderFactory factory =DocumentBuilderFactory.newInstance();
				//获取解析器
				DocumentBuilder builder_ipo = factory.newDocumentBuilder();
				//读取xml文档
				doc = builder_ipo.parse(file);
				doc_ABC = new DocumentImpl();
				doc_IBM = new DocumentImpl();
				abcNode = doc_ABC.createElement(doc.getDocumentElement().getNodeName());
				doc_ABC.appendChild(abcNode);
				ibmNode = doc_IBM.createElement(doc.getDocumentElement().getNodeName());
				doc_IBM.appendChild(ibmNode);
				split(doc);
		}
			catch(Exception e){
				e.printStackTrace(System.err);
			}
			
		    split_ABC(doc_ABC.getDocumentElement(),null);
			TransformerFactory transFactory = TransformerFactory.newInstance();
			Transformer trans = transFactory.newTransformer();
			DOMSource source1 = new DOMSource(doc_ABC);
			StreamResult result1 = new StreamResult(fileABC);
			trans.transform(source1, result1);
			split_IBM(doc_IBM.getDocumentElement(),null);
			DOMSource source2 = new DOMSource(doc_IBM);
			StreamResult result2 = new StreamResult(fileIBM);
			trans.transform(source2, result2);
			System.out.println("done");
		}
		
		catch(TransformerException exc1){
			exc1.printStackTrace();
		}
	}
	
}