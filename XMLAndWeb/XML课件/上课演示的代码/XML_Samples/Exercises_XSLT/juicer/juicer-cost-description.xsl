<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
 
    <xsl:output method="html"/>

    <xsl:template match="/">
        <HTML>
            <HEAD>
                <TITLE>Juicer Name/Cost and Name/Description</TITLE>
            </HEAD>
            <BODY>
                <TABLE BORDER="1" WIDTH="50%">
                    <TR>
                        <TH>Juicer</TH><TH>Cost</TH>
                    </TR>
                    <xsl:for-each select="/juicers/juicer">
                        <TR>
                            <TD><xsl:value-of select="name"/></TD>
                            <TD>
                                <xsl:text>$</xsl:text>
                                <xsl:value-of select="cost[@currency='USD']"/>
                            </TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
                <br/><br/><br/><br/><br/><br/><br/>
                <TABLE BORDER="1" WIDTH="100%">
                    <TR>
                        <TH>Juicer</TH><TH>Description</TH>
                    </TR>
                    <xsl:for-each select="/juicers/juicer">
                        <TR>
                            <TD><xsl:value-of select="name"/></TD>
                            <TD><xsl:value-of select="description"/></TD>
                        </TR>
                    </xsl:for-each>
                </TABLE>
            </BODY>
        </HTML>
    </xsl:template>

</xsl:stylesheet>