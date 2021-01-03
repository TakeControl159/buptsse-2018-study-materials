
package buptsse;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlType;

/**
 * <p>
 * Java class for AddString complex type.
 * 
 * <p>
 * The following schema fragment specifies the expected content contained within
 * this class.
 * 
 * <pre>
 * &lt;complexType name="AddString">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="str1" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *         &lt;element name="str2" type="{http://www.w3.org/2001/XMLSchema}string" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "AddString", propOrder = { "str1", "str2" })
public class AddString {

	protected String str1;
	protected String str2;

	/**
	 * Gets the value of the str1 property.
	 * 
	 * @return possible object is {@link String }
	 * 
	 */
	public String getStr1() {
		return str1;
	}

	/**
	 * Sets the value of the str1 property.
	 * 
	 * @param value allowed object is {@link String }
	 * 
	 */
	public void setStr1(String value) {
		this.str1 = value;
	}

	/**
	 * Gets the value of the str2 property.
	 * 
	 * @return possible object is {@link String }
	 * 
	 */
	public String getStr2() {
		return str2;
	}

	/**
	 * Sets the value of the str2 property.
	 * 
	 * @param value allowed object is {@link String }
	 * 
	 */
	public void setStr2(String value) {
		this.str2 = value;
	}

}
