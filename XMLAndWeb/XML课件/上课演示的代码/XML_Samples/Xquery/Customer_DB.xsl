<xsl:stylesheet 
 version="1.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform" >
 
<xsl:template match="/">
 <html>
  <head>
   <title>Database Test</title>
  </head>
  <body>
   <h3>DB XSLT debug.</h3>
   <!--<xsl:apply-templates select="/Import/Row/CustomerID" />-->
   <xsl:apply-templates />
  </body>
 </html> 
</xsl:template>

<xsl:template match="/Import/Row">
 <xsl:for-each select="following::*">
  <p><xsl:value-of select="name(.)" /> which contains the text "<xsl:value-of select='.' />".</p>
 </xsl:for-each>
</xsl:template>

</xsl:stylesheet>