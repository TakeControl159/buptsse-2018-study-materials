<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Juicers</TITLE>
            </HEAD>
            <BODY>
                <TABLE BORDER="1" WIDTH="50%">
                    <TR>
                        <TH>Juicers</TH>
                    </TR>
                    <xsl:for-each select="/juicers/juicer">
                        <TR>
                            <TD><xsl:value-of select="name"/></TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>