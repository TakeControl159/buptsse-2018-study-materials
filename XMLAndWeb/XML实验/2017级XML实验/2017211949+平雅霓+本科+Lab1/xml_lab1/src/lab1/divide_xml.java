package lab1;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.w3c.dom.Node;

public class divide_xml {

	static String displayText[] = new String[1500];
	static int numberLines = 0;
	static FileOutputStream outputStream_IBM = null;
	static FileOutputStream outputStream_ABC = null;

	public static void main(String[] args) {
		try {
			// 创建一个DocumentBuilderFactory
			DocumentBuilderFactory factory =
					DocumentBuilderFactory.newInstance();

			DocumentBuilder builder = null;
			try {
				//使用DocumentBuilderFactory得到一个DocumentBuilder对象
				builder = factory.newDocumentBuilder();
			}
			catch (ParserConfigurationException e) {}

			Document document = null;

			//使用DocumentBuilder对象解析xml文件，得到一个Document对象
			document = builder.parse("src/lab1/ipo.xml");

			//在同级目录创建ABC_COMP.xml文件
			File file_ABC = new File("src/lab1/ABC_COMP.xml");
			file_ABC.createNewFile();
			outputStream_ABC = new FileOutputStream(file_ABC);

			//在同级目录创建IBM_COMP.xml文件
			File file_IBM = new File("src/lab1/IBM_COMP.xml");
			file_IBM.createNewFile();
			outputStream_IBM = new FileOutputStream(file_IBM);
			
			//将XML文件的第一行输出到文件中
			String data_ABC = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"+"\n"
					+"<purchaseOrders>"+"\n"+"<ABC_COMP>"+"\n";
			String data_IBM = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"+"\n"
					+"<purchaseOrders>"+"\n"+"<IBM_COMP>"+"\n";
			outputStream_ABC.write(data_ABC.getBytes());
			outputStream_IBM.write(data_IBM.getBytes());

			//递归调用
			childLoop(document, "","");

			//将XML文件的结束部分输出到文件中
			data_ABC ="</ABC_COMP>\n" + "</purchaseOrders>";
			data_IBM = "</IBM_COMP>\r\n" + "</purchaseOrders>";
			outputStream_ABC.write(data_ABC.getBytes());
			outputStream_IBM.write(data_IBM.getBytes());

			//关闭文件输出流
			outputStream_ABC.close();
			outputStream_IBM.close();
			
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}      	
		
		System.out.println("Done!");
	}
	
	
	//向文件输出内容的函数
	public static void outputstream(String type,String data) throws IOException {
		
		//type判断是向ABC_COMP文件输出还是IBM_COMP文件输出
		if(type.equals("ABC")) {
			outputStream_ABC.write(data.getBytes());
			outputStream_ABC.write("\n".getBytes());
		}
		else if(type.equals("IBM")) {
			outputStream_IBM.write(data.getBytes());
			outputStream_IBM.write("\n".getBytes());
		}
	}

	//递归遍历子节点
	public static void childLoop(Node node, String indentation,String outputtype) throws IOException
	{
		if (node == null) {
			return;
		}

		int type = node.getNodeType();

		switch (type) {
		case Node.DOCUMENT_NODE: {
			NodeList rootList = (NodeList) node.getChildNodes(); 
			for(int i=0;i<rootList.getLength();i++)
				if(rootList.item(i).getNodeName()=="purchaseOrders") {
					//root为<purchaseOrders>根元素
					Node root = rootList.item(i);
					//获得<purchaseOrders>的所有子元素
					NodeList purchaseList = (NodeList) root.getChildNodes(); 
					//找出<purchaseOrders>的所有<purchaseOrder>子元素
					for(int j=0;j<purchaseList.getLength();j++) {
						if(purchaseList.item(j).getNodeName().equals("purchaseOrder")){ 
							//获得purchaseOrder的属性
							Attr attr =(Attr)purchaseList.item(j).getAttributes().item(0);
							//若purchaseOrder的属性值为ABC则传递参数“ABC”将文件写入ABC_COMP.xml文件
							if(attr.getNodeValue().equals("ABC")) {
								outputStream_ABC.write(new String("<purchaseOrder>\n").getBytes());
								NodeList childList = (NodeList)purchaseList.item(j).getChildNodes(); 	
								for(int k=0;k<childList.getLength();k++)
									childLoop(childList.item(k), "    ","ABC");
								outputStream_ABC.write(new String("</purchaseOrder>\n").getBytes());
							}
							//若purchaseOrder的属性值为IBM则则传递参数“IBM”将文件写入IBM_COMP.xml文件
							else if(attr.getNodeValue().equals("IBM")) {
								outputStream_IBM.write(new String("<purchaseOrder>\n").getBytes());
								NodeList childList = (NodeList) purchaseList.item(j).getChildNodes(); 	
								for(int k=0;k<childList.getLength();k++)
									childLoop(childList.item(k), "    ","IBM");
								outputStream_IBM.write(new String("</purchaseOrder>\n").getBytes());
							}
						}
					}
				}
			break;
		}

		case Node.ELEMENT_NODE: {
			//输出此元素
			displayText[numberLines] = indentation;
			displayText[numberLines] += "<";
			displayText[numberLines] += node.getNodeName();
			displayText[numberLines] += ">";
			//如果该元素含有子元素，则将起始标签输入到文件中，独占一行
			//若不包含子元素，则起始标签、内容、终止标签在同一行，直到出现终止标签时再写入文件
			if(node.getChildNodes().getLength()!=1)
				outputstream(outputtype, displayText[numberLines]);
			
			int length = (node.getAttributes() != null) ?
					node.getAttributes().getLength() : 0;
					
					//获得所有属性
					Attr attributes[] = new Attr[length];
					for (int loopIndex = 0; loopIndex < length; loopIndex++) {
						attributes[loopIndex] =
								(Attr)node.getAttributes().item(loopIndex);
					}
					
					//将属性转变为元素输出
					for (int loopIndex = 0; loopIndex < attributes.length;
							loopIndex++) {
						numberLines++;
						Attr attribute = attributes[loopIndex];
						displayText[numberLines] =  "    ";
						displayText[numberLines] += indentation;
						displayText[numberLines] += "<";
						displayText[numberLines] += attribute.getNodeName();
						displayText[numberLines] += ">";				
						displayText[numberLines] += attribute.getNodeValue();
						displayText[numberLines] += "</";
						displayText[numberLines] += attribute.getNodeName();
						displayText[numberLines] += ">";
						outputstream(outputtype, displayText[numberLines]);
					}
					
					//如果该元素拥有子元素，则行数+1，子元素写入文件的下一行
					if(node.getChildNodes().getLength()!=1)
						numberLines++;
					NodeList childNodes = node.getChildNodes();
					if (childNodes != null) {
						length = childNodes.getLength();						
						indentation += "    ";
						for (int loopIndex = 0; loopIndex < length; loopIndex++ ) {
							childLoop(childNodes.item(loopIndex), indentation,outputtype);
						}
					}
					break;
		}

		case Node.TEXT_NODE: {
			String trimmedText = node.getNodeValue().trim();
			if(trimmedText.indexOf("\n") < 0 && trimmedText.length() > 0){
				displayText[numberLines] += trimmedText;
			}
			break;
		}


		case Node.CDATA_SECTION_NODE: {
			displayText[numberLines] = indentation;
			displayText[numberLines] += "<![CDATA[";
			displayText[numberLines] += node.getNodeValue();
			displayText[numberLines] += "]]>";
			outputstream(outputtype, displayText[numberLines]);
			numberLines++;
			break;
		}
		}

		if (type == Node.ELEMENT_NODE) {
			//如果该元素没有子元素，则整个元素在终止标签后将其写入到文件中
			if(node.getChildNodes().getLength()==1) {
				displayText[numberLines] += "</";
				displayText[numberLines] += node.getNodeName();
				displayText[numberLines] += ">";
				outputstream(outputtype, displayText[numberLines]);
				numberLines++;
				indentation += "    ";
			}
			//如果该元素有子元素，终止标签在文件中独占一行
			else {
				displayText[numberLines] = indentation.substring(0,
						indentation.length() - 4);
				displayText[numberLines] += "</";
				displayText[numberLines] += node.getNodeName();
				displayText[numberLines] += ">";
				outputstream(outputtype, displayText[numberLines]);
				numberLines++;
				indentation += "    ";
			}		
		}
	}

}
