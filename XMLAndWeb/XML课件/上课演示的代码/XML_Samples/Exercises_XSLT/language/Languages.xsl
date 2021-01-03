<?xml version="1.0" ?>

<xsl:stylesheet
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

 <xsl:param name="Language">en</xsl:param>

 <xsl:template match="text()"/>

 <xsl:template match="Text">
  <xsl:if test="lang($Language)">
   <p><xsl:value-of select="."/>
   (<xsl:value-of select="@xml:lang"/>)</p>
  </xsl:if>
 </xsl:template>

</xsl:stylesheet>

