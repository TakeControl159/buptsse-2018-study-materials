<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Fitness Center</TITLE>
            </HEAD>
            <BODY>
                Member Names:
                <TABLE border="1" width="25%">
                    <xsl:for-each select="/FitnessCenter/Member">
                        <TR>
                            <xsl:if test="position() mod 2 = 0">
                                <xsl:attribute name="bgcolor">yellow</xsl:attribute>
                            </xsl:if> 
                            <TD><xsl:value-of select="Name"/></TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>