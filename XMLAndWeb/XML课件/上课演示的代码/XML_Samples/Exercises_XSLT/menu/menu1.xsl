<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <HTML><BODY>
    <TABLE border="2" bgcolor="green">
      <TR><TH>The Item</TH>
          <TH>Price</TH>
      </TR>
      <xsl:for-each select="MENU/SECTION/ITEM">
      <TR><TD><xsl:value-of select="NAME"/></TD>
          <TD><xsl:value-of select="NAME"/></TD>
      </TR>
      </xsl:for-each>
    </TABLE>
  </BODY></HTML>
</xsl:template>
</xsl:stylesheet>
