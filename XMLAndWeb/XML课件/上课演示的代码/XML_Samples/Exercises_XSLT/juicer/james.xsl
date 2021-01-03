<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="xml"/>

    <xsl:template match="/">
      <root>
          <xsl:for-each select="//book_start">
              <book>
                  <details>
                      <xsl:apply-templates select="following-sibling::*[1]/details/*[1]"/>
                  </details>
              </book>
          </xsl:for-each>
      </root>
    </xsl:template>

    <xsl:template match="*">
      <xsl:if test="name(.) != 'book_end'">
            <xsl:element name="{name(.)}">
                <xsl:value-of select="."/>
            </xsl:element>
            <xsl:apply-templates select="following-sibling::*[1]"/>
      </xsl:if>
    </xsl:template>

</xsl:stylesheet>