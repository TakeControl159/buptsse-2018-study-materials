package xmljdbc;

import java.io.*;
import java.util.Properties;
import javax.xml.transform.OutputKeys;
import org.apache.xalan.lib.sql.ConnectionPoolManager;
import org.apache.xalan.lib.sql.DefaultConnectionPool;
import org.apache.xpath.XPathAPI;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.stream.StreamSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.dom.DOMSource;
import org.apache.xml.serializer.WriterToUTF8;


public class Sample1 {
  public Sample1() {
  }

  public static void main(String[] args) throws Exception{
    //初始化一个连接池管理器
    ConnectionPoolManager cpMng=new ConnectionPoolManager();
    //构造一个默认的连接池
    DefaultConnectionPool cp = new DefaultConnectionPool();
    //将数据库的jdbc驱动程序填入连接池，此处用mysql的jdbc驱动
    cp.setDriver("org.gjt.mm.mysql.Driver");
    //将数据库的url填入连接池
    cp.setURL("jdbc:mysql://localhost/sppix");
    //将数据库的连接用户名填入连接池
    cp.setUser("root");
    //将数据库的连接密码填入连接池
    cp.setPassword("chenchen");
    //设置连接池
    cp.setMinConnections(10);
    //设置连接池的开启状态
    cp.setPoolEnabled(true);
    //注册连接池到连接池管理器
    cpMng.registerPool("sppixpool",cp);

    //用xml工具解析XSL文件
    javax.xml.parsers.DocumentBuilderFactory dbf=javax.xml.parsers.DocumentBuilderFactory.newInstance();
    javax.xml.parsers.DocumentBuilder db=dbf.newDocumentBuilder();
    org.w3c.dom.Document doc=db.parse(Sample1.class.getResource("sample1.xsl").openStream());
    //通过XPATH将XSL文件中的路径为/stylesheet/param[@name="query"]的节点的值替换为sql查询语句
    org.w3c.dom.Node node=XPathAPI.selectSingleNode(doc.getDocumentElement(),"/stylesheet/param[@name=\"query\"]");
    ((org.w3c.dom.Element)node).setAttribute("select","'select * from cat'");

    //创建一个transformer
    TransformerFactory tFactory = TransformerFactory.newInstance();

    DOMSource doms = new DOMSource (doc);


    Transformer transformer = tFactory.newTransformer();

    StringReader reader =
              new StringReader("<?xml version=\"1.0\"?> <doc/>");
    StringWriter writer=new StringWriter();
    //输出修改后的xsl数据流到StringWriter
    transformer.transform(doms,new StreamResult(writer));

    //根据xsl数据流生成整合了数据库查询结果的xml文档
    Transformer transformer1 = tFactory.newTransformer(
        new StreamSource(new StringReader(writer.toString())));
    //获取Transformser对象的输出属性,亦即XSLT引擎的缺省输出属性,这是一个
    //java.util.Properties对象。
    Properties properties = transformer1.getOutputProperties();

    //设置新的输出属性:输出字符编码为GB2312,这样可以支持中文字符,XSLT引擎所输出
    //的XML文档如果包含了中文字符,可以正常显示,不会出现所谓的"汉字问题"。
    //请留意OutputKeys类的字符串常数OutputKeys.ENCODING。
    properties.setProperty(OutputKeys.ENCODING,"UTF-8");
    properties.setProperty(OutputKeys.METHOD,"xml");

    //更新XSLT引擎的输出属性。
    transformer1.setOutputProperties(properties);


    transformer1.transform(new StreamSource(reader),
        new StreamResult(new FileOutputStream("result1.xml")));


  }

}
