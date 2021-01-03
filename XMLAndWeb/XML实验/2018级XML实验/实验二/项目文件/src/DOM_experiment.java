import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;

// 这个代码不能把属性也变成标签元素。。
public class DOM_experiment {
    public static void main(String[] args) {
        try{
            // 创建文档构建器工厂
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();

            // 为ipo.xml构建文件解析器
            Document ipo_doc = builder.parse("ipo.xml");
            NodeList purchaseOrderList = ipo_doc.getElementsByTagName("purchaseOrder");
            // 创建元素
            Element ABC_COMP = ipo_doc.createElement("ABC_COMP");
            Element IBM_COMP = ipo_doc.createElement("IBM_COMP");

            for (int i = 0; i < purchaseOrderList.getLength(); i++) {
                Node purchaseOrderNode = purchaseOrderList.item(i);

                // 如果<purchaseOrder>第一个属性的值为"ABC"
                if (purchaseOrderNode.getAttributes().item(0 ).getNodeValue().equals("ABC")){
                   childLoop(purchaseOrderNode, ipo_doc, ABC_COMP);
                }
                // 如果<purchaseOrder>第一个属性的值为"IBM"
                else if (purchaseOrderNode.getAttributes().item(0 ).getNodeValue().equals("IBM")){
                    childLoop(purchaseOrderNode, ipo_doc, IBM_COMP);
                }
            }

            Element ABC_purchaseOrders = ipo_doc.createElement("purchaseOrders");
            ABC_purchaseOrders.appendChild(ABC_COMP);

            Element IBM_purchaseOrders = ipo_doc.createElement("purchaseOrders");
            IBM_purchaseOrders.appendChild(IBM_COMP);

            // 将获取的信息存放到对应的文件中
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            transformer.transform(new DOMSource(ABC_purchaseOrders), new StreamResult(new File("ABC_COMP.xml")));
            transformer.transform(new DOMSource(IBM_purchaseOrders), new StreamResult(new File("IBM_COMP.xml")));

            // 输出后的文件在格式化后更容易观察, 在IDEA中按下ctrl+alt+l 使.xml文件格式化显示

        }catch(Exception e){
            System.out.println(e);
        }
    }

    public static void childLoop(Node purchaseOrderNode, Document ipo_doc, Element comp_name){
        // 创建一个ABC_purchaseOrder 用于存放purchaseOrder所有的子节点
        Element ABC_purchaseOrder = ipo_doc.createElement("purchaseOrder");
        Element text = ipo_doc.createElement("test");

        // 创建一个purchaseOrder子节点的指针
        Node nextElement = purchaseOrderNode.getFirstChild().getNextSibling();
        Node nextText = purchaseOrderNode.getFirstChild();

        while(nextElement != null){
            // 将purchaseOrder子节点 放入到ABC_purchaseOrder中
            ABC_purchaseOrder.appendChild(nextElement);
            text.appendChild(nextText);

            // 取下一个purchaseOrder的子节点
            nextElement = purchaseOrderNode.getFirstChild().getNextSibling();
            nextText = purchaseOrderNode.getFirstChild();
        }
        // 将ABC_purchaseOrder放入
        comp_name.appendChild(ABC_purchaseOrder);
    }
}
