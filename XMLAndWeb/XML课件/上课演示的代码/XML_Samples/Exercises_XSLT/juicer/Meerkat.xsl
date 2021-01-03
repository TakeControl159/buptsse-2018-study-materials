<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
      <HTML>
        <BODY>
           <xsl:variable name="Meerkat" select="document('
http://www.oreillynet.com/meerkat/?_fl=xml&amp;s=REST')"/>
           <TABLE border="1" width="75%">
               <TR>
                    <TH>Title</TH>
                    <TH>Description</TH>
               </TR>
               <xsl:for-each select="$Meerkat/meerkat/story">
                   <TR>
                        <TD><xsl:value-of select="title"/></TD>
                        <TD><xsl:value-of select="description"/></TD>
                   </TR>
               </xsl:for-each>
           </TABLE>
        </BODY>
      </HTML>
    </xsl:template>

</xsl:stylesheet>